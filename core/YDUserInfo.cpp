#include "YDUserInfo.h"

YDUserInfo::YDUserInfo(const QString &name, const QString &pwd,
                       const QString &date, Character::Powers powers) {
  Q_ASSERT(!name.isEmpty());
  Q_ASSERT(!pwd.isEmpty());
  Q_ASSERT(!date.isEmpty());
  m_sName = name;
  m_sPassword = pwd;
  m_sDate = date;
  m_ePower = powers;
}
