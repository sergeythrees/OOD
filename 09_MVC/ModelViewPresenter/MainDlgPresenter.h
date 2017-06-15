#pragma once
#include "FunctionType.h"


class IHarmonics;
class IMainDlgView;

class CMainDlgPresenter
{
public:
	CMainDlgPresenter(IHarmonics & harmonics, IMainDlgView & view);

	void ChangeFrequency(int index, float frequency);
	void ChangePhase(int index, float phase);
	void ChangeAmplitude(int index, float amplitude);
	void ChangeFunctionType(int index, FunctionType functionType);
	void ChangeSelection(int index);
	void AddDefaultHarmonic();
	void AddHarmonic(float aplitude, FunctionType  type, float frequency, float phase);
	void DeleteHarmonic(int index);
	void Update();

private:
	void UpdateChart();
	void UpdateView();
private:
	IHarmonics & m_harmonics;
	IMainDlgView & m_view;
};

