/*********************************************************************************************
    *  @Copyright (c) , All rights reserved.
    *  @file:       源.cpp
    *  @version:    ver 1.0
    *  @author:   Administrator
    *  @brief:  
    *  @change:
    *  @email: 	binbin_erices@163.com
    *  Date             Version    Changed By      Changes 
    *  2020/9/26 1:15    1.0       Administrator             create
**********************************************************************************************/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include<boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <process.h>
using namespace std;
using namespace boost::filesystem;
unordered_map<string, vector<string>>m;
void GetDirects(std::string &path);
void GetFiles(std::string path, std::vector<std::string> &fileList);
//************************************
// Method:    getFiles
// FullName:  getFiles
// Access:    public 
// Returns:   int
// Qualifier:
// Parameter: string & curPath
// Parameter: vector<string>fileNames
//************************************
//int getFiles(string &curPath, vector<string>fileNames)
//{
//	boost::filesystem::recursive_directory_iterator itEnd;
//	for (boost::filesystem::recursive_directory_iterator itor(curPath.c_str()); itor != itEnd; ++itor)
//	{
//		//itor->path().string()是目录下文件的路径
//		/*
//		 *当curPath是相对路径时，itor->string()也是相对路径
//		 *即当curPath = "../cur/",下面将输出"../cur/build.sh"
//		 */
//
//		 //当curPath是绝对路径时，itor->string()也是绝对路径
//		string file = itor->path().string(); // "/home/"
//		if (is_directory(file))
//		{
//			getFiles(file, fileNames);
//		}
//		//构造文件路径，以获得文件丰富的操作
//		//path可以接受C风格字符串和string类型作为构造函数的参数，而提供的路径可以是相对路径，也可以是绝对路径。
//		boost::filesystem::path filePath(file);
//		//path的方法如filename()等，返回的对象仍是path，如果可以通过path的string()方法，获取对象的string类型
//		//parent_path()获得的是当前文件的父路径
//		//cout << filePath.parent_path() << endl;  // "/home/test/cur/"
//
//		//filename()获得的是文件名，含拓展名
//		//cout << filePath.filename() << endl;  // "build.sh"
//		//cout << filePath.filename().string() << endl;
//		fileNames.push_back(filePath.filename().string());
//		////stem()获得的是文件的净文件名，即不含拓展名
//		//cout << filePath.stem() << endl; // "build"
//
//		////extension()文件的拓展名（主要是".sh"而不是"sh"）
//		//cout << filePath.extension() << endl; // ".sh"
//
//		////获得文件的大小,单位为字节
//		//int nFileSize = boost::filesystem::file_size(filePath);
//
//		//最后一次修改文件的时间
//		//last_write_time()返回的是最后一次文件修改的绝对秒数
//		//last_write_time(filePath,time(NULL))还可以修改文件的最后修改时间，相当于Linux中命令的touch
//		//if (last_write_time(filePath) - time(NULL) > 5)
//		//{
//		//	/*
//		//	 *在工程实践中，当需要不断的扫目录，而目录又会不断的加入新文件时，
//		//	 *借助last_write_time()可以判断新入文件的完整性，以避免错误的处理还未写完的文件
//		//	 */
//		//}
//
//		////判断文件的状态信息
//		//if (boost::filesystem::is_regular_file(file))
//		//{
//		//	//is_regular_file(file)普通文件
//		//	//is_directory(file)目录文件，如当遍历到"/home/test/cur/src/"时，这就是一个目录文件
//		//	//is_symlink(file)链接文件
//		//}
//
//		////更改拓展名
//		//boost::filesystem::path tmpPath = filePath;
//		////假设遍历到了cpp文件，想看下对应的.o文件是否存在
//		//tmpPath.replace_extension(".o");
//		////判断文件是否存在
//		//if (boost::filesystem::exists(tmpPath.string()))
//
//		//	//删除文件
//		//	//remove只能删除普通文件，而不能删除目录
//		//	boost::filesystem::remove(tmpPath.string());
//		////remove_all则提供了递归删除的功能，可以删除目录
//		//boost::filesystem::remove_all(tmpPath.string());
//
//		//移动文件 & 拷贝文件
//		//srcPath原路径，srcPath的类型为string
//		//destPath目标路径，destPath的类型为string
//	//	boost::filesystem::rename(srcPath, destPath);
//	//	boost::filesystem::copy_file(srcPath, destPath);
//	//	//拷贝目录
//	//	boost::filesystem::copy_files("/home/test", "/dev/shm")
//
//	}
//
//	////boost::filesystem还可以创建目录：
//	//if (!boost::filesystem::exists(strFilePath))
//	//{
//	//	boost::filesystem::create_directories(strFilePath)
//	//}
//	return 0;
//}
void scanFilesUseRecursive(const string& rootPath,vector<string> &directoryList,vector<string> &ret)
{
	namespace fs = boost::filesystem;
	fs::path fullpath(rootPath, fs::native);
	if (!fs::exists(fullpath)) { return; }
	fs::recursive_directory_iterator end_iter;
	for (fs::recursive_directory_iterator iter(fullpath); iter != end_iter; iter++) {
		try {
			if (fs::is_directory(*iter)) {
				directoryList.emplace_back(iter->path().string());
				//std::cout << *iter << "is dir" << std::endl;
				//ret.push_back(iter->path().string());
				scanFilesUseRecursive(iter->path().string(), directoryList,ret);
			}
			else {
				ret.push_back(iter->path().stem().string());
				//std::cout << *iter << " is a file" << std::endl;
			}
		}
		catch (const std::exception & ex) {
			std::cerr << ex.what() << std::endl;
			continue;
		}
	}
}

