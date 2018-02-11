#include "PaintWidgetTestWindow.h"
#include "ui_PaintWidgetTestWindow.h"

#include "PaintViewWidget.h"

#include <QColorDialog>

PaintWidgetTestWindow::PaintWidgetTestWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PaintWidgetTestWindow)
{
    ui->setupUi(this);

    connect(ui->paintView, &PaintViewWidget::ZoomChanged,
            this, &PaintWidgetTestWindow::ZoomChanged);
}

PaintWidgetTestWindow::~PaintWidgetTestWindow()
{
    delete ui;
}

void PaintWidgetTestWindow::showEvent(QShowEvent *)
{
    ui->paintView->LoadImage("./TestData/flower.jpg");
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
        ui->colorWidget->setStyleSheet("background-color:" + color.name());
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

void PaintWidgetTestWindow::on_pushButton_7_clicked()
{
    /*
     * Zoom in.
     */

    ui->paintView->ZoomIn();
}

void PaintWidgetTestWindow::on_pushButton_9_clicked()
{
    /*
     * Zoom reset.
     */

    ui->paintView->ZoomReset();
}

void PaintWidgetTestWindow::on_pushButton_8_clicked()
{
    /*
     * Zoom out.
     */

    ui->paintView->ZoomOut();
}

void PaintWidgetTestWindow::ZoomChanged(double newZoom)
{
    /*
     * (SLOT) Zoom has changed.
     */

    double percent = 100.0 * newZoom;
    ui->label_5->setText(QString::number(percent) + "%");
}
