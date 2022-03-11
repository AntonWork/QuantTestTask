#ifndef TABLEDELEGATE_H
#define TABLEDELEGATE_H

#include <QStyledItemDelegate>
#include <QObject>
#include <QDebug>

#include <QAbstractItemView>
#include <QPainter>
#include <QCheckBox>
#include <QApplication>
#include <QBoxLayout>
#include <QLabel>

#include "checkboxeditor.h"

class TableDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    TableDelegate(QObject* parent = nullptr);

    // QAbstractItemDelegate interface
public:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

};

#endif // TABLEDELIGATE_H
