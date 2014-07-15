/**
*@file LibMysql.h
*@brief ���ݿ����±�����������������
*
*���ļ��¶�������ݿ��࣬�������빤���������õ��������ݿ���ز����Ĺ��������
*
*@author ���� zhang nannan&&lu ying ,����email��
*@version �汾��(0.0)
*@data 2012-8-21
*/
#pragma once


#include "stdafx.h"
#include "winsock.h"
#include "publicheader.h"
#include <string.h>
#include "atlstr.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <vector>

using namespace std;


///��¼��Ƶǰ������Ϣ�Ľṹ��
typedef struct _VideoFGTable
{
	int nOldPara;        ///<�κ�
	int startFrame;      ///<������ʼ֡��
	int endFrame;        ///<���ν���֡��
}VideoFGTable;

///��¼��Ƶ��������Ϣ�Ľṹ��
typedef struct _VideoBGTable
{
	int BGImgID;           ///<����ͼ����
	int startFrame;        ///<����ͼ�����÷�Χ
	int endFrame;
}VideoBGTable;

///��¼ͼƬROI������������Ľṹ��
typedef struct _ImageROI
{
	/*int nTop;
	int nBottom;
	int nLeft;
	int nRight;*/
	int nX;
	int nY;
	int nWidth;
	int nHeight;
}ImageROI;

///ԭʼ��¼�˶�Ŀ����Ϣ�Ľṹ��
typedef struct _OrigTraceTable 
{
	int nOldPara;       ///<�ɶκ�
	int segID;          ///<������
	int nX;
	int nY;
	int nWidth;
	int nHeight;
	int origFrame;      ///<�������ڵ�ԭʼ֡��
	//CString segSize;    ///<�����С
	int segSize;
}OrigTraceTable;

///�¾ɶζ�Ӧ�Ľṹ��
typedef struct _NewToOldParaTable 
{
	int nNewPara;         ///<�¶κ�
	int nOldPara;         ///<�ɶκ�
}NewToOldParaTable;

///�¾�֡��Ӧ�Ľṹ��
typedef struct _NewToOldFrameTable
{
	int origFrame;       ///<��֡��
	int newFrame;        ///<��֡��
}NewToOldFrameTable;

///���ռ�¼�˶�Ŀ����Ϣ�Ľṹ��
typedef struct _NewTraceTable 
{
	int newFrame;        ///<�¶κ�
	int segID;           ///<������
	int nX;
	int nY;
	int nWidth;
	int nHeight;
	int CentX;          ///<���ĵ������
	int CentY;
	int origFrame;      ///<ԭʼ֡��
	int nTop;
	int nBottom;
	int nLeft;
	int nRight;
	
	//CString segSize;    ///<�����С
	int segSize;
}NewTraceTable;
typedef struct _NewTrackParams
{
	int newFrame;        ///<�¶κ�
	int segID;
	int CentX;          ///<���ĵ������
	int CentY;
	int origFrame;      ///<ԭʼ֡��
	int nTop;
	int nBottom;
	int nLeft;
	int nRight;
}NewTrackParam;

///��¼��¼��Ϣ�Ľṹ��
typedef struct _CaseTable
{
	CString caseName;       ///<��¼����
	CString caseCategory;   ///<��¼���
	CString caseRecordTime; ///<����ʱ��
	CString caseHappenTime; ///<��¼����ʱ��
	CString caseDescription;///<��¼����
	CString caseNote;       ///<��¼��ע

}CaseTable;

///��¼��Ƶ��Ϣ�Ľṹ��
typedef struct _VideoTable
{
	CString caseName;       ///<��¼����
	CString cameraName;     ///<��ص�����
	CString originPath;     ///<ԭʼ��Ƶ·��
	CString segPath;        ///<�ָ���Ƶ·��
	CString fusionPath;     ///<�ں���Ƶ·��
	int     origTotalFrames;///<ԭʼ��Ƶ����֡��
	int     segTotalFrames; ///<�и���Ƶ����֡��
	int     fusTotalFrames; ///<�ں���Ƶ����֡��
}VideoTable;

