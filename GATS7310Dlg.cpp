
// GATS7310Dlg.cpp: 구현 파일
//
//#pragma comment(lib, "UxTheme.lib")

#include "pch.h"
#include "framework.h"
#include "GATS7310.h"
#include "GATS7310Dlg.h"
#include "afxdialogex.h"
#include <math.h>
#include "XLAutomation.h"
#include "XLEzAutomation.h"
#include "CDlgError.h"
#include "CBufferDC.h"

#define PI 3.14159265358979323846

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGATS7310Dlg 대화 상자



CGATS7310Dlg::CGATS7310Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GATS7310_DIALOG, pParent)
	, m_nMode(0)
	, m_nInputData(1)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGATS7310Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDCANCEL, m_Button_Cancel);
	DDX_Radio(pDX, IDC_RADIO_ALL, m_nMode);
	DDX_Radio(pDX, IDC_RADIO_POS, m_nInputData);
}

BEGIN_MESSAGE_MAP(CGATS7310Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOAD_FILE, &CGATS7310Dlg::OnBnClickedButtonLoadFile)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_RADIO_ALL, &CGATS7310Dlg::OnBnClickedRadioAll)
	ON_BN_CLICKED(IDC_RADIO_ALIGN, &CGATS7310Dlg::OnBnClickedRadioAlign)
	ON_BN_CLICKED(IDC_RADIO_INSP, &CGATS7310Dlg::OnBnClickedRadioInsp)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CGATS7310Dlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_YAW, &CGATS7310Dlg::OnBnClickedButtonYaw)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CGATS7310Dlg 메시지 처리기

BOOL CGATS7310Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_Button_Cancel.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;//required for flatering and use bg color
	m_Button_Cancel.m_bTransparent = false;//reg for use bg color
	m_Button_Cancel.SetFaceColor(RGB(255, 0, 0), true);
	m_Button_Cancel.SetTextColor(RGB(255, 255, 255));



	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CGATS7310Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CGATS7310Dlg::OnPaint()
{
	//CPaintDC dc(this);
	CBufferDC dc(this);
	Graphics graphics(dc);
	graphics.SetSmoothingMode(SmoothingModeHighQuality);

	CBrush WhiteBrush(RGB(255, 255, 255));
	CRect rect(10, 0, 670, 1060);

	Pen BlackPen(Color(255, 0, 0, 0), 1.0f);
	BlackPen.SetEndCap(LineCapArrowAnchor);

	Pen GreenPen(Color(255, 0, 128, 0), 1.0f);
	GreenPen.SetStartCap(LineCapRoundAnchor);
	GreenPen.SetEndCap(LineCapArrowAnchor);

	Pen RedPen(Color(255, 255, 0, 0), 1.0f);
	RedPen.SetStartCap(LineCapRoundAnchor);
	RedPen.SetEndCap(LineCapArrowAnchor);

	UpdateData();
	switch (m_nMode)
	{
	case 0: //show all
		dc.FillRect(&rect, &WhiteBrush);
		graphics.DrawLine(&BlackPen, Point(10, 530), Point(670, 530));
		graphics.DrawLine(&BlackPen, Point(340, 1060), Point(340, 5));
		for (int i = 0; i < 33; i++)
		{
			for (int j = 0; j < 53; j++)
			{
				graphics.DrawLine(&GreenPen, PointF(20 + 20 * i, 1050 - 20 * j),
					PointF(20 + 20 * i + m_GP[i][j].m_evAlignPos.X, 1050 - 20 * j - m_GP[i][j].m_evAlignPos.Y));
				graphics.DrawLine(&RedPen, PointF(20 + 20 * i, 1050 - 20 * j),
					PointF(20 + 20 * i + m_GP[i][j].m_evInsPos.X, 1050 - 20 * j - m_GP[i][j].m_evInsPos.Y));
			}
		}
		break;
	case 1: //align pos
		dc.FillRect(&rect, &WhiteBrush);
		graphics.DrawLine(&BlackPen, Point(10, 530), Point(670, 530));
		graphics.DrawLine(&BlackPen, Point(340, 1060), Point(340, 5));
		for (int i = 0; i < 33; i++)
		{
			for (int j = 0; j < 53; j++)
			{
				graphics.DrawLine(&GreenPen, PointF(20 + 20 * i, 1050 - 20 * j),
					PointF(20 + 20 * i + m_GP[i][j].m_evAlignPos.X, 1050 - 20 * j - m_GP[i][j].m_evAlignPos.Y));
			}
		}
		break;
	case 2: //insp pos
		dc.FillRect(&rect, &WhiteBrush);
		graphics.DrawLine(&BlackPen, Point(10, 530), Point(670, 530));
		graphics.DrawLine(&BlackPen, Point(340, 1060), Point(340, 5));
		for (int i = 0; i < 33; i++)
		{
			for (int j = 0; j < 53; j++)
			{
				graphics.DrawLine(&RedPen, PointF(20 + 20 * i, 1050 - 20 * j),
					PointF(20 + 20 * i + m_GP[i][j].m_evInsPos.X, 1050 - 20 * j - m_GP[i][j].m_evInsPos.Y));
			}
		}
		break;
	}
	
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

	

}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CGATS7310Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGATS7310Dlg::OnBnClickedButtonLoadFile()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR szFile[] = _T("텍스트파일(*.txt)|*.txt||");

	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFile);
	CString strPathName = _T("");

	if (IDOK == dlg.DoModal())
	{
		strPathName = dlg.GetPathName();
	}

	FILE* fp=NULL;
	errno_t e=_wfopen_s(&fp, strPathName, L"rt");
	if (e != 0)
	{
		AfxMessageBox(_T("Failed to open file"));
		return;
	}

	UpdateData();

	if (m_nInputData == 1) // input data : error
	{
		for (int i = 0; i < 33; i++)
		{
			for (int j = 0; j < 53; j++)
			{
				fscanf_s(fp, "%lf\t%lf\t%lf\t%lf\n", &m_GP[i][j].m_evAlignPos.X, &m_GP[i][j].m_evInsPos.X, &m_GP[i][j].m_evAlignPos.Y, &m_GP[i][j].m_evInsPos.Y);
			}
		}

		for (int i = 0; i < 33; i++)
		{
			for (int j = 0; j < 53; j++)
			{
				m_GP[i][j].m_AlignPosX = (double)(-80 + 5 * i) + m_GP[i][j].m_evAlignPos.X / (double)1000;
				m_GP[i][j].m_AlignPosY = (double)(-130 + 5 * j) + m_GP[i][j].m_evAlignPos.Y / (double)1000;
				m_GP[i][j].m_InsPosX = (double)(-80 + 5 * i) + m_GP[i][j].m_evInsPos.X / (double)1000;
				m_GP[i][j].m_InsPosY = (double)(-130 + 5 * j) + m_GP[i][j].m_evInsPos.Y / (double)1000;
			}
		}
	}
	else // input data : position
	{
		for (int i = 0; i < 33; i++)
		{
			for (int j = 0; j < 53; j++)
			{
				fscanf_s(fp, "%lf\t%lf\t%lf\t%lf\n", &m_GP[i][j].m_AlignPosX, &m_GP[i][j].m_InsPosX, &m_GP[i][j].m_AlignPosY, &m_GP[i][j].m_InsPosY);
			}
		}

		for (int i = 0; i < 33; i++)
		{
			for (int j = 0; j < 53; j++)
			{
				m_GP[i][j].m_evAlignPos.X = (m_GP[i][j].m_AlignPosX - (double)(-80 + 5 * i)) * (double)1000;
				m_GP[i][j].m_evAlignPos.Y = (m_GP[i][j].m_AlignPosY - (double)(-130 + 5 * j)) * (double)1000;
				m_GP[i][j].m_evInsPos.X = (m_GP[i][j].m_InsPosX - (double)(-80 + 5 * i)) * (double)1000;
				m_GP[i][j].m_evInsPos.Y = (m_GP[i][j].m_InsPosY - (double)(-130 + 5 * j)) * (double)1000;
			}
		}
	}

	CalSlopeTheta();

	Invalidate();
}



