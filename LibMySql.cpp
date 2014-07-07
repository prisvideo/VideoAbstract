/**
*@file LibMySql.cpp
*@brief ���ݿ����ʵ��
*
*�������ݿ����¸�����������Ϊ
*����ʵ�ֹ��������õ������ݿ��Ĵ��������ҡ����º�ɾ������
*
*@author ���� zhang nannan&lu ying ,����email��
*@version �汾��(0.0)
*@data 2012-8-21
*/

#include "stdafx.h"
#include <afxwin.h>
#include <afxmt.h>///<���̱߳���Ӵ�ͷ�ļ�����Ȼ���޷��������ⲿ����
#include "LibMySql.h"

///@brief �����ռ�std
///
///�����ռ�std��װ���Ǳ�׼����������
using namespace std;

///@brief CDataMySql��Ĺ��캯�����������ݿ�ĳ�ʼ���͹��������ݿ�Ĺ���
///
///@param[in|out] NULL 
///@pre  NULL
///@return NULL
///@retval NULL
///@post NULL
CDataMySql::CDataMySql(void)
{
	const char user[] = "root";         ///<username        
	const char pswd[] = "123456";        ///<password
	const char host[] = "localhost";    ///<or"127.0.0.1"
	const char table[] = "mydb";        ///<database
	unsigned int port = 3306;           ///<server port        
	mysql_init(&m_mysql);               ///<���ݿ��ʼ��
	if(mysql_real_connect(&m_mysql,host,user,pswd,table,port,NULL,0)==NULL)///<�����ݿ�����
	{
		print_error(&m_mysql,"error message");
		mysql_close(&m_mysql);
		return;
	}
	mysql_query(&m_mysql,"SET NAMES GBK");                        ///<��ʾΪ����
}
///@brief vidPlayDlg�����������
///
///@param[in|out] NULL 
///@pre  NULL
///@return NULL
///@retval NULL
///@post NULL
CDataMySql::~CDataMySql(void)
{
}
///@brief CDataMySql��Ľ�����¼����
/// 
///������ݿ���û�м�¼���򴴽�һ����¼���м�������Ϊ(caseName VARCHAR(255) primary key,caseCategory VARCHAR(255) not Null,caseRecordTime VARCHAR(255) not Null,caseHappenTime VARCHAR(255) not Null,caseDescription TEXT not Null,caseNote TEXT not Null)
///@param[in|out] CaseTableName Ҫ�����ı���|NULL
///@pre  NULL
///@return NULL
///@retval BOOL ���ز����Ƿ�ɹ�
///@post NULL
bool CDataMySql::CreateCaseTable(CString CaseTableName)
{
	CString m_strSql;///<mysql��ѯ���
	m_strSql.Format("create table if not exists %s(caseName VARCHAR(255) primary key,caseCategory VARCHAR(255) not Null,caseRecordTime VARCHAR(255) not Null,caseHappenTime VARCHAR(255) ,caseDescription TEXT not Null,caseNote TEXT not Null)",CaseTableName);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		return true;
	}
}
///@brief CDataMySql��Ľ�����Ƶ����
/// 
///������ݿ���û����Ƶ���򴴽�һ����Ƶ���м�������Ϊ(caseName VARCHAR(255) not Null,cameraName VARCHAR(255) not Null,originPath VARCHAR(255) not Null,segPath VARCHAR(255),fusionPath VARCHAR(255),\
        origTotalFrames int,segTotalFrames int,fusTotalFrames int)
///@param[in|out] VideoTableName Ҫ�����ı���|NULL
///@pre  NULL
///@return NULL
///@retval BOOL ���ز����Ƿ�ɹ�
///@post NULL
bool CDataMySql::CreateVideoTable(CString VideoTableName)
{
	CString m_strSql;///<mysql��ѯ���
	m_strSql.Format("create table if not exists %s(caseName VARCHAR(255) not Null,cameraName VARCHAR(255) not Null,originPath VARCHAR(255) not Null,segPath VARCHAR(255),fusionPath VARCHAR(255),\
					origTotalFrames int,segTotalFrames int,fusTotalFrames int)",VideoTableName);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		return true;
	}
}
///@brief CDataMySql��Ľ���ͼƬ����
/// 
///������ݿ���û��ͼƬ���򴴽�һ��ͼƬ���м�������Ϊ(caseName VARCHAR(255) not Null,imageCategory VARCHAR(255) not Null,imagePath VARCHAR(255) not Null)
///@param[in|out] ImageTableName in Ҫ�����ı���|NULL
///@pre  NULL
///@return NULL
///@retval BOOL ���ز����Ƿ�ɹ�
///@post NULL
bool CDataMySql::CreateImageTable(CString ImageTableName)
{
	CString m_strSql;///<mysql��ѯ���
	m_strSql.Format("create table if not exists %s(caseName VARCHAR(255) not Null,imageCategory VARCHAR(255) not Null,imagePath VARCHAR(255) not Null)",ImageTableName);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		return true;
	}
}
///@brief CDataMySql��Ľ�����������
/// 
///������ݿ���û���������򴴽�һ���������м�������Ϊ(caseName VARCHAR(255) not Null,cameraName VARCHAR(255),clueHappenTime VARCHAR(255),clueCategory VARCHAR(255),latestModifyTime VARCHAR(255),filePath VARCHAR(255),clueDescription TEXT)
///@param[in|out] ClueTableName Ҫ�����ı���|NULL
///@pre  NULL
///@return NULL
///@retval BOOL ���ز����Ƿ�ɹ�
///@post NULL
bool CDataMySql::CreateClueTable(CString ClueTableName)
{
	CString m_strSql;///<mysql��ѯ���
	m_strSql.Format("create table if not exists %s(caseName VARCHAR(255) not Null,cameraName VARCHAR(255),clueHappenTime VARCHAR(255),clueCategory VARCHAR(255),latestModifyTime VARCHAR(255),filePath VARCHAR(255),clueDescription TEXT)",ClueTableName);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		return true;
	}
}
///@brief CDataMySql��Ľ���ԭʼtrace����
/// 
///����һ����Ϊ������ԭʼtrace���м�������Ϊ(nOldPara int not Null,segID int primary key,nTop int not Null,nBottom int not Null,nLeft int not Null,nRight int not Null,origFrame int not Null,segSize varchar(20) not Null)
///@param[in|out] OrigTraceTableName Ҫ�����ı���|NULL
///@pre  NULL
///@return NULL
///@retval BOOL ���ز����Ƿ�ɹ�
///@post NULL
bool CDataMySql::CreateOrigTraceTable(CString OrigTraceTableName)
{
	CString m_strSql;///<mysql��ѯ���
	//m_strSql.Format("create table %s(nOldPara int not Null,segID int primary key,nTop int not Null,nBottom int not Null,nLeft int not Null,nRight int not Null,origFrame int not Null,segSize varchar(20) not Null)",OrigTraceTableName);
	m_strSql.Format("create table %s(nOldPara smallint(3) not Null,segID int primary key,nX smallint(3) not Null,nY smallint(3) not Null,nWidth smallint(3) not Null,nHeight smallint(3) not Null,origFrame int not Null,segSize enum('0','1','2') not Null)",OrigTraceTableName);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		return true;
	}
}
///@brief CDataMySql��Ľ����¾ɶκŶ�Ӧ����
/// 
///����һ����Ϊ�������¾ɶκŶ�Ӧ���м�������Ϊ(nOldPara int primary key,nNewPara int not Null)
///@param[in|out] NewToOldParaTableName Ҫ�����ı���|NULL
///@pre  NULL
///@return NULL
///@retval BOOL ���ز����Ƿ�ɹ�
///@post NULL

bool CDataMySql::CreateNewToOldParaTable(CString NewToOldParaTableName)
{
	CString m_strSql;///<mysql��ѯ���
	m_strSql.Format("create table %s(nOldPara int primary key ,nNewPara int not Null)",NewToOldParaTableName);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		return true;
	}
}
///@brief CDataMySql��Ľ����¾�֡�Ŷ�Ӧ����
/// 
///����һ����Ϊ�������¾�֡�Ŷ�Ӧ���м�������Ϊ(origFrame int primary key,newFrame int not Null)
///@param[in|out] NewToOldFrameTableName Ҫ�����ı���|NULL
///@pre  NULL
///@return NULL
///@retval BOOL ���ز����Ƿ�ɹ�
///@post NULL
bool CDataMySql::CreateNewToOldFrameTable(CString NewToOldFrameTableName)
{
	CString m_strSql;///<mysql��ѯ���
	m_strSql.Format("create table %s(origFrame int primary key,newFrame int not Null)",NewToOldFrameTableName);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		return true;
	}
}

///@brief CDataMySql��Ľ����ϳ�ǰ��ͼ��Ϣ����
/// 
///����һ����Ϊ�����ĺϳ�ǰ��ͼ��Ϣ���м�������Ϊ(nOldPara int,segID int not null, nX smallint(3) not null,\
		nY smallint(3) not null,nWidth smallint(3) not null,nHeight smallint(3) not null)
///@param[in|out] CombineSegsTableName Ҫ�����ı���|NULL
///@pre  NULL
///@return NULL
///@retval BOOL ���ز����Ƿ�ɹ�
///@post NULL
bool CDataMySql::CreateCombineSegsTable(CString CombineSegsTableName)
{
	CString m_strSql;///<mysql��ѯ���
	m_strSql.Format("create table %s(nOldPara int,segID int not null, nX smallint(3) not null,\
		nY smallint(3) not null,nWidth smallint(3) not null,nHeight smallint(3) not null)", CombineSegsTableName);
	if (mysql_real_query(&m_mysql, (char*)(LPCTSTR)m_strSql, (UINT)m_strSql.GetLength()) != 0)
	{
		print_error(&m_mysql, "error message");
		return false;
	}
	else
	{
		return true;
	}
}

