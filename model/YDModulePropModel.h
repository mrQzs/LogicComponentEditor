#ifndef YDMODULEPROPMODEL_H
#define YDMODULEPROPMODEL_H

#include <QAbstractItemModel>
#include <QStyledItemDelegate>

class YDModule;

class YDModulePropModel : public QAbstractItemModel {
  Q_OBJECT
 public:
  explicit YDModulePropModel(QObject *parent = nullptr);

  // QAbstractItemModel interface
 public:
  QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  QModelIndex index(int row, int column, const QModelIndex &parent) const;
  QModelIndex parent(const QModelIndex &child) const;
  int rowCount(const QModelIndex &parent) const;
  int columnCount(const QModelIndex &parent) const;
  QVariant data(const QModelIndex &index, int role) const;
  Qt::ItemFlags flags(const QModelIndex &index) const;

 public:
  void setModule(YDModule *m);
  void updateView();

 private:
  YDModule *m_module;
};

class YDPropertyDelegate : public QStyledItemDelegate {
 public:
  YDPropertyDelegate(QObject *parent = nullptr);

  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                        const QModelIndex &index) const override;
  void setEditorData(QWidget *editor, const QModelIndex &index) const override;
  void setModelData(QWidget *editor, QAbstractItemModel *model,
                    const QModelIndex &index) const override;

 protected:
  QSize sizeHint(const QStyleOptionViewItem &option,
                 const QModelIndex &index) const override;
};

#endif  // YDMODULEPROPMODEL_H
