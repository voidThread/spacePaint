#ifndef PAINTWIDGETTESTWINDOW_H
#define PAINTWIDGETTESTWINDOW_H

#include <QDialog>

namespace Ui {
class PaintWidgetTestWindow;
}

class PaintWidgetTestWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PaintWidgetTestWindow(QWidget *parent = 0);
    ~PaintWidgetTestWindow();
    void showEvent(QShowEvent*);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_8_clicked();

private:
    Ui::PaintWidgetTestWindow *ui;

private slots:
    void ZoomChanged(double newZoom);
    void on_pushButton_10_clicked();
};

#endif // PAINTWIDGETTESTWINDOW_H