///@brief CDataMySql��Ĳ������ݵ��ϳ�ǰ��ͼ��Ϣ����
/// 
///��һ����¼���뵽����
///@param[in|out] traceTab ǰ����Ϣ; CombineSegsTableName ����|NULL
///@pre  NULL
///@return NULL
///@retval BOOL ���ز����Ƿ�ɹ�
///@post NULL
bool CDataMySql::InsertData2CombineSegsTable(OrigTraceTable traceTab, CString CombineSegsTableName)
{
	CString m_strSql;///<mysql��ѯ���
	m_strSql.Format("insert into %s(nOldPara, segID, nX, nY, nWidth, nHeight)\
		values(\'%d\',\'%d\',\'%d\',\'%d\',\'%d\',\'%d\')",\
		CombineSegsTableName, traceTab.nOldPara, traceTab.segID, traceTab.nX, traceTab.nY, traceTab.nWidth, traceTab.nHeight);
	if (mysql_real_query(&m_mysql, (char*)(LPCTSTR)m_strSql, (UINT)m_strSql.GetLength()) != 0)
	{
		print_error(&m_mysql, "error message");
		return false;
	}
	else
	{
		return true;
	}
}
///@brief CDataMySql��Ĳ������ݵ���¼����
/// 
///��һ����¼���뵽��¼����
///@param[in|out] CaseTableData Ҫ����ļ�¼;CaseTableName ��¼�������|NULL
///@pre  NULL
///@return NULL
///@retval BOOL ���ز����Ƿ�ɹ�
///@post NULL
bool CDataMySql::InsertDataCaseTable(CaseTable CaseTableData ,CString CaseTableName)
{
	CString m_strSql;///<mysql��ѯ���
	m_strSql.Format("insert into %s(caseName,caseCategory,caseRecordTime,caseHappenTime,caseDescription,caseNote)values(\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\')" ,CaseTableName,CaseTableData.caseName,CaseTableData.caseCategory,CaseTableData.caseRecordTime,CaseTableData.caseHappenTime,CaseTableData.caseDescription,CaseTableData.caseNote);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		return true;
	}
}
///@brief CDataMySql��Ĳ������ݵ���Ƶ����
/// 
///��һ����¼���뵽��Ƶ����
///@param[in|out] VideoTableData Ҫ����ļ�¼|NULL
///@pre  NULL
///@return NULL
///@retval BOOL ���ز����Ƿ�ɹ�
///@post NULL
bool CDataMySql::InsertData2VideoTable(VideoTable VideoTableData)
{
	CString m_strSql;///<mysql��ѯ���
	m_strSql.Format("insert into videoTable(caseName,cameraName,originPath,segPath,fusionPath) values(\'%s\',\'%s\',\'%s\',\'%s\',\'%s\')" ,VideoTableData.caseName,VideoTableData.cameraName,VideoTableData.originPath,VideoTableData.segPath,VideoTableData.fusionPath);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		return true;
	}
}
///@brief CDataMySql��Ĳ������ݵ�ͼƬ����
/// 
///��һ����¼���뵽ͼƬ����
///@param[in|out] imgTableData Ҫ����ļ�¼|NULL
///@pre NULL
///@return NULL
///@retval BOOL ���ز����Ƿ�ɹ�
///@post NULL
bool CDataMySql::InsertData2ImageTable(ImageTable imgTableData)
{
	CString m_strSql;///<mysql��ѯ���
	m_strSql.Format("insert into imageTable(caseName,imageCategory,imagePath) values(\'%s\',\'%s\',\'%s\')" ,imgTableData.caseName,imgTableData.imageCategory,imgTableData.imagePath);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		return true;
	}
}
///@brief CDataMySql��Ĳ������ݵ�ԭʼtrace����
/// 
///��һ����¼���뵽ԭʼtrace����
///@param[in|out] infor1 Ҫ����ļ�¼;OrigTraceTableName Ҫ�������ݵı���|NULL
///@pre NULL
///@return NULL
///@retval BOOL ���ز����Ƿ�ɹ�
///@post NULL
bool CDataMySql::InsertData2OrigTraceTable(OrigTraceTable infor1,CString OrigTraceTableName)
{
	CString m_strSql;///<mysql��ѯ���
	m_strSql.Format("insert into %s(nOldPara,segID,nX,nY,nWidth,nHeight,origFrame,segSize)\
					values(\'%d\',\'%d\',\'%d\',\'%d\',\'%d\',\'%d\',\'%d\',\'%d\')",\
					OrigTraceTableName,infor1.nOldPara,infor1.segID,infor1.nX,infor1.nY,infor1.nWidth,infor1.nHeight,infor1.origFrame,infor1.segSize); //sql�������
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		return true;
	}
}

///@brief CDataMySql��Ĳ������ݵ��¾ɶζ�Ӧ����
/// 
///��һ����¼���뵽�¾ɶζ�Ӧ����
///@param[in|out] infor2 Ҫ����ļ�¼;NewToOldParaTableName Ҫ�������ݵı���|NULL
///@pre NULL
///@return NULL
///@retval BOOL ���ز����Ƿ�ɹ�
///@post NULL
bool CDataMySql::InsertData2NewToOldParaTable(NewToOldParaTable infor2,CString NewToOldParaTableName)
{
	CString m_strSql;///<mysql��ѯ���
	m_strSql.Format("insert into %s(nNewPara,nOldPara)values(\'%d\',\'%d\')",NewToOldParaTableName,infor2.nNewPara,infor2.nOldPara);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		return true;
	}
}

///@brief CDataMySql��Ĳ������ݵ��¾�֡��Ӧ����
/// 
///��һ����¼���뵽�¾�֡��Ӧ����
///@param[in|out] infor3 Ҫ����ļ�¼;NewToOldFrameTableName Ҫ�������ݵı���|NULL
///@pre NULL
///@return NULL
///@retval BOOL ���ز����Ƿ�ɹ�
///@post NULL
bool CDataMySql::InsertData2NewToOldFrameTable(NewToOldFrameTable infor3,CString NewToOldFrameTableName)
{
	CString m_strSql;///<mysql��ѯ���
	m_strSql.Format("insert into %s(origFrame,newFrame)values(\'%d\',\'%d\')",NewToOldFrameTableName,infor3.origFrame,infor3.newFrame);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		return true;
	}
}

///@brief CDataMySql�������Ƶ���в���ԭʼ��Ƶ֡������
/// 
///������Ƶ����ĳ���ں���Ƶ��Ӧ�ļ�¼��ԭʼ��Ƶ����֡��
///@param[in|out] origTotalFrames ԭʼ��Ƶ����֡��;FusVideoName �ں���Ƶ������|NULL
///@pre NULL
///@return NULL
///@retval BOOL ���ز����Ƿ�ɹ�
///@post NULL
bool CDataMySql::InsertorigTotalFrames2VideoTable(int origTotalFrames,CString FusVideoName)
{
	CString m_strSql;///<mysql��ѯ���
	m_strSql.Format("update videoTable set origTotalFrames=\'%d\' where fusionPath=\'%s\'",origTotalFrames,FusVideoName);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		return true;
	}
}
///@brief CDataMySql�������Ƶ���в���ָ���Ƶ֡������
/// 
///������Ƶ����ĳ���ں���Ƶ��Ӧ�ļ�¼�зָ���Ƶ����֡��
///@param[in|out] segTotalFrames �ָ���Ƶ����֡��;FusVideoName �ں���Ƶ������|NULL
///@pre NULL
///@return NULL
///@retval BOOL ���ز����Ƿ�ɹ�
///@post NULL
bool CDataMySql::InsertsegTotalFrames2VideoTable(int segTotalFrames,CString FusVideoName)
{
	CString m_strSql;///<mysql��ѯ���
	m_strSql.Format("update videoTable set segTotalFrames=\'%d\' where fusionPath=\'%s\'",segTotalFrames,FusVideoName);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		return true;
	}
}
///@brief CDataMySql�������Ƶ���в����ں���Ƶ֡������
/// 
///������Ƶ����ĳ���ں���Ƶ��Ӧ�ļ�¼���ں���Ƶ����֡��
///@param[in|out] fusTotalFrames �ں���Ƶ����֡��;FusVideoName �ں���Ƶ������|NULL
///@pre NULL
///@return NULL
///@retval BOOL ���ز����Ƿ�ɹ�
///@post NULL
bool CDataMySql::InsertfusTotalFrames2VideoTable(int fusTotalFrames,CString FusVideoName)
{
	CString m_strSql;///<mysql��ѯ���
	m_strSql.Format("update videoTable set fusTotalFrames=\'%d\' where fusionPath=\'%s\'",fusTotalFrames,FusVideoName);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		return true;
	}
}
///@brief CDataMySql�������Ƶ���в����ں���Ƶ֡������
/// 
///������Ƶ����ĳ���ں���Ƶ��Ӧ�ļ�¼���ں���Ƶ����֡��
///@param[in|out] fusTotalFrames �ں���Ƶ����֡��;FusVideoName �ں���Ƶ������|NULL
///@pre NULL
///@return NULL
///@retval BOOL ���ز����Ƿ�ɹ�
///@post NULL
bool CDataMySql::InsertSegVideo2VideoTable(CString segVideoPath,CString caseName,CString cameraName,CString originPath)
{
	CString m_strSql;///<mysql��ѯ���
	m_strSql.Format("update videoTable set segPath=\'%s\' where caseName=\'%s\' and cameraName=\'%s\' and originPath=\'%s\'" ,segVideoPath,caseName,cameraName,originPath);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		return true;
	}
}
///@brief CDataMySql�������Ƶ���в����ں���Ƶ·������
/// 
///������Ƶ����ĳ��¼ĳ��ص�ĳ����Ƶ��Ӧ�ļ�¼���ں���Ƶ��·��
///@param[in|out] fusionVideoPath �ں���Ƶ����֡��;caseName ��¼����;cameraName ��ص�����;originPath ԭʼ��Ƶ·��|NULL
///@pre NULL
///@return NULL
///@retval BOOL ���ز����Ƿ�ɹ�
///@post NULL
bool CDataMySql::InsertFusionVideo2VideoTable(CString fusionVideoPath,CString caseName,CString cameraName,CString originPath)
{
	CString m_strSql;///<mysql��ѯ���
	m_strSql.Format("update videoTable set fusionPath=\'%s\' where caseName=\'%s\' and cameraName=\'%s\' and originPath=\'%s\'" ,fusionVideoPath,caseName,cameraName,originPath);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		return true;
	}
}
///@brief CDataMySql��Ĳ�����Ƶ����ԭʼ��Ƶ��֡���ĺ���
/// 
///���ں���Ƶ·���ڼ�¼���в��Ҹ��ں���Ƶ��Ӧ��ԭʼ��Ƶ����֡��
///@param[in|out] FusVideoName �ں���Ƶ·��|NULL
///@pre NULL
///@return NULL
///@retval int ���ز��ҵ����ں���Ƶ����֡�����������ʧ�ܲ���Ϊ-1
///@post NULL
int CDataMySql::GetorigTotalFramesFromVideoTable(CString FusVideoName)
{
	CString m_strSql;///<mysql��ѯ���
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	int params = -1;
	m_strSql.Format("select origTotalFrames from videoTable where fusionPath=\'%s\'",FusVideoName);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			params = atoi(m_sqlRow[0]);
		}
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
	}
	return params;
}
///@brief CDataMySql��Ĳ�����Ƶ���зָ���Ƶ��֡���ĺ���
/// 
///���ں���Ƶ·���ڼ�¼���в��Ҹ��ں���Ƶ��Ӧ�ķָ���Ƶ����֡��
///@param[in|out] FusVideoName �ں���Ƶ·��|NULL
///@pre NULL
///@return NULL
///@retval int ���ز��ҵ��ķָ���Ƶ����֡�����������ʧ�ܲ���Ϊ-1
///@post NULL
int CDataMySql::GetsegTotalFramesFromVideoTable(CString FusVideoName)
{
	CString m_strSql;///<mysql��ѯ���
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	int params = -1;
	m_strSql.Format("select segTotalFrames from videoTable where fusionPath=\'%s\'",FusVideoName);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			params = atoi(m_sqlRow[0]);
		}
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
	}
	return params;
}
///@brief CDataMySql��Ĳ�����Ƶ�����ں���Ƶ��֡���ĺ���
/// 
///���ں���Ƶ·���ڼ�¼���в��Ҹ��ں���Ƶ����֡��
///@param[in|out] FusVideoName �ں���Ƶ·��|NULL
///@pre NULL
///@return NULL
///@retval int ���ز��ҵ����ں���Ƶ����֡�����������ʧ�ܲ���Ϊ-1
///@post NULL
int CDataMySql::GetfusTotalFramesFromVideoTable(CString FusVideoName)
{
	CString m_strSql;///<mysql��ѯ���
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	int params = -1;
	m_strSql.Format("select fusTotalFrames from videoTable where fusionPath=\'%s\'",FusVideoName);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			params = atoi(m_sqlRow[0]);
		}
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
	}
	return params;
}


///@brief CDataMySql��Ĳ�ѯ�¶κŵĺ���
/// 
///���ݾɶκ����¾ɶζ�Ӧ���в����¶κ�
///@param[in|out] oldParag �ɶκ�;NewToOldParaTableName �¾ɶζ�Ӧ��ı���|NULL
///@pre NULL
///@return NULL
///@retval int ���ز鵽���¶κţ��������ʧ�ܷ���-1
///@post NULL
int CDataMySql::FindNewParaFromNewToOldParaTable(int oldParag,CString NewToOldParaTableName)
{
	CString m_strSql;///<mysql��ѯ���
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	int params = -1;
	m_strSql.Format("select nNewPara from %s where nOldPara = \'%d\'",NewToOldParaTableName,oldParag);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			params = atoi(m_sqlRow[0]);
		}
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
	}
	return params;
}

