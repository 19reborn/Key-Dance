// 这里的代码全部来自https://www.cnblogs.com/tgyf/p/3839894.html
// 谢谢他！
#ifndef FILEIO_H
#define FILEIO_H
#include <io.h>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// 读取某给定路径下所有文件夹与文件名称，并带完整路径。
void getAllFiles(string path, vector<string>& files) {
    //文件句柄
    long hFile = 0;
    //文件信息
    struct _finddata_t fileinfo;  //很少用的文件信息读取结构
    string p;  //string类很有意思的一个赋值函数:assign()，有很多重载版本
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) != -1) {
        do {
            if ((fileinfo.attrib & _A_SUBDIR)) {  //比较文件类型是否是文件夹
                if (strcmp(fileinfo.name,".") != 0 && strcmp(fileinfo.name,"..") != 0) {
                    files.push_back(p.assign(path).append("\\").append(fileinfo.name));
                    getAllFiles(p.assign(path).append("\\").append(fileinfo.name), files);
                }
            } else {
                files.push_back(p.assign(path).append("\\").append(fileinfo.name));
            }
        } while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则-1
        _findclose(hFile);
    }
}

// 只读取某给定路径下的当前文件夹名
void getJustCurrentDir(string path, vector<string>& files) {
    //文件句柄
    long hFile = 0;
    //文件信息 
    struct _finddata_t fileinfo;
    string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) != -1) {
        do {  
            if ((fileinfo.attrib & _A_SUBDIR)) {  
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
                    files.push_back(fileinfo.name);
                    //files.push_back(p.assign(path).append("\\").append(fileinfo.name));
                }
            }
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
}

// 只读取某给定路径下的当前文件名
void getJustCurrentFile(string path, vector<string>& files) {
    //文件句柄
    long hFile = 0;
    //文件信息
    struct _finddata_t fileinfo;
    string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
        do {
            if ((fileinfo.attrib & _A_SUBDIR)) {
                ;
            } else {
                files.push_back(fileinfo.name);
                //files.push_back(p.assign(path).append("\\").append(fileinfo.name));
            }
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
}

// 只读取某给定路径下的所有文件名(即包含当前目录及子目录的文件)
void getFilesAll(string path, vector<string>& files) {
    //文件句柄
    long hFile = 0;
    //文件信息
    struct _finddata_t fileinfo;
    string p;  
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
        do {
            if ((fileinfo.attrib & _A_SUBDIR)) {
                if (strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0) {
                    //files.push_back(p.assign(path).append("\\").append(fileinfo.name));
                    getFilesAll(p.assign(path).append("\\").append(fileinfo.name), files);
                }
            } else {  
                files.push_back(p.assign(path).append("\\").append(fileinfo.name));
            }
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
}

#endif