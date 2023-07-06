/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/07/04 00:31
*******************************************************************************/

#include <QComboBox>
#include <QFontDatabase>
#include <QStyleFactory>

#include "SettingDialog.h"
#include "ui_SettingDialog.h"

enum ListItems {
    Fount,
    Theme
};

SettingDialog::SettingDialog(QWidget *parent) : QDialog(parent),ui(new Ui::SettingDialog){
    ui->setupUi(this);

    QObject::connect(ui->listWidget, &QListWidget::itemSelectionChanged, [&]() {
        // 在这里执行特定功能

        switch (ui->listWidget->currentRow()) {
            case ListItems::Fount:
                qDebug() << "字体";
                SetFount();
                break;
            case ListItems::Theme:
                qDebug() << "主题";
                SetTheme();
                break;
            default:
                break;
        }
    });


}

SettingDialog::~SettingDialog() {
    delete ui;
}

void SettingDialog::SetFount() {
    ClearWindow();
    QComboBox *box = new QComboBox(ui->widget);
    box->move(100,100);
    QComboBox *fount_size_box = new QComboBox(ui->widget);
    fount_size_box->move(200,200);

    /* //列出系统支持的所有字体的名称
    foreach(const QString & family, database.families())
    {
        qDebug() << family;
    }
    */
    // 列出系统支持的所有中文字体的名称
    foreach(const QString & family, QFontDatabase::families(QFontDatabase::SimplifiedChinese)) {
            box->addItem(family);
    }
    for (int i = 5;i < 30; ++i) {
        fount_size_box->addItem(std::to_string(i).c_str());
    }

    box->show();
    fount_size_box->show();

    connect(box,&QComboBox::currentTextChanged,[=](QString choose_text){
        qDebug() << choose_text;
        emit SetTextFont(choose_text);
    });
    connect(fount_size_box,&QComboBox::currentTextChanged,[=](QString choose_text){
        qDebug() << choose_text;
        emit SetTextFontSize(choose_text);
    });

}

void SettingDialog::SetTheme() {
    ClearWindow();
    QComboBox *box = new QComboBox(ui->widget);
    for (auto theme : QStyleFactory::keys()) {
        qDebug() << theme;
        box->addItem(theme);
    }
    box->show();

    connect(box,&QComboBox::currentTextChanged,[=](const QString choose_text){
        setStyle(QStyleFactory::create(choose_text));
        qDebug() << choose_text;
    });

}

void SettingDialog::ClearWindow() {
    QLayout* layout = ui->widget->layout(); // 获取QWidget上的布局
    if (layout) {
        while (QLayoutItem* item = layout->takeAt(0)) {
            delete item->widget();
            delete item;
        }
    }

// 删除非布局管理的子部件
    QList<QWidget*> childWidgets = ui->widget->findChildren<QWidget*>();
    for (QWidget* widget : childWidgets) {
        if (widget->parent() == ui->widget) {
            delete widget;
        }
    }

}