///@brief CDataMySql��Ļ��ԭʼtrace�����м�¼�ĺ���
/// 
///�����к����ƶ����л�ø��е�һ����¼����ֵ���ṹ���ÿһ������
///@param[in|out] row �к�;OrigTraceTableName ԭʼtrace����|infor1 ��ô洢��¼��OrigTraceTable�ṹ��
///@pre NULL
///@return NULL
///@retval BOOL ���ز����Ƿ�ɹ�
///@post NULL
bool CDataMySql::GetInfor1DataFromOrigTraceTable(int segID,OrigTraceTable* infor1,CString OrigTraceTableName)
{
	CString m_strSql;///<mysql��ѯ���
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	m_strSql.Format("select nOldPara,segID,nX,nY,nWidth,nHeight,origFrame,segSize from %s where segID=\'%d\'",OrigTraceTableName,segID);
	
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
	   {
			m_sqlRow=mysql_fetch_row(m_result);
			infor1->nOldPara = atoi(m_sqlRow[0]);
			infor1->segID = atoi(m_sqlRow[1]);
			infor1->nX = atoi(m_sqlRow[2]);
			infor1->nY = atoi(m_sqlRow[3]);
			infor1->nWidth = atoi(m_sqlRow[4]);
			infor1->nHeight = atoi(m_sqlRow[5]);
			infor1->origFrame = atoi(m_sqlRow[6]);
			infor1->segSize = atoi(m_sqlRow[7]);
			mysql_free_result(m_result);///<�ͷŽ����Դ	  
		}
		return true; 
	}
		
}

///@brief CDataMySql��ĵõ�����Ŀ�������ĺ���
/// 
///�õ����ݿ���ĳ��Ĳ�ͬ�˶�Ŀ������
///@param[in|out] tableName ����|NULL
///@pre NULL
///@return NULL
///@retval int ���ز�ͬ���˶�Ŀ���������������ʧ�ܷ���-1
///@post NULL
int CDataMySql::GetTableDistinctNum(CString tableName)
{
	CString m_strSql;///<mysql��ѯ���
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	int params = -1;
	m_strSql.Format("select count(distinct objectID) from %s",tableName);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			params = atoi(m_sqlRow[0]);
		}
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
	}
	return params;
}
///@brief CDataMySql�����ձ�ĺ���
/// 
///������ݿ���ĳ����
///@param[in|out] tableName ����|NULL
///@pre NULL
///@return NULL
///@retval BOOL ���ز����Ƿ�ɹ�
///@post NULL
bool CDataMySql::CleanTable(CString tableName)
{
	CString m_strSql;///<mysql��ѯ���
	m_strSql.Format("truncate table %s",tableName); 
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		return true;
	}
}
///@brief CDataMySql���ɾ����ĺ���
/// 
///������ݿ��д���ĳ��������ɾ��
///@param[in|out] tableName ����|NULL
///@pre NULL
///@return NULL
///@retval BOOL ���ز����Ƿ�ɹ�
///@post NULL
bool CDataMySql::DropTable(CString tableName)
{
	CString m_strSql;///<mysql��ѯ���
	m_strSql.Format("drop table if exists mydb.%s",tableName); 
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		return true;
	}
}

///@brief CDataMySql��Ĵ���ǰ���α�ĺ���
/// 
///����ĳ�����ֵ�ǰ���α��м�������Ϊ(nOldPara int primary key,startFrame int not null,endFrame int not null)
///@param[in|out] tableName Ҫ�����ı���|NULL
///@pre NULL
///@return NULL
///@retval BOOL ���ز����Ƿ�ɹ�
///@post NULL
bool CDataMySql::CreateVideoFGTable(CString tableName)
{
	CString m_strSql;
	m_strSql.Format("create table %s(nOldPara int primary key,startFrame int not null,endFrame int not null)",tableName);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		return true;
	}
}
///@brief CDataMySql��Ĳ������ݵ�ǰ���α���
/// 
///��һ����¼���뵽ǰ���α���
///@param[in|out] tableName Ҫ�������ݵı���;infor Ҫ����ļ�¼|NULL
///@pre  NULL
///@return NULL
///@retval BOOL ���ز����Ƿ�ɹ�
///@post NULL
bool CDataMySql::InsertData2VideoFGTable(VideoFGTable infor,CString tableName)
{
	CString m_strSql;
	m_strSql.Format("insert into %s(nOldPara,startFrame,endFrame)values(\'%d\',\'%d\',\'%d\')",tableName,infor.nOldPara,infor.startFrame,infor.endFrame);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		return true;
	}
}
int CDataMySql::FindEndFrameFromVideoFGTable(int paraNum,CString TableName)
{
	CString m_strSql;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	int params = -1;
	m_strSql.Format("select endFrame from %s where nOldPara = \'%d\'",TableName,paraNum);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			params = atoi(m_sqlRow[0]);
		}
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
	}
	return params;
}
int CDataMySql::FindStartFrameFromVideoFGTable(int paraNum,CString TableName)
{
	CString m_strSql;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	int params = -1;
	m_strSql.Format("select startFrame from %s where nOldPara = \'%d\'",TableName,paraNum);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			params = atoi(m_sqlRow[0]);
		}
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
	}
	return params;
}
///@brief CDataMySql��ı����α�ĺ���
/// 
///����ĳ�����ֵı����α��м�������Ϊ(BGImgID int primary key,startFrame int not null,endFrame int not null)
///@param[in|out] tableName Ҫ�����ı���|NULL
///@pre NULL
///@return NULL
///@retval BOOL ���ز����Ƿ�ɹ�
///@post NULL
bool CDataMySql::CreateVideoBGTable(CString tableName)
{
	CString m_strSql;
	m_strSql.Format("create table %s(BGImgID int primary key,startFrame int not null,endFrame int not null)",tableName);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		return true;
	}
}
///@brief CDataMySql��Ĳ������ݵ������α���
/// 
///��һ����¼���뵽�����α���
///@param[in|out] tableName Ҫ�������ݵı���;infor Ҫ����ļ�¼|NULL
///@pre  NULL
///@return NULL
///@retval BOOL ���ز����Ƿ�ɹ�
///@post NULL
bool CDataMySql::InsertData2VideoBGTable(VideoBGTable infor,CString tableName)
{
	CString m_strSql;
	m_strSql.Format("insert into %s(BGImgID,startFrame,endFrame)values(\'%d\',\'%d\',\'%d\')",tableName,infor.BGImgID,infor.startFrame,infor.endFrame);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		return true;
	}
}
///@brief CDataMySql��Ĳ��ұ����ν���֡����
/// 
///���ݱ����κ��ڱ����α��в��ҸöεĽ���֡��
///@param[in|out] bkgID �����α��;tableName Ҫ���ҵı���|NULL
///@pre  NULL
///@return NULL
///@retval int ���ҵ��ı����ν���֡�ţ��������ʧ�ܷ���-1
///@post NULL
int CDataMySql::FindEndFrameFromVideoBGTable(int bkgID,CString TableName)
{
	CString m_strSql;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	m_strSql.Format("select endFrame from %s where BGImgID = \'%d\'",TableName,bkgID);
	int params = -1;
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			params = atoi(m_sqlRow[0]);
		}
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
	}
	return params;
}
///@brief CDataMySql��Ĳ��ұ�������ʼ֡����
/// 
///���ݱ����κ��ڱ����α��в��Ҹöε���ʼ֡��
///@param[in|out] bkgID �����α��;tableName Ҫ���ҵı���|NULL
///@pre  NULL
///@return NULL
///@retval int ���ҵ��ı�������ʼ֡�ţ��������ʧ�ܷ���-1
///@post NULL
int CDataMySql::FindStartFrameFromVideoBGTable(int bkgID,CString TableName)
{
	CString m_strSql;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	int params = -1;
	m_strSql.Format("select startFrame from %s where BGImgID = \'%d\'",TableName,bkgID);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			params = atoi(m_sqlRow[0]);
		}
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
	}
	return params;
}

///@brief CDataMySql��ĵõ�ĳ��¼ĳ��ص�����Ƶ�����ĺ���
/// 
///����Ƶ���еõ�ĳ��¼ĳ��ص�����Ƶ����
///@param[in|out] CaseName ��¼����;CameraName ��ص�����|NULL
///@pre  NULL
///@return NULL
///@retval int ������Ƶ��Ŀ���������ʧ�ܷ���-1
///@post NULL
int CDataMySql::GetOrigVideoNumFromVideoTable(CString CaseName,CString CameraName)    
{
	CString m_strSql;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	m_strSql.Format("select count(*) from VideoTable where caseName = \'%s\' and CameraName = \'%s\'",CaseName,CameraName);
	int params = -1;
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			params = atoi(m_sqlRow[0]);
		}
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
	}
	return params;
}
///@brief CDataMySql��ĵõ�ĳ��¼��ԭʼ��Ƶ�����ĺ���
/// 
///����Ƶ���еõ�ĳ��¼��ԭʼ��Ƶ����
///@param[in|out] CaseName ��¼����|NULL
///@pre  NULL
///@return NULL
///@retval int ������Ƶ��Ŀ���������ʧ�ܷ���-1
///@post NULL
int CDataMySql::GetCaseOrigVideoNumFromVideoTable(CString CaseName)
{
	CString m_strSql;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	m_strSql.Format("select count(*) from VideoTable where caseName = \'%s\'",CaseName);
	int params = -1;
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			params = atoi(m_sqlRow[0]);
		}
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
	}
	return params;

}
///@brief CDataMySql��Ļ���ں���Ƶ�ĺ���
/// 
///����Ƶ���еõ�ĳ��¼��ĳ��ص���ԭʼ��Ƶ��Ӧ���ں���Ƶ��·��
///@param[in|out] caseName ��¼����;cameraName ��ص�����;videoName ԭʼ��Ƶ����|NULL
///@pre  NULL
///@return NULL
///@retval CString �����ں���Ƶ���ƣ��������ʧ�ܷ��ء�-1��
///@post NULL
CString CDataMySql::GetFusionNameFromVideoTable(CString caseName,CString cameraName,CString videoName)
{
	CString m_strSql;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	CString params = "-1";
	m_strSql.Format("select fusionPath from VideoTable where caseName = \'%s\' and cameraName = \'%s\' and originPath = \'%s\'",caseName,cameraName,videoName) ; 
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			params = m_sqlRow[0];
		}
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
	}
	return params;
}

///@brief CDataMySql��Ļ����֡�������˶�Ŀ���ROI�ĺ���
/// 
///����trace���и�����֡�Ż�����и�֡���˶�Ŀ���ROI
///@param[in|out] newFrame ��֡��;tableName Ҫ���ҵ���trace��|m_ROI ������ҵ��ĸ�֡�е������ROI
///@pre  NULL
///@return NULL
///@retval BOOL ���ز����Ƿ�ɹ�
///@post NULL
bool CDataMySql::FindROIFromNewTraceTable(int NewFrame,vector <CvRect> *m_ROI,CString tableName)
{
	CString m_strSql;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	m_strSql.Format("select nX,nY,nWidth,nHeight from %s where newFrame = \'%d\'",tableName,NewFrame) ;
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		m_result = NULL;///<����
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		for (int i=0;i<m_result->row_count;i++)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			CvRect r;
			r.x = atoi(m_sqlRow[0]);
			r.y = atoi(m_sqlRow[1]);
			r.width = atoi(m_sqlRow[2]);
			r.height = atoi(m_sqlRow[3]);
			m_ROI->push_back(r);
		}
		if(m_result!=NULL)mysql_free_result(m_result);///<�ͷŽ����Դ
		return true;
	}
}

