#include "PaintViewWidget.h"

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QMatrix>
#include <QApplication>
#include <QWheelEvent>
#include <QDebug>

PaintViewWidget::PaintViewWidget(QWidget *parent)
    : QGraphicsView(parent)
{
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
