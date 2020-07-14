#if !defined(AFX_SELECTLEVEL_H__BC3AF866_75A7_496A_A09F_E373CC1E62FB__INCLUDED_)
#define AFX_SELECTLEVEL_H__BC3AF866_75A7_496A_A09F_E373CC1E62FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectLevel.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SelectLevel dialog

class SelectLevel : public CDialog
{
// Construction
public:
	int m_level;
public:
	SelectLevel(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SelectLevel)
	enum { IDD = IDD_DIALOG1 };
	CButton	m_Level1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SelectLevel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SelectLevel)
	afx_msg void OnLevel1();
	afx_msg void OnLevel2();
	afx_msg void OnLevel3();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTLEVEL_H__BC3AF866_75A7_496A_A09F_E373CC1E62FB__INCLUDED_)