///@brief CDataMySql��Ļ�úϳ�ǰ��ͼ�������˶�Ŀ���ROI�ĺ���
/// 
///��Combine���л�������˶�Ŀ���ROI
///@param[in|out] newFrame ��֡��;tableName Ҫ���ҵ���trace��|m_ROI ������ҵ��ĸ�֡�е������ROI
///@pre  NULL
///@return NULL
///@retval BOOL ���ز����Ƿ�ɹ�
///@post NULL
bool CDataMySql::FindROIFromCombineSegsTable( vector <CvRect> *m_ROI, CString tableName)
{
	CString m_strSql;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	m_strSql.Format("select nX,nY,nWidth,nHeight from %s ", tableName);
	if (mysql_real_query(&m_mysql, (char*)(LPCTSTR)m_strSql, (UINT)m_strSql.GetLength()) != 0)
	{
		m_result = NULL;///<����
		print_error(&m_mysql, "error message");
		return false;
	}
	else
	{
		m_result = mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		for (int i = 0; i<m_result->row_count; i++)
		{
			m_sqlRow = mysql_fetch_row(m_result);///<������н���ַ���
			CvRect r;
			r.x = atoi(m_sqlRow[0]);
			r.y = atoi(m_sqlRow[1]);
			r.width = atoi(m_sqlRow[2]);
			r.height = atoi(m_sqlRow[3]);
			m_ROI->push_back(r);
		}
		if (m_result != NULL)mysql_free_result(m_result);///<�ͷŽ����Դ
		return true;
	}
}


///@brief CDataMySql�����trace��ĺ���
/// 
///����ĳ�����ֵ���trace�α��м�������Ϊ(newFrame int not null,segID int primary key,nTop int not null,nBottom int not null,nLeft int not null,nRight int not null,CentX int not null,CentY int not null,origFrame int not null,segSize varchar(20) not null)
///@param[in|out] tableName Ҫ�����ı���|NULL
///@pre NULL
///@return NULL
///@retval BOOL ���ز����Ƿ�ɹ�
///@post NULL
bool CDataMySql::CreateNewTraceTable(CString tableName)
{
	CString m_strSql;
	m_strSql.Format("create table %s(newFrame int not null,segID int primary key,nX smallint(3) not null,nY smallint(3) not null,nWidth smallint(3) not null,nHeight smallint(3) not null,origFrame int not null,segSize enum('0','1','2') not null)",tableName);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		return true;
	}
}
///@brief CDataMySql����ں�������trace��ĺ���
/// 
///����ԭʼtrace����¾�֡��Ӧ��ľ�֡�������������������trace��
///@param[in|out] newTraceTable ��trace����;origTraceTable ԭʼtrace����;frameTable �¾�֡��Ӧ��|NULL
///@pre  NULL
///@return NULL
///@retval BOOL ���ز����Ƿ�ɹ�
///@post NULL
bool CDataMySql::Unite2NewTraceTable(CString newTraceTable,CString origTraceTable,CString frameTable)
{
	CString m_strSql;
	m_strSql.Format("insert into %s(newFrame,segID,nX,nY,nWidth,nHeight,origFrame,segSize) \
					select newFrame,segID,nX,nY,nWidth,nHeight,%s.origFrame,segSize from %s,%s \
					where %s.origFrame=%s.origFrame",newTraceTable,origTraceTable,origTraceTable,frameTable,origTraceTable,frameTable);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		return true;
	}
}
///@brief CDataMySql��ĸ��������С���ҵĺ���
/// 
///��������Ĵ�С�ڱ��в��ҷ��������ļ�¼���������ݴ���ṹ����
///@param[in|out] tableName Ҫ���ҵı���;segSize �����С|segIdParam ���ҵ����ݴ���vector������
///@pre  NULL
///@return NULL
///@retval BOOL ���ز����Ƿ�ɹ�
///@post NULL
bool CDataMySql::SearchSegOfSize(CString tableName,int segSize,vector<SearchSegIDParams>* segIdParam)
{
 CString m_strSql;
 MYSQL_RES *m_result;
 MYSQL_ROW m_sqlRow;
 m_strSql.Format("select origFrame,nX,nY,nWidth,nHeight from %s where segSize=\'%d\'",tableName,segSize);  
 if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
 { 
	 print_error(&m_mysql,"error message");
	 return false;
 }
 else
 {
	 m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
	 if (m_result)
	 {
		 SearchSegIDParams tempSearchData;
		 m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
		while (m_sqlRow)
		{
			CString  temp= m_sqlRow[0];
			 if(!temp.IsEmpty())
			 {
				 tempSearchData.origFrame   = atoi(m_sqlRow[0]);
				 tempSearchData.ROI.nX    = atoi(m_sqlRow[1]);
				 tempSearchData.ROI.nY = atoi(m_sqlRow[2]);
				 tempSearchData.ROI.nWidth   = atoi(m_sqlRow[3]);
				 tempSearchData.ROI.nHeight  = atoi(m_sqlRow[4]);
				 (*segIdParam).push_back(tempSearchData);
			 }
			 m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
		}
		 mysql_free_result(m_result);///<�ͷŽ����Դ
	 }
 }
 return true;
}
///@brief CDataMySql����ж����ݿ���ĳ�����Ƿ���ڵĺ���
/// 
///�ж����ݿ���ĳ�����Ƿ����
///@param[in|out] tableName Ҫ���ҵı���|ifExist ���Ƿ���ڵı�־
///@pre  NULL
///@return NULL
///@retval BOOL ���ز����Ƿ�ɹ�
///@post NULL
bool  CDataMySql::IfExistTable(CString tableName,bool* ifExist)
{
	CString m_strSql;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	//m_strSql.Format("show tables from mydb like '%s'",tableName);
	//�������ݿ������ƣ��޸�by luying 2013.3.4  
	m_strSql.Format("select TABLE_NAME from INFORMATION_SCHEMA.TABLES where TABLE_SCHEMA = 'mydb' and TABLE_NAME='%s'",tableName);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		//*ifExist = false;
		return false;
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			if(m_sqlRow==NULL)
			{
				*ifExist = false;
			}
			else
			{
				*ifExist = true;
			}
			mysql_free_result(m_result);///<�ͷŽ����Դ
		}
		else
		{
			*ifExist = false;
		}
		return true;
	}
}

///@brief CDataMySql��ĸ���ROI��Ϣ�ҵ�ԭʼ��Ƶ֡���ĺ���
/// 
///��new trace���и���ROI��Ϣ�ҵ�ԭʼ��Ƶ֡��
///@param[in|out] newTraceTable Ҫ���ҵı���;rect Ҫ���ҵ�ROI��Ϣ|NULL
///@pre  NULL
///@return NULL
///@retval int ������ԭʼ��Ƶ�е�֡��,�������ʧ�ܷ���-1
///@post NULL
int CDataMySql::FindOrigFrameFromNewTraceTable(CString newTraceTable,CvRect rect)
{

	CString m_strSql;
	m_strSql.Format("select origFrame from %s where nX =\'%d\' and nWidth = \'%d\'",newTraceTable,rect.x,rect.width);
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	int params = -1;
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			params = atoi(m_sqlRow[0]);
		}
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
	}
	return params;
}
///@brief CDataMySql��Ľ���clist��ĺ���
/// 
///����һ�����ڼ�¼������ص�������CListCtrl�кŵı�������������Ϊ(caseName VARCHAR(255) not null,cameraName VARCHAR(255) not null,videoName VARCHAR(255) not null,rowNum int primary key)
///@param[in|out] tableName Ҫ�����ı���|NULL
///@pre  NULL
///@return NULL
///@retval BOOL �����Ƿ�ɹ�
///@post NULL
bool CDataMySql::CreateCListItemTable(CString tableName)
{
	CString m_strSql;
	m_strSql.Format("create table %s(caseName VARCHAR(255) not null,cameraName VARCHAR(255) not null,videoName VARCHAR(255) not null,rowNum int primary key)",tableName);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		return true;
	}
}

///@brief CDataMySql����жϱ����Ƿ��Ѿ�����ĳ����Ƶ�ĺ���
/// 
///�б����Ƿ��Ѿ�����ĳ����¼ĳ����ص����Ƶ
///@param[in|out] tableName Ҫ��ѯ�ı���;caseName ��¼��;cameraName ��ص���|ifExist ��Ƶ�Ƿ����
///@pre  NULL
///@return NULL
///@retval BOOL �����Ƿ�ɹ�
///@post NULL
bool CDataMySql::IfExistCListItemTable(CString tableName,CString caseName,CString cameraName,bool* ifExist)
{
	CString m_strSql;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	m_strSql.Format("select count(*) from %s where caseName=\'%s\' and cameraName=\'%s\'",tableName,caseName,cameraName);
	int params = -1;
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			params = atoi(m_sqlRow[0]);
		}
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
	}
	if(params==0)
	{
		*ifExist = false;
	}
	else
	{
		*ifExist = true;
	}
	return true;

}
///@brief CDataMySql��Ĳ������ݵ�Clist����
/// 
///��һ����¼���뵽Clist����
///@param[in|out] tableName Ҫ�������ݵı���;caseName Ҫ����ļ�¼��;cameraName Ҫ�����¼�ļ�ص���;videoName Ҫ�����¼����Ƶ·��;clistRow Ҫ�����¼���к�|NULL
///@pre  NULL
///@return NULL
///@retval BOOL ���ز����Ƿ�ɹ�
///@post NULL
bool CDataMySql::InsertData2CListItemTable(CString tableName,CString caseName,CString cameraName,CString videoName,int clistRow)
{
	CString m_strSql;
	m_strSql.Format("insert into %s(caseName,cameraName,videoName,rowNum)values(\'%s\',\'%s\',\'%s\',\'%d\')",tableName,caseName,cameraName,videoName,clistRow);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		return true;
	}
}
///@brief CDataMySql��ĵõ�clist����ĳ�кŵ���Ƶ���Ƶĺ���
/// 
///����rowNum��clist���в���ԭʼ��Ƶ·��
///@param[in|out] clistTableName Ҫ��ѯ�ı���;clistRow ������rowNum��ֵ|NULL
///@pre  NULL
///@return NULL
///@retval CString ���ز�ѯ����ԭʼ��Ƶ·�����������ʧ�ܷ��ء�-1��
///@post NULL
CString CDataMySql::GetCurrentOrigVideoName(CString clistTableName,int clistRow)
{
	CString m_strSql;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	m_strSql.Format("select videoName from %s where rowNum=\'%d\'",clistTableName,clistRow);//originPath from videoTable,%s where videoTable.caseName=%s.caseName and videoTable.cameraName=%s.cameraName and %s.rowNum=\'%d\'",clistTableName,clistTableName,clistTableName,clistTableName,clistRow);
	CString params = "-1";
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			params = m_sqlRow[0];
		}
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
	}
	return params;
}
///@brief CDataMySql��ĵõ�clist����ĳ�кŵ��ں���Ƶ���Ƶĺ���
/// 
///����rowNum��clist�����Ƶ�����в����ں���Ƶ·��
///@param[in|out] clistTableName Ҫ��ѯ�ı���;clistRow ������rowNum��ֵ|NULL
///@pre  NULL
///@return NULL
///@retval CString ���ز�ѯ�����ں���Ƶ·�����������ʧ�ܷ��ء�-1��
///@post NULL
CString CDataMySql::GetCurrentFusionVideoName(CString clistTableName,int clistRow)
{
	CString m_strSql;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	m_strSql.Format("select fusionPath from videoTable,%s where videoTable.caseName=%s.caseName and videoTable.cameraName=%s.cameraName and %s.rowNum=\'%d\'",clistTableName,clistTableName,clistTableName,clistTableName,clistRow);
	CString params = "-1";
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			params = m_sqlRow[0];
		}
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
	}
	return params;
}
///@brief CDataMySql��ĵõ�Ŀǰ���ڴ�����Ƶ���ڵ��к�
/// 
///���ݼ�¼���ͼ�ص����õ�clist����ĳ��¼ĳ��ص��rowNum�ĺ���
///@param[in|out] clistTableName Ҫ��ѯ�ı���;caseName ��¼��;cameraName ��ص���|NULL
///@pre  NULL
///@return NULL
///@retval int ���ز�ѯ����rowNum���������ʧ�ܷ���-1
///@post NULL
int CDataMySql::GetCurrentProcessingRow(CString clistTableName,CString caseName,CString cameraName)
{
	CString m_strSql;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	m_strSql.Format("select rowNum from %s where caseName = \'%s\' and cameraName = \'%s\'",clistTableName,caseName,cameraName);
	int params = -1;
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			params = atoi(m_sqlRow[0]);
		}
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
	}
	return params;
}
///@brief CDataMySql��ĵõ�clist����ĳ�кŵļ�¼���Ƶĺ���
/// 
///����rowNum��clist���в��Ҹü�¼�ļ�¼����
///@param[in|out] clistTableName Ҫ��ѯ�ı���;clistRow ������rowNum��ֵ|NULL
///@pre  NULL
///@return NULL
///@retval CString ���ؼ�¼���ƣ��������ʧ�ܷ��ء�-1��
///@post NULL
CString CDataMySql::GetCurCaseName(CString clistTableName,int clistRow)
{
	CString m_strSql;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	m_strSql.Format("select caseName from %s where rowNum=\'%d\'",clistTableName,clistRow);
	CString params = "-1";
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			params = m_sqlRow[0];
		}
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
	}
	return params;
}
///@brief CDataMySql��ĵõ�clist����ĳ�кŵļ�ص����Ƶĺ���
/// 
///����rowNum��clist���в��Ҹü�¼�ļ�ص�����
///@param[in|out] clistTableName Ҫ��ѯ�ı���;clistRow ������rowNum��ֵ|NULL
///@pre  NULL
///@return NULL
///@retval CString ���ؼ�ص����ƣ��������ʧ�ܷ��ء�-1��
///@post NULL
CString CDataMySql::GetCurCameraName(CString clistTableName,int clistRow)
{
	CString m_strSql;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	m_strSql.Format("select cameraName from %s where rowNum=\'%d\'",clistTableName,clistRow);
	CString params = "-1";
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			params = m_sqlRow[0];
		}
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
	}
	return params;
}

