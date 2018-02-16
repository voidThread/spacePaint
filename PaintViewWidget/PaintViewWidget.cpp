#include "PaintViewWidget.h"

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QMatrix>
#include <QApplication>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QDebug>

PaintViewWidget::PaintViewWidget(QWidget *parent)
    : QGraphicsView(parent)
{
    CreatePaintToolChangedMapping();
    CreateMouseDownPaintToolMapping();
    CreateMouseUpPaintToolMapping();

    this->setScene(&scene);

    connect(this, &PaintViewWidget::CanvasCreated,
            this, &PaintViewWidget::OnCanvasCreated);
}

void PaintViewWidget::wheelEvent(QWheelEvent *event)
{
    /*
     * Mouse wheel handler.
     */

    // Handle zoom-in / zoom-out
    if (event->delta() > 0)
    {
        ZoomIn();
    }
    else
    {
        ZoomOut();
    }
}

void PaintViewWidget::mousePressEvent(QMouseEvent *event)
{
    if (paintTool != PaintTool::NN && event->button() == Qt::LeftButton)
    {
        CallMouseEventHandler(paintTool, PaintToolMouseDownMappings, event);
    }
}

void PaintViewWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (paintTool != PaintTool::NN && event->button() == Qt::LeftButton)
    {
        CallMouseEventHandler(paintTool, PaintToolMouseUpMappings, event);
    }
}

void PaintViewWidget::CallMouseEventHandler(PaintTool tool, MouseEventHandlerMap & handlerMap, QMouseEvent *event)
{
    auto TargetHandlerMethod = handlerMap.find(tool);

    if (TargetHandlerMethod == handlerMap.end() || !(*TargetHandlerMethod))
    {
        qDebug() << "CallMouseEventHandler: no handler found for selected paint tool (" <<
                    static_cast<unsigned>(tool) << ")";
        return;
    }

    (*TargetHandlerMethod)(event);
}

void PaintViewWidget::PaintToolChangeEventHandler(PaintTool tool)
{
    if (tool == PaintTool::NN)
    {
        qDebug() << "Unknown paint tool (" << static_cast<unsigned>(tool) << ")";
        return;
    }

    auto TargetHandlerMethod = PaintToolChangeMappings.find(tool);

    if (TargetHandlerMethod == PaintToolChangeMappings.end() || !(*TargetHandlerMethod))
    {
        qDebug() << "PaintToolChangeEventHandler: no handler found for selected paint tool (" <<
                    static_cast<unsigned>(tool) << ")";
        return;
    }

    (*TargetHandlerMethod)();
}

void PaintViewWidget::RenderToPainter(QPainter & painter)
{
    /*
     * Render the contents into QPainter instance.
     */
}

void PaintViewWidget::LoadImage(QImage & image)
{
    /*
     * Load raster image from QImage instance.
     */

    pixmapToLoad = QPixmap::fromImage(image);

    CreateNewCanvas(image.width(), image.height());
}

void PaintViewWidget::LoadImage(QString filename)
{
    /*
     * Load raster image from hard drive.
     */

    pixmapToLoad = QPixmap(filename);

    CreateNewCanvas(pixmapToLoad.width(), pixmapToLoad.height());
}

void PaintViewWidget::ChangePaintTool(PaintTool tool)
{
    /*
     * (SLOT) Change the current paint tool selected to use.
     */

    paintTool = tool;
    PaintToolChangeEventHandler(tool);

    emit PaintToolChanged(tool);
}

void PaintViewWidget::ChangeColor(QColor color)
{
    /*
     * (SLOT) Change the current selected color. Used by some painting tools
     * like pen, flood fill and so on.
     */

    emit ColorChanged(color);
}

void PaintViewWidget::CreateNewCanvas(unsigned width, unsigned height)
{
    /*
     * (SLOT) Clear the current canvas and create new.
     * \param width Width of the canvas in pixels.
     * \param height Height of the canvas in pixels.
     */

    canvasWidth = width;
    canvasHeight = height;

    emit CanvasCreated();
}

