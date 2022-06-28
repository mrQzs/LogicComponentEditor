#include <QApplication>

#include "MainWindow.h"
#include "common/YDHelper.h"
#include "common/YDLogger.h"
#include "core/YDProjectManage.h"
#include "debug/YDDgHelper.h"
#include "widget/YDProjectDialog.h"

//#include "vld.h"
#ifdef Q_OS_WIN
#include "breakpad/client/windows/handler/exception_handler.h"

bool callback(const wchar_t *dump_path, const wchar_t *id, void *context,
              EXCEPTION_POINTERS *exinfo, MDRawAssertionInfo *assertion,
              bool succeeded) {
  Q_UNUSED(dump_path);
  Q_UNUSED(id);
  Q_UNUSED(context);
  Q_UNUSED(exinfo);
  Q_UNUSED(assertion);
  return succeeded;
}
#endif

int main(int argc, char *argv[]) {
#ifdef Q_OS_WIN
  google_breakpad::ExceptionHandler eh(
      L".", NULL, callback, NULL,
      google_breakpad::ExceptionHandler::HANDLER_ALL);
#endif

  QApplication a(argc, argv);

  YDHelper ydhelper;
  Q_UNUSED(ydhelper);

  YDProjectManage ydprojectManage;
  Q_UNUSED(ydprojectManage);

  YDDgHelper yddgHelper;
  Q_UNUSED(yddgHelper);

  YDLogger ydlogger;
  Q_UNUSED(ydlogger);

  YDProjectManage::init();

  YDProjectDialog dia;
  if (dia.exec() == QDialog::Accepted) {
    MainWindow w;
    auto pName =
        QString("%1: %2").arg(MainWindow::tr("工程"), dia.getProjectName());
    auto name = QString("%1  ---  %2")
                    .arg(MainWindow::tr("业务逻辑编辑软件 v:1.1.0"), pName);
    w.setWindowTitle(name);

    YDLogger::setMessageWidget(w.getLogWidget());

    w.showMaximized();

    return a.exec();
  }
  return 0;
}
