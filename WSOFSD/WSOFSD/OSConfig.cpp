#include "stdafx.h"
#include <powersetting.h>
#include <fstream>
#include <ShlObj.h>
#include <IPHlpApi.h>
#include <Mprapi.h>
#include <Psapi.h>
#pragma comment(lib, "PowrProf.lib")	//��Դ����
#pragma comment(lib, "shell32.lib")		//shellExcuteEx
#pragma comment(lib, "Iphlpapi.lib")	//IP�ӿڿ�
#pragma comment(lib, "Mprapi.lib")		//·�ɹ���
#pragma comment(lib, "Psapi.lib")		//���̹���

#include "TransCoding.h"
#include "FolderHandle.h"
#include "OSConfig.h"


COSConfig::COSConfig()
{
}


COSConfig::~COSConfig()
{
}

CString COSConfig::ExcuteGetRt(CString strCmd)
{
	CString strRet;
	SECURITY_ATTRIBUTES sa;
	HANDLE hRead = NULL;
	HANDLE hWrite = NULL;

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	if (!CreatePipe(&hRead, &hWrite, &sa, 0))
		return strRet;

	CString Cmd(_T("cmd.exe /c"));
	Cmd.Append(strCmd);

	STARTUPINFO si;
	si.cb = sizeof(STARTUPINFO);
	PROCESS_INFORMATION pi;
	GetStartupInfo(&si);
	si.hStdOutput = hWrite;
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

	if (!CreateProcess(NULL, Cmd.GetBuffer(), NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
	{
		CloseHandle(hWrite);
		CloseHandle(hRead);
		return strRet;
	}
	CloseHandle(hWrite);
	char *pBuffer = new char[2048];
	DWORD bytesRead;
	while (true)
	{
		if (ReadFile(hRead, pBuffer, 2048, &bytesRead, NULL) == NULL)
			break;
		
		strRet = CTransCoding::Ansi2Unicode(pBuffer).c_str();
	}
	delete []pBuffer;
	CloseHandle(hRead);

	return strRet;
}

bool COSConfig::RebootComputer()
{
	if (GetPriv(SE_SHUTDOWN_NAME))
	{
		if (ExitWindowsEx(EWX_REBOOT | EWX_FORCE, 0))
			return true;
	}
	return false;
}

bool COSConfig::ExcuteCommand(CString strCmd)
{
	strCmd.Format(_T("/c %s"), strCmd);
	SHELLEXECUTEINFO ExeInfo;
	ZeroMemory(&ExeInfo, sizeof(SHELLEXECUTEINFO));
	ExeInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ExeInfo.lpFile = _T("cmd.exe");
	ExeInfo.lpParameters = strCmd;
	ExeInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ExeInfo.nShow = SW_HIDE;
	ExeInfo.hwnd = NULL;
	ExeInfo.lpVerb = _T("runas");
	ExeInfo.lpDirectory = NULL;
	ExeInfo.hInstApp = NULL;
	//ִ������  
	ShellExecuteEx(&ExeInfo);

	//�ȴ����̽���  
	WaitForSingleObject(ExeInfo.hProcess, INFINITE);
	CloseHandle(ExeInfo.hProcess);
	if ((int)ExeInfo.hInstApp > 32)
		return true;

	return false;
}

bool COSConfig::OperateFireWall(bool isOff)
{
	CString NetshFireWallCmd(_T("netsh advfirewall set allprofiles state "));
	if (isOff)
		NetshFireWallCmd += _T("off");
	else
		NetshFireWallCmd += _T("on");

	return ExcuteCommand(NetshFireWallCmd);
}

bool COSConfig::OperateWuAuServ(bool isSgop)
{
	CString key;
	if (isSgop)
		key = _T("stop");
	else
		key = _T("start");

	CString Cmd;
	Cmd.Format(_T("net %s WuAuServ"), key);

	return ExcuteCommand(Cmd);
}

bool COSConfig::OperatePowerCfg(DWORD Seconds)
{
	bool bRet = false;
	GUID *id = (GUID*)LocalAlloc(LPTR, sizeof(GUID));

	//��ȡ��ǰ��Դ�ƻ�
	PowerGetActiveScheme(NULL, &id);

	//���ü�����Ӳ�˯��
	PowerWriteACValueIndex(NULL, id, &GUID_SLEEP_SUBGROUP, &GUID_STANDBY_TIMEOUT, Seconds);
	PowerWriteDCValueIndex(NULL, id, &GUID_SLEEP_SUBGROUP, &GUID_STANDBY_TIMEOUT, Seconds);
	//����Ӳ�̴Ӳ�˯��
	PowerWriteACValueIndex(NULL, id, &GUID_DISK_SUBGROUP, &GUID_DISK_POWERDOWN_TIMEOUT, Seconds);
	PowerWriteDCValueIndex(NULL, id, &GUID_DISK_SUBGROUP, &GUID_DISK_POWERDOWN_TIMEOUT, Seconds);
	//ʹ������Ч
	if (ERROR_SUCCESS == PowerSetActiveScheme(NULL, id))
		bRet = true;

	LocalFree(id);

	return bRet;
}

bool COSConfig::OperateUA(bool isClose)
{
	CString Cmd(_T("%windir%\\System32\\reg.exe ADD HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /v EnableLUA /t REG_DWORD /d "));
	if (isClose)
		Cmd += _T("0 /f");
	else
		Cmd += _T("1 /f");
	
	return ExcuteCommand(Cmd);
}

bool COSConfig::SetExeRunAsAdmin(CString ExeName)
{
	bool bRet = false;
	TCHAR *data_Set = _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\AppCompatFlags\\Layers");
	CRegKey key;
	if (ERROR_SUCCESS == key.Open(HKEY_LOCAL_MACHINE, data_Set, KEY_ALL_ACCESS | KEY_WOW64_64KEY))
	{
		if (key.SetStringValue(ExeName, _T("RUNASADMIN")) == ERROR_SUCCESS)
			bRet = true;
	}
	key.Close();
	return bRet;
}

bool COSConfig::WriteRegistry(HKEY rootKey, CString keyName, CString valueName, CString Value)
{
	bool bRet = false;
	CRegKey key;
	if (ERROR_SUCCESS == key.Open(rootKey, keyName, KEY_WRITE))
	{
		if (key.SetStringValue(valueName, Value) == ERROR_SUCCESS)
			bRet = true;
	}
	key.Close();
	return bRet;
}

CString COSConfig::GetDesktopPath()
{
	CString DeskPath;
	SHGetSpecialFolderPath(NULL, DeskPath.GetBuffer(MAX_PATH), CSIDL_DESKTOP, FALSE);
	DeskPath.ReleaseBuffer();

	return DeskPath;
}

CString COSConfig::GetAppDataPath()
{
	CString AppDataPath;
	SHGetSpecialFolderPath(NULL, AppDataPath.GetBuffer(MAX_PATH), CSIDL_APPDATA, FALSE);
	AppDataPath.ReleaseBuffer();

	return AppDataPath;
}

CString COSConfig::GetProgramsPath()
{
	CString PorgramsPath;
	SHGetSpecialFolderPath(NULL, PorgramsPath.GetBuffer(MAX_PATH), CSIDL_PROGRAMS, FALSE);
	PorgramsPath.ReleaseBuffer();

	return PorgramsPath;
}

BOOL COSConfig::CreateFileShortcut(CString lpszFileName, CString lpszLnkFileDir, CString lpszLnkFileName, WORD wHotKey, CString lpszDescription, int iShowCmd)
{
	if (lpszLnkFileDir.IsEmpty())
		return FALSE;

	HRESULT hr;
	IShellLink     *pLink;  //IShellLink����ָ��  
	IPersistFile   *ppf; //IPersisFil����ָ��  

						 //����IShellLink����  
	hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&pLink);
	if (FAILED(hr))
		return FALSE;

	//��IShellLink�����л�ȡIPersistFile�ӿ�  
	hr = pLink->QueryInterface(IID_IPersistFile, (void**)&ppf);
	if (FAILED(hr))
	{
		pLink->Release();
		return FALSE;
	}

	//Ŀ��  
	if (lpszFileName.IsEmpty())
		pLink->SetPath((LPCWSTR)_get_pgmptr);
	else
		pLink->SetPath(lpszFileName);

	//��ݼ�  
	if (wHotKey != 0)
		pLink->SetHotkey(wHotKey);

	//��ע  
	if (lpszDescription.IsEmpty())
		pLink->SetDescription(lpszDescription);

	//��ʾ��ʽ  
	pLink->SetShowCmd(iShowCmd);


	//��ݷ�ʽ��·�� + ����  
	CString LnkPath;
	if (lpszLnkFileName.IsEmpty()) //ָ���˿�ݷ�ʽ������  
		LnkPath.Format(_T("%s\\%s.lnk"), lpszLnkFileDir, lpszLnkFileName);

	hr = ppf->Save(LnkPath, TRUE);

	ppf->Release();
	pLink->Release();
	return SUCCEEDED(hr);
}

int COSConfig::GetLanAdapterIndex(CString AdapterID)
{
	int index = -1;

	//PIP_ADAPTER_INFO�ṹ��ָ��洢����������Ϣ
	PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO();
	PIP_ADAPTER_INFO pAdapter = pIpAdapterInfo;
	//�õ��ṹ���С,����GetAdaptersInfo����
	unsigned long stSize = sizeof(IP_ADAPTER_INFO);
	//����GetAdaptersInfo����,���pIpAdapterInfoָ�����;����stSize��������һ��������Ҳ��һ�������
	int nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
	if (ERROR_BUFFER_OVERFLOW == nRel)
	{
		//����������ص���ERROR_BUFFER_OVERFLOW
		//��˵��GetAdaptersInfo�������ݵ��ڴ�ռ䲻��,ͬʱ�䴫��stSize,��ʾ��Ҫ�Ŀռ��С
		//��Ҳ��˵��ΪʲôstSize����һ��������Ҳ��һ�������
		//�ͷ�ԭ�����ڴ�ռ�
		delete pIpAdapterInfo;
		//���������ڴ�ռ������洢����������Ϣ
		pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];
		pAdapter = pIpAdapterInfo;
		//�ٴε���GetAdaptersInfo����,���pIpAdapterInfoָ�����
		nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
	}
	if (ERROR_SUCCESS == nRel)
	{
		//���������Ϣ
		//�����ж�����,���ͨ��ѭ��ȥ�ж�
		while (pIpAdapterInfo)
		{

			//if (pIpAdapterInfo->Type == IF_TYPE_IEEE80211)
			if (pIpAdapterInfo->Type == MIB_IF_TYPE_ETHERNET)
			{
				/*size_t len = 0;
				wchar_t* dest = new wchar_t[MAX_PATH];
				mbstowcs_s(&len, dest, MAX_PATH, pIpAdapterInfo->AdapterName, _TRUNCATE);*/
				AdapterID = pIpAdapterInfo->AdapterName;
				index = pIpAdapterInfo->Index;
			}
			pIpAdapterInfo = pIpAdapterInfo->Next;
		}
	}
	//�ͷ��ڴ�ռ�
	delete pAdapter;
	return index;
}

