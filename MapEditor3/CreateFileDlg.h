#pragma once


// CCreateFileDlg 对话框

class CCreateFileDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCreateFileDlg)

public:
	CCreateFileDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCreateFileDlg();

// 对话框数据
	enum { IDD = IDD_CREATE_FILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_add;
	afx_msg void OnBnClickedCreateFileChangeAddressBtn();
};
