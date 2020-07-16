
// MapEditor3View.cpp : CMapEditor3View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MapEditor3.h"
#endif

#include "MapEditor3Doc.h"
#include "MapEditor3View.h"
#include "CreateFileDlg.h"
#include "paint.h"
#include "WriteOrRead.h"
#include "Calculate.h"
#include "CircleSymbol.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

///-------------------------------��������ص�ȫ�ֿ��Ʊ���------------------------------
bool GPntFCreated = false;
CString GPntFName;
CString GPntTmpFName = CString("tempPntF.dat");
bool GPntChanged = false;
int GPntNum = 0;
int GPntLNum = 0;
CFile *GPntTmpF = new CFile();

///------------------------------��������ص�ȫ�ֿ��Ʊ���---------------------------------
bool GLinFCreated = false;
CString GLinFName;
CString GLinTmpNdxFName = CString("tempLinf.ndx");//��ʱ�����ļ���
CString GLinTmpDatFName = CString("tempLinF.dat");
bool GLinChanged = false;
int GLinNum = 0;
int GLinLNum = 0;
CFile *GLinTmpDatF = new CFile();
CFile *GLinTmpNdxF = new CFile();

///-----------------------------��������ص�ȫ�ֿ��Ʊ���----------------------------
bool GRegFCreated = false;
CString GRegFName;
CString GRegTmpNdxFName = CString("tempRegF.ndx");
CString GRegTmpDatFName= CString("tempRegF.dat");
bool GRegChanged = false;
int GRegNum =0;
int GRegLNum =0;
CFile *GRegTmpDatF = new CFile();
CFile *GRegTmpNdxF = new CFile();//��ȡ��ʱ�����ļ���ָ�����

///----------------------------Ĭ�ϵ�ṹ����ʱ��ṹ-----------------------
PNT_STRU GPnt ={GPnt.isDel = 0, GPnt.color = RGB(0,0,0),GPnt.pattern = 0};

///--------------------------Ĭ���������ṹ����ʱ�������ṹ�������----------------------


LIN_NDX_STRU GLin ={
	GLin.isDel=0,GLin.color = RGB(0,0,0),GLin.pattern = 0,
    GLin.dotNum =0,GLin.datOff =0                
};//Ĭ���߲���

LIN_NDX_STRU GTLin;
POINT GLPnt ={GLPnt.x = -1,GLPnt.y = -1};//��¼�߶ε����
CPoint GMPnt(-1,-1);//��¼�����һ��״̬�ĵ�




///----------------------------��������-----------------------------------------
enum Action{
	Noaction,
	OPERSTATE_INPUT_PNT,
	OPERSTATE_DELETE_PNT,
	OPERSTATE_MOVE_PNT,
	OPERSTATE_INPUT_LIN,
	OPERSTATE_DELETE_LIN,
	OPERSTATE_MOVE_LIN,
	OPERSTATE_INPUT_REG,
	OPERSTATE_DELETE_REG,
	OPERSTATE_MOVE_REG,
	OPERSTATE_ZOOM_IN,
	OPERSTATE_ZOOM_OUT,
	OPERSTATE_WINDOW_MOVE,
	OPERSTATE_LIN_DELETE_PNT,
	OPERSTATE_LIN_ADD_PNT,
	OPERSTATE_LINK_LIN,
	OPERSTATE_MODIFY_POINT_PARAMETER,
	OPERSTATE_MODIFY_REGION_PARAMETER,
	OPERSTATE_UNDELETE_PNT,
	OPERSTATE_UNDELETE_LIN,
	OPERSTATE_UNDELETE_REG


};//ö�ٲ���״̬

VERSION GPntVer={
	GPntVer.flag[0] = 'P',
	GPntVer.flag[1] = 'N',
	GPntVer.flag[2] = 'T',
	GPntVer.version = 10
};

Action GCurOperState;//��������

///----�ļ��汾��Ϣ��ȫ�ֱ����ͳ�ʼֵ-----------------






// CMapEditor3View

IMPLEMENT_DYNCREATE(CMapEditor3View, CView)

BEGIN_MESSAGE_MAP(CMapEditor3View, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_WINDOW_ZOOM_IN, &CMapEditor3View::OnWindowZoomIn)
	ON_COMMAND(ID_FILE_NEW, &CMapEditor3View::OnFileNew)
	ON_BN_CLICKED(IDC_CREATE_FILE_CHANGE_ADDRESS_BTN, &CMapEditor3View::OnBnClickedCreateFileChangeAddressBtn)
	ON_COMMAND(ID_POINT_CREATE, &CMapEditor3View::OnPointCreate)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_POINT_SAVE, &CMapEditor3View::OnPointSave)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_LINE_CREATE, &CMapEditor3View::OnLineCreate)
	ON_COMMAND(ID_POINT_CIRCLE, &CMapEditor3View::OnPointCircle)
END_MESSAGE_MAP()

// CMapEditor3View ����/����

CMapEditor3View::CMapEditor3View()
{
	// TODO: �ڴ˴���ӹ������

}

CMapEditor3View::~CMapEditor3View()
{
}

BOOL CMapEditor3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMapEditor3View ����

void CMapEditor3View::OnDraw(CDC* /*pDC*/)
{
	CMapEditor3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}

void CMapEditor3View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	//ClientToScreen(&point);
	//OnContextMenu(this, point);
	CClientDC dc(this);
	dc.SetROP2(R2_NOTXORPEN);
	if(GLinFCreated)
	{
		switch(GCurOperState)
		{
		   case OPERSTATE_INPUT_LIN:
			   if (GTLin.dotNum>1)
			   {
				   WriteLinNdxToFile(GLinTmpNdxF,GLinNum,GTLin);//��������д����������ʱ�ļ���
				   GLinNum++;
				   GLinLNum++;
				   DrawSeg(&dc,GTLin,GLPnt,point);
				   GLin.datOff+=(GTLin.dotNum*sizeof(D_DOT));
				   memset(&GTLin,0,sizeof(LIN_NDX_STRU));
				   GMPnt.SetPoint(-1,-1);
				   GLPnt.x =-1;
				   GLPnt.y = -1;

			   }
			   else if (GTLin.dotNum ==1)
			   {
				   DrawSeg(&dc,GTLin,GLPnt,point);
				   memset(&GTLin,0,sizeof(LIN_NDX_STRU));
				   GMPnt.SetPoint(-1,-1);
				   GLPnt.x = -1;
				   GLPnt.y = -1;
			   }
			   break;

		}
	}

}

void CMapEditor3View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMapEditor3View ���

#ifdef _DEBUG
void CMapEditor3View::AssertValid() const
{
	CView::AssertValid();
}

void CMapEditor3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMapEditor3Doc* CMapEditor3View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapEditor3Doc)));
	return (CMapEditor3Doc*)m_pDocument;
}
#endif //_DEBUG


// CMapEditor3View ��Ϣ�������


void CMapEditor3View::OnWindowZoomIn()
{
	// TODO: �ڴ���������������
	AfxMessageBox(_T("���ԣ�"),MB_OK,0);
}


void CMapEditor3View::OnFileNew()
{
	// TODO: �ڴ���������������
	//����Ƿ����½���ʱ�ļ���������ʱ�ļ��򷵻�
	if(GPntFCreated&&GLinFCreated&&GRegFCreated)
	{
		MessageBox(L"File have been created.",L"Message",MB_OK);
		return;
	}

	CCreateFileDlg dlg;//�������½���ʱ�ļ����Ի������
	if(dlg.DoModal()!=IDOK)
		return;
	CString str;
	if(!GPntFCreated)
	{
		GPntTmpFName = dlg.m_add+CString("\\")+GPntTmpFName;
		if(GPntTmpF->Open(GPntTmpFName,CFile::modeCreate|CFile::modeReadWrite|CFile::typeBinary))
		{
			GPntFCreated = true;
			str+="tempPntF.dat\n";
		}
		else
		{
			GPntTmpFName = CString("tempPntF.dat");
			TRACE(_T("File could not be opened n"));
		}
	}
	if(!GLinFCreated)
	{
		GLinTmpNdxFName = dlg.m_add + CString("\\")+ GLinTmpNdxFName;
		GLinTmpDatFName = dlg.m_add + CString("\\")+ GLinTmpDatFName;
		if(GLinTmpNdxF->Open(GLinTmpNdxFName,CFile::modeCreate|CFile::modeReadWrite|CFile::typeBinary)&&GLinTmpDatF->Open(GLinTmpDatFName,CFile::modeCreate|CFile::modeReadWrite|CFile::typeBinary))
		{
			GLinFCreated = true;
			str+="tempLinF.dat tempLinF.ndx\n";

		}
		else
		{
			GLinTmpDatFName = CString("tempLinF.dat");
			GLinTmpNdxFName = CString("tempLinF.ndx");
			TRACE(_T("File could not be opened \n"));
		}
	}

	if(!GRegFCreated)
	{
		GRegTmpNdxFName = dlg.m_add + CString("\\")+GRegTmpNdxFName;
		GRegTmpDatFName = dlg.m_add+CString("\\")+GRegTmpDatFName;
		if(GRegTmpNdxF->Open(GRegTmpNdxFName,CFile::modeCreate|CFile::modeReadWrite|CFile::typeBinary)&&GRegTmpDatF->Open(GRegTmpDatFName,CFile::modeCreate|CFile::modeReadWrite|CFile::typeBinary))
		{
			GRegFCreated = true;
			str+="tempRegF.ndx tempRegF.dat\n";

		}
		else
		{
			GRegTmpNdxFName = CString("tempRegF.ndx");
			GRegTmpDatFName = CString("tempRegF.dat");
			TRACE(_T("File could not be opened \n"));
		}
	}

	if(GPntFCreated&&GLinFCreated&&GRegFCreated)
	{
		str+="creat successful!";
		MessageBox(str,L"message",MB_OK);
	}

	

}


void CMapEditor3View::OnBnClickedCreateFileChangeAddressBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	

}


void CMapEditor3View::OnPointCreate()
{
	// TODO: �ڴ���������������
	if (GPntFCreated)
	{
		GCurOperState = OPERSTATE_INPUT_PNT;
	}
	else
	{
		MessageBox(L"File have not been create��",L"Message",MB_OK);

	}
}


void CMapEditor3View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CClientDC dc(this);
	dc.SetROP2(R2_NOTXORPEN);
	if (GPntFCreated)
	{
		switch (GCurOperState)
		{

		case OPERSTATE_INPUT_PNT :
			PNT_STRU pnt;
			memcpy_s(&pnt,sizeof(PNT_STRU),&GPnt,sizeof(PNT_STRU));
			pnt.x = point.x;
			pnt.y = point.y;
			WritePntToFile(GPntTmpF,GPntNum,pnt);
			DrawPnt(&dc,pnt);
			GPntNum++;
			GPntLNum++;
			GPntChanged = true;

			break;
		default:
			break;
		}
	}

	CView::OnLButtonDown(nFlags, point);

}


void CMapEditor3View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CView::OnLButtonUp(nFlags, point);

	if (GLinFCreated)
	{
		D_DOT dot;
		switch(GCurOperState)
		{
		case OPERSTATE_INPUT_LIN:
			if (GTLin.dotNum==0)
			{
				memcpy_s(&GTLin,sizeof(LIN_NDX_STRU),&GLin,sizeof(LIN_NDX_STRU));

			}
			PntToDot(dot,point);
			WriteLinDatToFile(GLinTmpDatF,GLin.datOff,GTLin.dotNum,dot);
			//���ߵĵ�����д����ʱ�ļ���
			GTLin.dotNum++;
			GLPnt.x = (long)dot.x;
			GLPnt.y = (long)dot.y;
			GLinChanged = true;
			break;


		}
	}
}


void CMapEditor3View::OnPointSave()
{
	// TODO: �ڴ���������������

	GCurOperState = Noaction;
	//1.�����û���½���򿪵��ļ�������ʾ�ļ���û�д򿪣�Ȼ�󷵻�
	if (GPntFCreated == false)
	{
		MessageBox(L"File have not been created.",L"Message",MB_OK);
		return;
	}
	CFile* pntF = new CFile();
	//2.������ļ�����Ϊ�գ���ɾ��ԭ�����ļ����������CFileDialog�����û������ļ���
	if (GPntFName.IsEmpty() == false)
	{
		CFile::Remove(GPntFName);
	}
	else
	{
		LPCTSTR lpszFilters;
		lpszFilters = _T("��(*.pnt)|*.pnt||");
		CFileDialog dlg(false,_T("pnt"),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,lpszFilters);
		int nPos = GPntTmpFName.ReverseFind(_T('\\'));
		CString folderAdd = GPntTmpFName.Left(nPos);
		dlg.m_ofn.lpstrInitialDir = folderAdd;
		if (dlg.DoModal() == IDOK)
		{
			GPntFName = dlg.GetPathName();
		}
		else
			return;

	}
	PNT_STRU tempPnt;
	//3.���´����������ļ�����д��汾��Ϣ�������������߼���
	if (pntF->Open(GPntFName,CFile::modeCreate|CFile::modeWrite|CFile::typeBinary))
	{
		pntF->Write(&GPntVer,sizeof(VERSION));
		pntF->Write(&GPntNum,sizeof(int));
		pntF->Write(&GPntLNum,sizeof(int));
	}
	else
	{
		TRACE(_T("File could not be opened\n"));
	}
	//4.������ʱ�ļ��е���Ϣ����д�������ļ���

	for (int i =0;i<GPntNum;i++)
	{
		ReadTempFileToPnt(GPntTmpF,i,tempPnt);
		pntF->Write(&tempPnt,sizeof(PNT_STRU));
	}
	pntF->Close();
	delete pntF;
	//5.�޸����ݱ仯��־���ı������ڱ�������

	GPntChanged = false;
	int nPos = GPntFName.ReverseFind(_T('\\'));
	CString windowText = GPntFName.Right(GPntFName.GetLength()-nPos -1)+"-MapEditor";
	GetParent()->SetWindowTextW(windowText);

}


void CMapEditor3View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CView::OnMouseMove(nFlags, point);

	if (GLinFCreated)
	{
		switch (GCurOperState)
		{
		case OPERSTATE_INPUT_LIN:
		{
			if (GTLin.dotNum > 0)
			{
				CClientDC dc(this);//��ñ����ڻ�ǰ���ͼ
				dc.SetROP2(R2_NOTXORPEN);//�������ģʽ����
				if (GMPnt.x != -1 && GMPnt.y != -1)
				{
					DrawSeg(&dc, GTLin, GLPnt, GMPnt);//Ĭ����ʽ����

				}
				GMPnt.x = point.x;
				GMPnt.y = point.y;//���������һ��״̬��y
				POINT mpoint = { mpoint.x = point.x,mpoint.y = point.y };
				DrawSeg(&dc, GTLin, GLPnt, mpoint);

			}
			break;
		}



		}

	}
}


	void CMapEditor3View::OnLineCreate()
	{
		// TODO: �ڴ���������������

		if (GLinFCreated)
		{
			GCurOperState = OPERSTATE_INPUT_LIN;//��ǰΪ����״̬
		}
		else
		{
			MessageBox(L"tEMPfILE have not been created.",L"Message",MB_OK);
		}
	}


	void CMapEditor3View::OnPointCircle()
	{
		// TODO: �ڴ���������������

		// TODO: �ڴ���������������
		this->pSymbol=new CircleSymbol();
		this->pSymbol->useBrush=false;
		this->pSymbol->Active=true;
	}