///@brief CDataMySql��Ļ��ĳ��¼��ص���������Ƶ�ĺ���
/// 
///�����Ƶ����ĳ��¼ĳ��ص��°���ԭʼ��Ƶ���ָ���Ƶ���ں���Ƶ���ڵ�������Ƶ������
///@param[in|out] CaseName ��¼��;CameraName ��ص���;videoTotalNum ĳ��¼ĳ��ص���ԭʼ��Ƶ����Ŀ|VideoName_str ���õ���������Ƶ��vector����
///@pre  NULL
///@return NULL
///@retval BOOL ���ز����Ƿ�ɹ�
///@post NULL
bool CDataMySql::GetVideoNameFromVideoTable(CString CaseName,CString CameraName,CString(*VideoName_str)[3],int videoTotalNum)
{
	CString m_strSql;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	m_strSql.Format("select originPath,segPath,fusionPath from VideoTable where caseName = \'%s\' and cameraName = \'%s\'",CaseName,CameraName) ; 
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if(m_result)
		{
			for (int Num = 0 ; Num<videoTotalNum; Num++)
			{
				m_sqlRow=mysql_fetch_row(m_result);
				*(*(VideoName_str+Num)+0) = m_sqlRow[0];
				if(!m_sqlRow[1])
				{
				}
				else
				{
					*(*(VideoName_str+Num)+1) = m_sqlRow[1];
				}
				if(!m_sqlRow[2])
				{
				}
				else
				{
					*(*(VideoName_str+Num)+2) = m_sqlRow[2];
				}

			}
			mysql_free_result(m_result);///<�ͷŽ����Դ
		}	 
	}
	return true ;
}
///@brief CDataMySql��ĵõ�ĳ�ں���Ƶ�ļ�¼���ĺ���
/// 
///�����ں���Ƶ��������Ƶ���л�ø��ں���Ƶ��Ӧ�ļ�¼����
///@param[in|out] FusVideoName �ں���Ƶ����|NULL
///@pre  NULL
///@return NULL
///@retval CString ���ؼ�¼�����������ʧ�ܷ��ء�-1��
///@post NULL
CString CDataMySql::GetCaseNameFromVideoTable(CString FusVideoName)
{
	CString m_strSql;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	m_strSql.Format("select caseName from VideoTable where fusionPath = \'%s\'",FusVideoName);
	CString params = "-1";
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			params = m_sqlRow[0];
		}
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
	}
	return params;
}
///@brief CDataMySql��ĵõ�ĳ�ں���Ƶ�ļ�ص����ĺ���
/// 
///�����ں���Ƶ��������Ƶ���л�ø��ں���Ƶ��Ӧ�ļ�ص�����
///@param[in|out] FusVideoName �ں���Ƶ����|NULL
///@pre  NULL
///@return NULL
///@retval CString ���ؼ�ص������������ʧ�ܷ��ء�-1��
///@post NULL
CString CDataMySql::GetCameraNameFromVideoTable(CString FusVideoName)
{
	CString m_strSql;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	m_strSql.Format("select cameraName from VideoTable where fusionPath = \'%s\'",FusVideoName);
	CString params = "-1";
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			params = m_sqlRow[0];
		}
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
	}
	return params;
}
///@brief CDataMySql����жϼ�¼�����Ƿ��Ѿ�����ĳ����¼�ĺ���
/// 
///�жϼ�¼�����Ƿ��Ѿ�����ĳ����¼
///@param[in|out] caseName ��¼����|ifExist �Ƿ����ĳ����¼trueΪ�Ѿ�����
///@pre  NULL
///@return NULL
///@retval BOOL �������ݿ�����Ƿ�ɹ�
///@post NULL
bool CDataMySql::IfExistCaseNameInCaseTable(CString caseName,bool* ifExist)
{
	CString m_strSql;
	m_strSql.Format("select count(*) from caseTable where caseName=\'%s\'",caseName);
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	int params = 0;
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			params = atoi(m_sqlRow[0]);
		}
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ		
	}
	if(params==0)
	{
		*ifExist = false;
	}
	else
	{
		*ifExist = true;
	}
	return true;
}
///@brief CDataMySql��ĸ��¼�¼��Ϣ�ĺ���
/// 
///���¼�¼����ĳ����¼��Ӧ�ļ�¼
///@param[in|out] caseData ���µļ�¼;caseName Ҫ���µļ�¼��;tableName Ҫ���µı���|NULL
///@pre  NULL
///@return NULL
///@retval BOOL �������ݿ�����Ƿ�ɹ�
///@post NULL
bool CDataMySql::UpdateCaseDataInCaseTable(CaseTable caseData,CString caseName,CString tableName)
{
	CString m_strSql;///<mysql��ѯ���
	m_strSql.Format("update %s set caseName=\'%s\',caseCategory=\'%s\',caseRecordTime=\'%s\',\
					caseHappenTime=\'%s\',caseDescription=\'%s\',caseNote=\'%s\' where caseName=\'%s\'" ,
					tableName,caseData.caseName,caseData.caseCategory,caseData.caseRecordTime,caseData.caseHappenTime,
					caseData.caseDescription,caseData.caseNote,caseName);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		return true;
	}
}
///@brief CDataMySql��ĵõ�ĳ����¼��ص����ں���Ƶ·���ĺ���
/// 
///���ݼ�¼������ص���������Ƶ���еõ��ü�¼�ü�ص��µ������ں���Ƶ������
///@param[in|out] caseName ��¼��;CameraName ��ص���|fusionName_Str �õ������ں���Ƶ���Ƶ�vector
///@pre  NULL
///@return NULL
///@retval BOOL �������ݿ�����Ƿ�ɹ�
///@post NULL
bool CDataMySql::GetFusionNameFromVideoTable(CString caseName,CString CameraName,vector<CString>* fusionName_Str)
{
	CString m_strSql;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow=NULL;
	(*fusionName_Str).clear();
	m_strSql.Format("select fusionPath from VideoTable where caseName = \'%s\' and cameraName = \'%s\'",caseName,CameraName) ; 
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if(m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			while (m_sqlRow)
			{
				CString  temp= m_sqlRow[0];
				if(!temp.IsEmpty())
				{
					(*fusionName_Str).push_back(m_sqlRow[0]);   
				}
				m_sqlRow = mysql_fetch_row(m_result);///<������н���ַ���
			}
			mysql_free_result(m_result);///<�ͷŽ����Դ
		}
	}
	return true;
}
///@brief CDataMySql��Ĳ����¼��������ĺ���
/// 
///����һ����¼����������
///@param[in|out] clueData Ҫ����ļ�¼|NULL
///@pre  NULL
///@return NULL
///@retval BOOL �������ݿ�����Ƿ�ɹ�
///@post NULL
bool CDataMySql::InsertData2ClueTable(ClueTable clueData)
{
	CString m_strSql;///<mysql��ѯ���
	m_strSql.Format("insert into clueTable(caseName,cameraName,clueHappenTime,\
					clueCategory,latestModifyTime,filePath,clueDescription) \
					values(\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\')" ,
		clueData.caseName,clueData.cameraName,clueData.clueHappenTime,clueData.clueCategory,clueData.latestModifyTime,clueData.filePath,clueData.clueDescription);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		return true;
	}
}
///@brief CDataMySql��Ļ��ĳ��¼������Ŀ�ĺ���
/// 
///����һ����¼����������
///@param[in|out] caseName ��¼��|NULL
///@pre  NULL
///@return NULL
///@retval int ����������Ŀ���������ʧ���򷵻�-1
///@post NULL
int CDataMySql::GetClueNumFromClueTable(CString caseName)
{
	CString m_strSql;///<mysql��ѯ���
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	int params = -1;
	m_strSql.Format("select count(*) from clueTable where caseName = \'%s\'",caseName);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			params = atoi(m_sqlRow[0]);
		}
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
	}
	return params;
}
///@brief CDataMySql����ж�ĳ�������Ƿ���ڵĺ���
/// 
///���������и��ݼ�¼����ص㡢�������������ļ�·���ж������Ƿ���ڣ������������������������Ϣ
///@param[in|out] clueData ���ڲ��Һͱ���ṹ��ClueTable�ṹ��|isExistClue �����Ƿ����
///@pre  NULL
///@return NULL
///@retval BOOL �������ݿ�����Ƿ�ɹ�
///@post NULL
bool CDataMySql::GetClueDataFromClueTable(ClueTable* clueData,bool*isExistClue)
{
	CString m_strSql;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	m_strSql.Format("select clueHappenTime,latestModifyTime,clueDescription\
					from clueTable where caseName = \'%s\' and cameraName=\'%s\' and clueCategory=\'%s\'and filePath=\'%s\'",\
					clueData->caseName,clueData->cameraName,clueData->clueCategory,clueData->filePath) ; 
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if(m_result)
		{
			m_sqlRow = mysql_fetch_row(m_result);///<������н���ַ���
			if(m_sqlRow!=NULL)
			{
				*isExistClue = true;
				clueData->clueHappenTime = m_sqlRow[0];
				clueData->latestModifyTime = m_sqlRow[1];
				clueData->clueDescription = m_sqlRow[2];
			}
			else
			{
				*isExistClue = false;
			}
			mysql_free_result(m_result);///<�ͷŽ����Դ
		}
		return true;
	}
}
///@brief CDataMySql��ĸ���ĳ�������������ĺ���
/// 
///������������ĳ��������¼����������
///@param[in|out] clueData ������¼|NULL
///@pre  NULL
///@return NULL
///@retval BOOL �������ݿ�����Ƿ�ɹ�
///@post NULL
bool CDataMySql::UpdateDescriptionInClueTable(ClueTable clueData)
{
	CString m_strSql;///<mysql��ѯ���
	m_strSql.Format("update clueTable set clueDescription=\'%s\' where caseName=\'%s\' and cameraName=\'%s\' and clueHappenTime=\'%s\'\
					and clueCategory=\'%s\' and latestModifyTime=\'%s\' and filePath=\'%s\'", 
					clueData.clueDescription,clueData.caseName,clueData.cameraName,clueData.clueHappenTime,clueData.clueCategory,clueData.latestModifyTime,clueData.filePath);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		return true;
	}
}
///@brief CDataMySql��Ļ��ĳ����¼�����м�ص�����Ƶĺ���
/// 
///����Ƶ���л��ĳ����¼�����м�ص������
///@param[in|out] caseName ��¼����|CameraName_Str ����õı������м�ص��vector
///@pre  NULL
///@return NULL
///@retval BOOL �������ݿ�����Ƿ�ɹ�
///@post NULL
bool CDataMySql::GetMoniorNameFromVideoTable(CString caseName,vector<CString>* CameraName_Str)
{
	CString m_strSql;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	(*CameraName_Str).clear();
	m_strSql.Format("select distinct cameraName from VideoTable where caseName = \'%s\'",caseName) ; 
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if(m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			while (m_sqlRow)
			{
				CString  temp= m_sqlRow[0];
				if(!temp.IsEmpty())
				{
					(*CameraName_Str).push_back(m_sqlRow[0]);   
				}
				m_sqlRow = mysql_fetch_row(m_result);///<������н���ַ���
			}
			mysql_free_result(m_result);///<�ͷŽ����Դ
		}
	}
	return true;
}
///@brief CDataMySql��Ļ�����м�¼���ĺ���
/// 
///�ڼ�¼���л�����м�¼��
///@param[in|out] NULL|CaseName_Str ����õı������м�¼����vector
///@pre  NULL
///@return NULL
///@retval BOOL �������ݿ�����Ƿ�ɹ�
///@post NULL
bool CDataMySql::GetAllCaseNameFromCaseTable(vector<CString>* CaseName_Str)
{
	CString m_strSql;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	(*CaseName_Str).clear();
	m_strSql.Format("select caseName from CaseTable") ; 
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if(m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			while (m_sqlRow)
			{
				CString  temp= m_sqlRow[0];
				if(!temp.IsEmpty())
				{
					(*CaseName_Str).push_back(m_sqlRow[0]);   
				}
				m_sqlRow = mysql_fetch_row(m_result);///<������н���ַ���
			}
			mysql_free_result(m_result);///<�ͷŽ����Դ
		}
	}
	return true;
}
///@brief CDataMySql��Ļ��ĳ��¼��ص�������ԭʼ��Ƶ�ĺ���
/// 
///�ڼ�¼���л��ĳ��¼��ص�������ԭʼ��Ƶ·��
///@param[in|out] CaseName ��¼��;CameraName ��ص���|VideoName_Str ����õı�������ԭʼ��Ƶ·����vector
///@pre  NULL
///@return NULL
///@retval BOOL �������ݿ�����Ƿ�ɹ�
///@post NULL
bool CDataMySql::GetOriginNameFromVideoTable(CString CaseName,CString CameraName,vector<CString>* VideoName_Str)
{
	CString m_strSql;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	m_strSql.Format("select originPath from VideoTable where caseName = \'%s\' and cameraName = \'%s\'",CaseName,CameraName) ; 
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if(m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			while (m_sqlRow)
			{
				CString  temp= m_sqlRow[0];
				if(!temp.IsEmpty())
				{
					(*VideoName_Str).push_back(m_sqlRow[0]);   
				}
				m_sqlRow = mysql_fetch_row(m_result);///<������н���ַ���
			}
			mysql_free_result(m_result);///<�ͷŽ����Դ
		}
	}
	return true ;
}
///@brief CDataMySql��Ļ��ĳһ��¼����ͼƬ�������ĺ���
/// 
///��ͼƬ���л��ĳһ��¼����ͼƬ���������
///@param[in|out] CaseName ��¼��|VideoName_Str ����õı�������ͼƬ�������vector
///@pre  NULL
///@return NULL
///@retval BOOL �������ݿ�����Ƿ�ɹ�
///@post NULL
bool CDataMySql::GetCategoryNameFromImageTable(CString caseName,vector<CString>* CategoryName_str)    
{
	CString m_strSql;
	m_strSql.Format("select distinct imageCategory from imageTable where caseName=\'%s\'",caseName);
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if(m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			while (m_sqlRow)
			{
				CString  temp= m_sqlRow[0];
				if(!temp.IsEmpty())
				{
					(*CategoryName_str).push_back(m_sqlRow[0]);   
				}
				m_sqlRow = mysql_fetch_row(m_result);///<������н���ַ���
			}
			mysql_free_result(m_result);///<�ͷŽ����Դ
		}
	}
	return true ;
}
///@brief CDataMySql��Ļ��ĳһ��¼ͼƬ���������ͼƬ·���ĺ���
/// 
///��ͼƬ���л��ĳһ��¼ͼƬ���������ͼƬ·��
///@param[in|out] CaseName ��¼��;category ͼƬ���|ImageName_Str ����õı�������ͼƬ·����vector
///@pre  NULL
///@return NULL
///@retval BOOL �������ݿ�����Ƿ�ɹ�
///@post NULL
bool CDataMySql::GetImgPathFromImageTable(CString caseName,CString category,vector<CString>* ImageName_Str)
{
	CString m_strSql;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	m_strSql.Format("select imagePath from imageTable where caseName = \'%s\' and imageCategory = \'%s\'",caseName,category) ; 
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if(m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			while (m_sqlRow)
			{
				CString  temp= m_sqlRow[0];
				if(!temp.IsEmpty())
				{
					(*ImageName_Str).push_back(m_sqlRow[0]);   
				}
				m_sqlRow = mysql_fetch_row(m_result);///<������н���ַ���
			}
			mysql_free_result(m_result);///<�ͷŽ����Դ
		}
	}
	return true ;
}
///@brief CDataMySql���ɾ��������ĳ����¼�ĺ���
/// 
///����������ɾ��������ĳ����¼
///@param[in|out] clueData Ҫɾ��������|NULL
///@pre  NULL
///@return NULL
///@retval BOOL �������ݿ�����Ƿ�ɹ�
///@post NULL
bool CDataMySql::DeleteDataFromClueTable(ClueTable clueData)
{
	CString m_strSql;
	m_strSql.Format("delete from clueTable where caseName=\'%s\' and cameraName=\'%s\' and clueHappenTime=\'%s\'\
					and clueCategory=\'%s\' and latestModifyTime=\'%s\' and filePath=\'%s\' and clueDescription=\'%s\'",
					clueData.caseName,clueData.cameraName,clueData.clueHappenTime,clueData.clueCategory,clueData.latestModifyTime,clueData.filePath,clueData.clueDescription);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		return true;
	}
}

