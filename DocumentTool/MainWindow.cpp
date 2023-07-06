/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/06/30 15:11
*******************************************************************************/

#include <iostream>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <filesystem>
#include <QFileSystemModel>
#include <QStandardItemModel>
#include <QLineEdit>
#include <fstream>

#include "DataBase.h"
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "SettingDialog.h"


void QtFileTree(Ui::MainWindow *ui) {

    // 创建一个 QFileSystemModel 数据模型
    QFileSystemModel* model = new QFileSystemModel();
    model->setRootPath(""); // 设置根路径为当前目录

    QTreeView* treeView = ui->treeView;
    // 将数据模型设置给 QTreeView
    treeView->setModel(model);

    // 设置树状视图的根索引为数据模型的根索引
    treeView->setRootIndex(model->index(QDir::currentPath()));
    // 隐藏完整路径，仅显示文件名称
    treeView->setRootIndex(model->index(QDir::currentPath()));
    treeView->setColumnHidden(1, true); // 隐藏路径列
    treeView->setColumnHidden(2, true); // 隐藏大小列
    treeView->setColumnHidden(3, true); // 隐藏类型列
}



void CppFileTree(Ui::MainWindow *ui) {
    //1，构造Model，这里示例具有3层关系的model构造过程
    auto model = new QStandardItemModel(ui->treeView);
    //    model->setHorizontalHeaderLabels(QStringList {"x1","x2"});     //设置列头
    ui->treeView->header()->hide();


    auto path = std::filesystem::current_path();
//    path = path.parent_path().parent_path();
    path = "/home/yongheng/Projects/Document";
    std::filesystem::path hide_dir = "/dev/null";

    std::cout << path.string() << std::endl;
    auto base_path = path.string();
    int tab = (- std::count(base_path.begin(),base_path.end(),'/')-1);

    std::vector<std::vector<QStandardItem *>>vec;
    std::cout << path.filename().string() << std::endl;

    vec.push_back({new QStandardItem(path.filename().string().c_str())});
    model->appendRow(vec[0][0]);
    for (auto file : std::filesystem::recursive_directory_iterator(path)) {
        bool is_hide_file = false;
        [&](int tab) {
            auto file_path_string = file.path().string();
            auto file_name = file.path().filename().string();

            tab += std::count(file_path_string.begin(),file_path_string.end(),'/');
            if (file.is_directory()) {
                // 首次出现的隐藏文件夹
                if (file.path().filename().string()[0] == '.') {
                    hide_dir = file.path();
                    is_hide_file = true;
                }
                // 隐藏文件夹的子路径
                else if (file.path().string().find(hide_dir) != std::string::npos) {
                    is_hide_file = true;
                }
                else {
                    // std::cout << std::string(tab*4,' ') << file.path().filename().string() << std::endl;
                }
            }
            else if (file.is_regular_file()) {
                if (auto pos = file.path().string().find(hide_dir);pos != std::string::npos) {
                    is_hide_file = true;
                }
                    // 隐藏文件
                else if (file.path().filename().string()[0] == '.') {
                    is_hide_file = true;
                }
                else {
                    // std::cout << std::string(tab*4,' ') << file.path().filename().string() << std::endl;
                }
            }

            if (is_hide_file == true) {
                return;
            }
            if (DataBase::Select(file_path_string).size() == 0) {
                DataBase::Insert(file_name,file_path_string);
            }
            else {
                std::cout << "数据:" + file_name + "已经存在" << std::endl;
            }

            auto it1 = new QStandardItem(file_name.c_str());
            it1->setData(file_path_string.c_str(), Qt::UserRole);

            if (vec.size() <= tab+1) {
                vec.back().back()->appendRow(it1);
                vec.push_back({});  // vec.size ++
                vec.back().push_back(it1);
            }
            // tab = 2,
            else {
                vec[tab].back()->appendRow(it1);
                vec[tab+1].push_back(it1);
            }

        }(tab);
    }

    ui->treeView->setModel(model);

    // 点击项的信号槽连接
    QObject::connect(ui->treeView, &QTreeView::clicked, [=](const QModelIndex& index){
        if (index.isValid()) {
            ui->textEdit->clear();
            QVariant data = model->data(index, Qt::UserRole);
            QString filePath = data.toString();
            qDebug() << "Clicked File Path: " << filePath;
            // 禁用撤销和重做操作
            ui->textEdit->setUndoRedoEnabled(false);

            std::fstream file(filePath.toStdString(),std::ios::in);
            std::string text;
            while (getline(file,text)) {
                ui->textEdit->append(text.c_str());
            }
            QTextCursor cursor = ui->textEdit->textCursor();
            // 移动光标到文本的开头位置
            cursor.movePosition(QTextCursor::Start);
            ui->textEdit->setTextCursor(cursor);
            // 启用撤销和重做操作
            ui->textEdit->setUndoRedoEnabled(true);
        }

    });

    QObject::connect(ui->treeView, &QTreeView::doubleClicked, [=](const QModelIndex &index){
        if (index.isValid()) {
            ui->treeView->edit(index);
        }
    });

    QObject::connect(ui->treeView->itemDelegate(), &QAbstractItemDelegate::closeEditor, [=](QWidget* editor, QAbstractItemDelegate::EndEditHint hint){
        QLineEdit* lineEdit = qobject_cast<QLineEdit *>(editor);
        if (lineEdit) {
            QString newValue = lineEdit->text();
            qDebug() << "Edited value: " << newValue;
        }
    });

}

MainWindow::MainWindow(QWidget *parent) :
                        QMainWindow(parent), ui(new Ui::MainWindow){

    ui->setupUi(this);
    setCentralWidget(ui->splitter);

    ui->treeView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->splitter->setStretchFactor(0,2);
    ui->splitter->setStretchFactor(1,8);

    ui->read_only->setCheckable(true);
    ui->read_only->setChecked(true);
    ui->textEdit->setReadOnly(true);
    connect(ui->read_only,&QAction::triggered,[=]{
        if (!ui->read_only->isChecked()) {
            ui->read_only->setChecked(false);
            ui->textEdit->setReadOnly(false);
        }
        else {
            ui->read_only->setChecked(true);
            ui->textEdit->setReadOnly(true);
        }

    });


    DataBase::Create();

//    QtFileTree(ui);

    CppFileTree(ui);

//    Select();


    auto setting_dialog_action = new QAction("设置面板");
    ui->menu_bar->addAction(setting_dialog_action);
    auto settingDialog = new SettingDialog;
    connect(setting_dialog_action,&QAction::triggered,[=]{
        settingDialog->exec();
    });

    QObject::connect(settingDialog,&SettingDialog::SetTextFont,[=](QString font){
        ui->textEdit->setFontFamily(font);
        auto tmp = ui->textEdit->toPlainText();
        ui->textEdit->clear();
        ui->textEdit->setText(tmp);
    });
    QObject::connect(settingDialog,&SettingDialog::SetTextFontSize,[=](QString font){

        ui->textEdit->setFontPointSize(font.toInt());
        ui->textEdit->setFontFamily(font);
        auto tmp = ui->textEdit->toPlainText();
        ui->textEdit->clear();
        ui->textEdit->setText(tmp);
    });

}



