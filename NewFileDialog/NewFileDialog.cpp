#include "NewFileDialog.h"
#include "ui_NewFileDialog.h"

NewFileDialog::NewFileDialog(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::NewFileDialog)
{
    ui->setupUi(this);

    ConnectNewFileButton();
    ConnectCancelButton();
}

NewFileDialog::~NewFileDialog() {
    delete ui;
}

void NewFileDialog::NewFileButtonClicked(bool)
{
    QSize CanvasSize(ui->newCanvasSizeWidth->text().toInt(), ui->newCanvasSizeHeight->text().toInt());
    emit NewFileCreate(CanvasSize);
}

void NewFileDialog::ConnectNewFileButton()
{
    connect(ui->NewFileButton, &QPushButton::clicked,
          this, &NewFileDialog::NewFileButtonClicked);
}

void NewFileDialog::CancelButtonClicked(bool)
{
    emit CancelNewFile(sender());
}

void NewFileDialog::ConnectCancelButton()
{
    connect(ui->CancellButton, &QPushButton::clicked,
          this, &NewFileDialog::CancelButtonClicked);
}
