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
