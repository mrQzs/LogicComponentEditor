#ifndef YDPLUGMANAGE_H
#define YDPLUGMANAGE_H

#include "modules/YDModules.h"

class YDPlugManage {
 public:
  YDPlugManage();

 public:
  QStringList getMotionNames();
  QStringList getControlNames();

 private:
  QList<YDModule*> m_motionList;
  QList<YDModule*> m_controlList;
};

#endif  // YDPLUGMANAGE_H
