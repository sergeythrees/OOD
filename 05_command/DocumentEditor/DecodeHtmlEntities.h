#pragma once
#include <map>
#include "stdafx.h"

namespace
{
	std::map<char, std::string> codes = {
		{ '&', "&amp;" },
		{ '<', "&lt;" },
		{ '>', "&gt;" },
		{ '\"', "&gt;" },
	};
	std::string DecodeToHtml(std::string text)
	{		
		for (auto& code : codes)
			for (size_t i = 0; i < text.size();++i)
				if (text[i] == code.first)
				{
					text.erase(i, 1);
					text.insert(i, code.second);
				}
		return text;
	}
}