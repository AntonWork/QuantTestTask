#include "tabledelegate.h"



TableDelegate::TableDelegate(QObject* parent) : QStyledItemDelegate(parent)
{

}

QWidget *TableDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QVariant::Type type = index.data().type();
    if (type == QVariant::Invalid) {
        return NULL;
    }
    if (type == QVariant::Bool) {
        Qt::CheckState state = index.data().toBool() ? Qt::Checked : Qt::Unchecked;
        CheckBoxEditor *editor = new CheckBoxEditor(state, parent);
        return editor;
    }
    return QStyledItemDelegate::createEditor(parent, option, index);

}

void TableDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QVariant::Type type = index.data().type();
    if (type == QVariant::Bool) {
         Qt::CheckState state = index.data().toBool() ? Qt::Checked : Qt::Unchecked;
         CheckBoxEditor *_editor = qobject_cast<CheckBoxEditor *>(editor);
         _editor->setData(state);
         return;
    }

    QStyledItemDelegate::setEditorData(editor, index);
}

void TableDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QVariant::Type type = index.data().type();
    if (type == QVariant::Bool) {
        CheckBoxEditor *_editor = static_cast<CheckBoxEditor *>(editor);
        int value = (_editor->checkState()==Qt::Checked)? 1 : 0;
        model->setData(index, value, Qt::EditRole);
        return;
    }

    QStyledItemDelegate::setModelData(editor,model, index);
}



void TableDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{    
    QStyledItemDelegate::paint(painter, option, index);
    return;

}