///@brief CDataMySql�����Ƶ�����Ƿ��Ѿ�����ĳ����Ƶ�ĺ���
/// 
///��Ƶ�����Ƿ��Ѿ�����ĳ����¼ĳ����ص�ĳ����Ƶ
///@param[in|out] caseName ��¼����;cameraName ��ص�����;videoName ԭʼ��Ƶ����|ifExist �Ƿ��Ѿ�����
///@pre  NULL
///@return NULL
///@retval BOOL �������ݿ�����Ƿ�ɹ�
///@post NULL
bool CDataMySql::IfExistOrigPathVideoTable(CString caseName,CString cameraName,CString videoName,bool* ifExist)
{
	CString m_strSql;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	m_strSql.Format("select count(*) from videoTable where caseName=\'%s\' and cameraName=\'%s\' and originPath=\'%s\'",caseName,cameraName,videoName);
	int params = -1;
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			params = atoi(m_sqlRow[0]);
		}
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
	}
	if(params==0)
	{
		*ifExist = false;
	}
	else
	{
		*ifExist = true;
	}
	return true;

}

/****************************DrawDetect�����õ��ı�********************************************/
///@brief CDataMySql����˶������ĺ���
/// 
///����ĳ�����ֵ��˶�������м�������Ϊ(objectID int not null,frameID int not null,centerX int not null,centerY int not null,\
nTop int not null,nBottom int not null,nLeft int not null,nRight int not null)
///@param[in|out] tableName Ҫ�����ı���|NULL
///@pre NULL
///@return NULL
///@retval BOOL ���ز����Ƿ�ɹ�
///@post NULL
bool CDataMySql::CreateObjectTable(CString tableName)
{
	CString m_strSql;
	m_strSql.Format("create table %s(objectID int not null,frameID int not null,centerX int not null,centerY int not null,\
					nTop int not null,nBottom int not null,nLeft int not null,nRight int not null)",tableName);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		return true;
	}
}
///@brief CDataMySql��Ĳ������ݵ��˶��������
/// 
///��һ����¼���뵽�˶��������
///@param[in|out] ObjectTableName Ҫ�������ݵı���;infor5 Ҫ����ļ�¼|NULL
///@pre  NULL
///@return NULL
///@retval BOOL ���ز����Ƿ�ɹ�
///@post NULL
bool CDataMySql::InsertData2ObjectTable(NewTrackParam infor5,CString ObjectTableName)
{
	CString m_strSql;///<mysql��ѯ���
	m_strSql.Format("insert into %s(objectID,frameID,centerX,centerY,nTop,nBottom,nLeft,nRight)\
					values(\'%d\',\'%d\',\'%d\',\'%d\',\'%d\',\'%d\',\'%d\',\'%d\')",\
					ObjectTableName,infor5.segID,infor5.origFrame,infor5.CentX,infor5.CentY,infor5.nTop,infor5.nBottom,infor5.nLeft,infor5.nRight); //sql�������
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		return true;
	}
}
///@brief CDataMySql��Ĳ����˶�������Ϣ�ĺ���
/// 
///
///@param[in|out] objectID ������;ObjectTableName Ҫ�������ݵı���|NULL
///@pre  NULL
///@return NULL
///@retval BOOL ���ز����Ƿ�ɹ�
///@post NULL
void CDataMySql::GetCenterFromObjectTable(int objectID, CString ObjectTableName, vector<CPoint>* centersOfObj)
{
	CString m_strSql;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	m_strSql.Format("select centerX,centerY from %s where objectID=\'%d\'",ObjectTableName,objectID);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			while (m_sqlRow)
			{
				centersOfObj->push_back(CPoint(atoi(m_sqlRow[0]),atoi(m_sqlRow[1])));
				m_sqlRow=mysql_fetch_row(m_result);
			}
		}
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
	}

}
///@brief CDataMySql��Ļ�ȡĳһ֡���˶������ID��Rect����
/// 
///
///@param[in|out] frameID ֡��;ObjectTableName ����|rect �����rect��Ϣ����; objID ID����
///@pre  NULL
///@return NULL
///@retval NULL
///@post NULL
void CDataMySql::GetRectFromObjectTable(int frameID, CString ObjectTableName, vector<CRect>* rect,vector<int>* objID)
{
	CString m_strSql;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	m_strSql.Format("select centerX,centerY,nLeft,nTop,nRight,nBottom,objectID from %s where frameID=\'%d\'",ObjectTableName,frameID);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
	}
	else
	{
		if (m_result=mysql_store_result(&m_mysql))///<�����ѯ�������ݵ�m_result
		{
			while (m_sqlRow=mysql_fetch_row(m_result))
			{
				rect->push_back(CRect(atoi(m_sqlRow[0]),atoi(m_sqlRow[1]),0,0));
				rect->push_back(CRect(atoi(m_sqlRow[2]),atoi(m_sqlRow[3]),atoi(m_sqlRow[4]),atoi(m_sqlRow[5])));
				objID->push_back(atoi(m_sqlRow[6]));
			}
		}
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
	}
}
///@brief CDataMySql���һ���Զ�ȡĳ���˶�Ŀ��Ĺ켣�㼯�Ϻ�Rect���Ϻ���
/// 
///
///@param[in|out] objID �˶�Ŀ����;ObjectTableName ����|rect �����rect��Ϣ����; centersOfObj �˶�Ŀ��Ĺ켣�㼯��
///@pre  NULL
///@return NULL
///@retval NULL
///@post NULL
void CDataMySql::GetSingleTraceFromObjectTable(int objID, CString ObjectTableName, vector<CRect>* rect,vector<CPoint>* centersOfObj)
{
	CString m_strSql;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	m_strSql.Format("select nLeft,nTop,nRight,nBottom,centerX,centerY from %s where objectID=\'%d\'",ObjectTableName,objID);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			while (m_sqlRow)
			{
				rect->push_back(CRect(atoi(m_sqlRow[0]),atoi(m_sqlRow[1]),atoi(m_sqlRow[2]),atoi(m_sqlRow[3])));
				centersOfObj->push_back(CPoint(atoi(m_sqlRow[4]),atoi(m_sqlRow[5])));
				m_sqlRow=mysql_fetch_row(m_result);
			}
		}
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
	}
}
///@brief CDataMySql��Ļ�ȡĳһ֡����λ�õ�����ID����
/// 
///
///@param[in|out] frameID ֡��;rect ĳһrectλ��;ObjectTableName ����|NULL
///@pre  NULL
///@return NULL
///@retval NULL
///@post NULL
int  CDataMySql::GetObjectIDFromObjectTable(int frameID,CRect rect,CString ObjectTableName)
{
	CString m_strSql;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	int param = -1;
	m_strSql.Format("select objectID from %s where nTop=\'%d\' and nBottom=\'%d\' and nLeft=\'%d\' and nRight=\'%d\'",ObjectTableName,rect.top,rect.bottom,rect.left,rect.right);

	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return param;
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			if (m_sqlRow)
			{
				param = atoi(m_sqlRow[0]);
			}
			
		}
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
		return param;
	}
}
///@brief CDataMySql��Ļ�ȡĳһ�˶�Ŀ���frameID���Ϻ���
/// 
///
///@param[in|out] objectID �˶�Ŀ����;ObjectTableName ����|frameID �˶�Ŀ�����ڵ�֡�ż���
///@pre  NULL
///@return NULL
///@retval BOOL ���ݿ�����Ƿ�ɹ�
///@post NULL
bool CDataMySql::GetFrameidFromObjectTable(int objectID,CString ObjectTableName,vector<int>* frameID)
{
	CString m_strSql;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	m_strSql.Format("select frameID from %s where objectID =\'%d\'",ObjectTableName,objectID);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			while(m_sqlRow)
			{
				frameID->push_back(atoi(m_sqlRow[0]));
				m_sqlRow=mysql_fetch_row(m_result);
			}
		}
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
	}
	return true;
}
///@brief CDataMySql����ж��Ƿ��Ѿ�����ĳ��ͼƬ�ĺ���
/// 
///�ж�ͼƬ�����Ƿ��Ѿ�����ĳ����¼ĳ������ĳ��ͼƬ
///@param[in|out] caseName ��¼��;category ͼƬ����;imgName ͼƬ·��|ifExist �Ƿ����
///@pre  NULL
///@return NULL
///@retval BOOL ���ݿ�����Ƿ�ɹ�
///@post NULL
bool CDataMySql::GetObjectInfoFromObjectTable(int objectID,CString ObjectTableName,objectInfo* tempInfo)
{
	CString m_strSql;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	m_strSql.Format("select objectID,frameID,nTop,nBottom,nLeft,nRight from %s where objectID=\'%d\'",ObjectTableName,objectID);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			if(m_sqlRow)
			{
				tempInfo->objectID		= atoi(m_sqlRow[0]);
				tempInfo->firstFrameID  = atoi(m_sqlRow[1]);
				tempInfo->lastFrameID	= atoi(m_sqlRow[1]);
				tempInfo->roi.top		= atoi(m_sqlRow[2]);
				tempInfo->roi.bottom	= atoi(m_sqlRow[3]);
				tempInfo->roi.left		= atoi(m_sqlRow[4]);
				tempInfo->roi.right		= atoi(m_sqlRow[5]);
			}
			while (m_sqlRow)
			{
				if (tempInfo->lastFrameID < atoi(m_sqlRow[1]))
				{
					tempInfo->lastFrameID = atoi(m_sqlRow[1]);
				}
				m_sqlRow=mysql_fetch_row(m_result);
			}
		}
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
		return true;
	}
	

}