void PaintViewWidget::ZoomIn()
{
    /*
     * (SLOT) Incrase current zoom.
     */

    SetZoomLevel(zoomLevel + zoomStep);
}

void PaintViewWidget::ZoomOut()
{
    /*
     * (SLOT) Decrase current zoom.
     */

    SetZoomLevel(zoomLevel - zoomStep);
}

void PaintViewWidget::ZoomReset()
{
    /*
     * (SLOT) Reset zoom to 100%.
     */

    zoomLevel = 1.0;
    this->resetTransform();

    emit ZoomChanged(zoomLevel);
}

double PaintViewWidget::GetZoom() const
{
    /*
     * Get current zoom level.
     * 1.0 = 100%
     */

    return zoomLevel;
}

void PaintViewWidget::FitInView()
{
    /*
     * (SLOT) Fit the image inside client area of paint widget.
     * Will recalculate the current zoom level.
     */

    this->fitInView(this->sceneRect(), Qt::KeepAspectRatio);

    // process the events - the scrollbar will goes to state `hidden`.
    QApplication::processEvents();

    // fit in view again - the scrollbars are invisible now
    this->fitInView(this->sceneRect(), Qt::KeepAspectRatio);

    // recalculate zoom level
    QMatrix currentMatrix = this->matrix();
    zoomLevel = currentMatrix.m11();

    emit ZoomChanged(zoomLevel);
}

unsigned PaintViewWidget::CanvasWidth() const
{
    return canvasWidth;
}

unsigned PaintViewWidget::CanvasHeight() const
{
    return canvasHeight;
}

PaintTool PaintViewWidget::SelectedPaintTool() const
{
    /*
     * Get the current selected paint tool.
     */

    return paintTool;
}

void PaintViewWidget::OnCanvasCreated()
{
    /*
     * (SLOT) New canvas has been created.
     */

    if (pixmapToLoad.isNull() == false)
    {
        backgroundItem = scene.addPixmap(pixmapToLoad);
        pixmapToLoad = QPixmap();

        ZoomReset();

        emit ImageLoaded();
    }
}

void PaintViewWidget::SetZoomLevel(double zoom)
{
    double delta = zoom - zoomLevel;

    this->zoomLevel = zoom;
    this->scale(1.0 + delta, 1.0 + delta);

    emit ZoomChanged(zoomLevel);
}

void PaintViewWidget::CreatePaintToolChangedMapping()
{
    /*
     * Bind handler methods for each paint tool.
     * Specific handler will be called when paint tool is switched.
     */

    PaintToolChangeMappings.insert(PaintTool::Hand,
                                   std::bind(&PaintViewWidget::HandToolChangeEvent, this));
}

void PaintViewWidget::CreateMouseDownPaintToolMapping()
{
    /*
     * Bind handler methods for each paint tool.
     * Specific handler will be called when left mouse button has been pressed.
     */

    PaintToolMouseDownMappings.insert(PaintTool::Hand,
                                      std::bind(&PaintViewWidget::HandToolMouseDownEvent,
                                                this,
                                                std::placeholders::_1));
}

void PaintViewWidget::CreateMouseUpPaintToolMapping()
{
    /*
     * Bind handler methods for each paint tool.
     * Specific handler will be called when left mouse button has been released.
     */

    PaintToolMouseUpMappings.insert(PaintTool::Hand,
                                    std::bind(&PaintViewWidget::HandToolMouseUpEvent,
                                              this,
                                              std::placeholders::_1));
}

/* Paint tool change event handlers */
void PaintViewWidget::HandToolChangeEvent()
{

}

/* Mouse down event handlers for paint tools */
void PaintViewWidget::HandToolMouseDownEvent(QMouseEvent * event)
{

}

/* Mouse up event handlers for paint tools */
void PaintViewWidget::HandToolMouseUpEvent(QMouseEvent * event)
{

}
