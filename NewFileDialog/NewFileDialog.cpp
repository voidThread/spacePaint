#include "NewFileDialog.h"
#include "ui_NewFileDialog.h"

NewFileDialog::NewFileDialog(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::NewFileDialog)
{
    ui->setupUi(this);

    ConnectNewFileButton();
}

NewFileDialog::~NewFileDialog() {
    delete ui;
}

void NewFileDialog::NewFileButtonClicked(bool)
{
    emit NewFileCreate(sender());
}

void NewFileDialog::ConnectNewFileButton()
{
  connect(ui->NewFileButton, &QPushButton::clicked,
          this, &NewFileDialog::NewFileButtonClicked);
}
