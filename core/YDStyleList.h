#ifndef YDSTYLELIST_H
#define YDSTYLELIST_H

#include <QMap>
#include <QString>

#include "common/YDGlobal.h"

class YDStyleList {
 public:
  YDStyleList();
  static YDStyleList* instance();

 public:
  QString getStyle(Window::Style style) const;

  void readStyleFile(const QString& file);

 private:
  void initNameMap();
  void initStyleList();

 private:
  QMap<int, QString> m_mNameMap;
  QStringList m_lStyleList;
};

#endif  // YDSTYLELIST_H
