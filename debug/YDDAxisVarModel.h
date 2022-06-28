#ifndef YDDAXISVARMODEL_H
#define YDDAXISVARMODEL_H

#include <QAbstractTableModel>
#include <QStyledItemDelegate>

#include "platform.h"
#include "yddef.h"

class QPushButton;

class YDDAxisVarModel : public QAbstractTableModel {
  Q_OBJECT
 public:
  explicit YDDAxisVarModel(QObject *parent = nullptr);

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
  void updateData(const yd::COORDS &coords);
  void updateData(const QStringList &values);
  QStringList getValues() const;
  QStringList getInitValues() const;

 private:
  yd::COORDS m_coords;
  QStringList m_axisNames;
  QStringList m_values;
  QStringList m_initValues;
};

class YDDAxisVarDeletegate : public QStyledItemDelegate {
  Q_OBJECT

 public:
  explicit YDDAxisVarDeletegate(QStringList btnNames, QWidget *parent = 0);
  ~YDDAxisVarDeletegate();
  void paint(QPainter *painter, const QStyleOptionViewItem &option,
             const QModelIndex &index) const;
  bool editorEvent(QEvent *event, QAbstractItemModel *model,
                   const QStyleOptionViewItem &option,
                   const QModelIndex &index);

 signals:
  void sigShow(const QModelIndex &index);
  void sigStartJog(const QModelIndex &index);
  void sigStopJog(const QModelIndex &index);
  void sigStartDJog(const QModelIndex &index);
  void sigStopDJog(const QModelIndex &index);
  void sigMove(const QModelIndex &index);

 private:
  QPoint m_mousePoint;
  int m_nType;
  QStringList m_btnNames;
};

class YDDAxisVarDeletegate2 : public QStyledItemDelegate {
  Q_OBJECT
 public:
  explicit YDDAxisVarDeletegate2(QWidget *parent = nullptr);

  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                        const QModelIndex &index) const override;
  void setEditorData(QWidget *editor, const QModelIndex &index) const override;
  void setModelData(QWidget *editor, QAbstractItemModel *model,
                    const QModelIndex &index) const override;

 private slots:
  void commitAndCloseEditor();
};

#endif  // YDDAXISVARMODEL_H
