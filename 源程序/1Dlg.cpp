// 1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "1.h"
#include "1Dlg.h"
#include "SelectLevel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy1Dlg dialog

CMy1Dlg::CMy1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy1Dlg::IDD, pParent)
{
	
	//��ʼ����
	snake.Add(CPoint(3*SIZE, SIZE));
	snake.Add(CPoint(2*SIZE, SIZE));
	snake.Add(CPoint(SIZE, SIZE));
	//��ʼ������
	direction = VK_RIGHT;
	//��ʼ��ʳ��
	if (MessageBox("�Ƿ��ȡ�Զ��嵥��", NULL, MB_YESNO) == IDYES)
		LoadKeyWord();
	else
		//��ʼ���������
		m_import=0;
	GetFood();
	//��ʼ���ؿ���
	Gate = 1;
	//��ʼ���ƶ�ʱ��
	m_time=300;
	//�ɼ�
	Score=0;
	MaxScore=0;
//����
	LoadData();
	PlayMusic();
//��ʼ���ȼ�
	level = 1;
//��ȡ��óɼ�
	ReadMaxScore(MaxScore);
	//{{AFX_DATA_INIT(CMy1Dlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMy1Dlg)
	DDX_Control(pDX, IDC_BUTTON4, m_help);
	DDX_Control(pDX, IDC_BUTTON1, m_start);
	DDX_Control(pDX, IDC_BUTTON3, m_open);
	DDX_Control(pDX, IDC_BUTTON2, m_pause);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMy1Dlg, CDialog)
	//{{AFX_MSG_MAP(CMy1Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON1, STARTGAME)
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_BUTTON2, PauseGame)
	ON_BN_CLICKED(IDC_BUTTON3, CloseMusic)
	ON_BN_CLICKED(IDC_BUTTON4, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy1Dlg message handlers

BOOL CMy1Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//��ʼ�����
	SetWindowText("����̰����2.5");
	CRect temprect(0,0,(GAME_COL+1)*SIZE+CONTROL_WIDTH,GAME_ROW*SIZE+CONTROL_HEIGHT);
	SetWindowPos(NULL,0,0,temprect.Width(),temprect.Height(),SWP_NOZORDER);
	CenterWindow();//������ʾ
	HBITMAP hBitmap = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_BITMAP11));//���ð�ť��λͼ
	m_start.SetBitmap(hBitmap);
	hBitmap = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_BITMAP12));
	m_pause.SetBitmap(hBitmap);
	hBitmap = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_BITMAP13));
	m_open.SetBitmap(hBitmap);
	hBitmap = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_BITMAP14));
	m_help.SetBitmap(hBitmap);
    GetClientRect(&temprect);    //��ȡ�ͻ�����С
	//���ð�ťλ��
	CWnd *pWnd;  
	pWnd = GetDlgItem( IDC_BUTTON1 );    //��ȡ�ؼ�ָ�룬IDC_BUTTON1Ϊ�ؼ�ID��  
	pWnd->SetWindowPos( NULL,GAME_COL*SIZE+(temprect.Width()-GAME_COL*SIZE-BOTTON_WIDTH)/2,temprect.Height()/2,BOTTON_WIDTH,BOTTON_HEIGHT,SWP_NOZORDER);    //�Ѱ�ť1�Ƶ�����λ��
	pWnd = GetDlgItem( IDC_BUTTON2 );    
	pWnd->SetWindowPos( NULL,GAME_COL*SIZE+(temprect.Width()-GAME_COL*SIZE-BOTTON_WIDTH)/2,temprect.Height()/2+SIZE/5+BOTTON_HEIGHT,BOTTON_WIDTH,BOTTON_HEIGHT,SWP_NOZORDER);    //�Ѱ�ť1�Ƶ�����λ��
	pWnd = GetDlgItem( IDC_BUTTON3 );     
	pWnd->SetWindowPos( NULL,GAME_COL*SIZE+(temprect.Width()-GAME_COL*SIZE-BOTTON_WIDTH)/2,temprect.Height()/2+2*SIZE/5+2*BOTTON_HEIGHT,BOTTON_WIDTH,BOTTON_HEIGHT,SWP_NOZORDER);    //�Ѱ�ť1�Ƶ�����λ��
	pWnd = GetDlgItem( IDC_BUTTON4 );     
	pWnd->SetWindowPos( NULL,GAME_COL*SIZE+(temprect.Width()-GAME_COL*SIZE-BOTTON_WIDTH)/2,temprect.Height()/2+3*SIZE/5+3*BOTTON_HEIGHT,BOTTON_WIDTH,BOTTON_HEIGHT,SWP_NOZORDER);    //�Ѱ�ť1�Ƶ�����λ��
	return TRUE;  
	
	
	
	// return TRUE  unless you set the focus to a control
}

