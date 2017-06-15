#pragma once
#include "Signals.h"
#include "FunctionType.h"

class IChartView;
class ITableView;

class IMainDlgView
{
public:
	typedef sig::signal<void(int, float)> ChangeHarmonicSignal;
	typedef sig::signal<void(int, FunctionType)> ChangeFunctionTypeSignal;
	typedef sig::signal<void()> AddHarmonicSignal;
	typedef sig::signal<void(int)> DeleteHarmonicSignal;
	typedef sig::signal<void(int)> ChangeSelectionSignal;


	typedef sig::signal<void()> InitSignal;

	virtual IChartView & GetChartView() = 0;
	//virtual ITableView & GetTableView() = 0;
	virtual void SetListItems(std::vector<std::wstring> const& list) = 0;
	virtual void UpdateSelectedHarmonic(float amplitude, FunctionType type, float frequency, float phase) = 0;
	// Signals
	virtual sig::connection DoOnInit(const InitSignal::slot_type & handler) = 0;
	virtual sig::connection DoOnAmplitudeChange(const ChangeHarmonicSignal::slot_type & handler) = 0;
	virtual sig::connection DoOnFrequencyChange(const ChangeHarmonicSignal::slot_type & handler) = 0;
	virtual sig::connection DoOnPhaseChange(const ChangeHarmonicSignal::slot_type & handler) = 0;
	virtual sig::connection DoOnFunctionTypeChange(const ChangeFunctionTypeSignal::slot_type & handler) = 0;
	virtual sig::connection DoOnDeleteHarmonic(const DeleteHarmonicSignal::slot_type & handler) = 0;
	virtual sig::connection DoOnAddHarmonic(const AddHarmonicSignal::slot_type & handler) = 0;
	virtual sig::connection DoOnChangeSelect(const ChangeSelectionSignal::slot_type & handler) = 0;

	virtual ~IMainDlgView() = default;
};