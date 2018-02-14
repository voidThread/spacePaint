//
// Created by dawid on 12.02.18.
//

#include <QtGui/QTextDocument>
#include <QtGui/QImageReader>
#include "MdiChild.h"

MdiChild::MdiChild()
{
    setAttribute(Qt::WA_DeleteOnClose);
    isUntitled = true;
}
void MdiChild::NewFile()
{
    static int sequenceNumber = 0;

    isUntitled = true;
    openedFile = tr("drawing%1.jpg").arg(sequenceNumber++);
    setWindowTitle(openedFile + "[*]");
}
bool MdiChild::LoadFile(const QString fileName)
{
    QImageReader imgRead(fileName);
    if (imgRead.canRead())
    {
        image = imgRead.read();
        LoadImage(image);
        setWindowTitle(fileName);
        setMaximumSize(image.size());
        setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        qDebug("Image readed");
        return true;
    } else
    {
        qDebug(imgRead.errorString().toStdString().c_str());
    }
    return false;
}
bool MdiChild::Save()
{
    return false;
}
bool MdiChild::SaveAs()
{
    return false;
}
bool MdiChild::SaveFile(const QString fileName)
{
    return false;
}
QString MdiChild::UserFriendlyCurrentFile()
{
    return QString();
}
QString MdiChild::CurrentFile()
{
    return QString();
}
void MdiChild::closeEvent(QCloseEvent *event)
{
    QWidget::closeEvent(event);
}
void MdiChild::DocumentWasModified()
{

}
bool MdiChild::MaybeSave()
{
    return false;
}
void MdiChild::SetCurrentFile(const QString fileName)
{

}
QString MdiChild::StrippedName(const QString fullFileName)
{
    return QString();
}