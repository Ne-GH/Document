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

#include "MainWindow.h"
#include "ui_MainWindow.h"

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


void GetFilePath() {
    auto path = std::filesystem::current_path();
    path = path.parent_path().parent_path();
    std::filesystem::path hide_dir = "/dev/null";

    std::cout << path.string() << std::endl;
    auto base_path = path.string();
    int tab = (- std::count(base_path.begin(),base_path.end(),'/')-1) * 4;

        for (auto file : std::filesystem::recursive_directory_iterator(path)) {
            [&](int tab) {
                auto tmp = file.path().string();
                tab += std::count(tmp.begin(),tmp.end(),'/') * 4;
                if (file.is_directory()) {
                    if (file.path().filename().string()[0] == '.') {
                        hide_dir = file.path();
                    }
                    else if (file.path().string().find(hide_dir) != std::string::npos) {
                        ;
                    }
                    else {
                        std::cout << std::string(tab,' ') << file.path().filename().string() << std::endl;
                    }
                }
                else if (file.is_regular_file()) {
                    if (auto pos = file.path().string().find(hide_dir);pos != std::string::npos) {
                        ;
                    }
                        // 隐藏文件
                    else if (file.path().filename().string()[0] == '.') {
                        ;
                    }
                    else {
                        std::cout << std::string(tab,' ') << file.path().filename().string() << std::endl;
                    }
                }
            }(tab);
        }

}


void CppFileTree(Ui::MainWindow *ui) {
    //1，构造Model，这里示例具有3层关系的model构造过程
    QStandardItemModel* model = new QStandardItemModel(ui->treeView);
    model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("序号") << QStringLiteral("名称"));     //设置列头
    for(int i=0;i<5;i++)
    {
        //一级节点，加入mModel
        QList<QStandardItem*> items1;
        QStandardItem* item1 = new QStandardItem(QString::number(i));
        QStandardItem* item2 = new QStandardItem(QStringLiteral("一级节点"));
        items1.append(item1);
        items1.append(item2);
        model->appendRow(items1);

        for(int j=0;j<5;j++)
        {
            //二级节点,加入第1个一级节点
            QList<QStandardItem*> items2;
            QStandardItem* item3 = new QStandardItem(QString::number(j));
            QStandardItem* item4 = new QStandardItem(QStringLiteral("二级节点"));
            items2.append(item3);
            items2.append(item4);
            item1->appendRow(items2);

            for(int k=0;k<5;k++)
            {
                //三级节点,加入第1个二级节点
                QList<QStandardItem*> items3;
                QStandardItem* item5 = new QStandardItem(QString::number(k));
                QStandardItem* item6 = new QStandardItem(QStringLiteral("三级节点"));
                items3.append(item5);
                items3.append(item6);
                item3->appendRow(items3);
            }
        }
    }
    //2，给QTreeView应用model
    ui->treeView->setModel(model);

}

MainWindow::MainWindow(QWidget *parent) :
                        QMainWindow(parent), ui(new Ui::MainWindow){

    ui->setupUi(this);
    setCentralWidget(ui->splitter);

    auto database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("documents.db");
    if (!database.open()) {
        std::cout << "打开数据库失败" << std::endl;
        qDebug() << database.lastError().text();
    }

    std::string table_name = "documents_table";
    if(database.tables().contains(table_name.c_str())){
        qDebug() << "表存在";

//        GetFilePath();


    }
    else {
//        qDebug() << "表不存在";
        QSqlQuery query(
                (std::string("CREATE TABLE ") + table_name.c_str() +
                    "(id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "file_name TEXT, "
                    "file_path TEXT, "
                    "file_size INTEGER)").c_str());
        if(query.isActive()) {
            qDebug() << "创建成功" ;
        }
        else {
            qDebug() << "创建失败" ;
            qDebug() << query.lastError().text();
        }

    }


//    QtFileTree(ui);

    CppFileTree(ui);

    ui->treeView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->splitter->setStretchFactor(0,1);
    ui->splitter->setStretchFactor(1,9);



}



