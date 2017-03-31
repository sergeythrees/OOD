#include "stdafx.h"
#include "../DocumentEditor/Paragraph.h"

using namespace std;
struct paragraphFixture
{
	paragraphFixture()
		:paragraph("text")
	{}

	CParagraph paragraph;
};

BOOST_FIXTURE_TEST_SUITE(CParagraph_, paragraphFixture)
	BOOST_AUTO_TEST_SUITE(after_construction)
		BOOST_AUTO_TEST_CASE(have_preset_text)
		{
			BOOST_CHECK_EQUAL(paragraph.GetText(), "text");
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(SetText_function)
		BOOST_AUTO_TEST_CASE(can_set_text)
		{
			paragraph.SetText("new text");
			BOOST_CHECK_EQUAL(paragraph.GetText(), "new text");
		}
	BOOST_AUTO_TEST_SUITE_END()
	
	BOOST_AUTO_TEST_CASE(can_get_text)
	{
		paragraph.SetText("new text");
		BOOST_CHECK_EQUAL(paragraph.GetText(), "new text");
	}

BOOST_AUTO_TEST_SUITE_END()
