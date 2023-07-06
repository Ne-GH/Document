/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/07/06 23:13
*******************************************************************************/


#ifndef _DataBase_H_
#define _DataBase_H_


class DataBase {

public:
    static void Create();


    static std::vector<std::string> Select(std::string file_path);

    static void DropTable();

    static void Delete();

    static void Insert(std::string file_name, std::string file_path);

    static void Update();
};


#endif  // _DataBase_H_
