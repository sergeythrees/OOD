#pragma once
#include "stdafx.h"

namespace
{
	void CompareTxtFiles(std::istream& ifs1, std::istream& ifs2)
	{
		std::istream_iterator<char> b1(ifs1), e1;
		std::istream_iterator<char> b2(ifs2), e2;

		BOOST_CHECK_EQUAL_COLLECTIONS(b1, e1, b2, e2);
	}
}