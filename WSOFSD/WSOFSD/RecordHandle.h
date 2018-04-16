#pragma once
class RecordHandle
{
private:
	RecordHandle();
	~RecordHandle();
public:
	//���IE��ʱ�ļ���Cookies��History�������ݡ�����
	static bool ClearIeRecord();
	//����ղؼ�������
	static bool ClearFavorite();
	//���RAS�Զ�������ʷ��¼
	static bool ClearRAS();
	//�����ʱ�ļ�
	static bool ClearTempFolder();
	//��ջ���վ
	static bool ClearRecycle();
	//���"����"�е���ʷ��¼
	static bool ClearRunMRU();
	//���"�ĵ�"�е���ʷ��¼
	static bool ClearFolder();
	//����ϴε�¼�û���¼
	static bool ClearLogin();
	//���"�����ļ�"�е���ʷ��¼
	static bool ClearFindFile();
	//���"���Ҽ����"�е���ʷ��¼
	static bool ClearFindComputer();
	//�������������ʷ��¼
	static bool ClearNetConnect();
	//���Զ�̵�½��ʷ��¼
	static bool ClearRemote();
	//��������ַ��ʷ��¼
	static bool ClearWebSite();
	//���������ʷ��¼
	static bool ClearAllRecords();
};

