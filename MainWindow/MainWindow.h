#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

    bool OpenFile(const QString &fileName);

 protected:
    void closeEvent(QCloseEvent *event) override;

 private slots:
    void NewFile();
    void Open();
    bool LoadFile(const QString &fileName);
    MdiChild* CreateMdiChild();
    void UpdateMenus();

 private:
    Ui::MainWindow *ui;

    MdiChild *ActiveMdiChild() const;
    QMdiSubWindow *FindMdiChild(const QString &fileName) const;

    void CreateActions();
    void CreateStatusBar();

    QMdiArea *mdiArea;
    QMenu *windowMenu;
    QAction *newAction;
    QAction *openAction;
};
#endif