void CMy1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMy1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM)dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		if (state!=1)
			//��Ϸ��ʼ����
		{
			Welcome();
		}
		else
		{
			int i;
			CPaintDC dc(this); // device context for painting
			CBitmap Bitmap;
			Bitmap.LoadBitmap(IDB_BITMAP9);
			CDC MemDC;
			MemDC.CreateCompatibleDC(&dc);
			MemDC.SelectObject(&Bitmap);
			Bitmap.Detach();             //���룬�����´�ʹ��
			//����

			//dc.StretchBlt(0,0,GAME_COL*SIZE,GAME_ROW*SIZE, &MemDC, 0, 0, 800,600, SRCCOPY);
			//��ǽ
			Bitmap.LoadBitmap(IDB_BITMAP6);
			MemDC.SelectObject(&Bitmap);
			Bitmap.Detach();
			for (i = 0; i < GAME_ROW; i++)
			{
				dc.StretchBlt(0, i*SIZE, SIZE, SIZE, &MemDC, 0, 0, SIZE, SIZE, SRCCOPY);
				dc.StretchBlt((GAME_COL - 1)*SIZE, i*SIZE, SIZE, SIZE, &MemDC, 0, 0, SIZE, SIZE, SRCCOPY);
			}
			for (i = 1; i < (GAME_COL - 1); i++)
			{
				dc.StretchBlt(i*SIZE, 0, SIZE, SIZE, &MemDC, 0, 0, SIZE, SIZE, SRCCOPY);
				dc.StretchBlt(i*SIZE, (GAME_ROW - 1)*SIZE, SIZE, SIZE, &MemDC, 0, 0, SIZE, SIZE, SRCCOPY);
			}
			//����
			for (i = 0; i <= snake.GetUpperBound(); i++)
			{
				if (i == 0)
				{
					switch (direction)
					{
					case VK_LEFT:
						Bitmap.LoadBitmap(IDB_BITMAP4);
						MemDC.SelectObject(&Bitmap);
						Bitmap.Detach();
						break;
					case VK_RIGHT:
						Bitmap.LoadBitmap(IDB_BITMAP5);
						MemDC.SelectObject(&Bitmap);
						Bitmap.Detach();
						break;
					case VK_UP:
						Bitmap.LoadBitmap(IDB_BITMAP2);
						MemDC.SelectObject(&Bitmap);
						Bitmap.Detach();
						break;
					case VK_DOWN:
						Bitmap.LoadBitmap(IDB_BITMAP3);
						MemDC.SelectObject(&Bitmap);
						Bitmap.Detach();
						break;
					default:
						break;
					}

				}
				else
				{
					Bitmap.LoadBitmap(IDB_BITMAP1);
					MemDC.SelectObject(&Bitmap);
					Bitmap.Detach();
				}
				dc.StretchBlt(snake[i].x, snake[i].y, SIZE, SIZE, &MemDC, 0, 0, SIZE, SIZE, SRCCOPY);
			}
			//��ʳ��
			/*Bitmap.LoadBitmap(IDB_BITMAP7);
			MemDC.SelectObject(&Bitmap);
			Bitmap.Detach();*/
			//���ɼ���ģʽ
			dc.SetBkColor(RGB(240, 240, 240));
			for (i = 0; i < strlen(Word); i++)
			{
				CFont m_Font;
				m_Font.CreatePointFont(SIZE*5.5, "��������_CNKI", NULL);
				dc.SelectObject(&m_Font);//��������
				m_Font.DeleteObject();//ɾ���������´�ʹ��
				if (i == Score / 100)
					dc.SetBkColor(RGB(255,0,0));
				dc.TextOut(food[i].x, food[i].y,Word.Mid(i,1));
				dc.SetBkColor(RGB(240,240,240));
			}
			CString s;
			CFont m_Font;
			m_Font.CreatePointFont(SIZE*2.5, "��������_CNKI", NULL);
			dc.SelectObject(&m_Font);//��������
			m_Font.DeleteObject();//ɾ���������´�ʹ��
			switch(level)
			{
			case 1:s.Format("�Ѷ�:��");
				break;
			case 2:s.Format("�Ѷ�:�е�");
				break;
			case 3:s.Format("�Ѷ�:����");
				break;
			}
			dc.TextOut(GAME_COL*SIZE+SIZE/2,SIZE/10, s);
			s.Format("�������:��%d��", MaxScore);
			dc.TextOut(GAME_COL*SIZE+SIZE/2,SIZE, s);
			s.Format("�÷�:%d",Score);
			dc.TextOut(GAME_COL*SIZE+SIZE/2,2*SIZE, s);
			s.Format("�ؼ���:%s", Word);
			dc.TextOut(GAME_COL*SIZE + SIZE/2, 3 * SIZE, s);
			s.Format("��%d��", Gate);
			dc.TextOut(GAME_COL*SIZE + SIZE/2, 4 * SIZE, s);

		}
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMy1Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMy1Dlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//Invalidate();
	CDialog::OnMouseMove(nFlags, point);
}

