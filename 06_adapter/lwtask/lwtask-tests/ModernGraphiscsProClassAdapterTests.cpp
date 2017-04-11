#include "stdafx.h"
#include "../modern_graphics_lib_pro.h"
#include "../ModernGraphiscsProClassAdapter.h"
#include <sstream>

using namespace std;
using namespace modern_graphics_lib_pro;

struct proClassAdapterFixture
{
	proClassAdapterFixture()
		: out(),
		expectedOut(),
		renderer(expectedOut),
		adapter(out)
	{}

	ostringstream out;
	ostringstream expectedOut;
	CModernGraphicsRenderer renderer;
	ModernGraphiscsProClassAdapter adapter;

};

BOOST_FIXTURE_TEST_SUITE(ModernGraphiscsProClassAdapter_, proClassAdapterFixture)
	BOOST_AUTO_TEST_SUITE(after_construction)
		BOOST_AUTO_TEST_CASE(do_not_change_stream)
		{
			BOOST_CHECK_EQUAL(out.str(), "");
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_CASE(can_draw_lines_in_modern_graphics_pro_style)
	{
		adapter.BeginDraw();
		adapter.SetColor(111012);
		adapter.MoveTo(1, 1);
		adapter.LineTo(2, 2);
		adapter.SetColor(123455);
		adapter.LineTo(-1, -2);
		adapter.EndDraw();

		renderer.BeginDraw();
		renderer.DrawLine({ 1,1 }, { 2,2 }, { 11,10,12,1.0 });
		renderer.DrawLine({ 2,2 }, { -1,-2 }, { 12,34, 55,1.0 });
		renderer.EndDraw();

		BOOST_CHECK_EQUAL(out.str(), expectedOut.str());
	}
BOOST_AUTO_TEST_SUITE_END()