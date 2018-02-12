#include "PaintViewWidget.h"

#include <QGraphicsScene>

PaintViewWidget::PaintViewWidget(QWidget *parent)
    : QGraphicsView(parent)
{
    this->setScene(&scene);
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
}

void PaintViewWidget::ChangePaintTool(PaintTool tool)
{
    /*
     * (SLOT) Change the current paint tool selected to use.
     */
}

void PaintViewWidget::ChangeColor(QColor color)
{
    /*
     * (SLOT) Change the current selected color. Used by some painting tools
     * like pen, flood fill and so on.
     */
}

void PaintViewWidget::CreateNewCanvas(unsigned width, unsigned height)
{
    /*
     * (SLOT) Clear the current canvas and create new.
     * \param width Width of the canvas in pixels.
     * \param height Height of the canvas in pixels.
     */
}

void PaintViewWidget::ZoomIn()
{
    /*
     * (SLOT) Incrase current zoom.
     */
}

void PaintViewWidget::ZoomOut()
{
    /*
     * (SLOT) Decrase current zoom.
     */
}

void PaintViewWidget::ZoomReset()
{
    /*
     * (SLOT) Reset zoom to 100%.
     */
}

double PaintViewWidget::GetZoom() const
{
    /*
     * Get current zoom level.
     * 1.0 = 100%
     */

    return 1.0;
}

unsigned PaintViewWidget::CanvasWidth() const
{
    return 0;
}

unsigned PaintViewWidget::CanvasHeight() const
{
    return 0;
}

PaintTool PaintViewWidget::SelectedPaintTool() const
{
    /*
     * Get the current selected paint tool.
     */

    return paintTool;
}
