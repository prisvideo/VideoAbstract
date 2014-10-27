/**
*@file ButtonBeautify.h
*@brief ��ҪΪʹ�ð�ť�����ĵ��ù�����Ķ��塣
*
*���ļ������CButtonBeautify�࣬�书������Ҫ��ɰ�ť��������
*
*@author ���� shen wei
*@version �汾��(0.0)
*@data 2012-5-23
*/
#include "stdafx.h"
#include "ButtonBeautify.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/// CButtonBeautify

CButtonBeautify::CButtonBeautify()
{
	m_bIsMouseMove = FALSE;
}

CButtonBeautify::~CButtonBeautify()
{
}


BEGIN_MESSAGE_MAP(CButtonBeautify, CButton)
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
/// CButtonBeautify message handlers
///@brief ��������������������ֵ������ 
///
///@param[in] NULL
///@return BOOL
///@retval NULL
///@post TRUE
void CButtonBeautify::PreSubclassWindow() 
{
	ModifyStyle(0, BS_OWNERDRAW);
	CButton::PreSubclassWindow();
}
///@brief ������ƶ�ʱ���ô˺��� 
///
///@param[in]  nFlags,ָʾ�������ⰴ���Ƿ���;
///            point,����X,Y���꣺������Ϊ ������ػ����Ϣ�Ĵ������Ͻǵ�λ�� ��һ�����λ�ö���������Ļ�����ϵľ���λ��
///@pre  NULL
///@return BOOL
///@retval NULL
///@post TRUE
void CButtonBeautify::OnMouseMove(UINT nFlags, CPoint point) 
{
	if( !m_bIsMouseMove )
	{
		m_bIsMouseMove = TRUE;
		Invalidate();

		TRACKMOUSEEVENT trackmouseevent;
		trackmouseevent.cbSize = sizeof(trackmouseevent);
		trackmouseevent.dwFlags = TME_LEAVE ;
		trackmouseevent.hwndTrack = GetSafeHwnd();
		trackmouseevent.dwHoverTime = HOVER_DEFAULT;
		_TrackMouseEvent(&trackmouseevent);
	}

	CButton::OnMouseMove(nFlags, point);
}


#define WM_MOUSEOFFBUTTON  WM_USER+101 
///@brief ������ƶ�ʱ���ô˺��� 
///
///@param[in]  wParam,��Ϣ��Ӧ����;
///            lParam,��Ϣ��Ӧ����
///@pre  NULL
///@return BOOL
///@retval NULL
///@post TRUE
LONG CButtonBeautify::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	m_bIsMouseMove = FALSE;
	::PostMessage(GetParent()->GetSafeHwnd(), WM_MOUSEOFFBUTTON, 0, 0);
	Invalidate();

	return 0;
}

#define WM_MOUSEONBUTTON  WM_USER+100 
///@brief ����DrawItem���Ի����Լ���Ҫ�Ŀؼ���� 
///
///@param[in]  lpDrawItemStruct,�����й�����Ļ�ͼ�����͵���Ϣ
///@pre  NULL
///@return BOOL
///@retval NULL
///@post TRUE
void CButtonBeautify::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct )
{

	CDC* pDC      = CDC::FromHandle(lpDrawItemStruct->hDC);
	DWORD nState  = lpDrawItemStruct->itemState;
	DWORD nAction = lpDrawItemStruct->itemAction; 
	CRect rc	  = lpDrawItemStruct->rcItem;
	UINT uStyle   = DFCS_BUTTONPUSH;

	pDC->SetBkMode(TRANSPARENT);
	CString strText;
	GetWindowText(strText);

	if (nState & ODS_SELECTED)///<select
	{
		m_bIsMouseMove = FALSE;
		DrawSelectedState(rc, pDC);
	}
	else ///<Normal
	{
		DrawNormalState(rc, pDC);
	}

	if (m_bIsMouseMove)///<hover on the button
	{
		DrawFocusState(rc, pDC);
		::PostMessage(GetParent()->GetSafeHwnd(), WM_MOUSEONBUTTON, 0, 0);

	}

	pDC->DrawText(strText, strText.GetLength(), 
		&lpDrawItemStruct->rcItem, 
		DT_SINGLELINE|DT_VCENTER|DT_CENTER);

}

