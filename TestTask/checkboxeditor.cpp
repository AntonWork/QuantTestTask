#include "checkboxeditor.h"

#include <QPainter>
#include <QSpacerItem>



CheckBoxEditor::CheckBoxEditor(const Qt::CheckState &checkState, QWidget *parent) : QWidget(parent)
{
    this->setStyleSheet("background-color: #99d971");

    //QSpacerItem *spacer = new QSpacerItem(4, 0, QSizePolicy::Maximum, QSizePolicy::Expanding);

    label = new QLabel(this);
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    label->setMinimumWidth(30);
    label->setMinimumHeight(this->size().height());

    checkBoxEditor = new QCheckBox(this);
    checkBoxEditor->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    setData(checkState);
    QObject::connect(checkBoxEditor, &QCheckBox::stateChanged, this, &CheckBoxEditor::setTextLabel);


    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setSpacing(0);
//    /layout->addItem(spacer);
    layout->addWidget(label);
    layout->addWidget(checkBoxEditor);
    layout->setAlignment(Qt::AlignCenter); // Qt::AlignHorizontal_Mask | Qt::AlignVertical_Mask /// выравнивание
    layout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(layout);
}

void CheckBoxEditor::setTextLabel(const int &CheckState)
{
    if (CheckState == 0) {
        label->setText(" false");
        return;
    }
    if (CheckState == 2) {
        label->setText(" true");
        return;
    }
}

void CheckBoxEditor::setData(const Qt::CheckState &checkState)
{
    setTextLabel(checkState);
    checkBoxEditor->setCheckState(checkState);
}

Qt::CheckState CheckBoxEditor::checkState()
{
    return checkBoxEditor->checkState();
}

//void CheckBoxEditor::paintEvent(QPaintEvent *event)
//{
//    QPainter painter;
//    painter.setBrush(QBrush(QColor(255, 0, 0, 100)));
//}