///��¼ͼ����Ϣ�Ľṹ��
typedef struct _ImageTable
{
	CString caseName;     ///<��¼����
	CString imageCategory;///<ͼƬ���
	CString imagePath;    ///<ͼƬ·��
}ImageTable;

///��¼������Ϣ�Ľṹ��
typedef struct _ClueTable
{
	CString caseName;        ///<��¼����
	CString cameraName;      ///<��ص�����
	CString clueHappenTime;  ///<��������ʱ��
	CString clueCategory;    ///<�������
	CString latestModifyTime;///<����޸�ʱ��
	CString filePath;        ///<�����ļ�·��
	CString clueDescription; ///<��������
}ClueTable;

///��¼����������Ϣ�Ľṹ��
typedef struct _SearchSegIDParams
{
	int origFrame;         ///<ԭʼ֡��
	ImageROI ROI;          ///<�Ǹ�Ŀ���ROI
}SearchSegIDParams;

///��¼�ֶ�Ŀ�������һ��Ŀ�����Ϣ�Ľṹ��
typedef struct  
{
	int nOldPara;
	int OriFrameID;
	CvRect roi;
}objectInfo;


///@brief �������ݿ���
///
///��������ݿ��࣬�����˹����������õ������ݿ�Ĳ���
///����ʵ�ֹ��������õ������ݿ��Ĵ��������ҡ����º�ɾ���Ȳ���
///
///@invariant
///
class CDataMySql
{
public:
	CDataMySql(void);
	~CDataMySql(void);
public:
	MYSQL m_mysql;
public:

	void print_error(MYSQL* conn,char* message);            ///<���ٳ�����Ϣ�ĺ���
	///
	///���ͨ�ò���
	///
	bool CleanTable(CString tableName);                             ///<��ձ��
	bool DropTable(CString tableName);                              ///<ɾ����
	bool IfExistTable(CString tableName,bool* ifExist);             ///<�鿴ĳ�����Ƿ����
	bool DeleteCertainCaseInfor(CString caseName);                  ///<ɾ���ĸ��������й��ڼ�¼����Ϣ
	bool StoreTableData2Text(CString txtPath,CString tableName);    ///<�����е����ݱ��浽txt�ļ���
	bool LoadTextData2Table(CString txtPath,CString tableName);     ///<��txt�е����ݵ������
  
	///
	///��¼�����غ���
	///
    bool CreateCaseTable(CString CaseTableName="caseTable");                     ///<������¼��
	bool InsertDataCaseTable(CaseTable CaseTableData ,CString CaseTableName);    ///< �������ݵ���¼��	
	bool IfExistCaseNameInCaseTable(CString caseName,bool* ifExist);             ///<�жϼ�¼�����Ƿ��Ѿ����ڴ����ֵļ�¼
	bool UpdateCaseDataInCaseTable(CaseTable caseData,CString caseName,CString tableName="caseTable");///<����ĳһ��¼���ļ�¼��Ϣ
    bool GetAllCaseNameFromCaseTable(vector<CString>* CaseName_Str);             ///<�õ����м�¼��
	bool GetCurCaseDataFromCurCaseTable(CaseTable* caseData,CString curCaseTable);///<�õ���ǰ��¼����Ϣ
	bool GetAllCaseDataFromCaseTable(vector<CaseTable>* allCaseData);             ///<�õ����м�¼����Ϣ

	///
	///��Ƶ�����غ���
	///
	bool CreateVideoTable(CString VideoTableName="videoTable");                   ///<������Ƶ��
	///������Ƶ֡����Ϣ
	bool InsertorigTotalFrames2VideoTable(int origTotalFrames,CString FusVideoName);
	bool InsertsegTotalFrames2VideoTable(int segTotalFrames,CString FusVideoName);
	bool InsertfusTotalFrames2VideoTable(int fusTotalFrames,CString FusVideoName);
	///��ȡ��Ƶ֡����Ϣ
	int GetorigTotalFramesFromVideoTable(CString FusVideoName);
	int GetsegTotalFramesFromVideoTable(CString FusVideoName);
	int GetfusTotalFramesFromVideoTable(CString FusVideoName);
	///�������ݲ���
	bool InsertData2VideoTable(VideoTable VideoTableData);
	bool InsertSegVideo2VideoTable(CString segVideoPath,CString caseName,CString cameraName,CString originPath);
	bool InsertFusionVideo2VideoTable(CString fusionVideoPath,CString caseName,CString cameraName,CString originPath);
	
