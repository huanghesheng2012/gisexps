// CreateFileDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MapEditor3.h"
#include "CreateFileDlg.h"
#include "afxdialogex.h"


// CCreateFileDlg 对话框

IMPLEMENT_DYNAMIC(CCreateFileDlg, CDialogEx)

CCreateFileDlg::CCreateFileDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCreateFileDlg::IDD, pParent)
	, m_add(_T(""))
{
	HMODULE module = GetModuleHandle(0);
	char* pFileName = new char[MAX_PATH];
	GetModuleFileName(module,LPWSTR(pFileName),MAX_PATH);
	m_add.Format(_T("%s"),pFileName);
	int nPos = m_add.ReverseFind(_T('\\'));
	if(nPos<0)
	{
		m_add ="";
	}
	else
	{
		m_add = m_add.Left(nPos);//得到.EXE的文件地址

	}
	delete[]pFileName;
}

CCreateFileDlg::~CCreateFileDlg()
{
	
}

void CCreateFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CREATE_FILE_ADDRESS, m_add);
}


BEGIN_MESSAGE_MAP(CCreateFileDlg, CDialogEx)
	ON_BN_CLICKED(IDC_CREATE_FILE_CHANGE_ADDRESS_BTN, &CCreateFileDlg::OnBnClickedCreateFileChangeAddressBtn)
END_MESSAGE_MAP()


// CCreateFileDlg 消息处理程序


void CCreateFileDlg::OnBnClickedCreateFileChangeAddressBtn()
{
	// TODO: 在此添加控件通知处理程序代码

	BROWSEINFO bInfo;
	ZeroMemory(&bInfo,sizeof(bInfo));
	bInfo.hwndOwner = GetSafeHwnd();
	bInfo.lpszTitle = _T("请选择临时文件存放的路径：“");
	bInfo.ulFlags = BIF_RETURNONLYFSDIRS;
	LPITEMIDLIST lpDlist;
	lpDlist = SHBrowseForFolder(&bInfo);//显示选择对话框
	if(lpDlist != NULL) //用户按下确定按钮
	{
		TCHAR chPath[MAX_PATH];
		SHGetPathFromIDList(lpDlist,chPath);//把项目标识列表转化成字符串
		m_add = chPath;//将TCHAR类型字符串转换为CString类型字符串
		UpdateData(FALSE);
	}
}