void CMy1Dlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	if (m_time >= 50)
	{
		if(level==1)
		SetTimer(1, (m_time - (snake.GetUpperBound() - 2)*EASY), NULL);
		else if(level==2)
			SetTimer(1, (m_time - (snake.GetUpperBound() - 2)*MEDIUM), NULL);
		else if(level==3)
			SetTimer(1, (m_time - (snake.GetUpperBound() - 2)*HARD), NULL);

	}
	//ǰ�����Ƿ��ʳ��
	Score = (snake.GetUpperBound() - 2) * 100;
	if(IsGameOver()==1)
	{
		KillTimer(1);
		Invalidate();
		SaveMaxScore(1);//������óɼ�
		mciSendString(_T("pause BGM"), 0, 0, 0);
		mciSendString(_T("seek GAMEOVER to start"), 0, 0, 0);
		mciSendString(_T("play GAMEOVER"), 0, 0, 0);
		if (MessageBox("��Ϸ�������Ƿ����¿�ʼ��", NULL, MB_YESNO) == IDYES)
		{
			CloseMusic();
			CloseMusic();//�����¿������ְ�ť��֤���¿�ʼ��ʱ������״̬����
			Gate=1;
			Restart();
		}
		else
			OnOK();
	}
	else
	{
		if (IsGameOver() == 2)//���ȫ����ȷ�Ե���ĸ����Ϸʤ��
		{
			KillTimer(1);
			Invalidate();
			mciSendString(_T("seek Upgate to start"), 0, 0, 0);
			mciSendString(_T("play Upgate"), 0, 0, 0);
			if (MessageBox("��Ϸʤ�����Ƿ������һ�أ�", NULL, MB_YESNO) == IDYES)
			{
				Gate++;
				Restart();
			}
			else
			{
				SaveMaxScore(1);//������óɼ�
				OnOK();
			}
		}
		SnakeMove();


	}
	CDialog::OnTimer(nIDEvent);
}

void CMy1Dlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnLButtonDown(nFlags, point);
}

void CMy1Dlg::STARTGAME() 
{
	// TODO: Add your control notification handler code here
	
	//ѡ����Ϸ�Ѷ�
	SelectLevel l;
	l.DoModal();
	level=l.m_level;
	state=1;
	SetTimer(1,m_time,NULL);
	Invalidate();
}

