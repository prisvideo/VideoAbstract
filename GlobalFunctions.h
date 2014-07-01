/**
*@file GlobalFunctions.cpp
*@brief ������һЩ�õĶ��ͨ�ú�����ʵ��
*
*�����ɾ���·���õ����ƣ���ȡ��\�����ߡ�.��ǰ�ַ������ݿ���ò���ʾ��combox�Ȳ�������Ϊ
*
*@author ���� zhang nannan ,����email��
*@version �汾��(0.0)
*@data 2012-8-21
*/
#pragma once

#include <string.h>
#include "LibMySql.h"
extern CDataMySql* m_MysqlHandle;

void GetVideoNameFromAbsolutePath(CString* absolutePath,CString* videoName); ///<�ɾ���·���õ��ļ�����������׺��
void GetVideoNameFromAbsolutePath1(CString* absolutePath,CString* videoName); 
void GetFileNameBeforeDot(CString* absolutePath,CString* fileName);         ///<�õ��ַ������ұߵġ�.��ǰ���ļ�����������·����������׺��
void GetFileNameBeforeSlider(CString* absolutePath,CString* fileName);      ///<�õ��ַ������ұߵġ�/���������ַ���
void ShowCaseDroplist(CComboBox* droplistBox);                              ///<��droplist����ʾ������
void ShowCameraDroplist(CString* caseName,CComboBox* droplistBox);          ///<��droplist����ʾ��ص���
void ShowCategoryDroplist(CString* caseName,CComboBox* droplistBox);        ///<��droplist����ʾͼƬ���
