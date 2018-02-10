#include "MainWindow.h"
#include "ui_mainwindow.h"

#include "PaintViewWidget/PaintWidgetTestWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    paintTestWindow = new PaintWidgetTestWindow(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{
    paintTestWindow->show();
}
