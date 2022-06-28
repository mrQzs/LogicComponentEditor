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
    : QDialog{parent},
      m_codeW{new YDCodeEditor(this)},
      m_script{nullptr},
      m_isSaved{false} {
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

bool YDCodeManage::isSaved() { return m_isSaved; }

void YDCodeManage::setScript(yd::adv::ExtendScript *script) {
  m_script = script;
  auto name = m_script->script_name;
  auto type = m_script->script_type;
  auto file = YDProjectManage::getExtendableScriptCodeFilePath(name, type);
  auto filestr = QString::fromLocal8Bit(file.c_str());
  auto code = YDHelper::readFile(filestr);
  if (code.isEmpty()) {
    if (type == SCRIPT_TYPE_VB_NET)
      code = YDProjectManage::getVbCode();
    else
      code = YDProjectManage::getVcCode();
    QString str = QString("YDTemp_%1").arg(YDHelper::genarateTail());
    code.replace("YDTemplate", str);
  }

  m_codeW->setText(code);
}

void YDCodeManage::closeEvent(QCloseEvent *) {
  if (!m_isSaved) {
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
  m_isSaved = true;
  auto name = m_script->script_name;
  auto type = m_script->script_type;
  auto code = m_codeW->getText();
  auto file = YDProjectManage::getExtendableScriptCodeFilePath(name, type);
  auto filestr = QString::fromLocal8Bit(file.c_str());

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
  auto ret = QString::fromLocal8Bit(result.c_str());
  emit sigResult(ret);
}