void GetDirects(std::string &path)
{
	boost::filesystem::path myPath(path);
	boost::filesystem::directory_iterator endIter;
	for (boost::filesystem::directory_iterator iter(myPath); iter != endIter; iter++) {
		if (boost::filesystem::is_directory(*iter)) {
			vector<string>fileList;
			GetFiles(iter->path().string(),fileList);
			m[iter->path().stem().string()] = fileList;
		}
		else {}
	}
}

void GetFiles(std::string path,std::vector<std::string> &fileList)
{
	boost::filesystem::path myPath(path);
	boost::filesystem::directory_iterator endIter;
	for (boost::filesystem::directory_iterator iter(myPath); iter != endIter; iter++) {
		if (boost::filesystem::is_directory(*iter)) {
		}
		else {
			fileList.emplace_back(iter->path().string());
		}
	}
}
//void listFiles(const char * dir, std::vector<const std::string> &fileList)
//{
//	char dirNew[200];
//	strcpy_s(dirNew, dir);
//	strcat_s(dirNew, "\\*.*"); 
//
//	intptr_t handle;
//	_finddata_t findData; // _finddata_t是存储文件各种信息的结构体
//
//	handle = _findfirst(dirNew, &findData);
//	if (handle == -1) // 检查是否成功
//		return;
//	do
//	{
//		if (findData.attrib & _A_SUBDIR) // 目录
//		{
//			if (strcmp(findData.name, ".") == 0 || strcmp(findData.name, "..") == 0)
//				continue;
//
//			cout << findData.name << "\t<dir>\n"; // 打印文件夹的名称
//			//fileList.push_back(findData.name); // 打印文件夹的名称
//
//			// 在目录后面加上"\\"和搜索到的目录名进行下一次搜索
//			strcpy_s(dirNew, dir);
//			strcat_s(dirNew, "\\");
//			strcat_s(dirNew, findData.name);
//
//			listFiles(dirNew, fileList);
//		}
//		else // 文件
//		{
//			fileList.push_back(findData.name); // 打印文件的名称，并且后面可以打印文件的数目
//		}
//
//	} while (_findnext(handle, &findData) == 0);
//
//	_findclose(handle); 
//}

const vector<string>& scanFilesUseRecursive(const string& rootPath, vector<string>& container = *(new vector<string>())) {
	namespace fs = boost::filesystem;
	fs::path fullpath(rootPath, fs::native);
	vector<string> &ret = container;

	if (!fs::exists(fullpath)) { return ret; }
	fs::recursive_directory_iterator end_iter;
	for (fs::recursive_directory_iterator iter(fullpath); iter != end_iter; iter++) {
		try {
			if (fs::is_directory(*iter)) {
				std::cout << *iter << "is dir" << std::endl;
				//ret.push_back(iter->path().string());
				//ScanAllFiles::scanFiles(iter->path().string(),ret);
			}
			else {
				ret.push_back(iter->path().string());
				std::cout << *iter << " is a file" << std::endl;
			}
		}
		catch (const std::exception & ex) {
			std::cerr << ex.what() << std::endl;
			continue;
		}
	}
	return ret;
}



int main()
{
	vector<string>v;
	path p = current_path();
	//p /= "project1.log";
	//remove("./a.txt");
	directory_iterator iter(p);
	while (iter != directory_iterator())
	{
		auto path = iter->path().string();
		v.push_back(path);
		++iter;
	}

	//rename("./Release/Project1.log", "./Project1.log");
	//int iPid = (int)_getpid();
	//auto path = current_path();
	//cout << path.string() << endl;
	//auto a = path.generic_path();
	//a = path.branch_path();
	//dir /= "System32";       //追加下级目录
	//dir /= "services.exe";
	//std::cout << dir << std::endl;
	//std::cout << dir.string() << std::endl;            //转换成std::string 类型
	//std::cout << dir.root_name() << std::endl;          //盘符名：C:
	//std::cout << dir.root_directory() << std::endl;     //根目录："\"
	//std::cout << dir.root_path() << std::endl;          //根路径："C:\"
	//std::cout << dir.relative_path() << std::endl;      // 相对路径:Windows\System32\services.exe
	//std::cout << dir.parent_path() << std::endl;        //上级目录：C:\Windows\System32
	//std::cout << dir.filename() << std::endl;           //文件名：services.exe
	//std::cout << dir.stem() << std::endl;               //不带扩展的文件名：services
	//std::cout << dir.extension() << std::endl;          //扩展名：.exe
	//cout<< system_complete(dir);//  返回完整路径(相对路径+当前路径) 
	/*cout << current_path() << endl;*/
	//current_path("C:\\");
	//cout << current_path() << endl;
	//定义一个可以递归的目录迭代器,用于遍历
	//string curPath = "D:\\test";
	//vector<string>directList;
	//auto a = scanFilesUseRecursive(curPath);
	//vector<const string>fileNames;
	//vector<string>directoryList;
	//listFiles(curPath.c_str(), fileNames);
	//fileNames = scanFilesUseRecursive(curPath, directoryList);

	//boost::filesystem::path filePath("C:\\Users\\Administrator\\desktop\\calcTest1.csv");
	//if (boost::filesystem::exists(filePath))
	//{
	//	cout << filePath.stem() << endl;
	//	cout << "exist" << endl;
	//}
	//auto a = last_write_time(filePath);
	//map<string, int>m;
	//if (m["a"] == 0)
	//{

	//}
	//else
	//{
	//	m["a"] = 1;
	//}

	system("pause");
	return 0;
}