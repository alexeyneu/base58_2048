
// MainFrm.cpp : implementation of the CMainFrame class
//
 
#include "stdafx.h"
#include "tool3.h"
#include <Richedit.h>
#include "MainFrm.h"
#include <map>
#include "base58_2048.h"
#include <openssl/sha.h>
#include <openssl/bn.h>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <base58.hpp>
#include <openssl/rand.h>
#include <openssl/conf.h>


const	std::string bin2hex(const unsigned char* p, size_t length) {
	std::stringstream f;
	f << std::hex << std::setfill('0');
	for (int i = 0; i < length; i++) f << std::setw(2) << (int)p[i];
	return f.str();
}

size_t hex2bin(unsigned char* p, const char* hexstr, const size_t length) {
	size_t wcount = 0;
	while (wcount++ < length) {    //last condition cause np if check fails on middle one.thats coz of short-circuit evaluation
		long long b = sscanf(hexstr, "%2hhx", p++);  //7x slower than tables but doesnt metter
		if (b < 1) break;
		hexstr = hexstr + 2;
	}
	return  --wcount;     // error check here is a waste  
}


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CWnd)
	ON_WM_CREATE()
	ON_BN_CLICKED(2133,tr)
	ON_BN_CLICKED(233,w)
	ON_WM_DESTROY()
	// WM_ret stays undefined that moment so .
	ON_MESSAGE(WM_CTLCOLORSTATIC, &CMainFrame::OnCtlcolorstatic)
END_MESSAGE_MAP()

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

// CMainFrame message handler
HWND hc;
CButton *bh;
CButton *q;
CButton *sx;
CButton *tx;
CButton *hux;
CButton *tux;
CStatic *b7;
CProgressCtrl *dc;
HANDLE cl;

DWORD CALLBACK E(DWORD_PTR dw, LPBYTE pb, LONG cb, LONG *pcb)
{
    std::wstringstream *fr = (std::wstringstream *)dw;
    fr->write((wchar_t *)pb, int(cb/2)); 
    *pcb = cb;
    return 0;
}

std::map< state , std::wstring> braze;

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	
	dc= new CProgressCtrl();
	cl=CreateEvent(NULL,1,0,NULL);

	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	bh = new CButton();
	b7=new CStatic();

	q = new CButton();
	sx = new CButton();
	tx = new CButton();
	hux = new CButton();
	tux = new CButton();

	CBitmap wq[2];

	wq[0].LoadBitmap(IDB_BITMAP1);
	wq[1].LoadBitmap(IDB_BITMAP4);


		
	braze[q_quit]= L"quit";
	braze[q_gundrop]= L"gundrop";
	braze[q_stay] = L"stay";
	braze[q_stop]= L"q_stop";
	braze[q_torque] = L"torque";


	bh->Create(L"start",BS_BITMAP|WS_CHILD|WS_VISIBLE,CRect(50,50,170,100),this,2133);
	bh->SetBitmap(wq[0]);
	q->Create(L"stop",BS_BITMAP|WS_CHILD|WS_VISIBLE,CRect(50+170,50,170+170,100),this,233);
	q->SetBitmap(wq[1]);
	sx->Create(L"compressor",BS_AUTORADIOBUTTON|WS_CHILD|WS_VISIBLE|WS_GROUP,CRect(0+10,20+292,98+10,48+292),this,73);
	tx->Create(L"decompressor",BS_AUTORADIOBUTTON|WS_CHILD|WS_VISIBLE,CRect(0+111,20+292,118+111,48+292),this,173);
	hux->Create(L"-hex32_24",BS_AUTORADIOBUTTON|WS_CHILD|WS_VISIBLE|WS_GROUP,CRect(0+240,20+292,95+240,48+292),this,7987);
	tux->Create(L"-wif24",BS_AUTORADIOBUTTON|WS_CHILD|WS_VISIBLE,CRect(0+337,20+292,97+341,48+292),this,543);
	b7->Create(L"",WS_CHILD|WS_VISIBLE|SS_WHITEFRAME|SS_SIMPLE,CRect(40,240,423,270),this);
	dc->Create(WS_VISIBLE|WS_CHILD|PBS_SMOOTH,CRect(120,100+130,120+220,100+170),this,21);
	dc->SetState(PBST_NORMAL);


	 hc = CreateWindowEx(WS_EX_NOPARENTNOTIFY, MSFTEDIT_CLASS,L"",
		ES_MULTILINE|ES_AUTOVSCROLL| WS_VISIBLE | WS_CHILD |WS_TABSTOP|WS_VSCROLL, 
        1, 350, 450, 201, 
		this->m_hWnd, NULL, h, NULL);
	HFONT newFont = CreateFont(22, 0, 0, 0,0 , FALSE, FALSE, FALSE, DEFAULT_CHARSET,
    OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_NATURAL_QUALITY,
    DEFAULT_PITCH | FF_DECORATIVE, L"Lucida Console");
	
	::PostMessage(b7->m_hWnd, WM_SETFONT, (WPARAM)newFont, (LPARAM)0);
	::PostMessage(hc,WM_SETFONT,(WPARAM)newFont,(LPARAM)0);
	return 0;
}
state bren = q_stay;
int cr,f,terminator;
std::string er;

