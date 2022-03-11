#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QStandardItemModel>

#include "testobjectclass.h"
#include "tablemodel.h"
#include "tabledelegate.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QList<TestObjectClass> obects;

private slots:
    void setDataFromObjects(); /// определяются объекты с данными и заносятся в модель
    void infoCells(const QModelIndex &topLeft, const QModelIndex &bottomRight); //const QStandardItem &item

    void on_setDataButton_clicked();
    void on_tableView_pressed(const QModelIndex &index);

    void on_pushButton_2_clicked();

private:
    //QStandardItemModel *model;
    TableModel *model;

    QList<TestObjectClass *> objList; /// список указателей на созданные объекты


    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