///@brief CDataMySql����ж��Ƿ��Ѿ�����ĳ��ͼƬ�ĺ���
/// 
///�ж�ͼƬ�����Ƿ��Ѿ�����ĳ����¼ĳ������ĳ��ͼƬ
///@param[in|out] caseName ��¼��;category ͼƬ����;imgName ͼƬ·��|ifExist �Ƿ����
///@pre  NULL
///@return NULL
///@retval BOOL ���ݿ�����Ƿ�ɹ�
///@post NULL
bool CDataMySql::IfExistImagePathImageTable(CString caseName,CString category,CString imgName,bool* ifExist)
{
	CString m_strSql;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	m_strSql.Format("select count(*) from imageTable where caseName=\'%s\' and imageCategory=\'%s\' and imagePath=\'%s\'",caseName,category,imgName);
	int params = -1;
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			params = atoi(m_sqlRow[0]);
		}
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
	}
	if(params==0)
	{
		*ifExist = false;
	}
	else
	{
		*ifExist = true;
	}
	return true;

}
///@brief CDataMySql���ɾ����Ƶ��¼�ĺ���
/// 
///ɾ����Ƶ����ĳһ����¼
///@param[in|out] caseName ��¼��;cameraName ��ص�����;originPath ԭʼ��Ƶ·��|NULL
///@pre  NULL
///@return NULL
///@retval BOOL ���ݿ�����Ƿ�ɹ�
///@post NULL
bool CDataMySql::DeleteDataFromVideoTable(CString caseName,CString cameraName,CString originPath)
{
	CString m_strSql;
	m_strSql.Format("delete from videoTable where caseName=\'%s\' and cameraName=\'%s\' and originPath=\'%s\'",caseName,cameraName,originPath);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		return true;
	}

}
///@brief CDataMySql���ɾ��ͼƬ��¼�ĺ���
/// 
///ɾ��ͼƬ����ĳһ����¼
///@param[in|out] caseName ��¼��;category ��¼����;imagePath ͼƬ·��|NULL
///@pre  NULL
///@return NULL
///@retval BOOL ���ݿ�����Ƿ�ɹ�
///@post NULL
bool CDataMySql::DeleteDataFromImageTable(CString caseName,CString category,CString imagePath)
{
	CString m_strSql;
	m_strSql.Format("delete from imageTable where caseName=\'%s\' and imageCategory=\'%s\' and imagePath=\'%s\'",caseName,category,imagePath);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		return true;
	}

}
///@brief CDataMySql��Ļ�õ�ǰ��¼��Ϣ�ĺ���
/// 
///�ڵ�ǰ��¼���л�õ�ǰ��¼����Ϣ
///@param[in|out] curCaseTable ��ǰ��¼����|caseData ��õļ�¼��Ϣ
///@pre  NULL
///@return NULL
///@retval BOOL ���ݿ�����Ƿ�ɹ�
///@post NULL
bool CDataMySql::GetCurCaseDataFromCurCaseTable(CaseTable* caseData,CString curCaseTable)
{
	CString m_strSql;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	m_strSql.Format("select caseName,caseCategory,caseRecordTime,caseHappenTime,caseDescription,caseNote\
					from %s",curCaseTable);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			if (m_sqlRow=mysql_fetch_row(m_result))///<������н���ַ���
			{
				(*caseData).caseName = m_sqlRow[0];
				(*caseData).caseCategory = m_sqlRow[1];
				(*caseData).caseRecordTime = m_sqlRow[2];
				(*caseData).caseHappenTime = m_sqlRow[3];
				(*caseData).caseDescription = m_sqlRow[4];
				(*caseData).caseNote = m_sqlRow[5];
			}
			
		}
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
		return true;
	}
}

