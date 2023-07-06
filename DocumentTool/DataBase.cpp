/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/07/06 23:13
*******************************************************************************/


#include <QSqlQuery>
#include <QSqlError>
#include <iostream>
#include "DataBase.h"

void DataBase::Create() {
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

}


void DataBase::Insert(std::string file_name,std::string file_path) {
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

void DataBase::Update() {
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

void DataBase::Delete() {
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
void DataBase::DeleteAllRecords() {
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

void DataBase::DropTable() {
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

std::vector<std::string> DataBase::Select(std::string file_path) {
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
