#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new TableModel(this);
    QObject::connect(model, &TableModel::dataChanged, this, &MainWindow::infoCells);
    ui->tableView->setModel(model);

    ui->tableView->setItemDelegate(new TableDelegate(ui->tableView)); /// делегат для отображения ячейки
    ui->tableView->setEditTriggers(QAbstractItemView::CurrentChanged | QAbstractItemView::DoubleClicked); /// тригер на редактирование по единичному и по двойному нажатию мыши (AllEditTriggers - вообще на все действия с ячейкой)


//    modelTMP = new ModelTMP(this);
//    ui->tableView->setModel(modelTMP);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setDataFromObjects()
{
    for (int i = 0; i < objList.count(); i++) {
        delete objList.at(i);
    }
    objList.clear();
    model->clear();


//    model->setColumnCount(4);
//    model->setRowCount(5);

    TestObjectClass *obj1 = new TestObjectClass("Объект 1",
                                                {"Ключ 1", "Ключ 2"},
                                                {QVariant::Bool, QVariant::String},
                                                {false, "Hello"});
    TestObjectClass *obj2 = new TestObjectClass("Объект 2",
                                                {"Ключ 2", "Ключ 3", "Ключ 4"},
                                                {QVariant::Double, QVariant::Bool, QVariant::String },
                                                {1.75, true, "Я строка"});
    TestObjectClass *obj3 = new TestObjectClass("Объект 3",
                                                {"Ключ 1", "Ключ 3", "Ключ 5"},
                                                {QVariant::Bool, QVariant::Bool, QVariant::Bool },
                                                {true, true, false});

    TestObjectClass *obj4 = new TestObjectClass("Объект 4",
                                                {"Ключ 1", "Ключ 2", "Ключ 3", "Ключ 4", "Ключ 5"},
                                                {QVariant::Double, QVariant::Bool, QVariant::String, QVariant::String, QVariant::String },
                                                {NULL, true, "Строка", "Строка", "Строка"});

    model->addObject(*obj1);
    model->addObject(*obj2);
    model->addObject(*obj3);
    model->addObject(*obj4);

    //заношу объекты в список, чтобы можно было при нажжатии на ячейку (в on_tableView_pressed)
    //выводить данные объекта отдельно от таблицы
    objList.append(obj1);
    objList.append(obj2);
    objList.append(obj3);
    objList.append(obj4);
}

void MainWindow::infoCells(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
   // qDebug() << "Данные поменялись:" << topLeft.data();
}



void MainWindow::on_setDataButton_clicked()
{
    setDataFromObjects();
}


/// при нажатии на таблицу выводим данные объекта
void MainWindow::on_tableView_pressed(const QModelIndex &index)
{
     QVariant variantData = model->data(ui->tableView->currentIndex(), Qt::DisplayRole);
     int column = index.column();
     int row = index.row();
     QString objectName = model->headerData(column, Qt::Horizontal).toString();
     QString keyName = model->headerData(row, Qt::Vertical).toString();
     ui->infoCell->setText("Объект: " + objectName + "\n" +
                           "Ключ: " + keyName + "\n" +
                           "Значение: " + objList.at(column)->getData(keyName).toString() + "\n" +
                           "Тип: " + variantData.typeName());
}

void MainWindow::on_pushButton_2_clicked()
{
    for (int i = 0; i < objList.count(); i++) {
        delete objList.at(i);
    }
    objList.clear();
    model->clear();
    ui->tableView->repaint();
}
