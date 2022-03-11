#ifndef CHECKBOXEDITOR_H
#define CHECKBOXEDITOR_H

#include <QDebug>
#include <QWidget>
#include <QCheckBox>
#include <QBoxLayout>
#include <QLabel>


class CheckBoxEditor : public QWidget
{
    Q_OBJECT
public:
    explicit CheckBoxEditor(const Qt::CheckState &checkState, QWidget *parent = nullptr);

private:
    QLabel *label;
    QCheckBox *checkBoxEditor;
signals:

public slots:
    void setTextLabel(const int &CheckState); /// меняет значение подписи
    void setData(const Qt::CheckState &checkState);
    Qt::CheckState checkState(); /// возвращает значение чекбокса

};

#endif // CHECKBOXEDITOR_H
