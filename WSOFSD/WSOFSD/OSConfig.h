#pragma once
class COSConfig
{
private:
	COSConfig();
	~COSConfig();
public:
	//执行外部exe并获取返回值
	static CString ExcuteGetRt(CString strCmd);
	//重启计算机
	static bool RebootComputer();
	//执行命令
	static bool ExcuteCommand(CString strCmd);
	//配置防火墙，打开或关闭
	static bool OperateFireWall(bool isOff = true);
	//配置系统更新，打开或关闭
	static bool OperateWuAuServ(bool isSgop = true);
	//配置电源选项，参数为0时关闭
	static bool OperatePowerCfg(DWORD Seconds = 0);
	//配置UAC，关闭或默认配置
	static bool OperateUA(bool isClose = true);
	//设置软件以管理员权限运行，参数包含绝对路径
	static bool SetExeRunAsAdmin(CString ExeName);
	//写注册表
	static bool WriteRegistry(HKEY rootKey, CString keyName, CString valueName, CString Value);
	//得到当前桌面路径
	static CString GetDesktopPath();
	//得到AppData路径
	static CString GetAppDataPath();
	//得到开始->程序组路径
	static CString GetProgramsPath();
	/*
	函数功能：对指定文件在指定的目录下创建其快捷方式
	函数参数：
	lpszFileName	指定文件，为NULL表示当前进程的exe文件
	lpszLnkFileDir	指定目录，不能为NULL
	lpszLnkFileName	快捷方式名称，为NULL时表示exe文件名
	wHotKey			为0时表示不设置快捷键
	pszDescription	备注
	iShowCmd		运行方式，默认常规窗口
	*/
	static BOOL CreateFileShortcut(CString lpszFileName, CString lpszLnkFileDir,
		CString lpszLnkFileName, WORD wHotKey, CString lpszDescription, int iShowCmd = SW_SHOWNORMAL);
	//获取当前网络适配器索引
	static int GetLanAdapterIndex(CString AdapterID);
	//获取当前网络适配器名称
	static void GetLanAdapterName(int index, TCHAR* Name, DWORD tchSize);
	//更改IP地址，通过后台调用netsh命令
	static bool NodifyIpAddress(CString IP, CString Mask);
	//获取系统权限，如SE_DEBUG_NAME,SE_SHUTDOWN_NAME
	static BOOL GetPriv(LPCWSTR SE_NAME);
	//查找指定进程
	static DWORD FindProcess(TCHAR *strProcessName);
	//杀死指定进程
	static VOID KillProcess(TCHAR *strProcessName);
	//更改火狐主页
	static bool ChangeFireFoxHomePage(CString WebSite);
	//固定任务栏
	static bool TaskbarBin();
	//卸载飞秋
	static bool UnInstallFeiQ();
};

