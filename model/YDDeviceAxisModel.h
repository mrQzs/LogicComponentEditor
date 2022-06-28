#ifndef YDDEVICEAXISMODEL_H
#define YDDEVICEAXISMODEL_H

#include <QAbstractTableModel>
#include <QStyledItemDelegate>

#include "yd_project.h"

class YDDeviceAxisModel : public QAbstractTableModel {
  Q_OBJECT
 public:
  explicit YDDeviceAxisModel(QObject *parent = nullptr);

  // QAbstractItemModel interface
 public:
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role) const override;
  int rowCount(const QModelIndex &parent) const;
  int columnCount(const QModelIndex &parent) const;
  QVariant data(const QModelIndex &index, int role) const;
  bool setData(const QModelIndex &index, const QVariant &value, int role);
  Qt::ItemFlags flags(const QModelIndex &index) const;

 public:
  void updateModel(const std::vector<yd::dev::MCAxis *> &list);
  void clearModel();

 private:
  std::vector<yd::dev::MCAxis *> m_axisList;
};

class YDDeviceAxisDelegate : public QStyledItemDelegate {
  Q_OBJECT
 public:
  using QStyledItemDelegate::QStyledItemDelegate;

  QSize sizeHint(const QStyleOptionViewItem &opt,
                 const QModelIndex &index) const override;

  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &opt,
                        const QModelIndex &index) const override;
  void setEditorData(QWidget *editor, const QModelIndex &index) const override;
  void setModelData(QWidget *editor, QAbstractItemModel *model,
                    const QModelIndex &index) const override;

 private slots:
  void commitAndCloseEditor();
  void commitAndCloseEditor2();
};

#endif  // YDDEVICEAXISMODEL_H
