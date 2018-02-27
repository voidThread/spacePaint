#include "NewFileDialog.h"
#include "ui_NewFileDialog.h"

NewFileDialog::NewFileDialog(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::NewFileDialog)
{
  ui->setupUi(this);
}

NewFileDialog::~NewFileDialog() {
  delete ui;
}
