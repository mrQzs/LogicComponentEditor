#ifndef YDDINPUTMODEL_H
#define YDDINPUTMODEL_H

#include <QAbstractTableModel>
#include <QStyledItemDelegate>

#include "platform.h"
#include "yd_project.h"
#include "yddef.h"

class YDDInputModel : public QAbstractTableModel {
  Q_OBJECT
 public:
  explicit YDDInputModel(QObject *parent = nullptr);

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
  void updateData();
  void setGroup(int id);

 private:
  int m_id;
  std::vector<yd::dev::IOInfo *> m_ioInfos;
  std::map<uint64, bool> m_mapState;
};

class YDDInputDeletegate : public QStyledItemDelegate {
  Q_OBJECT

 public:
  explicit YDDInputDeletegate(QWidget *parent = 0);
  void paint(QPainter *painter, const QStyleOptionViewItem &option,
             const QModelIndex &index) const;
};

#endif  // YDDINPUTMODEL_H
