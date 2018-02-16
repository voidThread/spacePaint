#ifndef PAINTVIEWWIDGET_H
#define PAINTVIEWWIDGET_H

#include <QGraphicsView>
#include <QMap>

#include "PaintTool.h"

class PaintViewWidget : public QGraphicsView
{
    Q_OBJECT

public:
    PaintViewWidget(QWidget * parent = Q_NULLPTR);

    void RenderToPainter(QPainter & painter);

    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;


    void LoadImage(QImage & image);
    void LoadImage(QString filename);

    double GetZoom() const;
    unsigned CanvasWidth() const;
    unsigned CanvasHeight() const;
    PaintTool SelectedPaintTool() const;

private:
    using MouseEventHandlerMap = QMap<PaintTool, std::function<void(QMouseEvent*)>>;
    using PaintToolChangeHandlerMap = QMap<PaintTool, std::function<void()>>;

    QGraphicsScene scene;
    PaintTool paintTool = PaintTool::NN;
    unsigned canvasWidth = 0;
    unsigned canvasHeight = 0;
    QPixmap pixmapToLoad;
    double zoomLevel = 1.0;
    QGraphicsPixmapItem * backgroundItem = nullptr;
    double zoomStep = 0.05; // To be configured by settings
    PaintToolChangeHandlerMap PaintToolChangeMappings;
    MouseEventHandlerMap PaintToolMouseDownMappings;
    MouseEventHandlerMap PaintToolMouseUpMappings;

    void CreatePaintToolChangedMapping();
    void CreateMouseDownPaintToolMapping();
    void CreateMouseUpPaintToolMapping();

    void CallMouseEventHandler(PaintTool tool, MouseEventHandlerMap & handlerMap, QMouseEvent * event);
    void PaintToolChangeEventHandler(PaintTool tool);

    /* Paint tool change event handlers */
    void HandToolChangeEvent();

    /* Mouse down event handlers for paint tools */
    void HandToolMouseDownEvent(QMouseEvent * event);

    /* Mouse up event handlers for paint tools */
    void HandToolMouseUpEvent(QMouseEvent * event);

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
