
// DNSserverDlg.cpp : 实现文件
//
#pragma comment(lib,"ws2_32.lib")

#include "stdafx.h"
#include "DNSserver.h"
#include "DNSserverDlg.h"
#include "afxdialogex.h"
#include <vector>
#include <iostream>
#include <sstream>
#include<Winsock2.h>
#define DEFAULT_PORT 53
#define BUFFER_LENGTH 1024

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDNSserverDlg 对话框



CDNSserverDlg::CDNSserverDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDNSserverDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDNSserverDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDNSserverDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDNSserverDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDNSserverDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON2, &CDNSserverDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CDNSserverDlg 消息处理程序

BOOL CDNSserverDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	CDNSserverDlg::OnBnClickedButton1();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDNSserverDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDNSserverDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDNSserverDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}






class typeofdns
{
public:
	string domain;
	string ip;
	int ttl;
	string mx;
	int mxpriority;
	string cname;
};
vector<typeofdns> alllist;
typeofdns temptypedns;

string Char2Hex(char a)
{
	string str = "";
	int n = a;
	for (int i = 2 * sizeof(char)-1; i >= 0; i--)
	{
		str += "0123456789ABCDEF"[((n >> i * 4) & 0xF)];
	}
	return str;
}
string GetStandardUrl(string in, string &id,string &in2)
{
	int j = 0;
	stringstream ss(in);
	string sub_str, res;
	while (getline(ss, sub_str, '^')) //以|为间隔分割test的内容
	{
		j++;
		if (j==1)
		{
			id = sub_str;
		}
		if (j==2)
		{
			in2 = sub_str;
		}
		if (j>2)
		{
			res = res + sub_str+'.';
		}
	}
	res = res.assign(res.c_str(),res.length()-1);
	return res;
}
string GetResponseText(string domain, string ip, string type, string id)
{
	string res = "";
	res = id;
	res = res + "84000001000100000000";

	return "";
}
int FindNumberOfAlllist(string in, string in2)
{
	for (int i = 0; i < alllist.size(); i++)
	{
		if (in2=="A")// search domain
		{
			if (alllist[i].domain == in)
			{
				return i;
			}
		}
	}
	return -1;
}
string GetSearchInfo(string in)
{
	string id;
	id=in.substr(1,2);
	return id;
}
void CDNSserverDlg::OnBnClickedButton1()
{
	temptypedns.domain = "www.tudou.com";
	temptypedns.ip = "127.0.0.1";
	temptypedns.ttl = 10;
	temptypedns.mx = "192.168.1.1";
	temptypedns.mxpriority = 10;
	temptypedns.cname = "my.tudou.com";
	alllist.push_back(temptypedns);
	temptypedns.domain = "www.youku.com";
	temptypedns.ip = "127.0.0.1";
	temptypedns.ttl = 10;
	temptypedns.mx = "192.168.1.1";
	temptypedns.mxpriority = 10;
	temptypedns.cname = "my.youku.com";
	alllist.push_back(temptypedns);
	// TODO: Add your control notification handler code here
}

void CDNSserverDlg::OnBnClickedButton2()
{
	GetSearchInfo("7DA50100000100000000000003777777057475646F7503636F6D0000010001");




	//string id, type;
	//string sss = GetStandardUrl("FF96^A^www^tudou^com", id, type);
	//int temp = FindNumberOfAlllist(sss, type);// 1 is for search A record
	//if (temp!=-1)// can find this domain in the list
	//{
	//	GetResponseText(sss, alllist[temp].ip, type, id);
	//}



	// TODO: Add your control notification handler code here
}