void CMy1Dlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	direction=nChar;
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CMy1Dlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class

	if( pMsg->message == WM_KEYDOWN )
{
switch( pMsg->wParam)
{
	//int x=0;
 case VK_LEFT:
	 if(direction==VK_RIGHT)
		 break;
	 direction=VK_LEFT;
	 if(!IsGameOver())
	 	 {
		KillTimer(1);
		OnTimer(1);
	 }
	 return true;
	 break;
 case VK_RIGHT:
	 if(direction==VK_LEFT)
		 break;
	 direction=VK_RIGHT;
	if(!IsGameOver())
	 {
		KillTimer(1);
		OnTimer(1);
	 }
	 return true;
	 break;
 case VK_UP:
	 if(direction==VK_DOWN)
		 break;
	 direction=VK_UP;
	 if(!IsGameOver())
	{
		KillTimer(1);
		OnTimer(1);
	}
	 return true;
	 break;
 case VK_DOWN:
	 if(direction==VK_UP)
		 break;
	 direction=VK_DOWN;
	 if(!IsGameOver())
	 {
		KillTimer(1);
		OnTimer(1);
	 }

	 return true;
	 break;
}
}

return CDialog::PreTranslateMessage(pMsg);
}


void CMy1Dlg::PauseGame() 
{
	// TODO: Add your control notification handler code here
	//OnOK();
	KillTimer(1);
}

void CMy1Dlg::GetFood()
{
	int x;
	srand((unsigned)time(NULL));
	
	if (!m_import)//��û�ж�ȡ�û��Զ���ؼ��ʣ���Ĭ�Ϲؼ���
	{
	KeyWord.Add("int");
	KeyWord.Add("double");
	KeyWord.Add("break");
	KeyWord.Add("main");
	}
	x = rand() % (KeyWord.GetUpperBound()+1);
	Word = KeyWord[x];
	for (int i = 0; i <strlen(Word); i++)//����ÿ����ĸ������
	{
		int a, b;
		a = 1 + rand() % GAME_COL - 1;
		b = 1 + rand() % GAME_ROW - 1;
		while (!IsCanFood(a, b))
		{
			a = 1 + rand() % GAME_COL - 1;
			b = 1 + rand() % GAME_ROW - 1;
		}
		food.Add(CPoint(a*SIZE, b*SIZE));
	}
}

int CMy1Dlg::IsCanFood(int a, int b)
{
	int x=1;
	for(int i=0;i<=snake.GetUpperBound();i++)
	{
		if(a*SIZE==snake[i].x&&b*SIZE==snake[i].y)
			x=0;
		if(a==0||b==0||a==(GAME_COL-1)||b==(GAME_ROW-1))
			x=0;
		if(a<=5&&b==1&&food.GetUpperBound()+1!=strlen(Word))//��ֹ��ĸ�����ʼ��ͷ̫��
			x=0;
		for(int j=0;j<=food.GetUpperBound();j++)//��������ĸ�׶η�ֹ��ĸ����
			if(a*SIZE==food[j].x&&b*SIZE==food[j].y&&food.GetUpperBound()+1!=strlen(Word))
				x=0;
	}
	return x;
}

void CMy1Dlg::CloseMusic() 
{
	// TODO: Add your control notification handler code here
	static int x=0;
	if((x++)%2==0)
	{
		mciSendString(_T("pause BGM"), 0, 0, 0);
	}
	else 
	{
		//LoadData();
		PlayMusic();
	}
    //�����ֹͣ��ťʱ,�����е���Ϣ�������  

}

void CMy1Dlg::LoadData()
{
	
	mciSendString(_T("open .\\res\\bgm.mp3 alias BGM"), 0, 0, 0);
	mciSendString(_T("open .\\res\\Score.mp3 alias GOAL"), 0, 0, 0);
	mciSendString(_T("open .\\res\\GAMEOVER.wav alias GAMEOVER"), 0, 0, 0);
	mciSendString(_T("open .\\res\\Upgate.mp3 alias Upgate"), 0, 0, 0);
	mciSendString(_T("play BGM repeat"), 0, 0, 0);
	
	

}

void CMy1Dlg::PlayMusic()
{
	mciSendString(_T("resume BGM"), 0, 0, 0);

}

