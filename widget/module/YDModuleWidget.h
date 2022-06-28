#ifndef YDMODULEWIDGET_H
#define YDMODULEWIDGET_H

#include <QWidget>

class YDModule;

class YDModuleWidget : public QWidget {
  Q_OBJECT
 public:
  explicit YDModuleWidget(YDModule *m, const QColor &bgColor,
                          const QColor &fontColor, QWidget *parent = nullptr);
  ~YDModuleWidget();

  void setText(const QString &text);

  // QWidget interface
 protected:
  void paintEvent(QPaintEvent *);

 private:
  QString m_text;
  YDModule *m_module;
  QColor m_color;
  QColor m_fontColor;
  QString m_text1;
  QPixmap m_pix;
};

#endif  // YDMODULEWIDGET_H
