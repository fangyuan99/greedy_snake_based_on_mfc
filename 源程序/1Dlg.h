// 1Dlg.h : header file
//

#if !defined(AFX_1DLG_H__2C5818B7_C497_40CC_BDAD_4CD84C70E9BF__INCLUDED_)
#define AFX_1DLG_H__2C5818B7_C497_40CC_BDAD_4CD84C70E9BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxtempl.h>
#include <mmsystem.h>

//程序用到的宏的定义
#define SIZE 50 //位图大小
#define GAME_ROW 14 //游戏行数
#define GAME_COL 20 //游戏列数
#define BOTTON_WIDTH 186//按钮宽度
#define BOTTON_HEIGHT 78//按钮高度
#define CONTROL_WIDTH 176//控制区宽度
#define CONTROL_HEIGHT 29//控制区高度
#define EASY 5
#define MEDIUM 10
#define HARD 20
/////////////////////////////////////////////////////////////////////////////
// CMy1Dlg dialog

class CMy1Dlg : public CDialog
{
	int m_import;//判断是否导入
	int Gate;//关卡数
	CString Word;//单词
	CArray <CString, CString> KeyWord;//用来存储用户的关键词
	CArray <CPoint,CPoint> snake;//蛇
	int direction;//方向
	CArray <CPoint, CPoint> food;//食物
	CPoint NewSnakeHead;//新蛇头的位置
	CString strFile1;	//声音文件字符串
	CString strFile2;	//声音文件字符串
	CString strFile3;	//声音文件字符串
	HWND m_hWnd;  		//窗口句柄
	MCI_OPEN_PARMS mciopenparms;//MCI_OPEN命令需要参数结构体
	DWORD DeviceId;  	//设备ID
	//位图从1到7分别是：身体，上下左右，墙，食物，欢迎界面，背景
	int m_time;//蛇移动的时间
	int state;//游戏状态
	int Score;//游戏成绩
	int MaxScore;//最好成绩
	int level;//游戏等级
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
