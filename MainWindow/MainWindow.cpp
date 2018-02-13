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
  createStatusBar();
  setWindowTitle(GLOBAL_STRINGS::PROGRAM_INFO::PROGRAM_NAME);
}

MainWindow::~MainWindow()
{
  delete ui;
}
void MainWindow::closeEvent(QCloseEvent *event)
{
  QWidget::closeEvent(event);
  mdiArea->closeAllSubWindows();

  if(mdiArea->currentSubWindow())
  {
    event->ignore();
  } else
  {
    event->accept();
  }
}
void MainWindow::newFile()
{
  MdiChild *child = createMdiChild();
  child->newFile();
  child->show();
  statusBar()->showMessage("File created", 2000);
}
void MainWindow::open()
{
  const QString fileName = QFileDialog::getOpenFileName(this);
  if (!fileName.isEmpty())
  {
    openFile(fileName);
  }
}
bool MainWindow::openFile(const QString &fileName)
{
  if (QMdiSubWindow *existing = findMdiChild(fileName))
  {
    mdiArea->setActiveSubWindow(existing);
    return true;
  }

  const bool succeeded = loadFile(fileName);
  if (succeeded)
  {
    statusBar()->showMessage("File loaded", 2000);
  }

  return succeeded;
}
bool MainWindow::loadFile(const QString &fileName)
{
  MdiChild *child = createMdiChild();
  const bool succeeded = child->loadFile(fileName);

  if (succeeded)
  {
    child->show();
  } else
  {
    child->close();
  }

  return succeeded;
}
void MainWindow::createActions()
{
  QMenu *fileMenu = menuBar()->addMenu(tr("File"));
  QToolBar *fileToolBar = addToolBar(tr("File"));

  newAction = new QAction(QIcon(), tr("New window"), this);
  connect(newAction, &QAction::triggered, this, &MainWindow::newFile);
  fileMenu->addAction(newAction);
  fileToolBar->addAction(newAction);

  openAction = new QAction(QIcon(), tr("Open file"), this);
  connect(openAction, &QAction::triggered, this, &MainWindow::open);
  fileMenu->addAction(openAction);
  fileToolBar->addAction(openAction);
}
void MainWindow::createStatusBar()
{
  statusBar()->showMessage("Ready");
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
