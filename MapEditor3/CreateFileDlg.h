#pragma once


// CCreateFileDlg �Ի���

class CCreateFileDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCreateFileDlg)

public:
	CCreateFileDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCreateFileDlg();

// �Ի�������
	enum { IDD = IDD_CREATE_FILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_add;
	afx_msg void OnBnClickedCreateFileChangeAddressBtn();
};