void CMainFrame::tr() //  bh->Create(L"start",BS_BITMAP|WS_CHILD|WS_VISIBLE|c,CRect(50,50,170,100),this,2133);
{   
	std::wstringstream fr;
	int argc = 2;
	char* argv[2];

	EDITSTREAM es = {};
	if(trigger)
	{	
		es.dwCookie = (DWORD_PTR) &fr;
		es.pfnCallback = E;
		::SendMessage(hc, EM_STREAMOUT, SF_TEXT|SF_UNICODE, (LPARAM)&es);		
		ZeroMemory(remmi,1218*2);
		fr.read(remmi,747);
	//	trigger = 0;
	}
	char wfae[1218] = {};
	wcstombs(wfae, remmi, 747);
	er = wfae;

	if (this->IsDlgButtonChecked(73))
	{	
		std::stringstream bt(er);
		if(this->IsDlgButtonChecked(7987))
			argc = 3, argv[1] = "-hex32_24";
		if(this->IsDlgButtonChecked(543))
			argc = 3, argv[1] = "-wif24";

		std::vector<std::string> b;
		do
		{
			std::string last;
			bt >> last;
			if (bt.fail()) break;
			b.insert(b.cend(), last);
		} while (bt.bad() == false);


		std::string harbour;
		std::pair<int, unsigned int> f = transfer2048_to_b58(b, harbour);
		if (f.first == 0)
		{
			return;
		}

		if (argc == 2)
		{
			wchar_t c[1218] = {};
			mbstowcs(c, harbour.c_str(), 747);
			SETTEXTEX fw = { 4, 1200 };
			::SendMessage(hc, EM_SETTEXTEX, (WPARAM)&fw, (LPARAM)(LPCWSTR)c);
		}
		if ((argc == 2 == false) && std::string(argv[1]) == "-wif24")
		{
			if (b.size() > 24)
			{	
				b7->SetWindowTextW(L"do not mess with it");
				return;
			}

			auto c = b58decode(harbour);
			if (c.second.size() == 32 == false)
			{
				b7->SetWindowTextW(L"do not mess with it");
				return;
			}

			std::string wb_final_compressed;

			wb_final_compressed.insert(wb_final_compressed.cbegin(), (char)0x80);
			wb_final_compressed.insert(1, c.second);
			wb_final_compressed.insert(wb_final_compressed.cend(), (char)0x01);

			unsigned char h_compressed[250] = {};
			unsigned char hf_compressed[250] = {};
			SHA256((unsigned char*)wb_final_compressed.c_str(), wb_final_compressed.size(), h_compressed);
			SHA256(h_compressed, 32, hf_compressed);

			wb_final_compressed.insert(wb_final_compressed.size(), std::string((char*)hf_compressed, 4));

			auto t_compressed = b58encode(wb_final_compressed);

			std::string wb_final;
			wb_final.insert(wb_final.cbegin(), (char)0x80);
			wb_final.insert(1, c.second);

			unsigned char h[250] = {};
			unsigned char hf[250] = {};
			SHA256((unsigned char*)wb_final.c_str(), wb_final.size(), h);
			SHA256(h, 32, hf);
			wb_final.insert(wb_final.size(), std::string((char*)hf, 4));

			auto t = b58encode(wb_final);
			std::string whydah = t.second;
			std::string mill = whydah + '\n' + t_compressed.second;
			wchar_t cb[1218] = {};
			mbstowcs(cb, mill.c_str(), 747);
			SETTEXTEX fw = { 4, 1200 };
			::SendMessage(hc, EM_SETTEXTEX, (WPARAM)&fw, (LPARAM)(LPCWSTR)cb);
			
		}
		if ((argc == 2 == false) && std::string(argv[1]) == "-hex32_24")
		{
			if (b.size() > 24)
			{
				b7->SetWindowTextW(L"do not mess with it");
				return;

			}

			auto c = b58decode(harbour);
			if (c.second.size() == 32 == false)
			{
				b7->SetWindowTextW(L"do not mess with it");
				return;

			}

			std::string draw = bin2hex((unsigned char*)c.second.c_str(), 32);
			wchar_t cb[1218] = {};
			mbstowcs(cb, draw.c_str(), 747);
			SETTEXTEX fw = { 4, 1200 };
			::SendMessage(hc, EM_SETTEXTEX, (WPARAM)&fw, (LPARAM)(LPCWSTR)cb);

		}
		return;

	}
	if (this->IsDlgButtonChecked(173))
	{
		std::string a = er;
		if(this->IsDlgButtonChecked(7987))
			argc = 3, argv[1] = "-hex32_24";
		if(this->IsDlgButtonChecked(543))
			argc = 3, argv[1] = "-wif24";

		if ((argc == 2 == false) && std::string(argv[1]) == "-hex32_24")
		{
			unsigned char bc[250] = {};

			size_t zx = hex2bin(bc, a.c_str(), 32);

			if (zx == 32 == false)
			{
				b7->SetWindowTextW(L"do not mess with it");
				return;

			}

			auto t = b58encode(std::string((char *)bc, 32 ));
			a = t.second;
		}

		if ((argc == 2 == false) && std::string(argv[1]) == "-wif24")
		{
			auto c = b58decode(a);
			if (c.second.size() == 37 == false && c.second.size() == 38 == false)
			{
				b7->SetWindowTextW(L"do not mess with it");
				return;

			}

			auto t = b58encode(std::string(c.second.c_str() + 1, 32 ));
			a = t.second;
		}

		std::vector<std::string> farstone;

		std::pair<int, unsigned int> tyr = b58_to_2048(a, farstone);
		if (tyr.first == 0)
		{
				b7->SetWindowTextW(L"High-bit set on invalid digit");
				return;

		}
		if (tyr.first == -1)
		{
				b7->SetWindowTextW(L"Invalid base58 digit");
				return;

		}

		if (argc == 3 && farstone.size() > 24)
		{
				b7->SetWindowTextW(L"leading zeroes, will not work");
				return;
		}
		std::stringstream ht;

		for (auto c:farstone)
			ht << std::endl << c << std::endl;
		ht << std::endl;

		wchar_t cb[1218] = {};
		mbstowcs(cb, ht.str().c_str(), 747);
		SETTEXTEX fw = { 4, 1200 };
		::SendMessage(hc, EM_SETTEXTEX, (WPARAM)&fw, (LPARAM)(LPCWSTR)cb);
		return ;
	}
//	::PostMessage(hc, WM_VSCROLL, SB_BOTTOM, 0);

}

