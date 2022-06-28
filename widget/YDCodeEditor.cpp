#include "YDCodeEditor.h"

#include <QCoreApplication>
#include <QHBoxLayout>
#include <QTabWidget>
#include <QTextEdit>
#include <QToolBar>
#include <QVBoxLayout>

#include "Qsci/qsciapis.h"
#include "Qsci/qscilexercpp.h"
#include "Qsci/qscilexercsharp.h"
#include "Qsci/qscilexervb.h"
#include "Qsci/qsciscintilla.h"
#include "YDBuildOptDialog.h"
#include "common/YDHelper.h"

YDCodeEditor::YDCodeEditor(QWidget *parent)
    : QWidget{parent},
      m_toolbar{new QToolBar(this)},
      m_tabW{new QTabWidget(this)},
      m_editor{new QsciScintilla(this)},
      m_editor1{new QsciScintilla(this)},
      m_editor2{new QsciScintilla(this)},
      m_textEdit{new QTextEdit(this)},
      m_line1{new QFrame(this)},
      m_line2{new QFrame(this)},
      m_optDialog{new YDBuildOptDialog(this)},
      m_textLexer{nullptr},
      m_textLexer1{nullptr},
      m_textLexer2{nullptr} {
  m_toolbar->setStyleSheet("background:#ffffff;");

  initEditor();

  m_line1->setFrameShape(QFrame::HLine);
  m_line1->setFrameShadow(QFrame::Sunken);

  m_line2->setFrameShape(QFrame::HLine);
  m_line2->setFrameShadow(QFrame::Sunken);

  m_toolbar->setFixedHeight(26);
  m_textEdit->setFixedHeight(100);
  m_textEdit->setReadOnly(true);
  m_editor->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  m_save =
      m_toolbar->addAction(QIcon(":/Icon/disk.png"), YDCodeEditor::tr("保存"),
                           this, SLOT(slotSaveClicked(bool)));
  m_prew =
      m_toolbar->addAction(QIcon(":/Icon/undo.png"), YDCodeEditor::tr("回退"),
                           this, SLOT(slotPrewClicked(bool)));
  m_next =
      m_toolbar->addAction(QIcon(":/Icon/redo.png"), YDCodeEditor::tr("前进"),
                           this, SLOT(slotNextClicked(bool)));

  m_save->setShortcut(
      QCoreApplication::translate("YDCodeEditor", "Ctrl+S", nullptr));

  m_build = m_toolbar->addAction(QIcon(":/Icon/Debug.png"),
                                 YDCodeEditor::tr("编辑选项"), this,
                                 SLOT(slotBuilderClicked(bool)));

  m_prew->setDisabled(true);
  m_next->setDisabled(true);

  m_prew->setToolTip(YDCodeEditor::tr("撤销"));
  m_next->setToolTip(YDCodeEditor::tr("恢复"));

  auto *vly = new QVBoxLayout(this);
  vly->setContentsMargins(0, 0, 0, 0);
  vly->setSpacing(0);
  vly->addWidget(m_toolbar);
  vly->addWidget(m_line1);
  vly->addWidget(m_tabW);
  vly->addWidget(m_line2);
  vly->addWidget(m_textEdit);

  connect(m_optDialog, &YDBuildOptDialog::finished, this,
          &YDCodeEditor::slotDialogFinished);

  connect(m_editor, SIGNAL(textChanged()), this, SLOT(slotEditChanged()));
}

void YDCodeEditor::setText(const QString &text) { m_editor->setText(text); }

QString YDCodeEditor::getText() const { return m_editor->text(); }

void YDCodeEditor::changeType(int type) {
  if (m_textLexer) delete m_textLexer;
  if (m_textLexer1) delete m_textLexer1;
  if (m_textLexer2) delete m_textLexer2;

  m_editor1->clear();
  m_editor2->clear();

  switch (type) {
    case 0: {
      QString finename =
          QCoreApplication::applicationDirPath() + "/codeTips/VbWord";

      m_textLexer = new QsciLexerVB;
      QsciAPIs *apis = new QsciAPIs(m_textLexer);
      apis->load(finename);
      apis->prepare();

      m_textLexer1 = new QsciLexerVB;
      QsciAPIs *apis1 = new QsciAPIs(m_textLexer1);
      apis1->load(finename);
      apis1->prepare();

      m_textLexer2 = new QsciLexerVB;
      QsciAPIs *apis2 = new QsciAPIs(m_textLexer2);
      apis2->load(finename);
      apis2->prepare();

      m_editor1->setText(m_srcvb1);
      m_editor2->setText(m_srcvb2);
    } break;
    case 1: {
      QString finename =
          QCoreApplication::applicationDirPath() + "/codeTips/CsharpWord";

      m_textLexer = new QsciLexerCSharp;
      QsciAPIs *apis = new QsciAPIs(m_textLexer);
      apis->load(finename);
      apis->prepare();

      m_textLexer1 = new QsciLexerCSharp;
      QsciAPIs *apis1 = new QsciAPIs(m_textLexer1);
      apis1->load(finename);
      apis1->prepare();

      m_textLexer2 = new QsciLexerCSharp;
      QsciAPIs *apis2 = new QsciAPIs(m_textLexer2);
      apis2->load(finename);
      apis2->prepare();

      m_editor1->setText(m_srcvc1);
      m_editor2->setText(m_srcvc2);
    } break;
    case 2: {
      QString finename =
          QCoreApplication::applicationDirPath() + "/codeTips/CppWord";

      auto src1 = YDHelper::readFile(QCoreApplication::applicationDirPath() +
                                     "/scripts/include/yd_motion_api.h");
      auto src2 =
          YDHelper::readFile(QCoreApplication::applicationDirPath() +
                             "/scripts/include/yd_motion_collections.h");
      m_editor1->setText(src1);
      m_editor2->setText(src2);
    } break;

    default:
      break;
  }

  m_editor->setLexer(m_textLexer);
  m_editor1->setLexer(m_textLexer1);
  m_editor2->setLexer(m_textLexer2);
}