int CMy1Dlg::IsGameOver()
{		

	switch (direction)
	{
	case VK_LEFT:
		NewSnakeHead = snake.GetAt(0) + CPoint(-SIZE, 0);
		break;
	case VK_RIGHT:
		NewSnakeHead = snake.GetAt(0) + CPoint(SIZE, 0);
		break;
	case VK_UP:
		NewSnakeHead = snake.GetAt(0) + CPoint(0, -SIZE);
		break;
	case VK_DOWN:
		NewSnakeHead = snake.GetAt(0) + CPoint(0, SIZE);
		break;
	default:
		break;
	}
	if (1 + Score / 100 > strlen(Word))
	{
		return 2;
	}
	else for (size_t i = 1+Score/100; i < strlen(Word); i++)
	{
		if (NewSnakeHead.x == food[i].x&&NewSnakeHead.y == food[i].y)
			return 1;
	}
	if(!IsCanFood(NewSnakeHead.x/SIZE,NewSnakeHead.y/SIZE))
	    return 1;
	else	
		return 0;
}

void CMy1Dlg::Restart()
{
	snake.RemoveAll();//�����һ�ֵ�����
	food.RemoveAll();
	snake.Add(CPoint(3 * SIZE, SIZE));
	snake.Add(CPoint(2 * SIZE, SIZE));
	snake.Add(CPoint(SIZE, SIZE));
	NewSnakeHead = CPoint(4 * SIZE, SIZE);
	//��ʼ������
	direction = VK_RIGHT;
	//��ʼ��ʳ��
	GetFood();
	//��ʼ��ʱ��
	m_time=300;
    //��ʼ
	SetTimer(1, m_time, NULL);
	Invalidate();
}

void CMy1Dlg::Welcome()
{
	CPaintDC dc(this); // device context for painting
	CBitmap Bitmap;
	Bitmap.LoadBitmap(IDB_BITMAP8);
	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	MemDC.SelectObject(&Bitmap);
	dc.StretchBlt(0,0,GAME_COL*SIZE,GAME_ROW*SIZE, &MemDC, 0, 0, 800,600, SRCCOPY);
	dc.SetBkMode(TRANSPARENT);//���ֱ���͸��
	CFont m_Font;
	m_Font.CreatePointFont(SIZE*10, "������ͷ��_CNKI", NULL);
	dc.SelectObject(&m_Font);//��������
	CString s;
	s.Format("��ĸ̰����");
	dc.TextOut(GAME_COL*SIZE/2.8,SIZE, s);	
	m_Font.DeleteObject();
	m_Font.CreatePointFont(SIZE*2.8, "��������_CNKI", NULL);
	dc.SelectObject(&m_Font);//��������
	s.Format("��Ϸ����:");
	dc.TextOut(GAME_COL*SIZE/3-SIZE,2*GAME_ROW*SIZE/3-SIZE, s);	
	m_Font.DeleteObject();//ɾ���������´�ʹ��
	m_Font.CreatePointFont(SIZE*2.8, "΢���ź�", NULL);
	dc.SelectObject(&m_Font);//��������
	s.Format("1.����ʹ���ļ��ʿ���Զ���ʿ�\n��resĿ¼�µ�data.dat�ļ���ע��һ��ֻ����һ�����ʣ�");
	dc.TextOut(GAME_COL*SIZE/3-SIZE,2*GAME_ROW*SIZE/3, s);	
	s.Format("2.ע�ⲻҪҧ���Լ���ǽ,������������Լ���");
	dc.TextOut(GAME_COL*SIZE/3-SIZE,2*GAME_ROW*SIZE/3+SIZE/1.5, s);
	s.Format("3.����ʾ��,����ʾ��,����ʾ��,����ʾ��");
	dc.TextOut(GAME_COL*SIZE/3-SIZE,2*GAME_ROW*SIZE/3+2*SIZE/1.5, s);
	s.Format("4.�����߳Ե���Ӧ����ĸ����ɫ������������Դ���ĸ����ʧ�ܣ�");
	dc.TextOut(GAME_COL*SIZE/3-SIZE,2*GAME_ROW*SIZE/3+3*SIZE/1.5, s);
	s.Format("5.ͬʱ������ѡ����Ѷȣ��ߵ��ƶ��ٶ�Ҳ���б仯");
	dc.TextOut(GAME_COL*SIZE / 3-SIZE, 2 * GAME_ROW*SIZE / 3 + 4 * SIZE/1.5, s);
	s.Format("6.���ǽ�Ϊ��������ѳɼ���������߸�����Ѱ�!");
	dc.TextOut(GAME_COL*SIZE / 3-SIZE, 2 * GAME_ROW*SIZE / 3 + 5 * SIZE/1.5, s);
	s.Format("����:�����");
	dc.TextOut(GAME_COL*SIZE-2*SIZE,GAME_ROW*SIZE-0.6*SIZE, s);
	m_Font.DeleteObject();
}

