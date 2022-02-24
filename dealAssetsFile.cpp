/*
处理重复的assets资源文件
*/

#include<iostream>
#include<io.h>
#include<string>
#include<vector>
#include <Windows.h>
using namespace std;

void getFiles(string path, vector<string>& files) {
    //文件句柄
    long hFile = 0;
    //文件信息
    struct _finddata_t fileinfo;
    string p;

    if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1) {
        do {
            //如果是目录,迭代之
            if((fileinfo.attrib &  _A_SUBDIR)) {
                if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)
                    getFiles( p.assign(path).append("\\").append(fileinfo.name), files );
            } else {  //如果不是,加入列表
                files.push_back(fileinfo.name);
            }
        }while(_findnext(hFile, &fileinfo)  == 0);
        _findclose(hFile);
    }
}


int main() {
    string iterfilePath = "D:\\MY_DOCUMENT\\Work\\Reverse\\assets";   // 迭代搜索路径
    string delfilePath = "D:\\MY_DOCUMENT\\Work\\Leetcode\\BookNote\\assets";   // 待删除路径
    vector<string> files;  //存储文件名

    // 获取 iter路径下的所有文件
    getFiles(iterfilePath, files);

    // 开删 del路径
    int size = files.size();
    for (int i = 0;i < size;i++){
        cout << files[i] <<endl;
        //cout << delfilePath + "\\" + files[i] << endl;
        DeleteFileA( (delfilePath + "\\" + files[i]).c_str() ); // string > LPCSTR
    }
    
    return 0;
}