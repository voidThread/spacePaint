#include "PaintToolsPalette.h"
#include "ui_PaintToolsPalette.h"

#include <QDebug>

PaintToolsPalette::PaintToolsPalette(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PaintToolsPalette)
{
    ui->setupUi(this);

    CreatePaintToolMapping();
}

PaintToolsPalette::~PaintToolsPalette()
{
    delete ui;
}

void PaintToolsPalette::PaintToolButtonClicked(QObject *button)
{
    /*
     * Paint tool button has been clicked.
     * Will emit signal `PaintToolChanged`.
     */

    QToolButton * currentButton = qobject_cast<QToolButton*>(button);
    currentButton->setDown(true);
    const auto paintToolIter = paintToolButtonMapping.find(currentButton);

    if (paintToolIter == paintToolButtonMapping.end())
    {
        qDebug() << "PaintToolToggled(): Paint tool not found.";
        return;
    }

    UncheckOtherButtons(currentButton);

    emit PaintToolChanged(paintToolIter.value());
}

void PaintToolsPalette::UncheckOtherButtons(QToolButton *current)
{
    for (auto button : paintToolButtonMapping.keys())
    {
        if (button == current)
        {
            button->setDown(true);
            continue;
        }

        button->setDown(false);
    }
}

void PaintToolsPalette::CreatePaintToolMapping()
{
    /*
     * Create map container toolbutton -> paint tool enum value
     */

    paintToolButtonMapping.insert(ui->BrushButton, PaintTool::Brush);
    paintToolButtonMapping.insert(ui->CrayonButton, PaintTool::Crayon);
    paintToolButtonMapping.insert(ui->EraserButton, PaintTool::Eraser);
    paintToolButtonMapping.insert(ui->PenButton, PaintTool::Pen);
    paintToolButtonMapping.insert(ui->SprayButton, PaintTool::Spray);
    paintToolButtonMapping.insert(ui->ZoomButton, PaintTool::Zoom);
    paintToolButtonMapping.insert(ui->FloodFillButton, PaintTool::FloodFill);
    paintToolButtonMapping.insert(ui->HandButton, PaintTool::Hand);
    paintToolButtonMapping.insert(ui->SelectionButton, PaintTool::Selection);

    ConnectToolButtonClickedSignals();
}

void PaintToolsPalette::ConnectToolButtonClickedSignals()
{
    for (auto iter = paintToolButtonMapping.begin();
         iter != paintToolButtonMapping.end(); ++iter)
    {
        QToolButton * button = iter.key();
        connect(button, &QToolButton::clicked,
                this, &PaintToolsPalette::ToolButtonClicked);
    }
}

void PaintToolsPalette::ToolButtonClicked(bool)
{
    /*
     * One of the paint tool buttons has been clicked.
     */

    PaintToolButtonClicked(sender());
}