void CMy1Dlg::ReadMaxScore(int &n)
{
	FILE *File;
    int flag = 1;//�ж��Ƿ�����ʷ��߷������ļ�
    File = fopen(".\\res\\MaxScore.dat", "r");
    if (File == NULL)
    {
        flag = 0;
        SaveMaxScore(flag);
        File = fopen(".\\res\\MaxScore.dat", "r");
		fscanf(File, "%d", &n);
    }
    else
        fscanf(File, "%d", &n);
    fclose(File);
}

void CMy1Dlg::SaveMaxScore(int flag)
{
  if (flag == 0)//��ʾû�������ļ����򴴽������ļ�
    {
        FILE *File;
        File = fopen(".\\res\\MaxScore.dat", "w");
        fprintf(File, "%d", Gate);
        fclose(File);
    }
    else  if (Gate> MaxScore)
    {
		MessageBox("��ϲ�㣬��������ѳɼ�����Ϊ������");
        MaxScore= Gate;
        FILE *File;
        File = fopen(".\\res\\MaxScore.dat", "w");
        fprintf(File, "%d", Gate);
        fclose(File);
    }
}

void CMy1Dlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
	
}


void CMy1Dlg::LoadKeyWord()
{
	m_import=1;
	CStdioFile f2;
	CString str;
	CString  path;
	int n = 0;
	if (MessageBox("�����ļ��ʻ���Ϊ�ʿ⣿�����ʾ�����Զ���ʿ�data.dat��", NULL, MB_YESNO) == IDYES)
		path = (".\\res\\�ļ��ʻ�.txt");
	else
		path = (".\\res\\data.dat");
	if (f2.Open(path, CFile::modeNoTruncate | CFile::modeRead) == false)
	{
		MessageBox("�ļ�������");
	}
	else
	{
		while (f2.ReadString(str))
		{

			KeyWord.Add(str);
			n++;
		}
	}
}

void CMy1Dlg::OnHelp() 
{
	// TODO: Add your control notification handler code here
	MessageBox("��ĸ̰����\n��Ϸ����:\n1.����ʹ���ļ��ʿ���Զ���ʿ⣨resĿ¼�µ�data.dat�ļ���ע��һ��ֻ����һ�����ʣ����������Ҫ��һ�У�\n2.ע�ⲻҪҧ���Լ���ǽ,������������Լ���\n3.����ʾ��,����ʾ��,����ʾ��,����ʾ��\n4.�����߳Ե���Ӧ����ĸ����ɫ������������Դ���ĸ����ʧ�ܣ�\n5.ͬʱ������ѡ����Ѷȣ��ߵ��ƶ��ٶ�Ҳ���б仯\n6.���ǽ�Ϊ��������ѳɼ���������߸�����Ѱ�!\n����:�����");
}

void CMy1Dlg::SnakeMove()
{
	snake.InsertAt(0, NewSnakeHead);
	if (Score/100<=food.GetUpperBound()&&NewSnakeHead.x == food[Score/100].x&&NewSnakeHead.y==food[Score / 100].y)
	{
		food.SetAt(Score / 100, CPoint(0, 0));
		mciSendString(_T("seek GOAL to start"), 0, 0, 0);
		mciSendString(_T("play GOAL"), 0, 0, 0);
	}
	else
	{
		snake.RemoveAt(snake.GetUpperBound());
	}
	//�ػ�
	//Invalidate();
	InvalidateRect(&CRect(SIZE,SIZE,SIZE*(GAME_COL-1),SIZE*(GAME_ROW-1)),true);//�ػ���Ϸ��
	InvalidateRect(&CRect(GAME_COL*SIZE,0,GAME_COL*SIZE+5*SIZE,8*SIZE),true);//�ػ������
}
