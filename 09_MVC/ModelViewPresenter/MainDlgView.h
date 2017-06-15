#pragma once
#include "IMainDlgView.h"
#include "afxwin.h"
#include "ChartView.h"

class CMainDlgView : public CDialogEx, public IMainDlgView
{
// Construction
public:
	CMainDlgView(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HARMONICS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	void SetListItems(std::vector<std::wstring>const& list) override final;
	void SetTableItems(std::vector<std::pair<float, float>>const& list)override final;
	void UpdateSelectedHarmonic(float amplitude, FunctionType type, float frequency, float phase) override final;
	IChartView & GetChartView() override final;

	sig::connection SetHandlerToInit(const InitSignal::slot_type & handler) override final;
	sig::connection SetHandlerToAmplitudeUpdate(const UpdateHarmonicSignal::slot_type & handler) override final;
	sig::connection SetHandlerToFrequencyUpdate(const UpdateHarmonicSignal::slot_type & handler) override final;
	sig::connection SetHandlerToPhaseUpdate(const UpdateHarmonicSignal::slot_type & handler) override final;
	sig::connection SetHandlerToFunctionTypeUpdate(const UpdateFunctionTypeSignal::slot_type & handler) override final;
	sig::connection SetHandlerToDeleteHarmonic(const DeleteHarmonicSignal::slot_type & handler) override final;
	sig::connection SetHandlerToAddHarmonic(const AddHarmonicSignal::slot_type & handler) override final;
	sig::connection SetHandlerToUpdateSelect(const UpdateSelectionSignal::slot_type & handler) override final;

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	virtual void OnOk();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	void OnKillFocusAmplitude();
	void OnKillFocusPhase();
	void OnKillFocusFrequency();

	void EnableEdit(bool enable);

	void UpdateEditBoxValues(CEdit & edit, UpdateHarmonicSignal & signal);

	InitSignal m_initSignal;
	UpdateHarmonicSignal m_changeAmplitudeSignal;
	UpdateHarmonicSignal m_changeFrequencySignal;
	UpdateHarmonicSignal m_changePhaseSignal;
	UpdateFunctionTypeSignal m_changeFunctionType;
	AddHarmonicSignal m_addHarmonicSignal;
	DeleteHarmonicSignal m_deleteHarmonicSignal;
	UpdateSelectionSignal m_changeSelection;
	
	CChartView m_chart;

public:
	afx_msg void OnBnClickedButton2();
	CListBox m_harmonicsList;
	afx_msg void OnBnClickedButtonDelete();
	CEdit m_amplitudeEdit;
	CEdit m_frequencyEdit;
	CEdit m_phaseEdit;
	afx_msg void OnLbnSelchangeHarmonicsList();
	afx_msg void OnBnClickedRadiosin();
	afx_msg void OnBnClickedRadiocos();
	afx_msg void OnLbnSetfocusHarmonicsList();
	afx_msg void OnLbnKillfocusHarmonicsList();
	afx_msg void OnLbnSelcancelHarmonicsList();
	CButton m_sinRadio;
	CStatic m_amplitudeHeader;
	CStatic m_freqHeader;
	CStatic m_phaseHeader;
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio3();
	CListBox m_tableView;
	CListBox m_tableViewY;
	CListBox m_tableView2;
};
