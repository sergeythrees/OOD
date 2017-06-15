#include "stdafx.h"
#include <boost\lexical_cast.hpp>
namespace utils
{


float GetEditValue(CEdit const& edit)
{
	CString str;
	edit.GetWindowTextW(str);
	return boost::lexical_cast<float>(str.GetBuffer());
}

}
