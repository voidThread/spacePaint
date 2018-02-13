#pragma once

#include <QMainWindow>
#include <QtWidgets>

class MdiChild;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  bool openFile(const QString &fileName);

 protected:
  void closeEvent(QCloseEvent *event) override;

 private slots:
  void newFile();
  void open();
  bool loadFile(const QString &fileName);
  MdiChild* createMdiChild();
  void updateMenus();

 private:
  Ui::MainWindow *ui;

  MdiChild *activeMdiChild() const;
  QMdiSubWindow *findMdiChild(const QString &fileName) const;

  void createActions();
  void createStatusBar();

  QMdiArea *mdiArea;
  QMenu *windowMenu;
  QAction *newAction;
  QAction *openAction;
};