void COSConfig::GetLanAdapterName(int index, TCHAR * Name, DWORD tchSize)
{
	HANDLE hMprConfig; //������Ϣ�ľ��  
	DWORD dwRet = 0; //����ֵ  
	PIP_INTERFACE_INFO plfTable = NULL; //�ӿ���Ϣ��  
	DWORD dwBufferSize = 0; //�ӿ���Ϣ��ռ��С  
	dwRet = MprConfigServerConnect(NULL, &hMprConfig); //��þ��  
	dwRet = GetInterfaceInfo(NULL, &dwBufferSize); //��ýӿ���Ϣ���С  
	if (dwRet == ERROR_INSUFFICIENT_BUFFER) //��ýӿ���Ϣ  
	{
		plfTable = (PIP_INTERFACE_INFO)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwBufferSize);
		GetInterfaceInfo(plfTable, &dwBufferSize);
	}
	IP_ADAPTER_INDEX_MAP AdaptMap; //�ӿ���Ϣ  
	for (int i = 0; i < plfTable->NumAdapters; i++)
	{
		AdaptMap = plfTable->Adapter[i];
		if (AdaptMap.Index == index)
		{
			dwRet = MprConfigGetFriendlyName(hMprConfig, AdaptMap.Name, (PWCHAR)Name, tchSize);
			break;
		}
	}
	HeapFree(GetProcessHeap(), HEAP_ZERO_MEMORY, plfTable);
}

