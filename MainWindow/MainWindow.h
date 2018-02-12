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

 private slots:
  void newFile();
  MdiChild* createMdiChild();
  void updateMenus();

 private:
  Ui::MainWindow *ui;

  MdiChild *activeMdiChild() const;
  QMdiSubWindow *findMdiChild(const QString &fileName) const;

  void createActions();

  QMdiArea *mdiArea;
  QMenu *windowMenu;
  QAction *newAction;
};