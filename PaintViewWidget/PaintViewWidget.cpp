#include "PaintViewWidget.h"

#include <QGraphicsScene>
#include <QDebug>

PaintViewWidget::PaintViewWidget(QWidget *parent)
    : QGraphicsView(parent)
{
    this->setScene(&scene);

    connect(this, &PaintViewWidget::CanvasCreated,
            this, &PaintViewWidget::OnCanvasCreated);
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

    SetZoomLevel(zoomLevel + 0.05);
}

void PaintViewWidget::ZoomOut()
{
    /*
     * (SLOT) Decrase current zoom.
     */

    SetZoomLevel(zoomLevel - 0.05);
}

void PaintViewWidget::ZoomReset()
{
    /*
     * (SLOT) Reset zoom to 100%.
     */

    // NOT IMPLEMENTED
}

double PaintViewWidget::GetZoom() const
{
    /*
     * Get current zoom level.
     * 1.0 = 100%
     */

    return zoomLevel;
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
        scene.addPixmap(pixmapToLoad);
        pixmapToLoad = QPixmap();

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
