#include "stdafx.h"
#include "Harmonic.h"
#include <complex>
#include <functional>
#include <map>

CHarmonic::CHarmonic(float amplitude, FunctionType function, float frequency, float phase)
	: m_amplitude (amplitude)
	, m_frequency(frequency)
	, m_function(function)
	, m_phase(phase)
{

}

CHarmonic::~CHarmonic()
{
}

FunctionType CHarmonic::GetType() const
{
	return m_function;
}

void CHarmonic::SetType(FunctionType type)
{
	if (m_function != type)
	{
		m_function = type;
		m_harmonicUpdateSignal();
	}

}

float CHarmonic::GetAmplitude() const
{
	return m_amplitude;
}

void CHarmonic::SetAmplitude(float amplitude)
{
	if (m_amplitude != amplitude)
	{
		m_amplitude = amplitude;
		m_harmonicUpdateSignal();
	}
}

float CHarmonic::GetFrequency() const
{
	return m_frequency;
}

void CHarmonic::SetFrequency(float frequency)
{
	if (m_frequency != frequency)
	{
		m_frequency = frequency;
		m_harmonicUpdateSignal();
	}
}

float CHarmonic::GetPhase() const
{
	return m_phase;
}

void CHarmonic::SetPhase(float phase)
{
	if (m_phase != phase)
	{
		m_phase = phase;
		m_harmonicUpdateSignal();
	}
}

float CHarmonic::CalculateAt(float x) const
{
	std::map<FunctionType, std::function<float(float)>> functions = {
		{ FunctionType::Sin, &std::sinf },
		{ FunctionType::Cos, &std::cosf },
	};

	return m_amplitude * functions.at(m_function)(m_frequency * x + m_phase);
}

sig::connection CHarmonic::SetHandlerToUpdateHarmonic(const HarmonicUpdateSignal::slot_type & handler)
{
	return m_harmonicUpdateSignal.connect(handler);
}
