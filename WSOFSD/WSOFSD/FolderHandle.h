#pragma once
class CFolderHandle
{
private:
	CFolderHandle();
	~CFolderHandle();
public:

	//���ļ���·�����β�ܣ����������
	static void AddSlash(CString &folder);
	//���ļ���·���޳�β�ܣ����������
	static void CutSlash(CString &folder);

	//�ж��ļ����ļ����Ƿ����
	static bool IsPathExists(CString folder);
	//ȥ���ļ�ֻ������
	static bool RemoveFileReadOnly(CString FileName);

	//�����ļ���
	static bool CopyFolder(CString destFolder, CString srcFolder);
	//ɾ���ļ���
	static bool DeleteFolder(CString folder);

	//��ȡָ��·���ļ��и���
	static int GetFolderCount(CString folder);
	//��ȡָ��·���ļ�����
	static bool GetFileCount(CString folder);

	//��ȡ�ļ��д�С
	static ULONGLONG GetFolderSize(CString folder);
};

