//
// Created by dawid on 12.02.18.
//

#include "MdiChild.h"
MdiChild::MdiChild() {

}
void MdiChild::newFile() {

}
bool MdiChild::loadFile(const QString &fileName) {
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
