// Created by voidThread on 12.02.18.
#ifndef MDICHILD_H
#define MDICHILD_H

#include "PaintViewWidget/PaintViewWidget.h"

class MdiChild : public PaintViewWidget
{
    Q_OBJECT

 public:
    MdiChild();

    void NewFile();
    bool LoadFile(const QString fileName);
    bool Save();
    bool SaveAs();
    bool SaveFile(const QString fileName);
    QString UserFriendlyCurrentFile();
    QString CurrentFile();

 protected:
    void closeEvent(QCloseEvent *event) override;

 private slots:
    void DocumentWasModified();

 private:
    bool MaybeSave();
    void SetCurrentFile(const QString fileName);
    QString StrippedName(const QString fullFileName);

    QString openedFile;
    bool isUntitled;
    QImage image;
};
#endif