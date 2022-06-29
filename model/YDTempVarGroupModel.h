#ifndef YDTEMPVARGROUPMODEL_H
#define YDTEMPVARGROUPMODEL_H

#include <QAbstractItemModel>
#include <QStyledItemDelegate>

class YDVariable;

class YDTempVarGroupModel : public QAbstractItemModel {
  Q_OBJECT

 public:
  explicit YDTempVarGroupModel(YDVariable *root, QObject *parent = nullptr);
  ~YDTempVarGroupModel();

 public:
  void setState(bool b);

  // QAbstractItemModel interface
 public:
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role) const override;
  QModelIndex index(int row, int column,
                    const QModelIndex &parent) const override;
  QModelIndex parent(const QModelIndex &child) const override;
  int rowCount(const QModelIndex &parent) const override;
  int columnCount(const QModelIndex &parent) const override;
  QVariant data(const QModelIndex &index, int role) const override;
  bool setData(const QModelIndex &index, const QVariant &value, int role);
  Qt::ItemFlags flags(const QModelIndex &index) const;

 public:
  bool insertRows(int row, int count, const QModelIndex &parent);
  bool removeRows(int row, int count, const QModelIndex &parent);

  QModelIndex addTree(const QModelIndex &parent);
  QModelIndex addTree(int row, const QModelIndex &parent);
  void removeTree(QModelIndex &parent);

  void updateRoot(YDVariable *root);

 private:
  YDVariable *m_root;
  bool m_enable;
};

class YDTempVarGroupDeletegate : public QStyledItemDelegate {
  Q_OBJECT
 public:
  YDTempVarGroupDeletegate(QObject *parent = nullptr);

  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                        const QModelIndex &index) const override;
  void setEditorData(QWidget *editor, const QModelIndex &index) const override;
  void setModelData(QWidget *editor, QAbstractItemModel *model,
                    const QModelIndex &index) const override;
  bool editorEvent(QEvent *event, QAbstractItemModel *model,
                   const QStyleOptionViewItem &option,
                   const QModelIndex &index);

 protected:
  QSize sizeHint(const QStyleOptionViewItem &option,
                 const QModelIndex &index) const override;

 private slots:
  void commitAndCloseEditor();
};

#endif  // YDTEMPVARGROUPMODEL_H
