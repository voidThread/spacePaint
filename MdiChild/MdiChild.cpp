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
void MdiChild::newFile()
{
  static int sequenceNumber = 0;

  isUntitled = true;
  openedFile = tr("drawing%1.jpg").arg(sequenceNumber++);
  setWindowTitle(openedFile + "[*]");
}
bool MdiChild::loadFile(const QString &fileName)
{
  QImageReader imgRead(fileName);
  if (imgRead.canRead())
  {
    image = imgRead.read();
    qDebug("Image readed");
    return true;
  } else
  {
    qDebug(imgRead.errorString().toStdString().c_str());
  }
  return false;
}
bool MdiChild::save() {
  return false;
}
bool MdiChild::saveAs() {
  return false;
}
bool MdiChild::saveFile(const QString &fileName) {
  return false;
}
QString MdiChild::userFriendlyCurrentFile() {
  return QString();
}
QString MdiChild::currentFile() {
  return QString();
}
void MdiChild::closeEvent(QCloseEvent *event) {
  QWidget::closeEvent(event);
}
void MdiChild::documentWasModified() {

}
bool MdiChild::maybeSave() {
  return false;
}
void MdiChild::setCurrentFile(const QString &fileName) {

}
QString MdiChild::strippedName(const QString &fullFileName) {
  return QString();
}
