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



void CppFileTree(Ui::MainWindow *ui) {
    //1，构造Model，这里示例具有3层关系的model构造过程
    auto model = new QStandardItemModel(ui->treeView);
    //    model->setHorizontalHeaderLabels(QStringList {"x1","x2"});     //设置列头
    model->setHorizontalHeaderLabels(QStringList {"文件名"});     //设置列头


    auto path = std::filesystem::current_path();
    path = path.parent_path().parent_path();
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
        //                    std::cout << std::string(tab*4,' ') << file.path().filename().string() << std::endl;
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
        //                    std::cout << std::string(tab*4,' ') << file.path().filename().string() << std::endl;
                }
            }

            if (is_hide_file == true) {
                return;
            }
            auto it1 = new QStandardItem(file_name.c_str());
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

// 假设您已经有一个名为 treeView 的 QTreeView 实例

// 连接 clicked 信号到自定义的槽函数
    connect(ui->treeView, &QTreeView::clicked, this, [=] (const QModelIndex &index) {

        // 检查 index 是否有效
        if (index.isValid())
        {
            // 获取点击的模型索引所表示的数据
            QVariant data = index.data();

            // 在这里处理您需要的逻辑，比如显示数据、执行操作等
            qDebug() << "Clicked on item: " << data.toString();
        }
    });


}



