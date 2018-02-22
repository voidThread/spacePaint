#include <QtGui/QTextDocument>
#include <QtGui/QImageReader>
#include <QDebug>
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
        qDebug() << "Image readed";
        return true;
    } else
    {
        qDebug() << imgRead.errorString();
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
