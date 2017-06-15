#pragma once
#include "FunctionType.h"
#include "Signals.h"

class IHarmonic
{
public:
	typedef sig::signal<void()> HarmonicUpdateSignal;

	virtual ~IHarmonic() = default;
	
	virtual FunctionType GetType() const = 0;
	virtual void SetType(FunctionType  type) = 0;

	virtual float GetAmplitude() const = 0;
	virtual void SetAmplitude(float amplitude) = 0;
	
	virtual float GetFrequency() const = 0;
	virtual void SetFrequency(float frequency) = 0;

	virtual float GetPhase() const = 0;
	virtual void SetPhase(float phase) = 0;

	virtual sig::connection SetHandlerToUpdateHarmonic(const HarmonicUpdateSignal::slot_type & handler) = 0;

	virtual float CalculateAt(float x) const = 0;
};


