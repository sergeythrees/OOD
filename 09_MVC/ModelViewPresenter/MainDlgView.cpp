
// HarmonicsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HarmonicsApp.h"
#include "MainDlgView.h"
#include "afxdialogex.h"

#include <boost/lexical_cast.hpp>
#include <afxmsg_.h>
#include "Utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHarmonicsDlg dialog



CMainDlgView::CMainDlgView(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HARMONICS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainDlgView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HARMONICS_LIST, m_harmonicsList);
	DDX_Control(pDX, IDC_EDIT_AMPLITUDE, m_amplitudeEdit);
	DDX_Control(pDX, IDC_EDIT_FREQUENCY, m_frequencyEdit);
	DDX_Control(pDX, IDC_EDIT_PHASE, m_phaseEdit);
	DDX_Control(pDX, IDC_BUTTON2, m_sinRadio);
	DDX_Control(pDX, IDC_STATIC_AMPLITUDE, m_amplitudeHeader);
	DDX_Control(pDX, IDC_STATIC_FREQ, m_freqHeader);
	DDX_Control(pDX, IDC_STATIC_PH, m_phaseHeader);
	DDX_Control(pDX, IDC_LIST1, m_tableView);
	DDX_Control(pDX, IDC_LIST2, m_tableView2);
}

void CMainDlgView::SetListItems(std::vector<std::wstring> const& list)
{
	m_harmonicsList.ResetContent();
	for (auto & string : list)
	{
		m_harmonicsList.AddString(string.c_str());
	}
}

void CMainDlgView::SetTableItems(std::vector<std::pair<float, float>> const & list)
{
	m_tableView.ResetContent();
	m_tableView2.ResetContent();
	for (auto & value : list)
	{
		m_tableView.AddString(std::to_wstring(value.first).c_str());
		m_tableView2.AddString(std::to_wstring(value.second).c_str());
	}
}

void CMainDlgView::UpdateSelectedHarmonic(
	float amplitude,
	FunctionType type,
	float frequency,
	float phase)
{
	m_amplitudeEdit.SetWindowTextW(boost::lexical_cast<std::wstring>(amplitude).c_str());
	m_phaseEdit.SetWindowTextW(boost::lexical_cast<std::wstring>(phase).c_str());
	m_frequencyEdit.SetWindowTextW(boost::lexical_cast<std::wstring>(frequency).c_str());

	std::map<FunctionType, DWORD> functions = {
		{FunctionType::Cos, IDC_RADIOCOS},
		{ FunctionType::Sin, IDC_RADIOSIN },
	};
	
	CheckRadioButton(IDC_RADIOSIN, IDC_RADIOCOS, functions.at(type));
}

IChartView & CMainDlgView::GetChartView()
{
	return m_chart;
}

sig::connection CMainDlgView::DoOnInit(const InitSignal::slot_type & handler)
{
	return m_initSignal.connect(handler);
}

sig::connection CMainDlgView::DoOnAmplitudeChange(const ChangeHarmonicSignal::slot_type & handler)
{
	return m_changeAmplitudeSignal.connect(handler);
}

sig::connection CMainDlgView::DoOnFrequencyChange(const ChangeHarmonicSignal::slot_type & handler)
{
	return m_changeFrequencySignal.connect(handler);
}

sig::connection CMainDlgView::DoOnPhaseChange(const ChangeHarmonicSignal::slot_type & handler)
{
	return m_changePhaseSignal.connect(handler);
}

sig::connection CMainDlgView::DoOnFunctionTypeChange(const ChangeFunctionTypeSignal::slot_type & handler)
{
	return m_changeFunctionType.connect(handler);
}

sig::connection CMainDlgView::DoOnDeleteHarmonic(const DeleteHarmonicSignal::slot_type & handler)
{
	return m_deleteHarmonicSignal.connect(handler);
}

sig::connection CMainDlgView::DoOnAddHarmonic(const AddHarmonicSignal::slot_type & handler)
{
	return m_addHarmonicSignal.connect(handler);
}

sig::connection CMainDlgView::DoOnChangeSelect(const ChangeSelectionSignal::slot_type & handler)
{
	return 	m_changeSelection.connect(handler);
}

BEGIN_MESSAGE_MAP(CMainDlgView, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CMainDlgView::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CMainDlgView::OnBnClickedButtonDelete)
	ON_LBN_SELCHANGE(IDC_HARMONICS_LIST, &CMainDlgView::OnLbnSelchangeHarmonicsList)
	ON_EN_KILLFOCUS(IDC_EDIT_AMPLITUDE, &CMainDlgView::OnKillFocusAmplitude)
	ON_EN_KILLFOCUS(IDC_EDIT_FREQUENCY, &CMainDlgView::OnKillFocusFrequency)
	ON_EN_KILLFOCUS(IDC_EDIT_PHASE, &CMainDlgView::OnKillFocusPhase)
	ON_BN_CLICKED(IDC_RADIOSIN, &CMainDlgView::OnBnClickedRadiosin)
	ON_BN_CLICKED(IDC_RADIOCOS, &CMainDlgView::OnBnClickedRadiocos)
	ON_LBN_SETFOCUS(IDC_HARMONICS_LIST, &CMainDlgView::OnLbnSetfocusHarmonicsList)
	ON_LBN_KILLFOCUS(IDC_HARMONICS_LIST, &CMainDlgView::OnLbnKillfocusHarmonicsList)
	ON_LBN_SELCANCEL(IDC_HARMONICS_LIST, &CMainDlgView::OnLbnSelcancelHarmonicsList)
	ON_BN_CLICKED(IDC_RADIO4, &CMainDlgView::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO3, &CMainDlgView::OnBnClickedRadio3)
