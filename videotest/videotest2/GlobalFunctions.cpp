/**
*@file GlobalFunctions.cpp
*@brief ������һЩͨ�ú�����ʵ��
*
*�����ɾ���·���õ����ƣ���ȡ��\�����ߡ�.��ǰ�ַ������ݿ���ò���ʾ��combox�Ȳ�������Ϊ
*
*@author ���� zhang nannan ,����email��
*@version �汾��(0.0)
*@data 2012-8-21
*/
#include "stdafx.h"
#include <afxwin.h>
#include <afxmt.h>
#include "GlobalFunctions.h"

///@brief �ɾ���·���õ��ļ�����������׺��
///
///@param[in|out] absolutePath �ļ�����·��|videoName ȥ��·�����ļ�����������׺��
///@pre  NULL
///@return NULL
///@retval NULL
///@post NULL
void GetVideoNameFromAbsolutePath(CString* absolutePath,CString* videoName)
{
	const char* m_constVideoText = NULL;
	char * m_charVideoText =(char*) malloc(255*sizeof(char));
	char *p = NULL;
	char *pre_p = NULL;
	int index = 0;

	m_constVideoText = *absolutePath;

	strcpy(m_charVideoText,m_constVideoText);
	p = strtok(m_charVideoText,"/");
	
	//p = strtok(m_charVideoText,"\\");
	while(p)
	{
		pre_p = p;
		p = strtok(NULL,"/");
		//p = strtok(NULL,"\\");
		if(!p)
		{
			*videoName = pre_p;
		}
	}
	free(m_charVideoText);
}
void GetVideoNameFromAbsolutePath1(CString* absolutePath,CString* videoName)
{
	const char* m_constVideoText = NULL;
	char * m_charVideoText =(char*) malloc(255*sizeof(char));
	char *p = NULL;
	char *pre_p = NULL;
	int index = 0;

	m_constVideoText = *absolutePath;

	strcpy(m_charVideoText,m_constVideoText);
	//p = strtok(m_charVideoText,"/");

	p = strtok(m_charVideoText,"\\");
	while(p)
	{
		pre_p = p;
		//p = strtok(NULL,"/");
		p = strtok(NULL,"\\");
		if(!p)
		{
			*videoName = pre_p;
		}
	}
	free(m_charVideoText);
}
///@brief �õ��ַ������ұߵġ�.��ǰ���ļ�����������·����������׺��
///
///@param[in|out] absolutePath �ļ�����·��|fileName ȥ����׺����·�����ļ���
///@pre  NULL
///@return NULL
///@retval NULL
///@post NULL
void GetFileNameBeforeDot(CString* absolutePath,CString* fileName)
{
	int dotNum = 0;
	for (int i=0;i<absolutePath->GetLength();i++)
	{
		dotNum = absolutePath->Find(".",i); 
		if (dotNum==-1)
		{
			dotNum=i;
			break;
		}
		else
		{
			i=dotNum;
		}
	}
	
	*fileName = absolutePath->Left(dotNum-1);
}
///@brief �õ��ַ������ұߵġ�/���������ַ���
///
///@param[in|out] absolutePath ������ַ���|fileName ��õ����ַ���
///@pre  NULL
///@return NULL
///@retval NULL
///@post NULL
void GetFileNameBeforeSlider(CString* absolutePath,CString* fileName)
{
	int dotNum = 0;
	for (int i=0;i<absolutePath->GetLength();i++)
	{
		dotNum = absolutePath->Find("/",i); 
		if (dotNum==-1)
		{
			dotNum=i;
			break;
		}
		else
		{
			i=dotNum;
		}
	}

	*fileName = absolutePath->Left(dotNum-1);
}
///@brief ��droplist����ʾ������
///
///�����ݿ��в������еİ���������combox��insert����ʾ��droplist��
///@param[in|out] droplistBox �б��|NULL
///@pre  NULL
///@return NULL
///@retval NULL
///@post NULL
void ShowCaseDroplist(CComboBox* droplistBox)
{
	vector<CString> caseName;
	if(!m_MysqlHandle->GetAllCaseNameFromCaseTable(&caseName))
	{
		AfxMessageBox("���ݿ����");
		return;
	}
	else
	{
		if(!caseName.empty())
		{
			CString itemNo;
			CString videoName;
			for(vector<CString>::size_type i=0;i!= caseName.size();i++)
			{
				(*droplistBox).AddString(caseName.at(i));
			}
		}
	}
	caseName.swap(vector<CString>());
	
}
///@brief ��droplist����ʾ��ص���
///
///�����ݿ��в���ĳ���������еļ�ص㣬��combox��insert����ʾ��droplist��
///@param[in|out] droplistBox �б��;caseName ������|NULL
///@pre  NULL
///@return NULL
///@retval NULL
///@post NULL
void ShowCameraDroplist(CString* caseName,CComboBox* droplistBox)
{
	droplistBox->ResetContent();
	vector<CString> cameraName;
	if(!m_MysqlHandle->GetMoniorNameFromVideoTable(*caseName,&cameraName))
	{
		AfxMessageBox("���ݿ����");
		return;
	}
	else
	{
		if(!cameraName.empty())
		{
			CString itemNo;
			CString videoName;
			for(vector<CString>::size_type i=0;i!= cameraName.size();i++)
			{
				(*droplistBox).AddString(cameraName.at(i));
			}
		}
	}
	cameraName.swap(vector<CString>());
}
///@brief ��droplist����ʾͼƬ���
///
///�����ݿ��в���ĳ���������е�ͼƬ�����combox��insert����ʾ��droplist��
///@param[in|out] droplistBox �б��;caseName ������|NULL
///@pre  NULL
///@return NULL
///@retval NULL
///@post NULL
void ShowCategoryDroplist(CString* caseName,CComboBox* droplistBox)
{
	droplistBox->ResetContent();
	vector<CString> categoryName;
	if(!m_MysqlHandle->GetCategoryNameFromImageTable(*caseName,&categoryName))
	{
		AfxMessageBox("���ݿ����");
		return;
	}
	else
	{
		if(!categoryName.empty())
		{
			CString itemNo;
			CString videoName;
			for(vector<CString>::size_type i=0;i!= categoryName.size();i++)
			{
				(*droplistBox).AddString(categoryName.at(i));
			}
		}
	}
	categoryName.swap(vector<CString>());
}

///@brief �ַ���ת������
///
///CString��string��char*֮����໥ת��
///@param[in|out] CString��string��char*����־λ
///@pre  NULL
///@return NULL
///@retval NULL
///@post NULL
void MyStringConversion(CString *mycstring, string *mystring, char *mychar,int flag)
{
	///<flag = 1, CString2string
	///<flag = 2, string2CString
	///<flag = 3, CString2char
	///<flag = 4, char2CString
	///<flag = 5, string2char
	///<flag = 6, char2string
	switch(flag)
	{
	case 1:
		*mystring = mycstring->GetBuffer(mycstring->GetLength());
		mycstring->ReleaseBuffer();
		break;
	case 2:
		*mycstring = mystring->c_str();
		break;
	case 3:
		mychar =(LPSTR)(LPCTSTR)(*mycstring);
		break;
	case 4:
		mycstring->Format("%s", *mychar); 
		break;
	case 5: 
		mychar = const_cast<char*>(mystring->c_str());
		break;
	case 6:
		*mystring = mychar;
	}
}