#include "testobjectclass.h"


TestObjectClass::TestObjectClass(const QString &objectName)
{
    this->objectName = objectName;
}

TestObjectClass::TestObjectClass(const QString &objectName, const QList<QString> &keyNames, const QList<QVariant::Type> &keyType, const QList<QVariant> &keyData)
{
    this->objectName = objectName;

    qDebug() << "" << Qt::endl;
    qDebug() << "Created new object:" << objectName;
    qDebug() << "-------------------------------";
    //keys = keyNames;
    StructData sData;
    for (int i = 0; i < keyNames.size(); ++i) {
        QVariant::Type _keyType = keyType.at(i);
        switch(_keyType)
        {
        case QVariant::Double:
            keys.append(keyNames.at(i));
            sData.type = _keyType;
            sData.dValue = (i < keyData.length()) ? keyData.at(i).toDouble() : NULL;
            data.insert(keyNames.at(i),sData);
            qDebug() << "key    = " << keyNames.at(i);
            qDebug() << "type   = " << sData.type;
            qDebug() << "dValue = " << sData.dValue;
            break;

        case QVariant::Bool:
            keys.append(keyNames.at(i));
            sData.type = _keyType;
            sData.bValue = (i < keyData.length()) ? keyData.at(i).toBool() : NULL;
            data.insert(keyNames.at(i),sData);
            qDebug() << "key    = " << keyNames.at(i);
            qDebug() << "type   = " << sData.type;
            qDebug() << "bValue = " << sData.bValue;
            break;

        case QVariant::String:
            keys.append(keyNames.at(i));
            sData.type = _keyType;
            sData.sValue = (i < keyData.length()) ? keyData.at(i).toString() : NULL;
            data.insert(keyNames.at(i),sData);
            qDebug() << "key    = " << keyNames.at(i);
            qDebug() << "type   = " << sData.type;
            qDebug() << "sValue = " << sData.sValue;
            break;

        default:
            qDebug() << "Не подходящий тип (Dooble, Bool, QString)";
            qDebug() << "key    = " << keyNames.at(i);
            qDebug() << "type   = " << _keyType;
            qDebug() << "sValue = " << keyData.at(i);
            //return;
            break;
        }

        qDebug() << "*";
    }
    qDebug() << "-------------------------------";
}

TestObjectClass::~TestObjectClass()
{
    qDebug() << "Удаление объекта:" << this->objectName;
}

bool TestObjectClass::setData(const QList<QString> &keyNames, const QList<QVariant::Type> &keyType, const QList<QVariant> &keyData)
{
    if (keyNames.count() < 0) return false;
    if (keyType.count() < 0) return false;

    keys.clear();
    data.clear();

    qDebug() << "" << Qt::endl;
    qDebug() << "setData for object:" << objectName;
    qDebug() << "-------------------------------";
    StructData sData;
    for (int i = 0; i < keyNames.size(); ++i) {
        QVariant::Type _keyType = keyType.at(i);
        switch(_keyType)
        {
        case QVariant::Double:
            keys.append(keyNames.at(i));
            sData.type = _keyType;
            sData.dValue = (i < keyData.length()) ? keyData.at(i).toDouble() : NULL;
            data.insert(keyNames.at(i),sData);
            qDebug() << "key    = " << keyNames.at(i);
            qDebug() << "type   = " << sData.type;
            qDebug() << "dValue = " << sData.dValue;
            break;

        case QVariant::Bool:
            keys.append(keyNames.at(i));
            sData.type = _keyType;
            sData.bValue = (i < keyData.length()) ? keyData.at(i).toBool() : NULL;
            data.insert(keyNames.at(i),sData);
            qDebug() << "key    = " << keyNames.at(i);
            qDebug() << "type   = " << sData.type;
            qDebug() << "bValue = " << sData.bValue;
            break;

        case QVariant::String:
            keys.append(keyNames.at(i));
            sData.type = _keyType;
            sData.sValue = (i < keyData.length()) ? keyData.at(i).toString() : NULL;
            data.insert(keyNames.at(i),sData);
            qDebug() << "key    = " << keyNames.at(i);
            qDebug() << "type   = " << sData.type;
            qDebug() << "sValue = " << sData.sValue;
            break;

        default:
            qDebug() << "Не подходящий тип (Dooble, Bool, QString)";
            qDebug() << "key    = " << keyNames.at(i);
            qDebug() << "type   = " << _keyType;
            qDebug() << "sValue = " << keyData.at(i);
            //return;
            break;
        }
        qDebug() << "*";
    }
    qDebug() << "-------------------------------";

    return true;

    //    this->keys = keyNames;
    //    this->types = keyType;
    //    this->values = keyData;
}



void TestObjectClass::editData(const QString &keyName, const QVariant &keyData)
{
    if (keys.indexOf(keyName) < 0)
        return;

    StructData strucntData = this->data.value(keyName);
    if (!strucntData.type)
        return;

    QVariant::Type type = strucntData.type;
    if (type == QVariant::Double) {
        strucntData.dValue = keyData.toDouble();
    }
    if (type == QVariant::Bool) {
        strucntData.bValue = keyData.toBool();
    }
    if (type == QVariant::String) {
        strucntData.sValue = keyData.toString();
    }

    data.insert(keyName, strucntData);
}

QVariant TestObjectClass::getData(const QString &key) const
{
    StructData _data = data.value(key);
    QVariant::Type _type = _data.type;

    if (_type == QVariant::Double) {
        return _data.dValue;
    }
    if (_type == QVariant::Bool) {
        return _data.bValue;
    }
    if (_type == QVariant::String) {
        return _data.sValue;
    }

    return QVariant();
}

QVariant TestObjectClass::getDataByIndex(const int &index) const
{
    return QVariant();
}



QList<QString> TestObjectClass::getKeys() const
{
    return this->keys;
}

int TestObjectClass::getIndexKey(const QString &key) const
{
    return keys.indexOf(key);
}

QString TestObjectClass::getKeyByIndex(const int &index) const
{
    if (index < 0 || index >= keys.count())
        return QString();
    return keys.at(index);
}

QVariant::Type TestObjectClass::getType(const QString &key)
{
    return data.value(key).type;
}

int TestObjectClass::count()
{
    return data.count();
}

QString TestObjectClass::name()
{
    return objectName;
}

