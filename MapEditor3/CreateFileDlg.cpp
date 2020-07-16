// CreateFileDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MapEditor3.h"
#include "CreateFileDlg.h"
#include "afxdialogex.h"


// CCreateFileDlg �Ի���

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
		m_add = m_add.Left(nPos);//�õ�.EXE���ļ���ַ

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


// CCreateFileDlg ��Ϣ�������


void CCreateFileDlg::OnBnClickedCreateFileChangeAddressBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	BROWSEINFO bInfo;
	ZeroMemory(&bInfo,sizeof(bInfo));
	bInfo.hwndOwner = GetSafeHwnd();
	bInfo.lpszTitle = _T("��ѡ����ʱ�ļ���ŵ�·������");
	bInfo.ulFlags = BIF_RETURNONLYFSDIRS;
	LPITEMIDLIST lpDlist;
	lpDlist = SHBrowseForFolder(&bInfo);//��ʾѡ��Ի���
	if(lpDlist != NULL) //�û�����ȷ����ť
	{
		TCHAR chPath[MAX_PATH];
		SHGetPathFromIDList(lpDlist,chPath);//����Ŀ��ʶ�б�ת�����ַ���
		m_add = chPath;//��TCHAR�����ַ���ת��ΪCString�����ַ���
		UpdateData(FALSE);
	}
}
