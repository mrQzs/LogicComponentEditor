#ifndef YDMODULEVIEW_H
#define YDMODULEVIEW_H

#include <QListView>

class YDModuleView : public QListView {
  Q_OBJECT
 public:
  explicit YDModuleView(QWidget *parent = nullptr);

 signals:

 public slots:

 protected:
  virtual void startDrag(Qt::DropActions supportedActions);
  virtual void dragEnterEvent(QEvent *);
};

#endif  // YDMODULEVIEW_H
