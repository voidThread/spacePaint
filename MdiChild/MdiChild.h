//
// Created by voidThread on 12.02.18.
//
#pragma once

#include "PaintViewWidget/PaintViewWidget.h"

class MdiChild : public PaintViewWidget
{
  Q_OBJECT

 public:
  MdiChild();

  void newFile();
  bool loadFile(const QString &fileName);
  bool save();
  bool saveAs();
  bool saveFile(const QString &fileName);
  QString userFriendlyCurrentFile();
  QString currentFile();

 protected:
  void closeEvent(QCloseEvent *event) override;

 private slots:
  void documentWasModified();

 private:
  bool maybeSave();
  void setCurrentFile(const QString &fileName);
  QString strippedName(const QString &fullFileName);

  QString openedFile;
  bool isUntitled;
};

