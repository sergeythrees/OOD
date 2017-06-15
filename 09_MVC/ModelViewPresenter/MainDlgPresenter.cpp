#include "stdafx.h"
#include "MainDlgPresenter.h"
#include "IHarmonics.h"
#include "IMainDlgView.h"
#include "IChartView.h"

using namespace std;
namespace ph = std::placeholders;

CMainDlgPresenter::CMainDlgPresenter(IHarmonics & harmonics, IMainDlgView & view)
	: m_harmonics(harmonics)
	, m_view(view)
{
	m_view.SetHandlerToAddHarmonic(std::bind(&CMainDlgPresenter::AddDefaultHarmonic, this));
	m_view.SetHandlerToAmplitudeUpdate(std::bind(&CMainDlgPresenter::UpdateAmplitude, this, ph::_1, ph::_2));
	m_view.SetHandlerToDeleteHarmonic(std::bind(&CMainDlgPresenter::DeleteHarmonic, this, ph::_1));
	m_view.SetHandlerToFrequencyUpdate(std::bind(&CMainDlgPresenter::UpdateFrequency, this, ph::_1, ph::_2));
	m_view.SetHandlerToFunctionTypeUpdate(std::bind(&CMainDlgPresenter::UpdateFunctionType, this, ph::_1, ph::_2));
	m_view.SetHandlerToInit(std::bind(&CMainDlgPresenter::Update, this));
	m_view.SetHandlerToPhaseUpdate(std::bind(&CMainDlgPresenter::UpdatePhase, this, ph::_1, ph::_2));
	m_view.SetHandlerToUpdateSelect(std::bind(&CMainDlgPresenter::UpdateSelection, this, ph::_1));
	m_harmonics.SetHandlerToUpdateHarmonics(std::bind(&CMainDlgPresenter::Update, this));

}

void CMainDlgPresenter::UpdateFrequency(int index, float frequency)
{
	m_harmonics.GetHarmonic(index)->SetFrequency(frequency);
}

void CMainDlgPresenter::UpdatePhase(int index, float phase)
{
	m_harmonics.GetHarmonic(index)->SetPhase(phase);
}

void CMainDlgPresenter::UpdateAmplitude(int index, float amplitude)
{
	m_harmonics.GetHarmonic(index)->SetAmplitude(amplitude);
}

void CMainDlgPresenter::UpdateFunctionType(int index, FunctionType functionType)
{
	m_harmonics.GetHarmonic(index)->SetType(functionType);
}

void CMainDlgPresenter::UpdateSelection(int index)
{
	auto harmonic = m_harmonics.GetHarmonic(index);
	m_view.UpdateSelectedHarmonic(harmonic->GetAmplitude(), harmonic->GetType(),
		harmonic->GetFrequency(), harmonic->GetPhase());
}

void CMainDlgPresenter::AddDefaultHarmonic()
{
	AddHarmonic(1, FunctionType::Sin, 1, 0);
}

void CMainDlgPresenter::AddHarmonic(float aplitude,FunctionType type, float frequency, float phase)
{
	m_harmonics.AddHarmonic(aplitude, type, frequency, phase);
	m_harmonics.GetHarmonic(m_harmonics.GetCount() - 1)
		->SetHandlerToUpdateHarmonic(std::bind(&CMainDlgPresenter::Update, this));
}

void CMainDlgPresenter::DeleteHarmonic(int index)
{
	m_harmonics.DeleteHarmonic(index);
}

void CMainDlgPresenter::Update()
{
	UpdateView();
	UpdateList();
	UpdateChart();
}

void CMainDlgPresenter::UpdateChart()
{
	IChartView::Points2D points;
	for (float x = 0; x <= 10; x += 0.1f)
	{
		points.emplace_back(x, m_harmonics.CalculateAt(x));
	}
	m_view.GetChartView().SetData(points);
}
void CMainDlgPresenter::UpdateList()
{
	std::vector<std::pair<float, float>> harmonicsTable;
	for (float x = 0; x <= 5.0f; x += 0.5f)
	{
		harmonicsTable.push_back({ x, m_harmonics.CalculateAt(x) });
	}
	m_view.SetTableItems(harmonicsTable);

}

void CMainDlgPresenter::UpdateView()
{
	std::vector<std::wstring> harmonicsStr;
	for (size_t i = 0; i < m_harmonics.GetCount(); ++i)
		harmonicsStr.push_back(ToString(m_harmonics.GetHarmonic(i)));
	m_view.SetListItems(harmonicsStr);
}

