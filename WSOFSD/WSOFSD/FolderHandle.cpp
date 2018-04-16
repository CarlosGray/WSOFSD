#include "stdafx.h"
#include "FolderHandle.h"


CFolderHandle::CFolderHandle()
{
}


CFolderHandle::~CFolderHandle()
{
}

void CFolderHandle::AddSlash(CString & folder)
{
	if (folder.Right(1) != "\\")
		folder += _T("\\");
}

void CFolderHandle::CutSlash(CString & folder)
{
	if (folder.Right(1) == "\\")
		folder.TrimRight(_T("\\"));
}

bool CFolderHandle::IsPathExists(CString folder)
{
	int nRet = _taccess(folder, 0);
	return 0 == nRet || EACCES == nRet;
}

bool CFolderHandle::RemoveFileReadOnly(CString FileName)
{
	return SetFileAttributesW(FileName, GetFileAttributes(FileName) & ~FILE_ATTRIBUTE_READONLY);
}

bool CFolderHandle::CopyFolder(CString destFolder, CString srcFolder)
{
	bool bRet = false;

	AddSlash(destFolder);
	AddSlash(srcFolder);

	if (!PathIsDirectory(destFolder))
		SHCreateDirectoryEx(0, destFolder, 0);

	CFileFind finder;
	srcFolder += _T("*.*");
	BOOL bWorking = finder.FindFile(srcFolder);
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (!finder.IsSystem() && !finder.IsDots())
		{
			if (finder.IsDirectory())
				CopyFolder(finder.GetFilePath(), destFolder + finder.GetFileName());
			else
			{
				if (!CopyFile(finder.GetFilePath(), destFolder + finder.GetFileName(), FALSE))
					bRet = false;
			}
		}
	}
	finder.Close();

	return bRet;
}

bool CFolderHandle::DeleteFolder(CString folder)
{
	if (folder.IsEmpty())
		return true;
	if (!PathIsDirectory(folder))
		return true;

	CString strFind = folder;
	AddSlash(strFind);
	strFind += _T("*.*");

	CFileFind finder;
	BOOL bWorking = finder.FindFile(strFind);

	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (finder.IsDots())
			continue;

		CString strSubFile = finder.GetFilePath();
		if (finder.IsDirectory())
		{
			if (!DeleteFolder(strSubFile))
			{
				return false;
			}
			else
			{
				if (!DeleteFile(strSubFile))
					return false;
			}
		}
	}
	finder.Close();
	return (bool)RemoveDirectory(folder);
}

int CFolderHandle::GetFolderCount(CString folder)
{
	int iCount = 0;
	CFileFind finder;
	AddSlash(folder);
	folder += _T("*.*");
	BOOL bWorking = finder.FindFile(folder);

	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (!finder.IsSystem() && !finder.IsDots() && finder.IsDirectory())
		{
			iCount++;
			iCount += GetFolderCount(finder.GetFilePath());
		}

	}
	finder.Close();
	return iCount;
}

bool CFolderHandle::GetFileCount(CString folder)
{
	int iCount = 0;
	CFileFind finder;
	AddSlash(folder);
	folder += _T("*.*");
	BOOL bWorking = finder.FindFile(folder);

	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (!finder.IsSystem() && !finder.IsDots())
		{
			if (finder.IsDirectory())
				iCount += GetFileCount(finder.GetFilePath());
			else
				iCount++;
		}

	}
	finder.Close();
	return iCount;
}

ULONGLONG CFolderHandle::GetFolderSize(CString folder)
{
	ULONGLONG size = 0;
	CFileFind finder;
	AddSlash(folder);
	folder += _T("*.*");
	BOOL bWorking = finder.FindFile(folder);

	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (!finder.IsSystem() && !finder.IsDots())
		{
			if (finder.IsDirectory())
				size += GetFileCount(finder.GetFilePath());
			else
				size += finder.GetLength();
		}

	}
	finder.Close();
	return size;
}