	int GetOrigVideoNumFromVideoTable(CString CaseName,CString CameraName);      ///<���ĳ��¼��ص��µ���Ƶ��Ŀ
	int GetCaseOrigVideoNumFromVideoTable(CString CaseName);                     ///<���ĳ��¼��������Ƶ����Ŀ

	CString GetFusionNameFromVideoTable(CString caseName,CString cameraName,CString videoName);///<�õ�ĳ��¼ĳ��ص��ĳ��Ƶ���ں���Ƶ·��
	CString GetCaseNameFromVideoTable(CString FusVideoName);                                   ///<�õ��ں���Ƶ�ļ�¼����
	CString GetCameraNameFromVideoTable(CString FusVideoName);                                 ///<�õ��ں���Ƶ�ļ�ص�����

	bool GetVideoNameFromVideoTable(CString CaseName,CString CameraName,CString(*VideoName_str)[3],int videoTotalNum);///<���ĳ��¼ĳ��ص���������Ƶ������
	bool GetFusionNameFromVideoTable(CString caseName,CString CameraName,vector<CString>* fusionName_Str);            ///<���ĳ��¼ĳ��ص��������ں���Ƶ������
	bool GetMoniorNameFromVideoTable(CString caseName,vector<CString>* CameraName_Str);                               ///<���ĳ��¼�����м�ص������
    bool GetOriginNameFromVideoTable(CString CaseName,CString CameraName,vector<CString>* VideoName_Str);             ///<���ĳ��¼ĳ��ص�������ԭʼ��Ƶ������

	bool IfExistOrigPathVideoTable(CString caseName,CString cameraName,CString videoName,bool* ifExist);              ///<�б����Ƿ��Ѿ�����ĳ����¼ĳ����ص����Ƶ
	bool DeleteDataFromVideoTable(CString caseName,CString cameraName,CString originPath);                            ///<ɾ����Ƶ���е�һ����¼
	bool GetCaseVideoDataFromVideoTable(vector<VideoTable>* caseAllVideoData,CString caseName);                       ///<�����Ƶ����ĳ��¼��������Ƶ����Ϣ
	///
	///ͼƬ�����غ���
	///
	bool CreateImageTable(CString ImageTableName="imageTable");                                     ///<����ͼƬ��
	bool InsertData2ImageTable(ImageTable imgTableData);                                            ///<ͼƬ���в���һ����¼
	bool GetCategoryNameFromImageTable(CString caseName,vector<CString>* CategoryName_str);         ///<���ĳ��¼������ͼƬ�������
	bool GetImgPathFromImageTable(CString caseName,CString category,vector<CString>* ImageName_Str);///<���ĳ��¼ĳ���������ͼƬ��·��
	bool IfExistImagePathImageTable(CString caseName,CString category,CString imgName,bool* ifExist);///<�ж�ĳ��¼ĳ������Ƿ��Ѿ�����ĳ��ͼƬ
    bool DeleteDataFromImageTable(CString caseName,CString category,CString imagePath);              ///<��ͼƬ����ɾ��һ����¼
	bool IfExistImgDataImageTable(ImageTable imgData,bool* ifExist);                                 ///<�ж�ͼƬ�����Ƿ�����һ����ͬ�ļ�¼
	int GetCaseImgNumFromImageTable(CString caseName);                                               ///<���ͼƬ����ĳһ����¼�µ�ͼƬ����
	bool GetCaseImgDataFromImageTable(vector<ImageTable> *caseAllImgData,CString caseName);          ///<���ĳһ��¼������ͼƬ��·��
	///
	///���������غ���
	///	
	bool CreateClueTable(CString ClueTableName="clueTable");                                         ///<����������
	bool InsertData2ClueTable(ClueTable clueData);                                                   ///<��һ����¼���뵽��������
	bool GetClueDataFromClueTable(vector<ClueTable>* caseClueData,CString caseName);                 ///<���ĳ��¼�����е�������Ϣ
	bool GetClueDataFromClueTable(ClueTable* clueData,bool*isExistClue);                             ///<�ж����������Ƿ��Ѿ�����һ����ͬ�ļ�¼
	bool UpdateDescriptionInClueTable(ClueTable clueData);                                           ///<�����������е���������
	bool UpdateClueDataInClueTable(ClueTable clueData);                                              ///<����һ��������¼
	bool DeleteDataFromClueTable(ClueTable clueData);                                                ///<ɾ���������е�ĳ����¼
	bool GetClueDescripFromClueTable(CString caseName,CString cameraName,CString cluePath,CString& clueDesrip);///<���ĳ��¼ĳ��ص��ĳ��·���ļ������ڼ�¼����������
	int GetClueNumFromClueTable(CString caseName);                                                   ///<�õ�ĳ����¼�����ĸ���

