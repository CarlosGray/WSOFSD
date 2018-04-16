#include "stdafx.h"
#include "OSConfig.h"
#include "RecordHandle.h"

#include "urlHist.h"
#pragma comment(lib, "shell32.lib")

HRESULT ClearHistory()
{
	HRESULT hr;
	CoInitialize(NULL);
	IUrlHistoryStg2* pUrlHistoryStg2 = NULL;
	hr = CoCreateInstance(CLSID_CUrlHistory, NULL, 1, IID_IUrlHistoryStg2, (void**)&pUrlHistoryStg2);
	if (SUCCEEDED(hr))
	{
		hr = pUrlHistoryStg2->ClearHistory();
		pUrlHistoryStg2->Release();
	}
	CoUninitialize();
	return hr;
}

RecordHandle::RecordHandle()
{
}


RecordHandle::~RecordHandle()
{
}

bool RecordHandle::ClearIeRecord()
{
	SHELLEXECUTEINFO ExeInfo;
	ZeroMemory(&ExeInfo, sizeof(SHELLEXECUTEINFO));
	ExeInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ExeInfo.lpFile = _T("rundll32.exe");
	ExeInfo.lpParameters = _T(" InetCpl.cpl,ClearMyTracksByProcess 255");
	ExeInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ExeInfo.nShow = SW_HIDE;
	ExeInfo.hwnd = NULL;
	ExeInfo.lpVerb = _T("runas");
	ExeInfo.lpDirectory = NULL;
	ExeInfo.hInstApp = NULL;
	//执行命令  
	ShellExecuteEx(&ExeInfo);

	//等待进程结束  
	WaitForSingleObject(ExeInfo.hProcess, INFINITE);
	CloseHandle(ExeInfo.hProcess);
	if ((int)ExeInfo.hInstApp > 32)
		return true;

	return false;
}

bool RecordHandle::ClearTempFolder()
{
	TCHAR szPath[MAX_PATH];
	if (GetTempPath(MAX_PATH, szPath))
	{
		CString cmd(_T("rd /s/q "));
		cmd.Append(szPath);
		return COSConfig::ExcuteCommand(cmd);
	}
	return false;
}

bool RecordHandle::ClearRecycle()
{
	return S_OK == SHEmptyRecycleBin(NULL, NULL, SHERB_NOCONFIRMATION | SHERB_NOPROGRESSUI | SHERB_NOSOUND) ? true : false;
}

bool RecordHandle::ClearRunMRU()
{
	return ERROR_SUCCESS == SHDeleteKey(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\RunMRU")) ? true : false;
}

bool RecordHandle::ClearFolder()
{
	bool bRet1 = false;
	bool bRet2 = false;
	TCHAR szPath[MAX_PATH];
	if (SHGetSpecialFolderPath(NULL, szPath, CSIDL_RECENT, FALSE))
	{
		CString cmd(_T("rd /s/q "));
		cmd.Append(szPath);
		bRet1 =  COSConfig::ExcuteCommand(cmd);
	}
	bRet2 = (ERROR_SUCCESS == SHDeleteKey(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\RecentDocs")) ? true : false);
	return bRet1 && bRet2;
}

bool RecordHandle::ClearLogin()
{
	bool isDelete1 = (ERROR_SUCCESS == SHDeleteValue(HKEY_CURRENT_USER,
		_T("Software\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon"),
		_T("DefaultUserName")) ? true : false);
	bool isDelete2 = (ERROR_SUCCESS == SHDeleteValue(HKEY_CURRENT_USER,
		_T("Software\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon"),
		_T("AltDefaultUserName")) ? true : false);
	bool isDelete3 = (ERROR_SUCCESS == SHDeleteValue(HKEY_CURRENT_USER,
		_T("Software\\Microsoft\\Windows\\CurrentVersion\\Winlogon"),
		_T("DefaultUserName")) ? true : false);

	return isDelete1 && isDelete2 && isDelete3;
}

bool RecordHandle::ClearFindFile()
{
	return ERROR_SUCCESS == SHDeleteKey(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\WordWheelQuery")) ? true : false;
}

bool RecordHandle::ClearFindComputer()
{
	return ERROR_SUCCESS == SHDeleteKey(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\TypedPaths")) ? true : false;
}

bool RecordHandle::ClearNetConnect()
{
	TCHAR szPath[MAX_PATH];
	if (SHGetSpecialFolderPath(NULL, szPath, CSIDL_NETHOOD, FALSE))
	{
		CString cmd(_T("rd /s/q "));
		cmd.Append(szPath);
		return COSConfig::ExcuteCommand(cmd);
	}
	return false;
}

bool RecordHandle::ClearRemote()
{
	return ERROR_SUCCESS == SHDeleteKey(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Terminal Server Client\\Default")) ? true : false;
}

bool RecordHandle::ClearWebSite()
{
	return S_OK == ClearHistory() ? true : false;
}

bool RecordHandle::ClearAllRecords()
{
	bool bRet1 = ClearIeRecord();
	bool bRet2 = ClearFavorite();
	bool bRet3 = ClearRAS();
	bool bRet4 = ClearTempFolder();
	bool bRet5 = ClearRecycle();
	bool bRet6 = ClearRunMRU();
	bool bRet7 = ClearFolder();
	bool bRet8 = ClearLogin();
	bool bRet9 = ClearFindFile();
	bool bRet10 = ClearFindComputer();
	bool bRet11 = ClearNetConnect();
	bool bRet12 = ClearRemote();
	bool bRet13 = ClearWebSite();
	if (bRet1 && bRet2 && bRet3 && bRet4 && bRet5 && bRet6 && bRet7 && bRet8 &&
		bRet9 && bRet10 && bRet11 && bRet12 && bRet13)
		return true;
	else
	{
		bool isDelete1 = false;
		bool isDelete2 = false;
		TCHAR szPath[MAX_PATH];
		GetWindowsDirectory(szPath, MAX_PATH);
		_tcscat_s(szPath, _T("\\History"));
		CString cmd(_T("rd /s/q "));
		cmd.Append(szPath);
		isDelete1 = COSConfig::ExcuteCommand(cmd);

		if (SHGetSpecialFolderPath(NULL, szPath, CSIDL_HISTORY, FALSE))
		{
			cmd.Format(_T("rd/s/q %s"), szPath);
			isDelete2 = COSConfig::ExcuteCommand(cmd);
		}
		return isDelete1 && isDelete2;
	}
}

bool RecordHandle::ClearFavorite()
{
	TCHAR szPath[MAX_PATH];
	if (SHGetSpecialFolderPath(NULL, szPath, CSIDL_FAVORITES, FALSE))
	{
		CString cmd(_T("rd /s/q "));
		cmd.Append(szPath);
		return COSConfig::ExcuteCommand(cmd);
	}
	return false;
}

bool RecordHandle::ClearRAS()
{
	return ERROR_SUCCESS == SHDeleteKey(HKEY_CURRENT_USER, _T("Software\\Microsoft\\RAS Autodial\\Addresses")) ? true : false;
}
