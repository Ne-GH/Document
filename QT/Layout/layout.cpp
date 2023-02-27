/*******************************************************************************
 * 这个文件只用来记录各种layout的使用方法
 * 本身并不具备什么运行支持
*******************************************************************************/

#include "mainwindow.h"
#include <QListWidget>

#include <QApplication>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QStackedLayout>
#include <QLabel>


/*******************************************************************************
 * 垂直布局
*******************************************************************************/
QWidget *VBoxLayout(){
    auto win = new QWidget;

    auto lab1 = new QLabel("lab1");
    auto lab2 = new QLabel("lab2");
    auto lab3 = new QLabel("lab3");

    lab1->setStyleSheet("QLabel{background:#dddddd;font:20px;}");
    lab1->setAlignment(Qt::AlignCenter);
    lab2->setStyleSheet("QLabel{background:#cccccc;font:20px;}");
    lab2->setAlignment(Qt::AlignCenter);
    lab3->setStyleSheet("QLabel{background:#ffffff;font:20px;}");
    lab3->setAlignment(Qt::AlignCenter);
    auto layout = new QVBoxLayout;
    layout->addWidget(lab1,1);
    layout->addWidget(lab2,2);
    layout->addWidget(lab3,3);
    win->setLayout(layout);
    return win;
}

/*******************************************************************************
 * 网格布局
*******************************************************************************/
QWidget *GridLayout(){

    auto grid_layout = new QGridLayout;

    auto push_button1 = new QPushButton("button1");
    auto push_button2 = new QPushButton("button2");
    auto push_button3 = new QPushButton("button3");
    auto push_button4 = new QPushButton("button4");
    auto push_button5 = new QPushButton("button5");

    grid_layout->addWidget(push_button1,0,0);
    grid_layout->addWidget(push_button2,0,2);
    grid_layout->addWidget(push_button3,1,0,3,3);
    grid_layout->addWidget(push_button4,4,0);
    grid_layout->addWidget(push_button5,4,2);

    auto win = new QWidget;
    win->setLayout(grid_layout);
    return win;
}

auto FormLayout() -> auto{

    auto win = new QWidget;

    auto form_layout = new QFormLayout;
    form_layout->addRow("Name:",new QLineEdit());
    form_layout->addRow("Email:",new QLineEdit());
    form_layout->addRow("Pass:",new QLineEdit());
    form_layout->setSpacing(1);
    form_layout->setRowWrapPolicy(QFormLayout::WrapAllRows);
    win->setLayout(form_layout);

    return win;

}

auto StackedLayout() -> auto
{
    auto win = new QWidget;

    auto layout = new QHBoxLayout();
    auto list_widget = new QListWidget(win);
    list_widget->addItem("QPushButton");
    list_widget->addItem("QLabel");
    list_widget->addItem("QLineEdit");

    auto widget_1 = new QWidget();
    auto push_button = new QPushButton("这是一个按钮",widget_1);


    auto widget_2 = new QWidget();
    auto line_edit = new QLineEdit("这是一个单行输入框",widget_2);

    auto widget_3 = new QWidget();
    auto lab = new QLabel("这是一个文本框",widget_3);
    widget_1->setMinimumSize(400,400);
    widget_2->setMinimumSize(400,400);
    widget_3->setMinimumSize(400,400);

    auto stacked_layout = new QStackedLayout();
    stacked_layout->addWidget(widget_1);
    stacked_layout->addWidget(widget_2);
    stacked_layout->addWidget(widget_3);



    layout->addWidget(list_widget,1);
    layout->addLayout(stacked_layout,4);



    win->setLayout(layout);
    QObject::connect(list_widget,&QListWidget::currentRowChanged,stacked_layout,&QStackedLayout::setCurrentIndex);

    return win;
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

//    auto v_window = VBoxLayout();
//    v_window->show();

//    auto grid_window = GridLayout();
//    grid_window->show();

//    auto form_window = FormLayout();
//    form_window->show();

    auto stacked_window = StackedLayout();
    stacked_window->show();


//    MainWindow w;
//    w.show();
    return a.exec();
}

/*
 *  额外批注:
 *  使用Qt 设计师的默认布局时,外边框存在间隙,可修改margin属性为0
 *  或在QWiget的构造函数中调用setContentsMargins()方法,将外边框设置为0
*/
