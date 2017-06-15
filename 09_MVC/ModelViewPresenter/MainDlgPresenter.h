#pragma once
#include "FunctionType.h"


class IHarmonics;
class IMainDlgView;

class CMainDlgPresenter
{
public:
	CMainDlgPresenter(IHarmonics & harmonics, IMainDlgView & view);
private:
	void UpdateFrequency(int index, float frequency);
	void UpdatePhase(int index, float phase);
	void UpdateAmplitude(int index, float amplitude);
	void UpdateFunctionType(int index, FunctionType functionType);
	void UpdateSelection(int index);
	void AddDefaultHarmonic();
	void AddHarmonic(float aplitude, FunctionType  type, float frequency, float phase);
	void DeleteHarmonic(int index);
	
	void Update();
	void UpdateChart();
	void UpdateView();
	void UpdateList();

	IHarmonics & m_harmonics;
	IMainDlgView & m_view;
};

