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

private:
    QGraphicsScene scene;

public slots:
    void ChangePaintTool(PaintTool tool);
    void ChangeColor(QColor color);
};

#endif // PAINTVIEWWIDGET_H
