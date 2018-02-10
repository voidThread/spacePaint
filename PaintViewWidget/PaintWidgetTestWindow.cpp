#include "PaintWidgetTestWindow.h"
#include "ui_PaintWidgetTestWindow.h"

#include "PaintViewWidget.h"

#include <QColorDialog>

PaintWidgetTestWindow::PaintWidgetTestWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PaintWidgetTestWindow)
{
    ui->setupUi(this);
}

PaintWidgetTestWindow::~PaintWidgetTestWindow()
{
    delete ui;
}

void PaintWidgetTestWindow::on_pushButton_clicked()
{
    /*
     *  Close test window.
     */

    close();
}

void PaintWidgetTestWindow::on_pushButton_3_clicked()
{
    /*
     * Select pen tool.
     */

    ui->paintView->ChangePaintTool(PaintTool::Pen);
}

void PaintWidgetTestWindow::on_pushButton_2_clicked()
{
    /*
     * Select eraser tool.
     */

    ui->paintView->ChangePaintTool(PaintTool::Eraser);
}

void PaintWidgetTestWindow::on_pushButton_4_clicked()
{
    /*
     * Select color.
     */

    QColor color = QColorDialog::getColor();

    if (color.isValid())
    {
        ui->paintView->ChangeColor(color);
    }
}

void PaintWidgetTestWindow::on_pushButton_5_clicked()
{
    /*
     * Undo last operation.
     */
}

void PaintWidgetTestWindow::on_pushButton_6_clicked()
{
    /*
     * Redo last operation.
     */
}
