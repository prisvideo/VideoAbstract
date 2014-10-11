/**
*@file ButtonBeautify.h
*@brief ��ҪΪʹ�ð�ť�����ĵ��ù������������
*
*���ļ������CButtonBeautify�࣬�书������Ҫ��ɰ�ť��������
*
*@author ���� shen wei
*@version �汾��(0.0)
*@data 2012-5-23
*/
#if !defined(AFX_MYBUTTON_H__1B425AEB_661D_426C_998C_37C85EF445D5__INCLUDED_)
#define AFX_MYBUTTON_H__1B425AEB_661D_426C_998C_37C85EF445D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
///@brief ����Ľ���������
///
///UIbeautify�����๦���Ϲ�������Ҫ��ɰ�ť������
///
///@invariant 
///
class CButtonBeautify : public CButton
{

public:
	CButtonBeautify();
	virtual ~CButtonBeautify();
	void SetBitmaps(CBitmap &nNormal, CBitmap &nSelect, CBitmap &nFocuse);///<����ͼ����ͼ����Ӧ�õ�Ч��
	void DrawNormalState(CRect rc, CDC *pDC);	///<ͼ����ͼ����Ӧ��m_bmNormal��Ч��
	void DrawSelectedState(CRect rc, CDC *pDC);	///<ͼ����ͼ����Ӧ��m_bmSelect��Ч��
	void DrawFocusState(CRect rc, CDC *pDC);	///<ͼ����ͼ����Ӧ��m_bmFocuse��Ч��
	void DrawFace(CRect& rc, COLORREF clrTopRight, COLORREF clrBottomLeft,
		CDC* pDC);
	void DrawFrame(CRect& rc, COLORREF clrTopRight, COLORREF clrBottomLeft,
		CDC *pDC);///<����ͼͼƬ����ʽ
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);///<����DrawItem���Ի����Լ���Ҫ�Ŀؼ����
	virtual void PreSubclassWindow();						 ///<��������������������ֵ������

public:
	BOOL	m_bIsMouseMove;
	CBitmap m_bmNormal;
	CBitmap m_bmSelect;
	CBitmap m_bmFocuse;

protected:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);		///<���ָ���ƶ���ťʱ����������Ϣ����
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam); ///<���ָ���뿪��ťʱ����������Ϣ����
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

///{{AFX_INSERT_LOCATION}}
/// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif ///< !defined(AFX_MYBUTTON_H__1B425AEB_661D_426C_998C_37C85EF445D5__INCLUDED_)
