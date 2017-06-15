#pragma once
#include "stdafx.h"
#include <memory>
#include "IHarmonic.h"
#include <sstream>
#include <boost\format.hpp>

using IHarmonicPtr = std::shared_ptr<IHarmonic>;

class IHarmonics
{
public:
	typedef sig::signal<void()> HarmonicsChangeSignal;

	virtual ~IHarmonics() = default;
	
	virtual float CalculateAt(float x) const = 0;
	virtual IHarmonicPtr GetHarmonic(size_t index) const = 0;
	virtual void AddHarmonic(float aplitude, FunctionType  type, float frequency, float phase) = 0;
	virtual void DeleteHarmonic(size_t index) = 0;

	virtual size_t GetCount() const = 0;

	virtual sig::connection DoOnChangeHarmonics(const HarmonicsChangeSignal::slot_type & handler) = 0;
};

static std::wstring ToString(const std::shared_ptr<IHarmonic> pHarmonic)
{
	auto ToSignedString = [](double value) {
		std::wostringstream strm;
		strm << std::abs(value);

		return ((value < 0) ? L"- " : L"+ ") + strm.str();
	};

	std::map<FunctionType, std::wstring> functions = {
		{ FunctionType::Sin, L"sin" },
		{ FunctionType::Cos, L"cos" },
	};

	std::wostringstream strm;
	strm << pHarmonic->GetAmplitude() << L"*" << functions.at(pHarmonic->GetType()) << L"(";
	if (pHarmonic->GetFrequency() != 1)
	{
		strm << pHarmonic->GetFrequency() << L"*x";
	}
	else
	{
		strm << L"x";
	}
	strm << (pHarmonic->GetPhase() != 0 ? ToSignedString(pHarmonic->GetPhase()) : L"") << L")";
	return strm.str();
}