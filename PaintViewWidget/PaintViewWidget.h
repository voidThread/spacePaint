#ifndef PAINTVIEWWIDGET_H
#define PAINTVIEWWIDGET_H

#include <QGraphicsView>

#include "PaintTool.h"

Q_DECLARE_METATYPE(PaintTool)

class PaintViewWidget : public QGraphicsView
{
#ifdef UNIT_TESTS
    friend class TestPaintViewWidget;
#endif

    Q_OBJECT

public:
    PaintViewWidget(QWidget * parent = Q_NULLPTR);

    void RenderToPainter(QPainter & painter);
    void wheelEvent(QWheelEvent *event) override;

    void LoadImage(const QImage & image);
    void LoadImage(const QString filename);

    double GetZoom() const;
    int CanvasWidth() const;
    int CanvasHeight() const;
    PaintTool SelectedPaintTool() const;
    QPixmap GetBackground();
    QColor SelectedColor() const;

private:
    QGraphicsScene scene;
    PaintTool paintTool = PaintTool::NN;
    int canvasWidth = 0;
    int canvasHeight = 0;
    QPixmap pixmapToLoad;
    double zoomLevel = 1.0;
    QGraphicsPixmapItem * backgroundItem = nullptr;
    double zoomStep = 0.05; // To be configured by settings
    QColor selectedColor;

private slots:
    void OnCanvasCreated();

public slots:
    void ChangePaintTool(const PaintTool tool);
    void ChangeColor(const QColor color);
    void CreateNewCanvas(const int width, const int height);
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
