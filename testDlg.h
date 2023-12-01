
// GATS7310Dlg.h: 헤더 파일
//

#pragma once
#include "CGridPoint.h"
#include "CDlgError.h"

// CGATS7310Dlg 대화 상자
class CGATS7310Dlg : public CDialogEx
{
// 생성입니다.
public:
	CGATS7310Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GATS7310_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CGridPoint m_GP[33][53];
	afx_msg void OnBnClickedButtonLoadFile();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CMFCButton m_Button_Cancel;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	int m_nMode = 0;
	afx_msg void OnBnClickedRadioAll();
	afx_msg void OnBnClickedRadioAlign();
	afx_msg void OnBnClickedRadioInsp();
	afx_msg void OnBnClickedButtonSave();

	double m_dSlopeXA[33];
	double m_dSlopeXI[33];
	double m_dSlopeYA[53];
	double m_dSlopeYI[53];

	double m_dThetaXA[33];
	double m_dThetaXI[33];
	double m_dThetaYA[53];
	double m_dThetaYI[53];

	void CalSlopeTheta();
	int m_nInputData = 1;
	CDlgError DlgErr;
	afx_msg void OnBnClickedButtonYaw();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