	///////////////////////////
	///��Ƶ�ָ��ںϴ����е���غ���
	//////////////////
	
	///
	///trace�����غ���
	///
	bool CreateOrigTraceTable(CString OrigTraceTableName);                                           ///<����ԭʼtrace��
	bool InsertData2OrigTraceTable(OrigTraceTable infor1,CString OrigTraceTableName);                ///<����в���һ����¼
	bool GetInfor1DataFromOrigTraceTable(int row,OrigTraceTable* infor1,CString OrigTraceTableName);  ///<�ӱ���ض��ж�ȡ���ݴ���ṹ��
	bool SearchSegOfSize(CString tableName,int segSize,vector<SearchSegIDParams>* segIdParam);	  ///<�Ӿ�trace���в�ѯ�ߴ��С�������ԭʼ֡�ź�ROI���õ���ѯ���
	///
	///newtrace�����غ���
	///
	bool CreateNewTraceTable(CString tableName);                                                        ///<����new trace��
	bool Unite2NewTraceTable(CString newTraceTable,CString origTraceTable,CString frameTable);	        ///<��ԭʼtrace����¾�֡��Ӧ������	
	bool FindROIFromNewTraceTable(int NewFrame,vector <CvRect> *m_ROI,CString tableName);                ///<�����֡�������˶�Ŀ���ROI
	int FindOrigFrameFromNewTraceTable(CString newTraceTable,CvRect rect);	                            ///<��new trace���и���ROI��Ϣ�ҵ�ԭʼ��Ƶ֡��
	int FindOrigFrameFromVideoFGTable(CString VideoFGTable,int origPara);	                            ///<��videofg���и��ݶκ��ҵ�ԭʼ��Ƶ֡��
	int FindOrigParaFromFGTraceTable(CString FGTraceTable, CvRect rect);	                            ///<��FGTrace���и���ROI��Ϣ�ҵ�ԭʼ��Ƶ�κ�
	int FindSegIDFromFGTraceTable(CString FGTraceTable,int nOldPara);	                            ///<��new trace���и���ROI��Ϣ�ҵ�ԭʼ��Ƶ֡��
	bool FindTimePositionFromNewTraceTable(int NewFrame,vector <CvPoint> *m_Point,vector<int> *origFrame,CString tableName);
	///
	///NewToOldParaTable�����غ���
	///
	bool CreateNewToOldParaTable(CString NewToOldParaTableName);                                         ///<�����¾ɶζ�Ӧ��
	bool InsertData2NewToOldParaTable(NewToOldParaTable infor2,CString NewToOldParaTableName);           ///<����в���һ����¼
	int FindNewParaFromNewToOldParaTable(int oldParag,CString NewToOldParaTableName);                   ///<���ݾɶκŴӱ��в�ѯ�¶κ�
	///
	///NewToOldFrameTable�����غ���
	///	
	bool CreateNewToOldFrameTable(CString NewToOldFrameTableName);                                      ///<�����¾�֡��Ӧ��
    bool InsertData2NewToOldFrameTable(NewToOldFrameTable infor3,CString NewToOldFrameTableName);       ///<����в���һ����¼
	///
	///�˶�ǰ���α����غ���
	///	
	bool CreateVideoFGTable(CString tableName);                                                         ///<�����˶�ǰ���α�
	bool InsertData2VideoFGTable(VideoFGTable infor,CString tableName);                                 ///<����в���һ����¼
	int FindEndFrameFromVideoFGTable(int paraNum,CString tableName);                                    ///<�ҵ�ĳһǰ���εĽ���֡��
	int FindStartFrameFromVideoFGTable(int paraNum,CString TableName);                                  ///<�ҵ�ĳһǰ���ε���ʼ֡��

	///
	///�˶������α����غ���
	///	
	bool CreateVideoBGTable(CString tableName);                                                           ///<�����˶������α�
	bool InsertData2VideoBGTable(VideoBGTable infor,CString tableName);                                  ///<����в���һ����¼
	int FindEndFrameFromVideoBGTable(int bkgID,CString tableName);                                       ///<�ҵ�ĳһǰ���εĽ���֡��
	int FindStartFrameFromVideoBGTable(int bkgID,CString TableName);                                     ///<�ҵ�ĳһǰ���ε���ʼ֡��

	///
	///CombineSegsTable�����õ��ı����غ���
	///
	bool CreateCombineSegsTable(CString CombineSegsTableName);											///����
	bool InsertData2CombineSegsTable(OrigTraceTable traceTab, CString CombineSegsTableName);			///��������
	bool FindROIFromCombineSegsTable(vector <CvRect> *m_ROI, CString tableName);						///�������ROI
	bool GetObjectInfoFromObjectTable(vector<objectInfo> *objDetectedInfos,CString ObjectTableName);       ///<��ȡ�����˶�Ŀ�����Ϣ

	///
	///VidAbstract�õ��ı����غ���
	///	
	bool CreateCListItemTable(CString tableName);                                                        ///<����һ�����ڼ�¼������ص�������CListCtrl�кŵı�
	bool InsertData2CListItemTable(CString tableName,CString caseName,CString cameraName,CString videoName,int clistRow);///<����в���һ����¼
	bool IfExistCListItemTable(CString tableName,CString caseName,CString cameraName,bool* ifExist);     ///<�б����Ƿ��Ѿ�����ĳ����¼ĳ����ص����Ƶ
	CString GetCurrentOrigVideoName(CString clistTableName,int clistRow);                                ///<�õ�Ŀǰ�����item��ԭʼ��Ƶ·��
	CString GetCurCameraName(CString clistTableName,int clistRow);                                       ///<�õ�Ŀǰ�����item�ļ�¼����
	CString GetCurCaseName(CString clistTableName,int clistRow);                                         ///<�õ�Ŀǰ�����item�ļ�ص�����
	CString GetCurrentFusionVideoName(CString clistTableName,int clistRow);                              ///<�õ�Ŀǰ�����item���ں���Ƶ·��
	int GetCurrentProcessingRow(CString clistTableName,CString caseName,CString cameraName);             ///<�õ�Ŀǰ���ڴ����item���к�

	///
	///DrawDetect�����õ��ı����غ���
	///
	bool CreateObjectTable(CString tableName);                                                            ///<������
	int GetTableDistinctNum(CString tableName);                                                           ///<�õ�����Ŀ������
	bool InsertData2ObjectTable(NewTrackParam infor5,CString ObjectTableName);                            ///<����в���һ����¼
	void GetCenterFromObjectTable(int objectID, CString ObjectTableName, vector<CPoint>* centersOfObj);   ///<��ȡĳ���˶�Ŀ��Ĺ켣�㼯��
	void GetRectFromObjectTable(int frameID, CString ObjectTableName, vector<CRect>* rect,vector<int>* objID);///<��ȡĳһ֡���˶������ID��Rect
	void GetSingleTraceFromObjectTable(int objID, CString ObjectTableName, vector<CRect>* rect,vector<CPoint>* centersOfObj);///<һ���Զ�ȡĳ���˶�Ŀ��Ĺ켣�㼯�Ϻ�Rect����
	int  GetObjectIDFromObjectTable(int frameID,CRect rect,CString ObjectTableName);                       ///<��ȡĳһ֡����λ�õ�����ID
	
	bool GetFrameidFromObjectTable(int objectID,CString ObjectTableName,vector<int>* frameID);              ///<��ȡĳһ�˶�Ŀ���frameID����


};