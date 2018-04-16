#pragma once
class CFolderHandle
{
private:
	CFolderHandle();
	~CFolderHandle();
public:

	//给文件夹路径添加尾杠，若有则忽略
	static void AddSlash(CString &folder);
	//给文件夹路径剔除尾杠，若无则忽略
	static void CutSlash(CString &folder);

	//判断文件或文件夹是否存在
	static bool IsPathExists(CString folder);
	//去除文件只读属性
	static bool RemoveFileReadOnly(CString FileName);

	//拷贝文件夹
	static bool CopyFolder(CString destFolder, CString srcFolder);
	//删除文件夹
	static bool DeleteFolder(CString folder);

	//获取指定路径文件夹个数
	static int GetFolderCount(CString folder);
	//获取指定路径文件个数
	static bool GetFileCount(CString folder);

	//获取文件夹大小
	static ULONGLONG GetFolderSize(CString folder);
};

