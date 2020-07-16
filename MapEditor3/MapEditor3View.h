
// MapEditor3View.h : CMapEditor3View 类的接口
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


protected: // 仅从序列化创建
	CMapEditor3View();
	DECLARE_DYNCREATE(CMapEditor3View)

// 特性
public:
	CMapEditor3Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:


// 实现
public:
	virtual ~CMapEditor3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // MapEditor3View.cpp 中的调试版本
inline CMapEditor3Doc* CMapEditor3View::GetDocument() const
   { return reinterpret_cast<CMapEditor3Doc*>(m_pDocument); }
#endif

