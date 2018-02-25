#ifndef PAINTTOOLSPALETTE_H
#define PAINTTOOLSPALETTE_H

#include <QDialog>
#include <QMap>
#include <QToolButton>

#include "PaintViewWidget/PaintTool.h"

namespace Ui {
class PaintToolsPalette;
}

class PaintToolsPalette : public QDialog
{
    Q_OBJECT

public:
    explicit PaintToolsPalette(QWidget *parent = 0);
    ~PaintToolsPalette();

private:
    Ui::PaintToolsPalette *ui;
    QMap<QToolButton*, PaintTool> paintToolButtonMapping;

    void PaintToolButtonClicked(QObject *button);
    void CreatePaintToolMapping();
    void UncheckOtherButtons(QToolButton * current);
    void ConnectToolButtonClickedSignals();

signals:
    void PaintToolChanged(const PaintTool tool);

private slots:
    void ToolButtonClicked(bool);
};

#endif // PAINTTOOLSPALETTE_H
