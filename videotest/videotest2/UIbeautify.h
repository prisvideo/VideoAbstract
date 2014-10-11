/**
*@file UIbeautify.h
*@brief ��ҪΪʹ�ý����������ܵĵ��ù������������
*
*���ļ������UIbeautify�࣬�书������Ҫ������������ݣ������Ͱ�ť��������
*Ϊ�˽����Ч��������Ӧ����Ĵ�С����Ҫ�õ�ͼƬ�����죬�˴��õ���opencv��ͼƬ���������
*
*@author ���� lu peng&&chen dai wu ,����email��
*@version �汾��(0.0)
*@data 2012-8-21
*/
#pragma  once
#include "afxwin.h"
#include "ButtonBeautify.h"                                ///@brief ��ť������չ��                                 
#include "publicheader.h"                                  ///@brief ����opencv��lib�ļ���

///@brief ����Ľ���������
///
///UIbeautify�����๦������Ҫ������������ݣ������Ͱ�ť��������
///Ϊ�˽����Ч��������Ӧ����Ĵ�С����Ҫ�õ�ͼƬ�����죬�˴��õ���opencv��ͼƬ���������
///
///@invariant rcDeskRect��ȡ�����С��ֵ����
///

class UIbeautify
{
public:
	UIbeautify();
	virtual ~UIbeautify();

	///�й����������Ĳ�����
	void LoadBackgroundPic(int n_IDC);                    ///<���ر���ͼƬ
	void PaintBackground(HWND phwnd);                     ///<�����������һЩ���ò���

    ///����ʵ�ְ�ť�������Լ���λ�ĺ�����
    ///�ڶ���LoadButtonBitmaps����������������,��������ͼƬ��С,��ʵ�ְ�ťͼƬ�ظ�����
	void LoadButtonBitmaps(CButtonBeautify &BtName, int n_IDB1, int n_IDB2, double LeftRatio, double TopRatio, double RightRatio, double BottomRatio); ///<ʵ�ְ�ť�������Լ���λ
	void LoadButtonBitmaps(CButtonBeautify &BtName, int n_IDB1, int n_IDB2, double LeftRatio, double TopRatio, double RightRatio, double BottomRatio, int width, int height);///<ʵ�ְ�ť�������Լ���λ
	void FillBitmapInfo(LPBITMAPINFO bmi, int width, int height, int bpp, int origin); ///<ʵ���½�BitmapͼƬʱ���Bitmap��Ϣ

	///�й�ͼƬ�ı��С�Ĳ�����
	///CBitmapResize������CBitmapToIplImage��IplImageToCBitmap��������CBitmapת��IplImage��
	///Ȼ������opencv��cvResize�ı��С,�ٱ����CBitmap��ʽ������ʱ������FillBitmapInfo������
	CBitmap  *CBitmapResize(CBitmap& Bmp,int width,int height);///<ʵ��CBitmap����ͼƬ��С�任
	CBitmap  *IplImageToCBitmap(const IplImage *pImage);       ///<ʵ��CBitmapתIplImage
	CBitmap m_BitmapBackGround;           ///<���汳��ͼƬ
	IplImage *CBitmapToIplImage(CBitmap& Bmp);                 ///<ʵ��CBitmapתIplImage
	CRect rcDeskRect;                     ///<������������
	LPBITMAPINFO bmi;                     ///<λͼ��Ϣͷ         
	BOOL OnEraseBkgnd(HWND phwnd, CDC* pDC, CBitmap& Bmp);///<����������
	
};