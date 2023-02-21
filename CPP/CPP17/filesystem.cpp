/*********************************************************************
 * Auther : yongheng
 * Date : 2022/10/02 21:43
*********************************************************************/

#include <iostream>
#include <chrono>
#include <fstream>
#include <filesystem>

using namespace std;

filesystem::path p;

/*********************************************************************
 * 判断路径
*********************************************************************/
void CheckPath(){
    /* 路径 */
    p = filesystem::path("/home/yongheng/Study/CPP/CPP17");
    /* 路径p是否是普通文件 */
    if(is_regular_file(p)){
        cout << p << " exists with " << file_size(p) << "bytes\n";
    }
        /* 是否是目录 */
    else if(is_directory(p)){
        cout << p << " is a directory containint:\n";
        for(const auto &e : filesystem::directory_iterator{p}){
            /* 会有双引号 */
            //  cout << " " << e.path() << "\n";
            /* 没有双引号 */
            cout << " " << e.path().string() << "\n";
        }

    }
        /* 路径p是否存在 */
    else if(exists(p)){
        cout << p << " is a special file\n";
    }
    else{
        cout << "path:" << p << "does not exist\n";
    }
}

/*********************************************************************
 * 用switch判断不同类型的文件
*********************************************************************/
void SwitchCheckDifferentFileType(){
    switch(status(p).type()){
        /* 不存在 */
        case filesystem::file_type::not_found:
            cout << "path: \"" << p.string() << "\" does not exist\n";
            break;
        /* 普通文件 */
        case filesystem::file_type::regular:
            cout << '"' << p.string() << "\" exists with " << file_size(p) << "bytes\n";
            break;
        /* 目录 */
        case filesystem::file_type::directory:
            std::cout << '"' << p.string() << "\" is a directory containing:\n";
            for (const auto& e : filesystem::directory_iterator{p}) {
                std::cout << " " << e.path().string() << '\n';
            }
            break;
        default:
            /* 特殊文件 */
            std::cout << '"' << p.string() << "\" is a special file\n";
            break;
    }
}

/*********************************************************************
 * 创建不同的文件类型
*********************************************************************/
void CreateDifferentTypeFile(){
    try{
        /* 如果目录dir不存在,则创建目录dir */
        filesystem::path dir("/home/yongheng/Project/untitled");
        /* create_directory(dir) ,只在已经存在的目录中创建目录 */
        /* 如果create_directories(dir),在dir目录存在时返回false */
        create_directories(dir);

        /* 创建data.txt文件 */
        auto file = dir / "data.txt";
        std::ofstream dataFile{file};
        if(!dataFile){
            std::cerr << "OOPS, can't open \"" << file.string() << "\"\n";
        }
        dataFile << "The answer is 42\n";

        /* 创建符号链接 tmp/slink/ , 指向tmp/test */
        /* create_directory_symlink,第一个参数的路径是以即将创建的符号链接所在的目录为起点的相对路径
         * create_symlink可代替上方函数,但是有些系统会进行一些优化,因此创建指向目录的符号链接时应该使用上方函数
         * 这个调用在windows上可能失败并导致错误处理,因为创建符号链接可能需要管理员权限
        */
        create_directory_symlink("test",dir.parent_path() / "slik");
    }
    catch (filesystem::filesystem_error & e){
        std::cerr << "EXCEPTION: " << e.what() << "\n";
        std::cerr << "\tpath1:\"" << e.path1().string() << "\"\n";
    }

    /* 递归打出所有文件 */
    std::cout << filesystem::current_path().string() << "\n";
    auto iterOputs(filesystem::directory_options::follow_directory_symlink);
    for(const auto &e : filesystem::recursive_directory_iterator(".",iterOputs)){
        std::cout << " " << e.path().lexically_normal().string() << "\n";
    }

}

