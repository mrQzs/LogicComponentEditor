#ifndef YDMODULELISTWIDGET_H
#define YDMODULELISTWIDGET_H

#include <QListWidget>

class YDModule;
class YDTask;
class QMenu;

class YDModuleListWidget : public QListWidget {
  Q_OBJECT
 public:
  explicit YDModuleListWidget(YDTask *task, QWidget *parent = nullptr);

 public:
  static QString mimeType();
  void addModule(YDModule *m, int row = -1);
  void insertModule(YDModule *m, int row = -1);
  void setTask(YDTask *task);

  // QListWidget interface
 protected:
  virtual void dragEnterEvent(QDragEnterEvent *e) override;
  virtual void dragMoveEvent(QDragMoveEvent *e) override;
  virtual void dropEvent(QDropEvent *e) override;
  virtual void startDrag(Qt::DropActions sa) override;
  Qt::DropActions supportedDropActions() const;

 private slots:
  void slotMenu(const QPoint &pos);
  void slotRemoveModule(bool);
  void slotItemClick(QListWidgetItem *item);
  void slotChangeItemSize(YDModule *);

 private:
  QMenu *m_menu;
  YDTask *m_task;
};

#endif  // YDMODULELISTWIDGET_H
