#ifndef YDUSERINFO_H
#define YDUSERINFO_H

#include <QString>

#include "common/YDGlobal.h"

class YDUserInfo {
 public:
  explicit YDUserInfo(const QString &name, const QString &pwd,
                      const QString &date, Character::Powers powers);

 private:
  QString m_sName;
  QString m_sPassword;
  QString m_sDate;
  Character::Powers m_ePower;
};

#endif  // YDUSERINFO_H
