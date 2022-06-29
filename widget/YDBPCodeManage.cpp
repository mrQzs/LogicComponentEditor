#include "YDBPCodeManage.h"

#include <QHBoxLayout>
#include <QMenu>
#include <QMessageBox>

#include "QVBoxLayout"
#include "YDCodeEditor.h"
#include "YDScriptPropDialog.h"
#include "common/YDHelper.h"
#include "core/YDProjectManage.h"
#include "model/YDScriptModel.h"
#include "view/YDListView.h"

YDBPCodeManage::YDBPCodeManage(QWidget *parent)
    : QDialog{parent},
      m_codeW{new YDCodeEditor(this)},
      m_name{HOME_MOVE_SCRIPT_NAME} {
  setWindowTitle(YDBPCodeManage::tr("回原点脚本管理"));

  QHBoxLayout *hlay = new QHBoxLayout(this);
  hlay->setContentsMargins(0, 0, 0, 0);
  hlay->setSpacing(0);
  hlay->addWidget(m_codeW);

  connect(m_codeW, &YDCodeEditor::sigSave, this,
          &YDBPCodeManage::slotSaveClicked);

  connect(m_codeW, &YDCodeEditor::sigCompile, this,
          &YDBPCodeManage::slotCompileClicked);

  connect(this, &YDBPCodeManage::sigResult, m_codeW, &YDCodeEditor::slotResult);
}

void YDBPCodeManage::setScript() {
  m_type = YDProjectManage::GetHomeMoveScriptType();
  auto file = YDProjectManage::getExtendableScriptCodeFilePath(m_name, m_type);
  auto filestr = STRTQSTR(file.c_str());
  auto code = YDHelper::readFile(filestr);
  if (code.isEmpty()) {
    if (m_type == SCRIPT_TYPE_VB_NET)
      code = YDProjectManage::getVbCode();
    else
      code = YDProjectManage::getVcCode();
    QString str = QString("YDTemp_%1").arg(YDHelper::genarateTail());
    code.replace("YDTemplate", str);
  }

  m_codeW->changeType(m_type - SCRIPT_TYPE_VB_NET);
  m_codeW->setText(code);
  m_code = code;
}

void YDBPCodeManage::closeEvent(QCloseEvent *) {
  if (m_code != m_codeW->getText()) {
    auto rt = QMessageBox::information(
        nullptr, YDBPCodeManage::tr("提示"),
        YDBPCodeManage::tr("代码未保存,是否保存?"), YDBPCodeManage::tr("是"),
        YDBPCodeManage::tr("否"));
    if (0 == rt) {
      slotSaveClicked();
    }
  }
}

void YDBPCodeManage::slotSaveClicked() {
  auto code = m_codeW->getText();
  auto file = YDProjectManage::getExtendableScriptCodeFilePath(m_name, m_type);
  auto filestr = STRTQSTR(file.c_str());
  m_code = code;
  YDHelper::writeFile(filestr, code);
}

void YDBPCodeManage::slotCompileClicked() {
  auto cpu = TARGET_CPU_X64 - m_codeW->getBuildCpu();
  std::vector<std::string> fram;
  YDProjectManage::enumFrameworks(cpu, fram);
  int findex = m_codeW->getBuildFram();
  auto str = YDHelper::getAvaliableFram(fram)[findex];
  auto framstr = QSTRTSTR(str);
  std::string result;
  YDProjectManage::compileExtendableScript(m_name, m_type, framstr, cpu,
                                           result);
  auto ret = STRTQSTR(result.c_str());
  emit sigResult(ret);
}