int YDCodeEditor::getBuildFram() { return m_optDialog->getStruct(); }

int YDCodeEditor::getBuildCpu() { return m_optDialog->getWay(); }

void YDCodeEditor::slotResult(const QString &ret) { m_textEdit->setText(ret); }

void YDCodeEditor::slotSaveClicked(bool) { emit sigSave(); }

void YDCodeEditor::slotPrewClicked(bool) {
  m_editor->undo();
  m_prew->setEnabled(m_editor->isUndoAvailable());
  m_next->setEnabled(m_editor->isRedoAvailable());
}

void YDCodeEditor::slotNextClicked(bool) {
  m_editor->redo();
  m_prew->setEnabled(m_editor->isUndoAvailable());
  m_next->setEnabled(m_editor->isRedoAvailable());
}

void YDCodeEditor::slotBuilderClicked(bool) {
  emit sigSave();
  m_optDialog->open();
}

void YDCodeEditor::slotDialogFinished() {
  if (m_optDialog->result() == QDialog::Accepted) {
    emit sigCompile();
  }
}

void YDCodeEditor::slotEditChanged() {
  m_prew->setEnabled(m_editor->isUndoAvailable());
  m_next->setEnabled(m_editor->isRedoAvailable());
}

void YDCodeEditor::initEditor() {
  m_editor1->setReadOnly(true);
  m_editor2->setReadOnly(true);

  m_srcvb1 = YDHelper::readFile(QCoreApplication::applicationDirPath() +
                                "/scripts/include/yd_motion_api.vb");
  m_srcvb2 = YDHelper::readFile(QCoreApplication::applicationDirPath() +
                                "/scripts/include/yd_motion_collections.vb");

  m_srcvc1 = YDHelper::readFile(QCoreApplication::applicationDirPath() +
                                "/scripts/include/yd_motion_api.cs");
  m_srcvc2 = YDHelper::readFile(QCoreApplication::applicationDirPath() +
                                "/scripts/include/yd_motion_collections.cs");

  //设置编号为0的页边显示行号
  m_editor->setMarginType(0, QsciScintilla::NumberMargin);
  m_editor->setMarginLineNumbers(0, true);
  m_editor->setMarginWidth(0, 35);
  m_editor->SendScintilla(QsciScintilla::SCI_SETCODEPAGE,
                          QsciScintilla::SC_CP_UTF8);

  m_editor1->setMarginType(0, QsciScintilla::NumberMargin);
  m_editor1->setMarginLineNumbers(0, true);
  m_editor1->setMarginWidth(0, 35);
  m_editor1->SendScintilla(QsciScintilla::SCI_SETCODEPAGE,
                           QsciScintilla::SC_CP_UTF8);

  m_editor2->setMarginType(0, QsciScintilla::NumberMargin);
  m_editor2->setMarginLineNumbers(0, true);
  m_editor2->setMarginWidth(0, 35);
  m_editor2->SendScintilla(QsciScintilla::SCI_SETCODEPAGE,
                           QsciScintilla::SC_CP_UTF8);

  changeType(0);

  m_editor->setAutoCompletionSource(QsciScintilla::AcsAll);
  m_editor->setAutoCompletionCaseSensitivity(true);
  m_editor->setAutoCompletionThreshold(2);
  m_editor->setAutoIndent(true);
  m_editor->setIndentationGuides(true);
  m_editor->setCaretLineVisible(true);
  m_editor->setCaretLineBackgroundColor(Qt::lightGray);
  m_editor->setMarginsBackgroundColor(Qt::gray);
  m_editor->setBraceMatching(QsciScintilla::SloppyBraceMatch);

  m_editor1->setAutoCompletionSource(QsciScintilla::AcsAll);
  m_editor1->setAutoCompletionCaseSensitivity(true);
  m_editor1->setAutoCompletionThreshold(2);
  m_editor1->setAutoIndent(true);
  m_editor1->setIndentationGuides(true);
  m_editor1->setCaretLineVisible(true);
  m_editor1->setCaretLineBackgroundColor(Qt::lightGray);
  m_editor1->setMarginsBackgroundColor(Qt::gray);
  m_editor1->setBraceMatching(QsciScintilla::SloppyBraceMatch);

  m_editor2->setAutoCompletionSource(QsciScintilla::AcsAll);
  m_editor2->setAutoCompletionCaseSensitivity(true);
  m_editor2->setAutoCompletionThreshold(2);
  m_editor2->setAutoIndent(true);
  m_editor2->setIndentationGuides(true);
  m_editor2->setCaretLineVisible(true);
  m_editor2->setCaretLineBackgroundColor(Qt::lightGray);
  m_editor2->setMarginsBackgroundColor(Qt::gray);
  m_editor2->setBraceMatching(QsciScintilla::SloppyBraceMatch);

  QFont font("Courier", 10, QFont::Normal);
  QFontMetrics fontmetrics = QFontMetrics(font);
  m_editor->setMarginWidth(0, fontmetrics.horizontalAdvance("000"));
  m_editor->setMarginLineNumbers(0, true);
  m_editor->setBraceMatching(QsciScintilla::SloppyBraceMatch);  //括号匹配
  m_editor->setTabWidth(4);

  m_editor1->setMarginWidth(0, fontmetrics.horizontalAdvance("000"));
  m_editor1->setMarginLineNumbers(0, true);
  m_editor1->setBraceMatching(QsciScintilla::SloppyBraceMatch);  //括号匹配
  m_editor1->setTabWidth(4);

  m_editor2->setMarginWidth(0, fontmetrics.horizontalAdvance("000"));
  m_editor2->setMarginLineNumbers(0, true);
  m_editor2->setBraceMatching(QsciScintilla::SloppyBraceMatch);  //括号匹配
  m_editor2->setTabWidth(4);

  QFont margin_font;
  margin_font.setFamily("SimSun");
  margin_font.setPointSize(11);
  m_editor->setMarginsFont(margin_font);  //设置页边字体
  m_editor->setMarginType(
      0, QsciScintilla::NumberMargin);  //设置标号为0的页边显示行号
  // m_editor->setMarginMarkerMask(0,QsciScintilla::Background);//页边掩码
  // m_editor->setMarginSensitivity(0,true);//设置是否可以显示断点,注册通知事件，当用户点击边栏时，scintilla会通知我们
  // textEdit->setMarginsBackgroundColor(QColor("#bbfaae"));
  //    m_editor->setMarginLineNumbers(0,true);//设置第0个边栏为行号边栏，True表示显示
  //    m_editor->setMarginWidth(0,15);//设置0边栏宽度
  m_editor->setMarginsBackgroundColor(Qt::gray);  //显示行号背景颜色
  m_editor->setMarginsForegroundColor(Qt::white);
  m_editor->setFolding(QsciScintilla::BoxedTreeFoldStyle);  //折叠样式
  m_editor->setFoldMarginColors(Qt::gray, Qt::lightGray);   //折叠栏颜色
  m_editor->setAutoCompletionSource(
      QsciScintilla::AcsAll);  //自动补全。对于所有Ascii字符
  // m_editor->setAutoCompletionCaseSensitivity(false);//大小写敏感度，设置lexer可能会更改，不过貌似没啥效果
  m_editor->setAutoCompletionThreshold(
      3);  //设置每输入一个字符就会出现自动补全的提示
  // m_editor->setAutoCompletionReplaceWord(false);//是否用补全的字符串替代光标右边的字符串

  m_editor1->setMarginsFont(margin_font);  //设置页边字体
  m_editor1->setMarginType(
      0, QsciScintilla::NumberMargin);  //设置标号为0的页边显示行号
  m_editor1->setMarginsBackgroundColor(Qt::gray);  //显示行号背景颜色
  m_editor1->setMarginsForegroundColor(Qt::white);
  m_editor1->setFolding(QsciScintilla::BoxedTreeFoldStyle);  //折叠样式
  m_editor1->setFoldMarginColors(Qt::gray, Qt::lightGray);   //折叠栏颜色
  m_editor1->setAutoCompletionSource(
      QsciScintilla::AcsAll);  //自动补全。对于所有Ascii字符
  m_editor1->setAutoCompletionThreshold(3);

  m_editor2->setMarginsFont(margin_font);  //设置页边字体
  m_editor2->setMarginType(
      0, QsciScintilla::NumberMargin);  //设置标号为0的页边显示行号
  m_editor2->setMarginsBackgroundColor(Qt::gray);  //显示行号背景颜色
  m_editor2->setMarginsForegroundColor(Qt::white);
  m_editor2->setFolding(QsciScintilla::BoxedTreeFoldStyle);  //折叠样式
  m_editor2->setFoldMarginColors(Qt::gray, Qt::lightGray);   //折叠栏颜色
  m_editor2->setAutoCompletionSource(
      QsciScintilla::AcsAll);  //自动补全。对于所有Ascii字符
  m_editor2->setAutoCompletionThreshold(3);

  m_tabW->addTab(m_editor, YDCodeEditor::tr("代码区"));
  m_tabW->addTab(m_editor1, YDCodeEditor::tr("参考1"));
  m_tabW->addTab(m_editor2, YDCodeEditor::tr("参考2"));
}
