#ifndef YDDEVICEOUTPUTMODEL_H
#define YDDEVICEOUTPUTMODEL_H

#include <QAbstractTableModel>
#include <QStyledItemDelegate>

#include "yd_project.h"

class YDDeviceOutputModel : public QAbstractTableModel {
  Q_OBJECT
 public:
  explicit YDDeviceOutputModel(QObject *parent = nullptr);

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
  void updateModel(const std::vector<yd::dev::MCDOGroup *> &list);
  void cleaerModel();

 private:
  int getGroupIndex(int index) const;
  yd::dev::MCDO *getMCDO(int index) const;

 private:
  std::vector<yd::dev::MCDOGroup *> m_doList;
};

class YDDeviceOutputDelegate : public QStyledItemDelegate {
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

#endif  // YDDEVICEOUTPUTMODEL_H