/*********************************************************************
 * 异常处理
*********************************************************************/
void Error(){
    /*
     * create_directory 在文件存在时返回false,
     * 其他情况,例如没有权限创建目录,路径p无效,违反了文件系统限制等,会抛出异常
    */
    try{
        if(!create_directory(p)) {
            std::cout << p << " already exists\n";
        }
    }
    catch (const std::filesystem::filesystem_error & e){
        /* what返回特定的错误信息 */
        std::cout << "exception: " << e.what() << "\n";
        /* path1,获取错误相关的第一个路径,path2,获取错误相关的第二个路径 */
        std::cout << "\tpath: " << e.path1() << "\n";
    }

    std::error_code ec;
    /* 发生错误时,设置错误码 */
    create_directory(p,ec);
    if(ec){
        std::cout << "ERROR: " << ec.message() << "\n";
        /* 如果设置了特定的错误码 */
        if(ec == std::errc::read_only_file_system){
            std::cout << "ERROR: " << p << " is read-only\n";
        }
    }
}

/*********************************************************************
 * 文件类型
 * regualar:普通文件
 * directory:目录文件
 * symlink:符号链接文件
 * character:字符特殊文件
 * block:块特殊文件
 * fifo:FIFO或者管道文件
 * socket:套接字文件
 * ... :附加的实现定义的文件类型
 * none:文件类型未知
 * unknown:文件存在但是推断不出类型
 * not_found:虚拟的表示文件不存在的类型
*********************************************************************/

/*********************************************************************
 * 路径操作
 * path{ charseq }              用一个字符序列初始化路径
 * path{begin,end}              用一个范围初始化路径
 * u8path(u8string)             用一个UTF-8字符串初始化路径
 * current_path()               返回当前工作目录的路径
 * current_path(path)           设置当前工作目录为path
 * temp_directory_path()        返回临时文件的路径
 * current_path , temp_directory_path 开销均较大,因为依赖于系统调用
 * 用UTF-8字符串创建目录:
 * string utf8string = readUTF8String(...);
 * create_directory(filesystem::u8path(utf8string));
*********************************************************************/

/*********************************************************************
 * 检查路径
 * p.empty()                返回路径是否为空
 * p.is_absolute()          返回路径是否是绝对的
 * p.is_relative()          返回路径是否是相对的
 * p.has_filename()         返回路径是否既不是目录也不是根名称
 * p.has_stem()             同 has_filename()
 * p.has_extension()        返回路径是否有扩展名
 * p.has_root_name()        返回路径是否包含根名称
 * p.has_root_directory()   返回路径是否包含根目录
 * p.has_root_path()        返回路径是否包含根名称或根目录
 * p.has_parent_path()      返回路径是否包含父路径
 * p.has_relative_path()    返回路径是否不止包含根元素
 * p.filename()             返回文件名（或者空路径）
 * p.stem()                 返回没有扩展名的文件名（或者空路径）
 * p.extension()            返回扩展名（或者空路径）
 * p.root_name()            返回根名称（或者空路径）
 * p.root_directory()       返回根目录（或者空路径）
 * p.root_path()            返回根元素（或者空路径）
 * p.parent_path()          返回父路径（或者空路径）
 * p.relative_path()        返回不带根元素的路径（或者空路径）
 * p.begin()                返回路径元素的起点
 * p.end()                  返回路径元素的终点
*********************************************************************/

/*********************************************************************
 * 路径I/O
 * strm << p 用双引号括起来输出路径
 * strm >> p 读取用双引号括起来的路径
 * p.string() 以 std::string 返回路径
 * p.wstring() 以 std::wstring 返回路径
 * p.u8string() 以类型为 std::u8string 的 UTF8 字符串返回路径
 * p.u16string() 以类型为 std::u16string 的 UTF16 字符串返回路径
 * p.u32string() 以类型为 std::u32string 的 UTF32 字符串返回路径
 * p.string<...>() 以 std::basic_string<...> 返回路径
 * p.lexically_normal() 返回正规化的路径
 * p.lexically_relative(p2) 返回从 p2 到 p 的相对路径（如果没有则返回空路径）
 * p.lexically_proximate(p2) 返回从 p2 到 p 的路径（如果没有则返回 p）
*********************************************************************/

