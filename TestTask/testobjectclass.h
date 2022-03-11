#ifndef TESTOBJECTCLASS_H
#define TESTOBJECTCLASS_H

#include <QObject>
#include <QDebug>

class TestObjectClass
{
private:
    struct StructData {
        QVariant::Type type;
        double dValue;
        bool bValue;
        QString sValue;
//        QVariant value;
//        QString type;
    };
    QString objectName = "empty";
    QList<QString> keys;
    QMap<QString, StructData> data; // набор данных ключ - значение


public:
    TestObjectClass(const QString &objectName);
    TestObjectClass(const QString &objectName, const QList<QString> &keyNames, const QList<QVariant::Type> &keyType, const QList<QVariant> &keyData);
    ~TestObjectClass();

//    QList<QString> keys;         // набор ключей
//    QList<QVariant::Type> types; // типы значений ключей
//    QList<QVariant> values;      // значения ключей

    /// функции задающие и меняющие данные объекта    
    bool setData(const QList<QString> &keyNames, const QList<QVariant::Type> &keyType, const QList<QVariant> &keyData);
    void editData(const QString &keyName, const QVariant &keyData);

    /// функции для получения данных из объекта
    QVariant getData(const QString &key) const;
    QVariant getDataByIndex(const int &index) const;

    /// функции для ключей
    QList<QString> getKeys() const;
    int getIndexKey(const QString &key) const;
    QString getKeyByIndex(const int &index) const;

    QVariant::Type getType(const QString &key);
    int count();
    QString name();
};

#endif // TESTOBJECTCLASS_H
