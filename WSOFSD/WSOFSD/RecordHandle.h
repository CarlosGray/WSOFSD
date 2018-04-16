#pragma once
class RecordHandle
{
private:
	RecordHandle();
	~RecordHandle();
public:
	//清除IE临时文件、Cookies、History、表单数据、密码
	static bool ClearIeRecord();
	//清除收藏夹中内容
	static bool ClearFavorite();
	//清除RAS自动拨号历史记录
	static bool ClearRAS();
	//清除临时文件
	static bool ClearTempFolder();
	//清空回收站
	static bool ClearRecycle();
	//清除"运行"中的历史记录
	static bool ClearRunMRU();
	//清除"文档"中的历史记录
	static bool ClearFolder();
	//清除上次登录用户记录
	static bool ClearLogin();
	//清除"查找文件"中的历史记录
	static bool ClearFindFile();
	//清除"查找计算机"中的历史记录
	static bool ClearFindComputer();
	//清除网络连接历史记录
	static bool ClearNetConnect();
	//清除远程登陆历史记录
	static bool ClearRemote();
	//清除浏览网址历史记录
	static bool ClearWebSite();
	//清除所有历史记录
	static bool ClearAllRecords();
};