BOOL CGATS7310Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		
		if (pMsg->wParam == VK_RETURN)
		{
			return TRUE;
		}
		
		else if (pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;
		}
	}


	return CDialogEx::PreTranslateMessage(pMsg);
}


HBRUSH CGATS7310Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	UINT nID = pWnd->GetDlgCtrlID();

	if (nID == IDC_STATIC_ALIGN)
	{
		pDC->SetTextColor(RGB(0, 128, 0));
	}

	if (nID == IDC_STATIC_INSP)
	{
		pDC->SetTextColor(RGB(255, 0, 0));
	}
	
	return hbr;
}


void CGATS7310Dlg::OnBnClickedRadioAll()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	Invalidate();
}


void CGATS7310Dlg::OnBnClickedRadioAlign()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	Invalidate();
}


void CGATS7310Dlg::OnBnClickedRadioInsp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	Invalidate();
}


void CGATS7310Dlg::OnBnClickedButtonSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int i, j;
	FILE* fp = NULL;
	errno_t e = fopen_s(&fp, "yaw.txt", "wt");
	if (e != 0)
	{
		AfxMessageBox(_T("Failed to open output file"));
		return;
	}

	for (i = 0; i < 33; i++)
	{
		fprintf(fp, "\tx=%d\t",-80+5*i);
	}
	fprintf(fp, "\nAlign");
	
	for (i = 0; i < 33; i++)
	{
		fprintf(fp, "\t%lf ", m_dThetaXA[i]);
	}
	fprintf(fp, "\nInsp");

	for (i = 0; i < 33; i++)
	{
		fprintf(fp, "\t%lf ", m_dThetaXI[i]);
	}

	fprintf(fp, "\n\n\n\tAlign\t\tInsp");

	for (j = 52; j >=0; j--)
	{
		fprintf(fp, "\ny=%d\t%lf \t%lf", -130 + 5 * j, m_dThetaYA[j], m_dThetaYI[j]);
	}
	
	fclose(fp);

}


