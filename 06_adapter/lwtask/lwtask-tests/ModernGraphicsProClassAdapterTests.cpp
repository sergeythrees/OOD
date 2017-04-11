#include "stdafx.h"
#include "../modern_graphics_lib_pro.h"
#include "../ModernGraphicsProClassAdapter.h"
#include <sstream>

using namespace std;
using namespace modern_graphics_lib_pro;

struct ProClassAdapterFixture
{
	ProClassAdapterFixture()
		: out(),
		expectedOut(),
		renderer(expectedOut),
		adapter(out)
	{}

	ostringstream out;
	ostringstream expectedOut;
	CModernGraphicsRenderer renderer;
	ModernGraphicsProClassAdapter adapter;

};

BOOST_FIXTURE_TEST_SUITE(ModernGraphicsProClassAdapter_, ProClassAdapterFixture)
	BOOST_AUTO_TEST_SUITE(after_construction)
		BOOST_AUTO_TEST_CASE(do_not_change_stream)
		{
			BOOST_CHECK_EQUAL(out.str(), "");
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_CASE(can_draw_lines_in_modern_graphics_pro_style)
	{
		adapter.BeginDraw();
		adapter.SetColor(0x1e3246);
		adapter.MoveTo(1, 1);
		adapter.LineTo(2, 2);
		adapter.SetColor(0xFFFFFF);
		adapter.LineTo(-1, -2);
		adapter.EndDraw();

		renderer.BeginDraw();
		renderer.DrawLine({ 1,1 }, { 2,2 }, { 0.118f,0.196f,0.275f,1.0 });
		renderer.DrawLine({ 2,2 }, { -1,-2 }, { 1.0f,1.0f, 1.0f,1.0f });
		renderer.EndDraw();

		BOOST_CHECK_EQUAL(out.str(), expectedOut.str());
	}
BOOST_AUTO_TEST_SUITE_END()