HWND erg;
unsigned long long c;
LRESULT CALLBACK LowLevel(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode == HC_ACTION) {
		const int b[2] = { wParam, lParam };
		RAND_add(b, 8, 8 * 0.25);
		c++;
		dc->SetPos(int(100 * c/9000.0));

	}
	if (c == 9000)
	{
		c = 0;
		SetEvent(cl);
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

HHOOK hter;
VOID hammer(VOID *)
{	
			WaitForSingleObject(cl,INFINITE);
			std::pair<int, std::string> c{0, std::string(32,' ')};
			RAND_bytes((unsigned char*)&c.second[0], 32);

			std::string wb_final_compressed;

			wb_final_compressed.insert(wb_final_compressed.cbegin(), (char)0x80);
			wb_final_compressed.insert(1, c.second);
			wb_final_compressed.insert(wb_final_compressed.cend(), (char)0x01);

			unsigned char h_compressed[250] = {};
			unsigned char hf_compressed[250] = {};
			SHA256((unsigned char*)wb_final_compressed.c_str(), wb_final_compressed.size(), h_compressed);
			SHA256(h_compressed, 32, hf_compressed);

			wb_final_compressed.insert(wb_final_compressed.size(), std::string((char*)hf_compressed, 4));

			auto t_compressed = b58encode(wb_final_compressed);

			std::string wb_final;
			wb_final.insert(wb_final.cbegin(), (char)0x80);
			wb_final.insert(1, c.second);

			unsigned char h[250] = {};
			unsigned char hf[250] = {};
			SHA256((unsigned char*)wb_final.c_str(), wb_final.size(), h);
			SHA256(h, 32, hf);
			wb_final.insert(wb_final.size(), std::string((char*)hf, 4));

			auto t = b58encode(wb_final);
			std::string whydah = t.second;
			std::string mill = whydah + '\n' + t_compressed.second;
			wchar_t cb[1218] = {};
			mbstowcs(cb, mill.c_str(), 747);
			SETTEXTEX fw = { 4, 1200 };
			::SendMessage(hc, EM_SETTEXTEX, (WPARAM)&fw, (LPARAM)(LPCWSTR)cb);
			UnhookWindowsHookEx(hter);
}


void CMainFrame::w()			   // q->Create(L"stop",BS_BITMAP|WS_CHILD|WS_VISIBLE|WS_DISABLED,CRect(50+170,50,170+170,100),this,233);
{		

	erg = this->m_hWnd;
	OPENSSL_init_crypto(OPENSSL_INIT_ENGINE_ALL_BUILTIN, NULL);
	RAND_set_rand_engine(NULL);
	if (c == false) 
		hter = SetWindowsHookExW(WH_MOUSE_LL, LowLevel, afxCurrentInstanceHandle, 0);
	else
	{
	}
	CWinThread *rewh = AfxBeginThread((AFX_THREADPROC)hammer,NULL);	


	return;
}



HBRUSH hbrBkgnd;
void CMainFrame::OnDestroy()
{
	CWnd::OnDestroy();
	delete bh;
	delete q;
	DeleteObject(hbrBkgnd);
}




afx_msg LRESULT CMainFrame::OnCtlcolorstatic(WPARAM wParam, LPARAM lParam)
{
	HDC hdcStatic = (HDC)wParam;
	SetTextColor(hdcStatic, RGB(2, 5, 55));
	SetBkColor(hdcStatic, RGB(255, 255, 255));
    if (hbrBkgnd == NULL) hbrBkgnd = CreateSolidBrush(RGB(255, 255, 255));
    return (INT_PTR)hbrBkgnd;
}
