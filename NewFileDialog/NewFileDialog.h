#ifndef NEWFILEDIALOG_H
#define NEWFILEDIALOG_H

#include <QtWidgets/QDialog>

namespace Ui {
  class NewFileDialog;
}

class NewFileDialog : public QDialog
{
    Q_OBJECT

 public:
  explicit NewFileDialog(QWidget *parent = 0);
  ~NewFileDialog();

 signals:
  void NewFileCreate(QObject *button);

 private slots:
  void NewFileButtonClicked(bool);

 private:
  Ui::NewFileDialog *ui;
  
  void ConnectNewFileButton();
};
#endif // NEWFILEDIALOG_H
