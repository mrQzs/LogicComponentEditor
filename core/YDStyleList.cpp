#include "YDStyleList.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

Q_GLOBAL_STATIC(YDStyleList, stylelist)

YDStyleList::YDStyleList() {
  initNameMap();
  initStyleList();
}

YDStyleList *YDStyleList::instance() { return stylelist; }

QString YDStyleList::getStyle(Window::Style style) const {
  int index = (int)style;
  Q_ASSERT(index >= 0);
  Q_ASSERT(index < m_lStyleList.size());
  return m_lStyleList[index];
}

void YDStyleList::initNameMap() {
  m_mNameMap[0] = "MainWListBtnDefault";
  m_mNameMap[1] = "MainWListBtnSelect";
  m_mNameMap[2] = "MainWListBtnBackground";
  m_mNameMap[3] = "MainWindow";
}

void YDStyleList::initStyleList() {
  QFile file(":/Style/NormalStyle.yds");
  file.open(QFile::ReadOnly);
  QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
  file.close();

  Q_ASSERT(doc.object().contains("Styles"));

  QJsonObject Styles = doc["Styles"].toObject();

  for (int i = 0; i < m_mNameMap.size(); ++i) {
    QString key = m_mNameMap[i];
    m_lStyleList.push_back(Styles[key].toString());
  }
}