bool COSConfig::NodifyIpAddress(CString IP, CString Mask)
{
	CString AdapterID;
	int index = GetLanAdapterIndex(AdapterID);
	TCHAR AdapterName[MAX_PATH]; //�ӿ�����  
	DWORD tchSize = sizeof(TCHAR) * MAX_PATH;
	ZeroMemory(&AdapterName, tchSize);
	GetLanAdapterName(index, AdapterName, tchSize);
	//netsh interface ip set address "��������" static IP��ַ �������� ����
	CString Cmd(_T("netsh interface ip set address"));
	Cmd.Format(_T("%s %s static %s %s"), Cmd, AdapterName, IP, Mask);

	return ExcuteCommand(Cmd);
}

BOOL COSConfig::GetPriv(LPCWSTR SE_NAME)
{
	HANDLE hToken;
	LUID sedebugnameValue;
	TOKEN_PRIVILEGES tkp;

	if (!OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
		return FALSE;

	if (!LookupPrivilegeValue(NULL, SE_NAME, &sedebugnameValue))
	{
		CloseHandle(hToken);
		return FALSE;
	}
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Luid = sedebugnameValue;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof(tkp), NULL, NULL))
	{
		CloseHandle(hToken);
		return FALSE;
	}

	return TRUE;
}

DWORD COSConfig::FindProcess(TCHAR * strProcessName)
{
	DWORD aProcesses[1024], cbNeeded, cbMNeeded;
	HMODULE hMods[1024];
	HANDLE hProcess;
	TCHAR szProcessName[MAX_PATH];

	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
		return 0;
	
	for (int i = 0; i < (int)(cbNeeded / sizeof(DWORD)); i++)
	{
		hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, aProcesses[i]);
		EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbMNeeded);
		GetModuleFileNameEx(hProcess, hMods[0], szProcessName, sizeof(szProcessName));

		CString strPrcFullName(szProcessName);
		CString strPrcName(strProcessName);
		if (_tcsstr(strPrcFullName, strPrcName) || _tcsstr(strPrcFullName, strPrcName.MakeLower()))
		{
			return (aProcesses[i]);
		}
	}

	return 0;
}

