#ifndef YDSAFEVARIABLEMODEL_H
#define YDSAFEVARIABLEMODEL_H

#include <QAbstractTableModel>
#include <QStyledItemDelegate>

#include "yddef.h"

class YDSafeVariableModel : public QAbstractTableModel {
  Q_OBJECT
 public:
  explicit YDSafeVariableModel(QObject *parent = nullptr);

  // QAbstractItemModel interface
 public:
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role) const override;
  int rowCount(const QModelIndex &parent) const;
  int columnCount(const QModelIndex &parent) const;
  QVariant data(const QModelIndex &index, int role) const;
  Qt::ItemFlags flags(const QModelIndex &index) const;

  void setGroupId(uint16 id);

 private:
  uint16 m_groupId;
};

#endif  // YDSAFEVARIABLEMODEL_H
