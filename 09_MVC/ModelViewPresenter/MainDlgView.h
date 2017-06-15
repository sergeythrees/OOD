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
	void UpdateSelectedHarmonic(float amplitude, FunctionType type, float frequency, float phase) override final;
	IChartView & GetChartView() override final;

	// Signals
	sig::connection DoOnInit(const InitSignal::slot_type & handler) override final;
	sig::connection DoOnAmplitudeChange(const ChangeHarmonicSignal::slot_type & handler) override final;
	sig::connection DoOnFrequencyChange(const ChangeHarmonicSignal::slot_type & handler) override final;
	sig::connection DoOnPhaseChange(const ChangeHarmonicSignal::slot_type & handler) override final;
	sig::connection DoOnFunctionTypeChange(const ChangeFunctionTypeSignal::slot_type & handler) override final;
	sig::connection DoOnDeleteHarmonic(const DeleteHarmonicSignal::slot_type & handler) override final;
	sig::connection DoOnAddHarmonic(const AddHarmonicSignal::slot_type & handler) override final;
	sig::connection DoOnChangeSelect(const ChangeSelectionSignal::slot_type & handler) override final;

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

	void UpdateDataAndSaveSelect(CEdit & edit, ChangeHarmonicSignal & signal);

	InitSignal m_initSignal;
	ChangeHarmonicSignal m_changeAmplitudeSignal;
	ChangeHarmonicSignal m_changeFrequencySignal;
	ChangeHarmonicSignal m_changePhaseSignal;
	ChangeFunctionTypeSignal m_changeFunctionType;
	AddHarmonicSignal m_addHarmonicSignal;
	DeleteHarmonicSignal m_deleteHarmonicSignal;
	ChangeSelectionSignal m_changeSelection;
	
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
};