VOID COSConfig::KillProcess(TCHAR * strProcessName)
{
	HANDLE hYourTargetProcess = OpenProcess(PROCESS_QUERY_INFORMATION
		| PROCESS_CREATE_THREAD
		| PROCESS_VM_OPERATION
		| PROCESS_VM_WRITE
		| PROCESS_TERMINATE, FALSE, FindProcess(strProcessName));

	if (hYourTargetProcess == NULL)
	{
		DWORD ulErrCode = GetLastError();
		CString strError;
		strError.Format(_T("��ȡ����ʧ�ܣ�������:%ld"), ulErrCode);
		AfxMessageBox(strError);
	}
	BOOL result = TerminateProcess(hYourTargetProcess, 0);
	if (!result)
	{
		DWORD ulErrCode = GetLastError();
		CString strError;
		strError.Format(_T("ɱ������ʧ�ܣ�������:%ld"), ulErrCode);
		AfxMessageBox(strError);
	}
}

bool COSConfig::ChangeFireFoxHomePage(CString WebSite)
{
	CString rootPath;
	CString cfgPath;
	CString iniPath = GetAppDataPath();
	TCHAR *pOutName = new TCHAR[MAX_PATH];
	memset(pOutName, 0, sizeof(TCHAR) * MAX_PATH);

	iniPath.Append(_T("\\Mozilla\\FireFox\\"));
	rootPath = iniPath;
	iniPath.Append(_T("profiles.ini"));
	
	//�������ļ������ڣ����˳���ǰ����
	if (CFolderHandle::IsPathExists(iniPath))
	{
		delete[] pOutName;
		return false;
	}
	int Num = ::GetPrivateProfileInt(_T("Profile0"), _T("IsRelative"), 2, iniPath);
	::GetPrivateProfileString(_T("Profile0"), _T("Path"), _T(""), pOutName, MAX_PATH, iniPath);

	if (Num == 0)
		cfgPath = pOutName;
	else if (Num == 1)
		cfgPath = rootPath + pOutName;
	else
	{
		delete[] pOutName;
		return false;
	}
	cfgPath += _T("\\prefs.js");
	std::ofstream outStream(cfgPath, std::ios::out | std::ios::app);
	std::string strInput("user_pref(\"browser.startup.homepage\", ");
	strInput = strInput + "\"" + CTransCoding::Unicode2Ansi(WebSite.GetBuffer()) + "\");";
	outStream << strInput.c_str();
	delete[]pOutName;

	return true;
}

bool COSConfig::TaskbarBin()
{
	CString IEPath = GetProgramsPath();
	IEPath.Append(_T("\\Internet Explorer.lnk"));
	ShellExecute(NULL, _T("taskbarunpin"), IEPath, NULL, NULL, SW_SHOW);

	return true;
}

bool COSConfig::UnInstallFeiQ()
{
	KillProcess(_T("FeiQ.exe"));
	CString Path = GetAppDataPath();
	Path.Append(_T("\\feiq"));
	CString cmd(_T("rd/s/q"));
	cmd.Append(Path);
	ExcuteCommand(cmd);
	cmd = _T("rd/s/q \"C:\\Program Files\\Feiq\"");
	ExcuteCommand(cmd);
	return true;
}
