#ifndef YDCODEEDITOR_H
#define YDCODEEDITOR_H

#include <QWidget>

class QsciScintilla;
class YDModule;
class QToolBar;
class QTextEdit;
class QFrame;
class QAction;
class YDBuildOptDialog;
class QsciLexer;
class QTabWidget;

class YDCodeEditor : public QWidget {
  Q_OBJECT

 public:
  YDCodeEditor(QWidget *parent = nullptr);

 public:
  void setText(const QString &text);
  QString getText() const;
  void changeType(int type);
  int getBuildFram();
  int getBuildCpu();

 public slots:
  void slotResult(const QString &);

 signals:
  void sigSave();
  void sigCompile();

 private slots:
  void slotSaveClicked(bool);
  void slotPrewClicked(bool);
  void slotNextClicked(bool);
  void slotBuilderClicked(bool);
  void slotDialogFinished();
  void slotEditChanged();

 private:
  void initEditor();

 private:
  QToolBar *m_toolbar;
  QTabWidget *m_tabW;
  QsciScintilla *m_editor;
  QsciScintilla *m_editor1;
  QsciScintilla *m_editor2;
  QTextEdit *m_textEdit;
  QFrame *m_line1;
  QFrame *m_line2;
  QAction *m_save;
  QAction *m_prew;
  QAction *m_next;
  QAction *m_build;

  YDBuildOptDialog *m_optDialog;
  QsciLexer *m_textLexer;
  QsciLexer *m_textLexer1;
  QsciLexer *m_textLexer2;

  QString m_srcvb1;
  QString m_srcvb2;

  QString m_srcvc1;
  QString m_srcvc2;

  QString m_srccc1;
  QString m_srccc2;
};

#endif  // YDCODEEDITOR_H