/*********************************************************************
 * 本地和通用格式的转换
 * p.generic_string() 返回 std::string 类型的通用路径
 * p.generic_wstring() 返回 std::wstring 类型的通用路径
 * p.generic_u8string() 返回 std::u8string 类型的通用路径
 * p.generic_u16string() 返回 std::u16string 类型的通用路径
 * p.generic_u32string() 返回 std::u32string 类型的通用路径
 * p.generic_string<...>() 返回 std::basic_string<...>() 类型的通用路径
 * p.native() 返回 path::string_type 类型的本地路径格式
 * 到本地路径的转换 到本地字符串类型的隐式转换
 * p.c_str() 返回本地字符串格式的字符序列形式的路径
 * p.make_preferred() 把 p 中的目录分隔符替换为本地格式的分隔符并返回修改后的 p
*********************************************************************/

/*********************************************************************
 * 遍历路径
*********************************************************************/
void IterateDirectory(){
    std::cout << "path elements of \"" << p.string() << "\":\n";
    for(std::filesystem::path elem : p){
       std::cout << " \"" << elem.string() << "\"";
    }
    cout << "\n";

    /* 同下面代码效果相同 */
    std::cout << "path emements of \"" << p.string() << "\" : \n";
    for(auto pos = p.begin(); pos != p.end(); ++pos){
        std::filesystem::path elem = *pos;
        cout << " \"" << elem.string() << "\"";
    }
    std::cout << "\n";

    /* 遍历目录中的所有文件 */
    for (const auto& e : std::filesystem::directory_iterator(p)) {
        std::cout << e.path() << '\n';
    }
    /* 递归遍历文件系统的子树 */
    for (const auto& e : std::filesystem::recursive_directory_iterator(p)) {
        std::cout << e.path() << '\n';
    }

}

/*********************************************************************
 * 修改路径
 * p = p2 赋予一个新路径
 *  p = sv 赋予一个字符串（视图）作为新路径
 *  p.assign(p2) 赋予一个新路径
 *  p.assign(sv) 赋予一个字符串（视图）作为新路径
 *  p.assign(beg, end) 赋予从 beg 到 end 的元素组成的路径
 *  p1 / p2 返回把 p2 作为子路径附加到 p1 之后的结果
 *  p /= sub 把 sub 作为子路径附加到路径 p 之后
 *  p.append(sub) 把 sub 作为子路径附加到路径 p 之后
 *  p.append(beg, end) 把从 beg 到 end 之间的元素作为子路径附加到路径 p 之后
 *  p += str 把 str 里的字符添加到路径 p 之后
 *  p.concat(str) 把 str 里的字符添加到路径 p 之后
 *  p.concat(beg, end) 把从 beg 到 end 之间的元素附加到路径 p 之后
 *  p.remove_filename() 移除路径末尾的文件名
 *  p.replace_filename(repl) 替换末尾的文件名（如果有的话）
 *  p.replace_extension() 移除末尾的文件的扩展名
 *  p.replace_extension(repl) 替换末尾的文件的扩展名（如果有的话）
 *  p.clear() 清空路径
 *  p.swap(p2) 交换两个路径
 *  swap(p1, p2) 交换两个路径
 *  p.make_preferred() 把 p 中的目录分隔符替换为本地格式的分隔符并返回修改后的 p
*********************************************************************/
void ModifyPath(){
   std::filesystem::path pp{"myfile"};
   pp += ".git";                    // pp: myfile.git
   pp /= ".git";                    // pp: myfile.git/.git
   p.concat("1");                 // pp: myfile.git/.git1
   p.append("1");             // pp: myfile.git/.git1/1

   auto p1 = std::filesystem::path("/usr") / "tmp";     // /usr/tmp  or  /usr\tmp
   auto p2 = std::filesystem::path("/usr/") / "tmp";    // /usr/tmp
   auto p3 = std::filesystem::path("/usr") / "/tmp";    // /tmp
   auto p4 = std::filesystem::path("/usr/") / "/tmp";   // /tmp
}

