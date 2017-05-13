#pragma once
#include "stdafx.h"
#include <iostream>
#include <boost/test/output_test_stream.hpp>
#include <functional>

namespace 
{
	struct RedirectCout
	{
		boost::test_tools::output_test_stream output;
		RedirectCout()
			:output(),
			old(std::cout.rdbuf(output.rdbuf()))
		{
		}
		~RedirectCout() {
			std::cout.rdbuf(old);
		}
		void CheckFunctionOutput(std::function<void()> func, const std::string& outputMess)
		{
			output.str("");
			func();
			BOOST_CHECK_EQUAL(output.str(), outputMess);
		}
	private:
		std::streambuf * old;
	};

}