void CGATS7310Dlg::CalSlopeTheta()
{
	// TODO: 여기에 구현 코드 추가.
	double dSumX = 0;
	double dSumY = 0;
	double dSumX2 = 0;
	double dSumXY = 0;
	int i, j;

	for (i = 0; i < 33; i++)
	{
		dSumX = 0, dSumY = 0, dSumX2 = 0, dSumXY = 0;
		for (j = 0; j < 53; j++)
		{
			dSumX = dSumX + m_GP[i][j].m_AlignPosX;
			dSumY = dSumY + m_GP[i][j].m_AlignPosY;
			dSumX2 = dSumX2 + m_GP[i][j].m_AlignPosX * m_GP[i][j].m_AlignPosX;
			dSumXY = dSumXY + m_GP[i][j].m_AlignPosX * m_GP[i][j].m_AlignPosY;
		}
		m_dSlopeXA[i] = (53 * dSumXY - dSumX * dSumY) / (53 * dSumX2 - dSumX * dSumX);
		if (m_dSlopeXA[i] < 0)
		{
			m_dThetaXA[i] = (double)(90) + (atan(m_dSlopeXA[i]) * 180 / PI);
		}
		else
		{
			m_dThetaXA[i] = (double)(-90) + atan(m_dSlopeXA[i]) * 180 / PI;
		}

		dSumX = 0, dSumY = 0, dSumX2 = 0, dSumXY = 0;
		for (j = 0; j < 53; j++)
		{
			dSumX = dSumX + m_GP[i][j].m_InsPosX;
			dSumY = dSumY + m_GP[i][j].m_InsPosY;
			dSumX2 = dSumX2 + m_GP[i][j].m_InsPosX * m_GP[i][j].m_InsPosX;
			dSumXY = dSumXY + m_GP[i][j].m_InsPosX * m_GP[i][j].m_InsPosY;
		}
		m_dSlopeXI[i] = (53 * dSumXY - dSumX * dSumY) / (53 * dSumX2 - dSumX * dSumX);
		if (m_dSlopeXI[i] < 0)
		{
			m_dThetaXI[i] = (double)(90) + (atan(m_dSlopeXI[i]) * 180 / PI);
		}
		else
		{
			m_dThetaXI[i] = (double)(-90) + atan(m_dSlopeXI[i]) * 180 / PI;
		}
	}

	for (j = 0; j < 53; j++)
	{
		dSumX = 0, dSumY = 0, dSumX2 = 0, dSumXY = 0;
		for (i = 0; i < 33; i++)
		{
			dSumX = dSumX + m_GP[i][j].m_AlignPosX;
			dSumY = dSumY + m_GP[i][j].m_AlignPosY;
			dSumX2 = dSumX2 + m_GP[i][j].m_AlignPosX * m_GP[i][j].m_AlignPosX;
			dSumXY = dSumXY + m_GP[i][j].m_AlignPosX * m_GP[i][j].m_AlignPosY;
		}
		m_dSlopeYA[j] = (33 * dSumXY - dSumX * dSumY) / (33 * dSumX2 - dSumX * dSumX);
		m_dThetaYA[j] =  atan(m_dSlopeYA[j]) * 180 / PI;
		
		dSumX = 0, dSumY = 0, dSumX2 = 0, dSumXY = 0;
		for (i = 0; i < 33; i++)
		{
			dSumX = dSumX + m_GP[i][j].m_InsPosX;
			dSumY = dSumY + m_GP[i][j].m_InsPosY;
			dSumX2 = dSumX2 + m_GP[i][j].m_InsPosX * m_GP[i][j].m_InsPosX;
			dSumXY = dSumXY + m_GP[i][j].m_InsPosX * m_GP[i][j].m_InsPosY;
		}
		m_dSlopeYI[j] = (33 * dSumXY - dSumX * dSumY) / (33 * dSumX2 - dSumX * dSumX);
		m_dThetaYI[j] = atan(m_dSlopeYI[j]) * 180 / PI;
	}

}


void CGATS7310Dlg::OnBnClickedButtonYaw()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int i = 0;
	for (i = 0; i < 33; i++)
	{
		DlgErr.m_dDegXA[i] = m_dThetaXA[i] * 1000;
		DlgErr.m_dDegXI[i] = m_dThetaXI[i] * 1000;
	}
	for (i = 0; i < 53; i++)
	{
		DlgErr.m_dDegYA[i] = m_dThetaYA[i] * 1000;
		DlgErr.m_dDegYI[i] = m_dThetaYI[i] * 1000;
	}
	DlgErr.DoModal();
}


BOOL CGATS7310Dlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return FALSE;
	//return CDialogEx::OnEraseBkgnd(pDC);
}
