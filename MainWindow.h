#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class PaintWidgetTestWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void showEvent(QShowEvent *);

private:
    Ui::MainWindow *ui;
    PaintWidgetTestWindow * paintTestWindow = nullptr;
};

#endif // MAINWINDOW_H
