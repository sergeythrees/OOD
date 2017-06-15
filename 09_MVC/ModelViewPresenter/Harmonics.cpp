#include "stdafx.h"
#include "Harmonics.h"
#include <algorithm>
#include "Harmonic.h"


CHarmonics::CHarmonics()
{
}


CHarmonics::~CHarmonics()
{
}

float CHarmonics::CalculateAt(float x) const
{
	float result = 0;
	std::for_each(m_harmonics.cbegin(), m_harmonics.cend(), [&](auto & harmonic) {
		result += harmonic->CalculateAt(x);
	});
	return result;
}

IHarmonicPtr CHarmonics::GetHarmonic(size_t index) const
{
	if (index >= m_harmonics.size())
	{
		throw std::out_of_range("Out of range");
	}
	return m_harmonics[index];
}

void CHarmonics::AddHarmonic(float amplitude,FunctionType type, float frequency, float phase)
{
	auto pHarmonic = std::make_shared<CHarmonic>(amplitude, type, frequency, phase);
	m_harmonics.push_back(pHarmonic);
	m_harmonicsChangeSignal();
}

void CHarmonics::DeleteHarmonic(size_t index)
{
	if (index >= m_harmonics.size())
	{
		throw std::out_of_range("Out of range");
	}
	m_harmonics.erase(m_harmonics.begin() + index);
	m_harmonicsChangeSignal();
}

size_t CHarmonics::GetCount() const
{
	return m_harmonics.size();
}

sig::connection CHarmonics::DoOnChangeHarmonics(const HarmonicsChangeSignal::slot_type & handler)
{
	std::for_each(m_harmonics.begin(), m_harmonics.end(), [&](auto & harmonic) {
		harmonic->DoOnChangeHarmonic(handler);
	});

	return m_harmonicsChangeSignal.connect(handler);
}
