#include "tablemodel.h"

TableModel::TableModel(QObject *parent) : QAbstractTableModel (parent)  //QAbstractTableModel
{
    _data = new QList<TestObjectClass*>();
}

TableModel::~TableModel()
{
    delete _data;
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    return _rowCount;
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    return _columnCount;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    //qDebug() << "data(): index:" << index;
    if (!index.isValid())
        return QVariant();

    int row = index.row();
    int column = index.column();

    if (row >= _headerLabelsV.count())
        return QVariant();
    if (column >= _headerLabelsH.count())
        return QVariant();

    QString key;
    QVariant value;
    switch (role) {
    case Qt::DisplayRole:
    case Qt::EditRole:
        key = _headerLabelsV.at(row);
        value = _data->at(column)->getData(key);
        break;
    case Qt::BackgroundRole: /// когда опроисходит обращение к роли фона - закрашиваю фон светолозеленным
        key = _headerLabelsV.at(row);
        if (_data->at(column)->getType(key))
            value = QBrush("#e3ffd1"); //#e8e8e8 //#ffdbdb //#ebebeb
        else
            value = QBrush("#f0f0f0");
        break;
    default:
        value = QVariant();
        break;
    }
    return value;
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    //qDebug() << "headerData(): section:" << section << orientation << _headerLabelsH.size() << _headerLabelsV.size();
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        if (section >= _headerLabelsH.size())
            return QVariant();
        return _headerLabelsH[section];
    }
    if (orientation == Qt::Vertical) {
        if (section >= _headerLabelsV.size())
            return QVariant();
        return _headerLabelsV[section];
    }

    return QVariant();
}


bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    //qDebug() << "setData(): QVariant" << value.type();
    if (!index.isValid())
        return false;

    int column = index.column();
    int row = index.row();
    if (role == Qt::EditRole) {
        QString key = _headerLabelsV.at(row);
        _data->at(column)->editData(key, value);
        emit dataChanged(index, index);
        return true;
    }
//        if (role == Qt::DisplayRole) {
//            return _data.value(index, QVariant());
//        }
    return false;
}

bool TableModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    //qDebug() << "setHeaderData" << value;
    if (role != Qt::EditRole || section < 0)
        return false;
    if (orientation == Qt::Horizontal) {
        _headerLabelsH.append(value.toString());
    }
    if (orientation == Qt::Vertical) {
        _headerLabelsV.append(value.toString());
    }

    emit headerDataChanged(orientation, section, section);
    return true;
}

void TableModel::setColumnCount(const int &columnCount)
{
    _columnCount = columnCount;
}

void TableModel::setRowCount(const int &rowCount)
{
    _rowCount = rowCount;
}

void TableModel::addObject(TestObjectClass &object)
{
    /// в горизонтальный заголовок идет имя объекта
    /// в вертикальный заголовок идет название ключей
    setHeaderData(0, Qt::Horizontal, object.name());
    int count = object.count();
    for (int i = 0; i < count; i++) {
        QString key = object.getKeyByIndex(i);
        if (_headerLabelsV.indexOf(key) < 0) {
            setHeaderData(1, Qt::Vertical, key);            
            _rowCount++;
        }
    }
    _columnCount++;

    /// добавление объекта в список модели
    //beginInsertRows(QModelIndex (), _data->size(), _data->size());
    _data->append(&object);
    //endInsertRows();
}

void TableModel::clear()
{
    _data->clear();
    _headerLabelsH.clear();
    _headerLabelsV.clear();
    _rowCount = 0;
    _columnCount = 0;
    emit dataChanged(QModelIndex(), QModelIndex());
    emit headerDataChanged(Qt::Orientation(), int(), int());
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    int row = index.row();
    int column = index.column();

    if (row >= _headerLabelsV.count())
        return Qt::NoItemFlags;
    if (column >= _headerLabelsH.count())
        return Qt::NoItemFlags;

    QString key = _headerLabelsV.at(row);
    /// если данных нет, сообщаем вьюверу, что ячейка блокируется для взаимодействий
    if (!_data->at(column)->getType(key))
        return Qt::NoItemFlags;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}