/*********************************************************************
 * 比较路径
 * p1 == p2 返回两个路径是否相等
 * p1 != p2 返回两个路径是否不相等
 * p1 < p2 返回一个路径是否小于另一个
 * p1 <= p2 返回一个路径是否小于等于另一个
 * p1 >= p2 返回一个路径是否大于等于另一个
 * p1 > p2 返回一个路径是否大于另一个
 * p.compare(p2) 返回 p 是小于、等于还是大于 p2
 * p.compare(sv) 返回 p 是小于、等于还是大于字符串（视图）sv 转换成的路径
 * equivalent(p1, p2) 访问实际文件系统的开销较大的比较操作
*********************************************************************/

/*********************************************************************
 * 其他路径操作
 * p.hash_value()   返回一个路径的哈希值
 * 只有相同的路径才会返回相同的哈希值,因此使用前应该先将路径进行正规化
*********************************************************************/

/*********************************************************************
 * 文件属性
 * exists(p)            返回是否存在一个可访问到的文件
 * is_symlink(p)        返回是否文件 p 存在并且是符号链接
 * is_regular_file(p)   返回是否文件 p 存在并且是普通文件
 * is_directory(p)      返回是否文件 p 存在并且是目录
 * is_other(p)          返回是否文件 p 存在并且不是普通文件或目录或符号链接
 * is_block_file(p)     返回是否文件 p 存在并且是块特殊文件
 * is_character_file(p) 返回是否文件 p 存在并且是字符特殊文件
 * is_fifo(p)           返回是否文件 p 存在并且是 FIFO 或者管道文件
 * is_socket(p)         返回是否文件 p 存在并且是套接字
 * is_empty()           返回文件是否为空
 * file_size()          返回文件大小(Byte)
 * hard_link_count(p)   返回硬链接数量
 * last_write_time(p)   返回最后一次修改文件的时间
*********************************************************************/

/*********************************************************************
 * 文件状态
 * status(p) 返回文件 p 的 file_status（解析符号链接）
 * symlink_status(p) 返回文件 p 的 file_status（不解析符号链接）
 * exists(fs) 返回是否有文件存在
 * is_regular_file(fs) 返回是否有文件存在并且是普通文件
 * is_directory(fs) 返回是否有文件存在并且是目录
 * is_symlink(fs) 返回是否有文件存在并且是符号链接
 * is_other(fs) 返回是否有文件存在并且不是普通文件或目录或符号链接
 * is_character_file(fs) 返回是否有文件存在并且是字符特殊文件
 * is_block_file(fs) 返回是否有文件存在并且是块特殊文件
 * is_fifo(fs) 返回是否有文件存在并且是 FIFO 或者管道文件
 * is_socket(fs) 返回是否有文件存在并且是套接字
 * fs.type() 返回文件的 file_type
 * fs.permissions() 返回文件的权限
*********************************************************************/


