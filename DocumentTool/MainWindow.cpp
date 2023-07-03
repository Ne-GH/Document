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
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <fstream>

auto Select(std::string file_path) {
    QSqlQuery query;
    query.prepare("SELECT * FROM documents_table WHERE file_path = :filepath");
    query.bindValue(":filepath", file_path.c_str());
    std::vector<std::string> select_ret;
    if (query.exec()) {
        while (query.next()) {
            // 读取每一条记录的数据
            int id = query.value("id").toInt();
            QString fileName = query.value("file_name").toString();
            QString filePath = query.value("file_path").toString();
            int fileSize = query.value("file_size").toInt();
            // 处理数据...
            qDebug() << filePath;
            select_ret.push_back(fileName.toStdString());
        }
    } else {
        // 查询失败
    }
    return select_ret;
}

void Insert(std::string file_name,std::string file_path) {
//    query.prepare("INSERT INTO documents_table (file_name, file_path, file_size) "
//                  "SELECT :fileName, :filePath, :fileSize "
//                  "WHERE NOT EXISTS (SELECT 1 FROM documents_table WHERE file_name = :fileName)");
    QSqlQuery query;
    query.prepare("INSERT INTO documents_table (file_name, file_path, file_size) "
                  "VALUES (:fileName, :filePath, :fileSize)");
    query.bindValue(":fileName", file_name.c_str());
    query.bindValue(":filePath", file_path.c_str());
    query.bindValue(":fileSize", 1024);
    if (query.exec()) {
        qDebug() << "插入成功" ;
    }
    else {
        qDebug() << "插入失败" ;
        qDebug() << query.lastError().text();
    }
}

void Update() {
    QSqlQuery query;
    query.prepare("UPDATE documents_table SET file_name = :newFileName, file_path = :newFilePath "
                  "WHERE file_name = :oldFileName AND file_path = :oldFilePath");
    query.bindValue(":newFileName", "T");
    query.bindValue(":newFilePath", "../../");
    query.bindValue(":oldFileName", "QT");
    query.bindValue(":oldFilePath", "././");
    if (query.exec()) {
        if (query.numRowsAffected() > 0) {
            // 更新成功
            qDebug() << "Record updated";
        } else {
            // 没有满足条件的记录需要更新
            qDebug() << "No matching record found";
        }
    } else {
        // 更新失败
        qDebug() << "Update failed:" << query.lastError().text();
    }
}

void Delete() {
    QSqlQuery query;
    query.prepare("DELETE FROM documents_table WHERE file_name = :fileName AND file_path = :filePath");
    query.bindValue(":fileName", "QT");
    query.bindValue(":filePath", "././");
    if (query.exec()) {
        if (query.numRowsAffected() > 0) {
            // 删除成功
            qDebug() << "Record deleted";
        } else {
            // 没有满足条件的记录需要删除
            qDebug() << "No matching record found";
        }
    } else {
        // 删除失败
        qDebug() << "Deletion failed:" << query.lastError().text();
    }

}
void DeleteAllRecords() {
    QSqlQuery query;
    query.exec("DELETE FROM documents_table");
    if (query.isActive()) {
        // 删除成功
        qDebug() << "All records deleted";
    } else {
        // 删除失败
        qDebug() << "Deletion failed:" << query.lastError().text();
    }
}

void DropTable() {
    QSqlQuery query;
    query.exec("DROP TABLE documents_table");
    if (query.isActive()) {
        // 删除表成功
        qDebug() << "Table dropped";
    } else {
        // 删除表失败
        qDebug() << "Table drop failed:" << query.lastError().text();
    }
}

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
            if (Select(file_path_string).size() == 0) {
                Insert(file_name,file_path_string);
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

//    Select();


}



