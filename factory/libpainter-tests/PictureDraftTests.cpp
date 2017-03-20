#include "stdafx.h"
#include "../libpainter/PictureDraft.h"
#include "../libpainter/Shape.h"

using namespace std;

class CMockShape : public CShape
{
public:
	CMockShape() = default;
	void Draw(ICanvas& canvas) const override
	{
		canvas;
	}
	CColor GetColor() const override
	{
		return CColor();
	}
	string descr;
};
struct Picture_draft_
{
	CPictureDraft draft;
};

BOOST_FIXTURE_TEST_SUITE(Picture_draft, Picture_draft_)
	BOOST_AUTO_TEST_SUITE(by_default)
		BOOST_AUTO_TEST_CASE(is_empty)
		{
			BOOST_CHECK(draft.IsEmpty());
		}
		BOOST_AUTO_TEST_CASE(has_equal_begin_and_end_iterators)
		{
			BOOST_CHECK(draft.begin() == draft.end());
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct after_adding_a_shape_ : Picture_draft_
	{
		unique_ptr<CShape> shape1 = make_unique<CMockShape>();
		CShape & refShape1 = *shape1;
		unique_ptr<CShape> shape2 = make_unique<CMockShape>();
		CShape & refShape2 = *shape2;
		unique_ptr<CShape> shape3 = make_unique<CMockShape>();
		CShape & refShape3 = *shape3;

		after_adding_a_shape_()
		{
			draft.AddShape(move(shape1));
			draft.AddShape(move(shape2));
			draft.AddShape(move(shape3));
		}
	};
	BOOST_FIXTURE_TEST_SUITE(after_adding_a_shape, after_adding_a_shape_)
		BOOST_AUTO_TEST_CASE(becomes_not_empty)
		{
			BOOST_CHECK(!draft.IsEmpty());
		}
		BOOST_AUTO_TEST_CASE(has_different_begin_and_end_iterators)
		{
			BOOST_CHECK(draft.begin() != draft.end());
		}
		BOOST_AUTO_TEST_CASE(allows_iteration_across_added_shapes)
		{
			auto it = draft.begin();
			BOOST_CHECK_EQUAL(addressof(*(it++)), addressof(refShape1));
			BOOST_REQUIRE(it != draft.end());
			BOOST_CHECK_EQUAL(addressof(*(it++)), addressof(refShape2));
			BOOST_REQUIRE(it != draft.end());
			BOOST_CHECK_EQUAL(addressof(*(it++)), addressof(refShape3));
			BOOST_REQUIRE(it == draft.end());
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()