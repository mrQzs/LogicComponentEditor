#ifndef YDDVARIABLEMODEL_H
#define YDDVARIABLEMODEL_H

#include <QAbstractTableModel>
#include <QStyledItemDelegate>

#include "YDDgHelper.h"
#include "platform.h"
#include "yddef.h"

class QPushButton;

class YDDVariableModel : public QAbstractTableModel {
  Q_OBJECT
 public:
  explicit YDDVariableModel(QObject *parent = nullptr);

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
  void updateData(uint16 id);

  yd::vr::SystemVariable *getVar(int row);

 private:
  std::vector<yd::vr::SystemVariable *> m_varList;
  yd::proto::MapId2VariableRTValue m_stateMap;
};

class YDDVarDeletedage : public QStyledItemDelegate {
  Q_OBJECT

 public:
  explicit YDDVarDeletedage(QStringList btnNames, QWidget *parent = 0);
  ~YDDVarDeletedage();
  void paint(QPainter *painter, const QStyleOptionViewItem &option,
             const QModelIndex &index) const;
  bool editorEvent(QEvent *event, QAbstractItemModel *model,
                   const QStyleOptionViewItem &option,
                   const QModelIndex &index);

 signals:
  void sigPress(const QModelIndex &index);

 private:
  QPoint m_mousePoint;
  int m_nType;
  QStringList m_btnNames;
};

#endif  // YDDVARIABLEMODEL_H
