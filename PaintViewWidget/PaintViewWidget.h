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

    void LoadImage(const QImage & image);
    void LoadImage(const QString filename);

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
    void ChangePaintTool(const PaintTool tool);
    void ChangeColor(const QColor color);
    void CreateNewCanvas(const unsigned width, const unsigned height);
    void ZoomIn();
    void ZoomOut();
    void ZoomReset();
    void SetZoomLevel(const double zoom);
    void FitInView();

signals:
    void ZoomChanged(const double newZoom) const;
    void CanvasCreated() const;
    void ImageLoaded() const;
    void PaintToolChanged(const PaintTool tool) const;
    void ColorChanged(const QColor color) const;
};

#endif // PAINTVIEWWIDGET_H
