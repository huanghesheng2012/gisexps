
// MapEditor3View.h : CMapEditor3View ��Ľӿ�
//

#pragma once
#include "AbstractSymbol.h"
#include <D:/Program Files (x86)/Microsoft Visual Studio 10.0/VC/include/math.h>
#include <vector>
#include <map>


class CMapEditor3View : public CView
{
private:
	AbstractSymbol *pSymbol;
	vector<AbstractSymbol *> pSymbolArray;


protected: // �������л�����
	CMapEditor3View();
	DECLARE_DYNCREATE(CMapEditor3View)

// ����
public:
	CMapEditor3Doc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:


// ʵ��
public:
	virtual ~CMapEditor3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnWindowZoomIn();
	afx_msg void OnFileNew();
	afx_msg void OnBnClickedCreateFileChangeAddressBtn();
	afx_msg void OnPointCreate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPointSave();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLineCreate();
	afx_msg void OnPointCircle();
};

#ifndef _DEBUG  // MapEditor3View.cpp �еĵ��԰汾
inline CMapEditor3Doc* CMapEditor3View::GetDocument() const
   { return reinterpret_cast<CMapEditor3Doc*>(m_pDocument); }
#endif

