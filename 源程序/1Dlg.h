// 1Dlg.h : header file
//

#if !defined(AFX_1DLG_H__2C5818B7_C497_40CC_BDAD_4CD84C70E9BF__INCLUDED_)
#define AFX_1DLG_H__2C5818B7_C497_40CC_BDAD_4CD84C70E9BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxtempl.h>
#include <mmsystem.h>

//�����õ��ĺ�Ķ���
#define SIZE 50 //λͼ��С
#define GAME_ROW 14 //��Ϸ����
#define GAME_COL 20 //��Ϸ����
#define BOTTON_WIDTH 186//��ť���
#define BOTTON_HEIGHT 78//��ť�߶�
#define CONTROL_WIDTH 176//���������
#define CONTROL_HEIGHT 29//�������߶�
#define EASY 5
#define MEDIUM 10
#define HARD 20
/////////////////////////////////////////////////////////////////////////////
// CMy1Dlg dialog

class CMy1Dlg : public CDialog
{
	int m_import;//�ж��Ƿ���
	int Gate;//�ؿ���
	CString Word;//����
	CArray <CString, CString> KeyWord;//�����洢�û��Ĺؼ���
	CArray <CPoint,CPoint> snake;//��
	int direction;//����
	CArray <CPoint, CPoint> food;//ʳ��
	CPoint NewSnakeHead;//����ͷ��λ��
	CString strFile1;	//�����ļ��ַ���
	CString strFile2;	//�����ļ��ַ���
	CString strFile3;	//�����ļ��ַ���
	HWND m_hWnd;  		//���ھ��
	MCI_OPEN_PARMS mciopenparms;//MCI_OPEN������Ҫ�����ṹ��
	DWORD DeviceId;  	//�豸ID
	//λͼ��1��7�ֱ��ǣ����壬�������ң�ǽ��ʳ���ӭ���棬����
	int m_time;//���ƶ���ʱ��
	int state;//��Ϸ״̬
	int Score;//��Ϸ�ɼ�
	int MaxScore;//��óɼ�
	int level;//��Ϸ�ȼ�
// Construction
public:
	void SaveMaxScore(int flag);
	void ReadMaxScore(int &n);
	void Welcome();
	void Restart();
	int IsGameOver();
	void PlayMusic();
	void LoadData();
	int IsCanFood(int a,int b);
	void GetFood();
	CMy1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMy1Dlg)
	enum { IDD = IDD_MY1_DIALOG };
	CButton	m_help;
	CButton	m_start;
	CButton	m_open;
	CButton	exit;
	CButton	m_pause;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy1Dlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMy1Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void STARTGAME();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void PauseGame();
	afx_msg void CloseMusic();
	afx_msg void OnButton4();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void SnakeMove();
	void LoadKeyWord();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_1DLG_H__2C5818B7_C497_40CC_BDAD_4CD84C70E9BF__INCLUDED_)
