#include "stdafx.h"
#include "../modern_graphics_lib.h"
#include "../ModernGraphiscsObjectAdapter.h"
#include <sstream>

using namespace std;

struct adapterFixture
{
	adapterFixture()
		: out(),
		expectedOut(),
		rendererForAdapter(out),
		renderer(expectedOut),
		adapter(rendererForAdapter)
	{}

	ostringstream out;
	ostringstream expectedOut;
	modern_graphics_lib::CModernGraphicsRenderer renderer;
	modern_graphics_lib::CModernGraphicsRenderer rendererForAdapter;
	ModernGraphiscsObjectAdapter adapter;

};

BOOST_FIXTURE_TEST_SUITE(ModernGraphiscsObjectAdapter_, adapterFixture)
	BOOST_AUTO_TEST_SUITE(after_construction)
		BOOST_AUTO_TEST_CASE(do_not_change_stream)
		{
			BOOST_CHECK_EQUAL(out.str(), "");
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(LineTo_function)
		BOOST_AUTO_TEST_CASE(can_draw_lines_in_modern_graphics_style)
		{
			rendererForAdapter.BeginDraw();
			adapter.MoveTo(1, 1);
			adapter.LineTo(2, 2);
			adapter.MoveTo(3, 3);
			adapter.LineTo(-1, -2);
			rendererForAdapter.EndDraw();

			renderer.BeginDraw();
			renderer.DrawLine({ 1,1 }, { 2,2 });
			renderer.DrawLine({ 3,3 }, { -1,-2 });
			renderer.EndDraw();

			BOOST_CHECK_EQUAL(out.str(), expectedOut.str());
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()