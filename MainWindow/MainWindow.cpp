#include <GlobalNames.h>
#include <MainWindow/MainWindow.h>
#include <MdiChild/MdiChild.h>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      mdiArea(new QMdiArea)
{
  ui->setupUi(this);
  mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

  setCentralWidget(mdiArea);
  connect(mdiArea, &QMdiArea::subWindowActivated, this, &MainWindow::updateMenus);

  createActions();
  setWindowTitle(GLOBAL_STRINGS::PROGRAM_INFO::PROGRAM_NAME);
}

MainWindow::~MainWindow()
{
  delete ui;
}
void MainWindow::createActions()
{
  QMenu *fileMenu = menuBar()->addMenu(tr("File"));
  QToolBar *fileToolBar = addToolBar(tr("File"));

  newAction = new QAction(QIcon(), tr("New window"), this);
  connect(newAction, &QAction::triggered, this, &MainWindow::newFile);
  fileMenu->addAction(newAction);
  fileToolBar->addAction(newAction);
}
void MainWindow::newFile()
{
  MdiChild *child = createMdiChild();
  child->newFile();
  child->show();
}
MdiChild *MainWindow::createMdiChild()
{
  MdiChild *child = new MdiChild;
  mdiArea->addSubWindow(child);
  return child;
}
void MainWindow::updateMenus() {

}
MdiChild *MainWindow::activeMdiChild() const {
  return nullptr;
}
QMdiSubWindow *MainWindow::findMdiChild(const QString &fileName) const {
  return nullptr;
}
