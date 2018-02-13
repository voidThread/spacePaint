#ifndef PAINTVIEWWIDGET_H
#define PAINTVIEWWIDGET_H

#include <QGraphicsView>

#include "PaintTool.h"

class PaintViewWidget : public QGraphicsView
{
    Q_OBJECT

public:
    PaintViewWidget(QWidget * parent = Q_NULLPTR);

    void RenderToPainter(QPainter & painter);
    void wheelEvent(QWheelEvent *event) override;

    void LoadImage(QImage & image);
    void LoadImage(QString filename);

    double GetZoom() const;
    unsigned CanvasWidth() const;
    unsigned CanvasHeight() const;
    PaintTool SelectedPaintTool() const;

private:
    QGraphicsScene scene;
    PaintTool paintTool = PaintTool::NN;
    unsigned canvasWidth = 0;
    unsigned canvasHeight = 0;
    QPixmap pixmapToLoad;
    double zoomLevel = 1.0;
    QGraphicsPixmapItem * backgroundItem = nullptr;
    double zoomStep = 0.05; // To be configured by settings

private slots:
    void OnCanvasCreated();

public slots:
    void ChangePaintTool(PaintTool tool);
    void ChangeColor(QColor color);
    void CreateNewCanvas(unsigned width, unsigned height);
    void ZoomIn();
    void ZoomOut();
    void ZoomReset();
    void SetZoomLevel(double zoom);
    void FitInView();

signals:
    void ZoomChanged(double newZoom);
    void CanvasCreated();
    void ImageLoaded();
    void PaintToolChanged(PaintTool tool);
    void ColorChanged(QColor color);
};

#endif // PAINTVIEWWIDGET_H
