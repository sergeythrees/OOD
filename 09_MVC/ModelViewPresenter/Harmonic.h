#pragma once
#include "IHarmonic.h"
class CHarmonic : public IHarmonic
{
public:
	CHarmonic(float amplitude, FunctionType  function, float frequency, float phase);
	~CHarmonic();

	

	FunctionType GetType() const override final;
	void SetType(FunctionType  type) override final;

	float GetAmplitude() const override final;
	void SetAmplitude(float amplitude) override final;

	float GetFrequency() const override final;
	void SetFrequency(float frequency) override final;

	float GetPhase() const override final;
	void SetPhase(float phase) override final;

	float CalculateAt(float x) const override final;
	sig::connection DoOnChangeHarmonic(const HarmonicChangeSignal::slot_type & handler) override final;

private:
	float m_amplitude;
	FunctionType m_function;
	float m_frequency;
	float m_phase;

	HarmonicChangeSignal m_harmonicChangeSignal;
};