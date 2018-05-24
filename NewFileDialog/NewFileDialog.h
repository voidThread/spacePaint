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
  void NewFileCreate(QSize);

 private slots:
  void NewFileButtonClicked(bool);
  void CancelButtonClicked(bool);

 private:
  Ui::NewFileDialog *ui;
  
  void ConnectNewFileButton();
  void ConnectCancelButton();
};
#endif // NEWFILEDIALOG_H