///@brief CDataMySql���ͼƬ��Ϣ�Ƿ��Ѿ����ڵĺ���
/// 
///�ж���ͼƬ�����Ƿ��Ѿ�����ĳ����¼ĳ��ͼƬ�����µ�ͼƬ
///@param[in|out] imgData ͼƬ��Ϣ|ifExist �Ƿ��Ѿ�����
///@pre  NULL
///@return NULL
///@retval BOOL ���ݿ�����Ƿ�ɹ�
///@post NULL
bool CDataMySql::IfExistImgDataImageTable(ImageTable imgData,bool* ifExist)
{
	CString m_strSql;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	m_strSql.Format("select count(*) from imageTable where caseName=\'%s\'and imageCategory=\'%s\'and imagePath=\'%s\'",imgData.caseName,imgData.imageCategory,imgData.imagePath);
	int params = -1;
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			params = atoi(m_sqlRow[0]);
		}
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
	}
	if(params==0)
	{
		*ifExist = false;
	}
	else
	{
		*ifExist = true;
	}
	return true;

}
///@brief CDataMySql��Ļ��ĳ�����������������ĺ���
/// 
///���������и��ݼ�¼������ص���������ļ�·����ø�������¼����������
///@param[in|out] caseName ��¼��;cameraName ��ص���;cluePath ��������ļ�·��|clueDesrip ��õ���������
///@pre  NULL
///@return NULL
///@retval BOOL ���ݿ�����Ƿ�ɹ�
///@post NULL
bool CDataMySql::GetClueDescripFromClueTable(CString caseName,CString cameraName,CString cluePath,CString& clueDesrip)
{
	CString m_strSql;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	m_strSql.Format("select clueDescription from clueTable where caseName=\'%s\' and cameraName=\'%s\' and filePath=\'%s\'",caseName,cameraName,cluePath);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			if(m_sqlRow==NULL)
			{
				clueDesrip.Empty();
			}
			else
			{
				clueDesrip = m_sqlRow[0];
			}
		}
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
	}
	return true;

}
///@brief CDataMySql��ĸ���������¼�ĺ���
/// 
///���������и���ĳ������
///@param[in|out] clueData Ҫ���µ�����|NULL
///@pre  NULL
///@return NULL
///@retval BOOL ���ݿ�����Ƿ�ɹ�
///@post NULL
bool CDataMySql::UpdateClueDataInClueTable(ClueTable clueData)
{
	CString m_strSql;
//	MYSQL_RES *m_result;
	//MYSQL_ROW m_sqlRow;
	m_strSql.Format("update clueTable set clueHappenTime=\'%s\',cameraName=\'%s\',clueDescription=\'%s\', \
					latestModifyTime=\'%s\' where caseName=\'%s\'and cameraName=\'%s\' and filePath=\'%s\'", 
		clueData.clueHappenTime,clueData.cameraName,clueData.clueDescription,clueData.latestModifyTime,\
		clueData.caseName,clueData.cameraName,clueData.filePath);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		return true;
	}

}
///@brief CDataMySql��Ļ�����м�¼��Ϣ�ĺ���
/// 
///�ڼ�¼���л�����м�¼��Ϣ
///@param[in|out] NULL|allCaseData �����¼��Ϣ��vector
///@pre  NULL
///@return NULL
///@retval BOOL ���ݿ�����Ƿ�ɹ�
///@post NULL
bool CDataMySql::GetAllCaseDataFromCaseTable(vector<CaseTable>* allCaseData)
{
	CString m_strSql;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	allCaseData->clear();
	m_strSql.Format("select caseName,caseCategory,caseRecordTime,caseHappenTime,caseDescription,caseNote from caseTable");

	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			CaseTable caseData;
			while(m_sqlRow)
			{
				caseData.caseName = m_sqlRow[0];
				caseData.caseCategory = m_sqlRow[1];
				caseData.caseRecordTime = m_sqlRow[2];
				caseData.caseHappenTime = m_sqlRow[3];
				caseData.caseDescription = m_sqlRow[4];
				caseData.caseNote = m_sqlRow[5];
				allCaseData->push_back(caseData);
				m_sqlRow=mysql_fetch_row(m_result);
			}
		}
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
	}
	return true;
}
///@brief CDataMySql���ɾ��ĳ��¼��������Ϣ�ĺ���
/// 
///�ڼ�¼��������ͼƬ�����Ƶ���У�ɾ�����й��ڸü�¼�ļ�¼
///@param[in|out] caseName ��¼����|NULL
///@pre  NULL
///@return NULL
///@retval BOOL ���ݿ�����Ƿ�ɹ�
///@post NULL
bool CDataMySql::DeleteCertainCaseInfor(CString caseName)
{
	CString m_strSql;
	m_strSql.Format("delete from caseTable where caseName=\'%s\'",caseName);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	m_strSql.Format("delete from clueTable where caseName=\'%s\'",caseName);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	m_strSql.Format("delete from imageTable where caseName=\'%s\'",caseName);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	m_strSql.Format("delete from videoTable where caseName=\'%s\'",caseName);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	return true;
}
///@brief CDataMySql��Ļ��ĳ��¼��ͼƬ�������ĺ���
/// 
///��ͼƬ���л��ĳ��¼�µ�ͼƬ������
///@param[in|out] caseName ��¼����|NULL
///@pre  NULL
///@return NULL
///@retval int ����ͼƬ����Ŀ���������ʧ���򷵻�-1
///@post NULL
int CDataMySql::GetCaseImgNumFromImageTable(CString caseName)
{
	CString m_strSql;
	int params = -1;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	m_strSql.Format("select count(distinct imagePath) from imageTable where caseName=\'%s\'",caseName);

	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			params = atoi(m_sqlRow[0]);
		}
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
	}
	return params;
}
///@brief CDataMySql��Ļ��ĳ��¼�µ�������Ƶ��Ϣ�ĺ���
/// 
///����Ƶ���л��ĳ��¼�µ�������Ƶ��Ϣ
///@param[in|out] caseName ��¼����|caseAllVideoData ������Ƶ��Ϣ��vector
///@pre  NULL
///@return NULL
///@retval BOOL �������ݿ�����Ƿ�ɹ�
///@post NULL
bool CDataMySql::GetCaseVideoDataFromVideoTable(vector<VideoTable>* caseAllVideoData,CString caseName)
{
	CString m_strSql;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	caseAllVideoData->clear();
	m_strSql.Format("select caseName,cameraName,originPath,segPath,fusionPath from videoTable where caseName=\'%s\'",caseName);

	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			VideoTable videoData;
			while(m_sqlRow)
			{
				videoData.caseName = m_sqlRow[0];
				videoData.cameraName = m_sqlRow[1];
				videoData.originPath = m_sqlRow[2];
				videoData.segPath = m_sqlRow[3];
				videoData.fusionPath = m_sqlRow[4];
				caseAllVideoData->push_back(videoData);
				m_sqlRow=mysql_fetch_row(m_result);
			}
		}
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
	}
	return true;

}
///@brief CDataMySql��Ļ��ĳ��¼�µ�����������Ϣ�ĺ���
/// 
///���������л��ĳ��¼�µ�����������Ϣ
///@param[in|out] caseName ��¼����|caseClueData ����������Ϣ��vector
///@pre  NULL
///@return NULL
///@retval BOOL �������ݿ�����Ƿ�ɹ�
///@post NULL
bool CDataMySql::GetClueDataFromClueTable(vector<ClueTable>* caseClueData,CString caseName)
{
	CString m_strSql;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	caseClueData->clear();
	m_strSql.Format("select caseName,cameraName,clueHappenTime,clueCategory,latestModifyTime,filePath,clueDescription\
					from clueTable where caseName = \'%s\'",caseName) ; 

	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			ClueTable clueData;
			while(m_sqlRow)
			{
				clueData.caseName = m_sqlRow[0];
				clueData.cameraName = m_sqlRow[1];
				clueData.clueHappenTime = m_sqlRow[2];
				clueData.clueCategory = m_sqlRow[3];
				clueData.latestModifyTime = m_sqlRow[4];
				clueData.filePath = m_sqlRow[5];
				clueData.clueDescription = m_sqlRow[6];
				caseClueData->push_back(clueData);
				m_sqlRow=mysql_fetch_row(m_result);
			}
		}
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
	}
	return true;

}
///@brief CDataMySql��Ļ��ĳ��¼�µ�����ͼƬ��Ϣ�ĺ���
/// 
///��ͼƬ���л��ĳ��¼�µ�����ͼƬ��Ϣ
///@param[in|out] caseName ��¼����|caseAllImgData ����ͼƬ��Ϣ��vector
///@pre  NULL
///@return NULL
///@retval BOOL �������ݿ�����Ƿ�ɹ�
///@post NULL
bool CDataMySql::GetCaseImgDataFromImageTable(vector<ImageTable> *caseAllImgData,CString caseName)
{
	CString m_strSql;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	caseAllImgData->clear();
	m_strSql.Format("select caseName,imageCategory,imagePath from imageTable where caseName = \'%s\'",caseName) ; 

	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			ImageTable imgData;
			while(m_sqlRow)
			{
				imgData.caseName = m_sqlRow[0];
				imgData.imageCategory= m_sqlRow[1];
				imgData.imagePath = m_sqlRow[2];
				caseAllImgData->push_back(imgData);
				m_sqlRow=mysql_fetch_row(m_result);
			}
		}
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
	}
	return true;

}
///@brief CDataMySql��Ľ�txt�ļ����ݵ����ĺ���
/// 
///��txt�ļ����ݵ�����ļ������ݱ����ԡ�,��Ϊ�����Էָ�������"\t\n"�����з�Ϊ�зָ���
///@param[in|out] txtPath txt�ļ�·�� in,tableName Ҫ�������ݵı���|NULL
///@pre  NULL
///@return NULL
///@retval BOOL �������ݿ�����Ƿ�ɹ�
///@post NULL
bool CDataMySql::LoadTextData2Table(CString txtPath,CString tableName)
{
	CString m_strSql;///<mysql��ѯ���
	m_strSql.Format("LOAD DATA INFILE '%s' REPLACE INTO TABLE %s FIELDS TERMINATED BY ',' LINES TERMINATED BY '\r\n'",txtPath,tableName);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		return true;
	}
}
///@brief CDataMySql��ĸ��ٳ�����Ϣ�ĺ���
/// 
///
///@param[in|out] conn MYSQL�ṹ in,message ����ĳ�����Ϣ in|NULL
///@pre  NULL
///@return NULL
///@retval NULL
///@post NULL
void CDataMySql::print_error(MYSQL* conn,char* message)
{
	TRACE("%s\n",message);
	if(conn!=NULL)
	{
		TRACE("Error %u(%s):%s\n",mysql_errno(conn),mysql_sqlstate(conn),mysql_error(conn));
	}

}
///@brief CDataMySql��Ľ������ݱ��浽txt�ļ��ĺ���
/// 
///�������ݱ��浽txt�ļ��������ļ��е������ԡ�,��Ϊ�����Էָ�������"\t\n"�����з�Ϊ�зָ���
///@param[in|out] txtPath txt�ļ�·�� in,tableName Ҫ�������ݵı���|NULL
///@pre  NULL
///@return NULL
///@retval BOOL �������ݿ�����Ƿ�ɹ�
///@post NULL
bool CDataMySql::StoreTableData2Text(CString txtPath,CString tableName)
{
	CString m_strSql;///<mysql��ѯ���
	m_strSql.Format("SELECT * INTO OUTFILE '%s' FIELDS TERMINATED BY ',' LINES TERMINATED BY '\r\n' FROM %s ",txtPath,tableName);
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		return true;
	}
}

bool CDataMySql::FindTimePositionFromNewTraceTable(int NewFrame,vector <CvPoint> *m_Point,vector<int> *origFrame,CString tableName)
{
	CString m_strSql;
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	m_strSql.Format("select nX,nY,origFrame from %s where newFrame = \'%d\'",tableName,NewFrame) ;
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		m_result = NULL;///<����
		print_error(&m_mysql,"error message");
		return false;
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		for (int i=0;i<m_result->row_count;i++)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			CvPoint p;
			int f;
			p.x = atoi(m_sqlRow[0]);
			p.y = atoi(m_sqlRow[1]);
			f = atoi(m_sqlRow[2]);
			m_Point->push_back(p);
			origFrame->push_back(f);
		}
		if(m_result!=NULL)mysql_free_result(m_result);///<�ͷŽ����Դ
		return true;
	}
}

int CDataMySql::FindOrigParaFromFGTraceTable(CString FGTraceTable, CvRect rect)
{

	CString m_strSql;
	m_strSql.Format("select nOldPara from %s where nX =\'%d\' and nWidth = \'%d\'", FGTraceTable, rect.x, rect.width);
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	int params = -1;
	if (mysql_real_query(&m_mysql, (char*)(LPCTSTR)m_strSql, (UINT)m_strSql.GetLength()) != 0)
	{
		print_error(&m_mysql, "error message");
	}
	else
	{
		m_result = mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			m_sqlRow = mysql_fetch_row(m_result);///<������н���ַ���
			params = atoi(m_sqlRow[0]);
		}
		if (m_result != NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
	}
	return params;
}

int CDataMySql::FindSegIDFromFGTraceTable(CString FGTraceTable,int origPara)	                            ///<��new trace���и���ROI��Ϣ�ҵ�ԭʼ��Ƶ֡��
{
	CString m_strSql;
	m_strSql.Format("select segID from %s where nOldPara =\'%d\' ", FGTraceTable, origPara);
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	int segIDnum = -1;
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			segIDnum = atoi(m_sqlRow[0]);
		}
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
	}
	return segIDnum;
}

int CDataMySql::FindOrigFrameFromVideoFGTable(CString VideoFGTable, int origPara)
{

	CString m_strSql;
	m_strSql.Format("select startFrame from %s where nOldPara =\'%d\' ", VideoFGTable, origPara);
	MYSQL_RES *m_result;
	MYSQL_ROW m_sqlRow;
	int frameNO = -1;
	if(mysql_real_query(&m_mysql,(char*)(LPCTSTR)m_strSql,(UINT)m_strSql.GetLength())!=0)
	{ 
		print_error(&m_mysql,"error message");
	}
	else
	{
		m_result=mysql_store_result(&m_mysql);///<�����ѯ�������ݵ�m_result
		if (m_result)
		{
			m_sqlRow=mysql_fetch_row(m_result);///<������н���ַ���
			frameNO = atoi(m_sqlRow[0]);
		}
		if(m_result!=NULL) mysql_free_result(m_result);///<�ͷŽ����Դ
	}
	return frameNO;
}