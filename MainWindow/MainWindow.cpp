#include <GlobalNames.h>
#include <MainWindow/MainWindow.h>
#include <MdiChild/MdiChild.h>
#include <QToolBar>
#include <NewFileDialog/NewFileDialog.h>

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
    connect(mdiArea, &QMdiArea::subWindowActivated, this, &MainWindow::UpdateMenus);

    CreateActions();
    CreateStatusBar();
    setWindowTitle(GLOBAL_STRINGS::PROGRAM_INFO::PROGRAM_NAME);

    CreatePaintToolsBar();

    //TODO - temporary setting size from magic numbers
    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    mdiArea->closeAllSubWindows();
}

void MainWindow::NewFile()
{
  NewFileDialog newFileDialog(this);
  connect(static_cast<QDialog*>(&newFileDialog), SIGNAL(NewFileCreate(QSize)),
          this, SLOT(NewFileCreate(QSize)));
  newFileDialog.exec();
}

void MainWindow::NewFileCreate(QSize CanvasSize)
{
    MdiChild *child = CreateMdiChild();
  child->NewFile(CanvasSize);
    child->show();
    statusBar()->showMessage("File created", 2000);
}

void MainWindow::Open()
{
    const QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
    {
        OpenFile(fileName);
    }
}

bool MainWindow::OpenFile(const QString fileName)
{
    const bool succeeded = LoadFile(fileName);
    if (succeeded)
    {
        statusBar()->showMessage("File loaded", 2000);
    }
    return succeeded;
}

bool MainWindow::LoadFile(const QString fileName)
{
    MdiChild *child = CreateMdiChild();
    const bool succeeded = child->LoadFile(fileName);

    if (succeeded)
    {
        child->show();
    } else
    {
        child->close();
    }

    return succeeded;
}

void MainWindow::CreateActions()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("File"));
    QToolBar *fileToolBar = addToolBar(tr("File"));

    newAction = new QAction(QIcon(), tr("New window"), this);
    connect(newAction, &QAction::triggered, this, &MainWindow::NewFile);
    fileMenu->addAction(newAction);
    fileToolBar->addAction(newAction);

    openAction = new QAction(QIcon(), tr("Open file"), this);
    connect(openAction, &QAction::triggered, this, &MainWindow::Open);
    fileMenu->addAction(openAction);
    fileToolBar->addAction(openAction);
}

void MainWindow::CreateStatusBar()
{
    statusBar()->showMessage("Ready");
}

void MainWindow::CreatePaintToolsBar()
{
    paintToolsPalette = new PaintToolsPalette();

    paintToolsBar = new QToolBar("Tools");
    paintToolsBar->addWidget(paintToolsPalette);

    this->addToolBar(Qt::LeftToolBarArea, paintToolsBar);
}

MdiChild *MainWindow::CreateMdiChild()
{
    MdiChild *child = new MdiChild;

    connect(paintToolsPalette, &PaintToolsPalette::PaintToolChanged,
            child, &MdiChild::ChangePaintTool);

    mdiArea->addSubWindow(child);
    return child;
}

void MainWindow::UpdateMenus()
{

}

MdiChild *MainWindow::ActiveMdiChild() const
{
    return nullptr;
}

QMdiSubWindow *MainWindow::FindMdiChild(const QString fileName) const
{
    return nullptr;
}
