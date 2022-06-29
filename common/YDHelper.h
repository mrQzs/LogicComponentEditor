#ifndef YDHELPER_H
#define YDHELPER_H

#include <QCoreApplication>

class MainWindow;
class YDUserInfo;
class YDTaskGroup;
class YDModule;
class YDModulePropModel;
class YDTask;
class YDTabWidget;
class QElapsedTimer;
class QRandomGenerator;
class QTextStream;
class QListWidget;

#include "platform.h"
#include "yddef.h"

class YDHelper {
  Q_DECLARE_TR_FUNCTIONS(YDHelper)
 public:
  YDHelper();
  ~YDHelper();

 public:
  // get
  static MainWindow* getMainW();
  static YDUserInfo* getUserInfo();
  static YDModule* getModule(int type);
  static YDModulePropModel* getModPropModel();
  static QStringList getDataTypeList();
  static QString getDataType(uint8 index);
  static int getDataTypeIndex(const QString& str);
  static std::string qstringToString(const QString& str);
  static uint8 getCompareIndex(const QString& str);
  static QString getCompareStr(uint8 index);
  static bool isDebugMode();
  static bool getTestStart();

  // set
  static void setMainW(MainWindow* mainW);
  static void setUserInfo(YDUserInfo* usrInfo);
  static void setTestStart(bool);

  // other
  static QString getMD5(const QString& str);
  static void UpdateTabName(YDTask* task);
  static void updateCoorData(yd::COORD& coor, const QStringList& info);
  static QString CoorData2QStr(yd::COORD& coor);
  static void copyData(char a[], const char*, int size);
  static void setDebugMode(bool b);
  static void calculateTime();
  static QStringList getAvaliableFram(const std::vector<std::string>& fram);
  static QString genarateName();
  static QString genarateTail();
  static QString readFile(const QString& name);
  static void writeFile(const QString& name, const QString& data);
  static void resizeModel(QListWidget* list);
  static QString moduleLog(const YDModule* p);

 private:
  static YDHelper* s_instance;
  int m_nameIndex;
  MainWindow* m_pMain;
  YDUserInfo* m_pUserInfo;
  QList<YDModule*> m_moveModuleList;
  int m_curIndex;
  QStringList m_list;
  QList<QString> m_cmpStrs;
  QRandomGenerator* m_random;

  // debug
  bool m_debugMode;

  // calcu
  bool m_isStart;
  bool m_isTestStart;
  QElapsedTimer* m_timer;
  QTextStream* m_stream;
};

#define QSTRTSTR(str) YDHelper::qstringToString(str)
#define STRTQSTR(str) QString::fromLocal8Bit(str)

#endif  // YDHELPER_H
