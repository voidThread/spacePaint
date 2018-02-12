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

private slots:
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();

private:
    Ui::PaintWidgetTestWindow *ui;
};

#endif // PAINTWIDGETTESTWINDOW_H
