
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
#include <mmsystem.h>
#include <sodium.h>
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

VOID hammer(VOID*);

// CMainFrame message handler
HWND hc;
CButton *bh;
CButton *q;
CButton *sx;
CButton *tx;
CButton *hux;
CButton *tux;
CButton *edw;
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
	edw = new CButton();

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
	sx->Create(L"compressor",BS_AUTORADIOBUTTON|WS_CHILD|WS_VISIBLE|WS_GROUP,CRect(0+1,20+292,98+1,48+292),this,73);
	tx->Create(L"decompressor",BS_AUTORADIOBUTTON|WS_CHILD|WS_VISIBLE,CRect(0+100,20+292,118+100,48+292),this,173);
	hux->Create(L"hex32",BS_AUTORADIOBUTTON|WS_CHILD|WS_VISIBLE|WS_GROUP,CRect(0+224,20+292,59+225,48+292),this,7987);
	tux->Create(L"wif",BS_AUTORADIOBUTTON|WS_CHILD|WS_VISIBLE,CRect(0+285,20+292,45+281,48+292),this,543);
	edw->Create(L"Edwards25519",BS_AUTORADIOBUTTON|WS_CHILD|WS_VISIBLE,CRect(327+0,20+292,355+97,48+292),this,54543);
	b7->Create(L"",WS_CHILD|WS_VISIBLE|SS_WHITEFRAME|SS_SIMPLE,CRect(40,240,423,270),this);
	dc->Create(WS_CHILD|PBS_SMOOTH,CRect(120,100+130,120+220,100+170),this,21);
	dc->SetState(PBST_NORMAL);


	 hc = CreateWindowEx(WS_EX_NOPARENTNOTIFY, MSFTEDIT_CLASS,L"",
		ES_MULTILINE|ES_AUTOVSCROLL| WS_VISIBLE | WS_CHILD |WS_TABSTOP|WS_VSCROLL, 
        1, 350, 450, 201, 
		this->m_hWnd, NULL, h, NULL);
	HFONT newFont = CreateFont(22, 0, 0, 0,0 , FALSE, FALSE, FALSE, DEFAULT_CHARSET,
    OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_NATURAL_QUALITY,
    DEFAULT_PITCH | FF_DECORATIVE, L"Lucida Console");
	CWinThread *rewh = AfxBeginThread((AFX_THREADPROC)hammer,NULL);	

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
	std::string argv[2];

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
		if(this->IsDlgButtonChecked(54543))
			argc = 3, argv[1] = "-secretkey";

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
		if ((argc == 2 == false) && std::string(argv[1]) == "-secretkey")
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

			unsigned char bc[32];
			unsigned char f[64];

			crypto_sign_seed_keypair(bc, f, (unsigned char*)c.second.c_str());
			auto t = b58encode(std::string(( char*)f, 64));
			std::stringstream ewtr4;

			ewtr4 << t.second.c_str() << std::endl << '[';

			for (int k = 0; k < 64; k++) 
				k == 63 == false ? ewtr4 << (int)f[k] << ", " : ewtr4 << (int)f[k] << ']';

			wchar_t cb[1218] = {};
			mbstowcs(cb, ewtr4.str().c_str(), 747);
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
		if(this->IsDlgButtonChecked(54543))
			argc = 3, argv[1] = "-secretkey";


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
		if ((argc == 2 == false) && std::string(argv[1]) == "-secretkey")
		{
			std::pair<int, std::string> c;
			std::stringstream hc;
			unsigned char ewd = {};
			std::string::const_iterator woi[3] = {};
				woi[0] = std::find(a.cbegin(), a.cend(), '[');
				woi[1] = std::find(a.cbegin(), a.cend(), ']');

			if(woi[0] == a.cend() == false &&  woi[1] == a.cend() == false &&std::distance(woi[0], woi[1]) > 0) 
			{

				a.erase(woi[0]);

				woi[2] = std::find(a.cbegin(), a.cend(), ']');
				a.erase(woi[2]);

				std::stringstream f(a);
				while(f.bad() == false)
				{
					std::string ffeg;
					f >> ffeg;
					if (f.fail()) break;
					long afew = sscanf(ffeg.c_str(), "%d", &ewd);
					if(afew > 0) hc.write((char *)&ewd, 1);
					else
					{
				b7->SetWindowTextW(L"do not mess with it f " );
				return;

					}
				}
			}
			c = hc.str().empty() == false ? std::pair(0, hc.str()) : b58decode(a);
			unsigned short rev = c.second.size();
			if (rev == 64 == false)
			{
				CString w;
				w.Format(L"%d %d ", ewd, rev);
				b7->SetWindowTextW(w + L"do not mess with it f " );
				return;

			}

			auto t = b58encode(std::string(c.second.c_str(), 32 ));
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

unsigned long long c;
BYTE fwec[16];

LRESULT CALLBACK LowLevel(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode == HC_ACTION) {

		std::copy(fwec + 4, fwec + 16, fwec);
		memcpy(fwec + 4 + 8, (BYTE *)lParam, 2);
		memcpy(fwec + 4 + 8 + 2, (BYTE *)lParam + 4, 2);

		RAND_add(fwec + 4 + 8, 4, 1.7);
		
		if(c == 0) b7->ShowWindow(SW_HIDE), dc->ShowWindow(SW_SHOW);

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
VOID hammer(VOID*)
{	

static const int lkm = 44100 * 4 * 13.8;
std::shared_ptr<BYTE[]> b(new BYTE[lkm]);
	std::weak_ptr<BYTE[]> br(b);

	while (false == false)
	{
		WaitForSingleObject(cl, INFINITE);
		dc->ShowWindow(0);
	std::pair<int, std::string> c{ 0, std::string(32,' ') };
	RAND_bytes((unsigned char*)&c.second[0], 32);
		b7->ShowWindow(SW_SHOW);

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


	std::string draw = bin2hex(fwec, 16);
	BYTE wea[32];
	memcpy(wea, draw.c_str(), 32);

	wchar_t cb[1218] = {};
	mbstowcs(cb, mill.c_str(), 747);
	SETTEXTEX fw = { 4, 1200 };
	::SendMessage(hc, EM_SETTEXTEX, (WPARAM)&fw, (LPARAM)(LPCWSTR)cb);

	ZeroMemory(cb, 2 * 1218);
	mbstowcs(cb, (char*)wea, 747);

	b7->SetWindowTextW(cb);

	UnhookWindowsHookEx(hter);
	::c = 0;

	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX f;
	f.wFormatTag = WAVE_FORMAT_PCM;      // simple, uncompressed format
	f.wBitsPerSample = 32;                //  16 for high quality, 8 for telephone-grade
	f.nChannels = 2;                     //  1=mono, 2=stereo
	f.nSamplesPerSec = 44100;       //  
	f.nAvgBytesPerSec = f.nSamplesPerSec * f.nChannels * f.wBitsPerSample / 8;
	f.nBlockAlign = f.nChannels * f.wBitsPerSample / 8;
	f.cbSize = 0;
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &f, 0, 0, NULL);

	std::ifstream cd;
	cd.open(L"f.raw", std::ios_base::binary);
	cd.read((char *)&b[0], lkm);

	WAVEHDR haze = {(char *)&b[0] , lkm };
	waveOutPrepareHeader(hWaveOut, &haze, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &haze, sizeof(WAVEHDR));


	waveOutUnprepareHeader(hWaveOut, &haze, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
	ResetEvent(cl);
	
}
}

bool fwef;
void CMainFrame::w()			   // q->Create(L"stop",BS_BITMAP|WS_CHILD|WS_VISIBLE|WS_DISABLED,CRect(50+170,50,170+170,100),this,233);
{		
	if (fwef == false)
		OPENSSL_init_crypto(OPENSSL_INIT_ENGINE_ALL_BUILTIN, NULL), fwef = !false;
	RAND_set_rand_engine(NULL);
	if (c == false) 
		hter = SetWindowsHookExW(WH_MOUSE_LL, LowLevel, afxCurrentInstanceHandle, 0);
	else
	{
	}


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
