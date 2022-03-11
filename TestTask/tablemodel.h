#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QObject>
#include <QDebug>
#include <QStandardItemModel>
#include <testobjectclass.h>


class TableModel : public QAbstractTableModel // QAbstractTableModel//QStandardItemModel
{
    Q_OBJECT
private:
    int _rowCount = 0;
    int _columnCount = 0;
protected:
    QList<TestObjectClass *> *_data; /// список объектов, с которыми работает модель
    //QHash<QModelIndex, TestObjectClass> *_data;
    QList<QString> _headerLabelsH; /// список горизонтальных заголовков
    QList<QString> _headerLabelsV; /// список вертикальных заголовков

public:
    explicit TableModel(QObject *parent = nullptr);
    ~TableModel();

//    enum Roles {
//        EmptyRole = Qt::UserRole + 1,
//        DataTypesRole = EmptyRole + 1
//    };

    int rowCount(const QModelIndex &parent) const; //virtual
    int columnCount(const QModelIndex &parent) const;

    /// модель сообщает о запрошенных данных
    QVariant data(const QModelIndex &index, int role) const;
    /// модель сообщает о запрошенных хаголовках
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;


    /// модель редактирует данные
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    /// модель редактирует данные заголовков
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole);
    /// модель определяет размерности
    void setColumnCount(const int &columnCount);
    void setRowCount(const int &rowCount);

    /// добавление объеквтов в модель
    void addObject(TestObjectClass &object);

    /// очистка модели
    void clear();

    Qt::ItemFlags flags(const QModelIndex &index) const;



signals:

};

#endif // TABLEMODEL_H
