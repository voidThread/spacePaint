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
  NewFileDialog(QWidget *parent);
  virtual ~NewFileDialog();

 private:
  Ui::NewFileDialog *ui;
};
#endif // NEWFILEDIALOG_H