END_MESSAGE_MAP()


// CHarmonicsDlg message handlers

BOOL CMainDlgView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	m_chart.SubclassDlgItem(IDC_CHART, this);

	m_initSignal();

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMainDlgView::OnOk()
{
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMainDlgView::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMainDlgView::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMainDlgView::OnKillFocusAmplitude()
{
	UpdateDataAndSaveSelect(m_amplitudeEdit, m_changeAmplitudeSignal);
}

void CMainDlgView::OnKillFocusPhase()
{
	UpdateDataAndSaveSelect(m_phaseEdit, m_changePhaseSignal);
}

void CMainDlgView::OnKillFocusFrequency()
{
	UpdateDataAndSaveSelect(m_frequencyEdit, m_changeFrequencySignal);
}

void CMainDlgView::EnableEdit(bool enable)
{
	m_amplitudeEdit.EnableWindow(enable);
	m_phaseEdit.EnableWindow(enable);
	m_frequencyEdit.EnableWindow(enable);
	GetDlgItem(IDC_RADIOSIN)->EnableWindow(enable);
	GetDlgItem(IDC_RADIOCOS)->EnableWindow(enable);
	m_amplitudeHeader.EnableWindow(enable);
	m_phaseHeader.EnableWindow(enable);
	m_freqHeader.EnableWindow(enable);
	GetDlgItem(IDC_BUTTON_DELETE)->EnableWindow(enable);
}

void CMainDlgView::UpdateDataAndSaveSelect(CEdit & edit, ChangeHarmonicSignal & signal)
{
	if (UpdateData())
	{
		int index = m_harmonicsList.GetCurSel();
		if (index >= 0)
		{
			signal(index, utils::GetEditValue(edit));
		}
		m_harmonicsList.SetCurSel(index);
	}
}

void CMainDlgView::OnBnClickedButton2()
{
	m_addHarmonicSignal();
	m_harmonicsList.SetCurSel(m_harmonicsList.GetCount()-1);
	m_changeSelection(m_harmonicsList.GetCount() - 1);
	EnableEdit(true);
	// TODO: Add your control notification handler code here
}


void CMainDlgView::OnBnClickedButtonDelete()
{
	int index = m_harmonicsList.GetCurSel();
	if (index >= 0)
	{
		m_deleteHarmonicSignal(index);
	}
	if (m_harmonicsList.GetCount() <= 0)
	{
		EnableEdit(false);
	}
	else
	{
		m_harmonicsList.SetCurSel((m_harmonicsList.GetCount()-1 >= index? index : index - 1));
		m_changeSelection((m_harmonicsList.GetCount() - 1 >= index ? index : index - 1));
	}
	
	// TODO: Add your control notification handler code here
}


void CMainDlgView::OnLbnSelchangeHarmonicsList()
{
	auto index = m_harmonicsList.GetCurSel();
	if (index >= 0)
	{
		m_changeSelection(index);
	}
	// TODO: Add your control notification handler code here
}


void CMainDlgView::OnBnClickedRadiosin()
{
	if (UpdateData())
	{
		int index = m_harmonicsList.GetCurSel();
		if (index >= 0)
		{
			m_changeFunctionType(index, FunctionType::Sin);
		}
		m_harmonicsList.SetCurSel(index);
	}
	// TODO: Add your control notification handler code here
}


void CMainDlgView::OnBnClickedRadiocos()
{
	if (UpdateData())
	{
		int index = m_harmonicsList.GetCurSel();
		if (index >= 0)
		{
			m_changeFunctionType(index, FunctionType::Cos);
		}
		m_harmonicsList.SetCurSel(index);
	}
}


void CMainDlgView::OnLbnSetfocusHarmonicsList()
{
	// TODO: Add your control notification handler code here
}


void CMainDlgView::OnLbnKillfocusHarmonicsList()
{
	// TODO: Add your control notification handler code here
}


void CMainDlgView::OnLbnSelcancelHarmonicsList()
{
	// TODO: Add your control notification handler code here
}


void CMainDlgView::OnBnClickedRadio4()
{
	GetDlgItem(IDC_CHART)->ShowWindow(false);
	GetDlgItem(IDC_LIST1)->ShowWindow(true);
	GetDlgItem(IDC_LIST2)->ShowWindow(true);
	// TODO: Add your control notification handler code here
}


void CMainDlgView::OnBnClickedRadio3()
{
	GetDlgItem(IDC_CHART)->ShowWindow(true);
	GetDlgItem(IDC_LIST1)->ShowWindow(false);
	GetDlgItem(IDC_LIST2)->ShowWindow(false);

	// TODO: Add your control notification handler code here
}
