#pragma once
#include "IHarmonics.h"
#include <vector>

class CHarmonics :	public IHarmonics
{
public:
	CHarmonics();
	~CHarmonics();

	float CalculateAt(float x) const override final;

	IHarmonicPtr GetHarmonic(size_t index) const override final;

	void AddHarmonic(float amplitude,FunctionType type, float frequency, float phase) override final;
	void DeleteHarmonic(size_t index) override final;

	size_t GetCount() const override final;
	sig::connection SetHandlerToUpdateHarmonics(const HarmonicsUpdateSignal::slot_type & handler) override final;

private:
	std::vector<IHarmonicPtr> m_harmonics;
	HarmonicsUpdateSignal m_harmonicsUpdateSignal;
};

