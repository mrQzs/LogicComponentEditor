#ifndef YDVARIABLEMODEL_H
#define YDVARIABLEMODEL_H

#include <QAbstractTableModel>
#include <QStyledItemDelegate>

#include "yddef.h"

class YDVariableModel : public QAbstractTableModel {
  Q_OBJECT
 public:
  explicit YDVariableModel(QObject *parent = nullptr);

  // QAbstractItemModel interface
 public:
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role) const override;
  int rowCount(const QModelIndex &parent) const;
  int columnCount(const QModelIndex &parent) const;
  QVariant data(const QModelIndex &index, int role) const;
  bool setData(const QModelIndex &index, const QVariant &value, int role);
  Qt::ItemFlags flags(const QModelIndex &index) const;

  void setGroupId(uint16 id);

 private:
  uint16 m_groupId;
};

#endif  // YDVARIABLEMODEL_H
