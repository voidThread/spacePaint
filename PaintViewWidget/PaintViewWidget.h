#ifndef PAINTVIEWWIDGET_H
#define PAINTVIEWWIDGET_H

#include <QGraphicsView>

#include "PaintTool.h"

class PaintViewWidget : public QGraphicsView
{
public:
    PaintViewWidget(QWidget * parent = Q_NULLPTR);

    void RenderToPainter(QPainter & painter);
    void LoadImage(QImage & image);
    double GetZoom() const;
    unsigned CanvasWidth() const;
    unsigned CanvasHeight() const;
    PaintTool SelectedPaintTool() const;

private:
    QGraphicsScene scene;
    PaintTool paintTool = PaintTool::NN;

public slots:
    void ChangePaintTool(PaintTool tool);
    void ChangeColor(QColor color);
    void CreateNewCanvas(unsigned width, unsigned height);
    void ZoomIn();
    void ZoomOut();
    void ZoomReset();

signals:
    void ZoomChanged(double newZoom);
    void CanvasCreated();
};

#endif // PAINTVIEWWIDGET_H
