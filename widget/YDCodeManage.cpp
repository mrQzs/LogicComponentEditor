#include "YDCodeManage.h"

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

YDCodeManage::YDCodeManage(QWidget *parent)
    : QDialog{parent}, m_codeW{new YDCodeEditor(this)}, m_script{nullptr} {
  setWindowTitle(YDCodeManage::tr("自定义脚本管理"));

  QHBoxLayout *hlay = new QHBoxLayout(this);
  hlay->setContentsMargins(0, 0, 0, 0);
  hlay->setSpacing(0);
  hlay->addWidget(m_codeW);

  connect(m_codeW, &YDCodeEditor::sigSave, this,
          &YDCodeManage::slotSaveClicked);

  connect(m_codeW, &YDCodeEditor::sigCompile, this,
          &YDCodeManage::slotCompileClicked);

  connect(this, &YDCodeManage::sigResult, m_codeW, &YDCodeEditor::slotResult);
}

void YDCodeManage::setScript(yd::adv::ExtendScript *script) {
  m_script = script;
  auto name = m_script->script_name;
  auto type = m_script->script_type;
  auto file = YDProjectManage::getExtendableScriptCodeFilePath(name, type);
  auto filestr = STRTQSTR(file.c_str());
  auto code = YDHelper::readFile(filestr);
  if (code.isEmpty()) {
    if (type == SCRIPT_TYPE_VB_NET)
      code = YDProjectManage::getBPVbCode();
    else
      code = YDProjectManage::getBPVCCode();
    QString str = QString("YDTemp_%1").arg(YDHelper::genarateTail());
    code.replace("YDTemplate", str);
  }

  m_codeW->changeType(type - SCRIPT_TYPE_VB_NET);
  m_codeW->setText(code);
  m_code = code;
}

void YDCodeManage::closeEvent(QCloseEvent *) {
  if (m_code != m_codeW->getText()) {
    auto rt = QMessageBox::information(nullptr, YDCodeManage::tr("提示"),
                                       YDCodeManage::tr("代码未保存,是否保存?"),
                                       YDCodeManage::tr("是"),
                                       YDCodeManage::tr("否"));
    if (0 == rt) {
      slotSaveClicked();
    }
  }
}

void YDCodeManage::slotSaveClicked() {
  auto name = m_script->script_name;
  auto type = m_script->script_type;
  auto code = m_codeW->getText();
  auto file = YDProjectManage::getExtendableScriptCodeFilePath(name, type);
  auto filestr = STRTQSTR(file.c_str());
  m_code = code;
  YDHelper::writeFile(filestr, code);
}

void YDCodeManage::slotCompileClicked() {
  auto name = m_script->script_name;
  auto type = m_script->script_type;
  auto cpu = TARGET_CPU_X64 - m_codeW->getBuildCpu();
  std::vector<std::string> fram;
  YDProjectManage::enumFrameworks(cpu, fram);
  int findex = m_codeW->getBuildFram();
  auto str = YDHelper::getAvaliableFram(fram)[findex];
  auto framstr = QSTRTSTR(str);
  std::string result;
  YDProjectManage::compileExtendableScript(name, type, framstr, cpu, result);
  auto ret = STRTQSTR(result.c_str());
  emit sigResult(ret);
}
