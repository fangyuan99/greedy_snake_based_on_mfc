// SelectLevel.cpp : implementation file
//

#include "stdafx.h"
#include "1.h"
#include "SelectLevel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SelectLevel dialog


SelectLevel::SelectLevel(CWnd* pParent /*=NULL*/)
	: CDialog(SelectLevel::IDD, pParent)
{
	//{{AFX_DATA_INIT(SelectLevel)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void SelectLevel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SelectLevel)
	DDX_Control(pDX, IDC_BUTTON1, m_Level1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SelectLevel, CDialog)
	//{{AFX_MSG_MAP(SelectLevel)
	ON_BN_CLICKED(IDC_BUTTON1, OnLevel1)
	ON_BN_CLICKED(IDC_BUTTON2, OnLevel2)
	ON_BN_CLICKED(IDC_BUTTON3, OnLevel3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SelectLevel message handlers

void SelectLevel::OnLevel1() 
{
	// TODO: Add your control notification handler code here
	m_level=1;
	OnOK();
}

void SelectLevel::OnLevel2() 
{
	// TODO: Add your control notification handler code here
	m_level=2;
	OnOK();
}

void SelectLevel::OnLevel3() 
{
	// TODO: Add your control notification handler code here
	m_level=3;
	OnOK();
}

BOOL SelectLevel::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetWindowText("ÄÑ¶ÈÑ¡Ôñ");
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
