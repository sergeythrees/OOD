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
	m_view.DoOnAddHarmonic(std::bind(&CMainDlgPresenter::AddDefaultHarmonic, this));
	m_view.DoOnAmplitudeChange(std::bind(&CMainDlgPresenter::ChangeAmplitude, this, ph::_1, ph::_2));
	m_view.DoOnDeleteHarmonic(std::bind(&CMainDlgPresenter::DeleteHarmonic, this, ph::_1));
	m_view.DoOnFrequencyChange(std::bind(&CMainDlgPresenter::ChangeFrequency, this, ph::_1, ph::_2));
	m_view.DoOnFunctionTypeChange(std::bind(&CMainDlgPresenter::ChangeFunctionType, this, ph::_1, ph::_2));
	m_view.DoOnInit(std::bind(&CMainDlgPresenter::Update, this));
	m_view.DoOnPhaseChange(std::bind(&CMainDlgPresenter::ChangePhase, this, ph::_1, ph::_2));
	m_view.DoOnChangeSelect(std::bind(&CMainDlgPresenter::ChangeSelection, this, ph::_1));
	m_harmonics.DoOnChangeHarmonics(std::bind(&CMainDlgPresenter::Update, this));

}

void CMainDlgPresenter::ChangeFrequency(int index, float frequency)
{
	auto harmonic = m_harmonics.GetHarmonic(index);
	harmonic->SetFrequency(frequency);
}

void CMainDlgPresenter::ChangePhase(int index, float phase)
{
	auto harmonic = m_harmonics.GetHarmonic(index);
	harmonic->SetPhase(phase);
}

void CMainDlgPresenter::ChangeAmplitude(int index, float amplitude)
{
	auto harmonic = m_harmonics.GetHarmonic(index);
	harmonic->SetAmplitude(amplitude);
}

void CMainDlgPresenter::ChangeFunctionType(int index, FunctionType functionType)
{
	auto harmonic = m_harmonics.GetHarmonic(index);
	harmonic->SetType(functionType);
}

void CMainDlgPresenter::ChangeSelection(int index)
{
	auto pHarmonic = m_harmonics.GetHarmonic(index);
	m_view.UpdateSelectedHarmonic(pHarmonic->GetAmplitude(), pHarmonic->GetType(),
		pHarmonic->GetFrequency(), pHarmonic->GetPhase());
}

void CMainDlgPresenter::AddDefaultHarmonic()
{
	AddHarmonic(1, FunctionType::Sin, 1, 0);
}

void CMainDlgPresenter::AddHarmonic(float aplitude,FunctionType type, float frequency, float phase)
{
	m_harmonics.AddHarmonic(aplitude, type, frequency, phase);
	auto pHarmonic = m_harmonics.GetHarmonic(m_harmonics.GetCount() - 1);
	pHarmonic->DoOnChangeHarmonic(std::bind(&CMainDlgPresenter::Update, this));
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
	{
		auto pHarmonic = m_harmonics.GetHarmonic(i);
		harmonicsStr.push_back(ToString(pHarmonic));
	}
	m_view.SetListItems(harmonicsStr);


}

