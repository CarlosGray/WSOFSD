#pragma once
class COSConfig
{
private:
	COSConfig();
	~COSConfig();
public:
	//ִ���ⲿexe����ȡ����ֵ
	static CString ExcuteGetRt(CString strCmd);
	//���������
	static bool RebootComputer();
	//ִ������
	static bool ExcuteCommand(CString strCmd);
	//���÷���ǽ���򿪻�ر�
	static bool OperateFireWall(bool isOff = true);
	//����ϵͳ���£��򿪻�ر�
	static bool OperateWuAuServ(bool isSgop = true);
	//���õ�Դѡ�����Ϊ0ʱ�ر�
	static bool OperatePowerCfg(DWORD Seconds = 0);
	//����UAC���رջ�Ĭ������
	static bool OperateUA(bool isClose = true);
	//��������Թ���ԱȨ�����У�������������·��
	static bool SetExeRunAsAdmin(CString ExeName);
	//дע���
	static bool WriteRegistry(HKEY rootKey, CString keyName, CString valueName, CString Value);
	//�õ���ǰ����·��
	static CString GetDesktopPath();
	//�õ�AppData·��
	static CString GetAppDataPath();
	//�õ���ʼ->������·��
	static CString GetProgramsPath();
	/*
	�������ܣ���ָ���ļ���ָ����Ŀ¼�´������ݷ�ʽ
	����������
	lpszFileName	ָ���ļ���ΪNULL��ʾ��ǰ���̵�exe�ļ�
	lpszLnkFileDir	ָ��Ŀ¼������ΪNULL
	lpszLnkFileName	��ݷ�ʽ���ƣ�ΪNULLʱ��ʾexe�ļ���
	wHotKey			Ϊ0ʱ��ʾ�����ÿ�ݼ�
	pszDescription	��ע
	iShowCmd		���з�ʽ��Ĭ�ϳ��洰��
	*/
	static BOOL CreateFileShortcut(CString lpszFileName, CString lpszLnkFileDir,
		CString lpszLnkFileName, WORD wHotKey, CString lpszDescription, int iShowCmd = SW_SHOWNORMAL);
	//��ȡ��ǰ��������������
	static int GetLanAdapterIndex(CString AdapterID);
	//��ȡ��ǰ��������������
	static void GetLanAdapterName(int index, TCHAR* Name, DWORD tchSize);
	//����IP��ַ��ͨ����̨����netsh����
	static bool NodifyIpAddress(CString IP, CString Mask);
	//��ȡϵͳȨ�ޣ���SE_DEBUG_NAME,SE_SHUTDOWN_NAME
	static BOOL GetPriv(LPCWSTR SE_NAME);
	//����ָ������
	static DWORD FindProcess(TCHAR *strProcessName);
	//ɱ��ָ������
	static VOID KillProcess(TCHAR *strProcessName);
	//���Ļ����ҳ
	static bool ChangeFireFoxHomePage(CString WebSite);
	//�̶�������
	static bool TaskbarBin();
	//ж�ط���
	static bool UnInstallFeiQ();
};