///@brief ͼ����ͼ����Ӧ��m_bmNormal��Ч�� 
///
///@param[in]  rc,���ڶ�����ε����ϽǺ����½ǵ�ĳ�Ա������*pDC �豸�����Ķ������
///@pre  NULL
///@return BOOL
///@retval NULL
///@post TRUE
void CButtonBeautify::DrawNormalState(CRect rc, CDC *pDC)
{

	pDC->DrawState(CPoint(0, 0), CSize(rc.Width(), rc.Height()),
		m_bmNormal, DSS_NORMAL);

}
///@brief ͼ����ͼ����Ӧ��m_bmSelect��Ч�� 
///
///@param[in]  rc,���ڶ�����ε����ϽǺ����½ǵ�ĳ�Ա������*pDC �豸�����Ķ������
///@pre  NULL
///@return BOOL
///@retval NULL
///@post TRUE
void CButtonBeautify::DrawSelectedState(CRect rc, CDC *pDC)
{

	pDC->DrawState(CPoint(0, 0), CSize(rc.Width(), rc.Height()),
		m_bmSelect, DSS_NORMAL);

}

///@brief ͼ����ͼ����Ӧ��m_bmFocuse��Ч�� 
///
///@param[in]  rc,���ڶ�����ε����ϽǺ����½ǵ�ĳ�Ա������pDC �豸�����Ķ������
///@pre  NULL
///@return BOOL
///@retval NULL
///@post TRUE
void CButtonBeautify::DrawFocusState(CRect rc, CDC *pDC)
{

	pDC->DrawState(CPoint(0, 0), CSize(rc.Width(), rc.Height()),
		m_bmFocuse, DSS_NORMAL);
}

void CButtonBeautify::DrawFace(CRect &rc, COLORREF clrTopRight, COLORREF clrBottomLeft,
	CDC* pDC)
{

	CPen Pen;
	CPen* pOldPen = pDC->SelectObject(&Pen);
	int R,G, B;
	R = (GetRValue(clrTopRight) - GetRValue(clrBottomLeft)) / rc.Height();
	G = (GetGValue(clrTopRight) - GetGValue(clrBottomLeft)) / rc.Height();
	B = (GetBValue(clrTopRight) - GetBValue(clrBottomLeft)) / rc.Height();
	int nColR = GetRValue(clrTopRight); 
	int	nColG = GetGValue(clrTopRight);
	int	nColB = GetBValue(clrTopRight);
	COLORREF clrColMax = clrTopRight > clrBottomLeft ? clrTopRight  : clrBottomLeft;
	COLORREF clrColMin = clrTopRight > clrBottomLeft ? clrBottomLeft: clrTopRight;

	for(int i=0; i<rc.Height(); i++)
	{
		nColR -= R;
		nColG -= G;
		nColB -= B;
    	Pen.CreatePen(PS_SOLID, 1, RGB(nColR, nColG, nColB));
		pDC->SelectObject(&Pen);
		pDC->MoveTo(rc.left, rc.top+i);
		pDC->LineTo(rc.right, rc.top+i);
		Pen.DeleteObject();
	}

	pDC->SelectObject(pOldPen);

}
///@brief ����ͼͼƬ����ʽ 
///
///@param[in]  rc ���ڶ�����ε����ϽǺ����½ǵ�ĳ�Ա����,clrTopRight ���һ��RGB��ɫ,clrBottomLeft ���һ��RGB��ɫ,pDC �豸�����Ķ������
///@pre  NULL
///@return BOOL
///@retval NULL
///@post TRUE
void CButtonBeautify::DrawFrame(CRect& rc, COLORREF clrTopRight, COLORREF clrBottomLeft,
	CDC* pDC)
{
	CBrush NullBrush;
	NullBrush.CreateStockObject(NULL_BRUSH);
	CBrush* pOldBrush = pDC->SelectObject(&NullBrush);
	CPen Pen;
	Pen.CreatePen(PS_SOLID, 1, RGB(0, 64, 128));
	CPen* pOldPen = pDC->SelectObject(&Pen);
	pDC->RoundRect(rc, CPoint(3, 3) );
	rc.DeflateRect(1, 1, 1, 1); 
	pDC->Draw3dRect(rc, clrTopRight, clrBottomLeft);
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}

///@brief ����ͼ����ͼ����Ӧ�õ�Ч�� 
///
///@param[in]  &nNormal,&nSelect,&nFocuseЧ����ʽ
///@pre  NULL
///@return BOOL
///@retval NULL
///@post TRUE

void CButtonBeautify::SetBitmaps(CBitmap &nNormal, CBitmap &nSelect, CBitmap &nFocuse)
{
    m_bmNormal.Attach(nNormal);
	m_bmSelect.Attach(nSelect);
	m_bmFocuse.Attach(nFocuse);
	nNormal.Detach();
	nSelect.Detach();
	nFocuse.Detach();
	
	return;
}

