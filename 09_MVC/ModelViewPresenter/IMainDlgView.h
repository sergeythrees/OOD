#pragma once
#include "Signals.h"
#include "FunctionType.h"

class IChartView;
class ITableView;

class IMainDlgView
{
public:
	typedef sig::signal<void(int, float)> UpdateHarmonicSignal;
	typedef sig::signal<void(int, FunctionType)> UpdateFunctionTypeSignal;
	typedef sig::signal<void()> AddHarmonicSignal;
	typedef sig::signal<void(int)> DeleteHarmonicSignal;
	typedef sig::signal<void(int)> UpdateSelectionSignal;


	typedef sig::signal<void()> InitSignal;

	virtual IChartView & GetChartView() = 0;
	//virtual ITableView & GetTableView() = 0;
	virtual void SetListItems(std::vector<std::wstring> const& list) = 0;
	virtual void SetTableItems(std::vector<std::pair<float, float>> const& list) = 0;
	virtual void UpdateSelectedHarmonic(float amplitude, FunctionType type, float frequency, float phase) = 0;
	// Signals
	virtual sig::connection SetHandlerToInit(const InitSignal::slot_type & handler) = 0;
	virtual sig::connection SetHandlerToAmplitudeUpdate(const UpdateHarmonicSignal::slot_type & handler) = 0;
	virtual sig::connection SetHandlerToFrequencyUpdate(const UpdateHarmonicSignal::slot_type & handler) = 0;
	virtual sig::connection SetHandlerToPhaseUpdate(const UpdateHarmonicSignal::slot_type & handler) = 0;
	virtual sig::connection SetHandlerToFunctionTypeUpdate(const UpdateFunctionTypeSignal::slot_type & handler) = 0;
	virtual sig::connection SetHandlerToDeleteHarmonic(const DeleteHarmonicSignal::slot_type & handler) = 0;
	virtual sig::connection SetHandlerToAddHarmonic(const AddHarmonicSignal::slot_type & handler) = 0;
	virtual sig::connection SetHandlerToUpdateSelect(const UpdateSelectionSignal::slot_type & handler) = 0;

	virtual ~IMainDlgView() = default;
};