/*********************************************************************
 * 权限
 * none 0 没有权限集
 * owner_read 0400 S_IRUSR 所属用户有读权限
 * owner_write 0200 S_IWUSR 所属用户有写权限
 * owner_exec 0100 S_IXUSR 所属用户有执行/搜索权限
 * owner_all 0700 S_IRWXU 所属用户有所有权限
 * group_read 040 S_IRGRP 同组用户有读权限
 * group_write 020 S_IWGRP 同组用户有写权限
 * group_exec 010 S_IXGRP 同组用户有执行/搜索权限
 * group_all 070 S_IRWXG 同组用户有所有权限
 * others_read 04 S_IROTH 其他用户有读权限
 * others_write 02 S_IWOTH 其他用户有写权限
 * others_exec 01 S_IXOTH 其他用户有执行/搜索权限
 * others_all 07 S_IRWXO 其他用户有所有权限
 * all 0777 所有用户有所有权限
 * set_uid 04000 S_ISUID 运行时设置用户 ID
 * set_gid 02000 S_ISGID 运行时设置组 ID
 * sticky_bit 01000 S_ISVTX 操作系统特定
 * mask 07777 所有可能位的掩码
 * unknown 0xFFFF 未知权限
*********************************************************************/
void OutputPermission(){
    const std::filesystem::perms& pm = status(p).permissions();
    using perms = std::filesystem::perms;
    std::string s;
    s.resize(9);
    s[0] = (pm & perms::owner_read) != perms::none ? 'r' : '-';
    s[1] = (pm & perms::owner_write) != perms::none ? 'w' : '-';
    s[2] = (pm & perms::owner_exec) != perms::none ? 'x' : '-';
    s[3] = (pm & perms::group_read) != perms::none ? 'r' : '-';
    s[4] = (pm & perms::group_write) != perms::none ? 'w' : '-';
    s[5] = (pm & perms::group_exec) != perms::none ? 'x' : '-';
    s[6] = (pm & perms::others_read) != perms::none ? 'r' : '-';
    s[7] = (pm & perms::others_write) != perms::none ? 'w' : '-';
    s[8] = (pm & perms::others_exec) != perms::none ? 'x' : '-';
    cout << s << endl;
}

/*********************************************************************
 * 修改文件
 * create_directory(p)                  创建目录
 * create_directory(p, attrPath)        创建属性为 attrPath 的目录
 * create_directories(p)                创建目录和该路径中所有不存在的目录
 * create_hard_link(to, new)            为已存在文件 to 创建另一个文件系统项 new
 * create_symlink(to, new)              创建指向 to 的符号链接 new
 * create_directory_symlink(to, new)    创建指向目录 to 的符号链接 new
 * copy(from, to)                       拷贝任意类型的文件
 * copy(from, to, options)              以选项 options 拷贝任意类型的文件
 * copy_file(from, to)                  拷贝文件（不能是目录或者符号链接）
 * copy_file(from, to, options)         以选项 options 拷贝文件
 * copy_symlink(from, to)               拷贝符号链接（to 也指向 from 指向的文件）
 * remove(p)                            删除一个文件或者空目录,没有需要删除的文件时返回false
 * remove_all(p)                        删除路径 p 并递归删除所有子文件（如果有的话）,返回uintmax_t类型表示删除的文件数量,出错时返回uintmax_t(-1)
 * rename(old, new)                     重命名并/或移动文件
 * last_write_time(p, newtime)          修改最后修改时间
 * permissions(p, prms)                 用 prms 替换文件权限
 * permissions(p, prms, mode)           根据 mode 修改文件权限
 * resize_file(p, newSize)              修改普通文件的大小
 * equivalent(p1, p2)                   返回是否 p1 和 p2 指向同一个文件
 * space(p)                             返回路径 p 的磁盘空间信息
 * current_path(p)                      将当前工作目录设置为 p
*********************************************************************/
/*********************************************************************
 * copy的选项
 * none                     默认值（值为 0）
 * skip_existing            跳过覆盖已有文件
 * overwrite_existing       覆盖已有文件
 * update_existing          如果新文件更新的话覆盖已有文件
 * recursive                递归拷贝子目录和内容
 * copy_symlinks            拷贝符号链接为符号链接
 * skip_symlinks            忽略符号链接
 * directories_only         只拷贝目录
 * create_hard_links        创建新的硬链接而不是拷贝文件
 * create_symlinks          创建符号链接而不是拷贝文件（源路径必须是绝对路径，除非目标路径在当前目录下）
*********************************************************************/
int main(){


    CheckPath();
    SwitchCheckDifferentFileType();
    OutputPermission();





    return 0;
}