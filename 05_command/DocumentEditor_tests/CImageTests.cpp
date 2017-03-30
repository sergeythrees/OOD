#include "stdafx.h"
#include "../DocumentEditor/Image.h"
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost;

void CompareTxtFiles(const string& path1, const string& path2)
{
	std::ifstream ifs1(path1);
	std::ifstream ifs2(path2);

	std::istream_iterator<char> b1(ifs1), e1;
	std::istream_iterator<char> b2(ifs2), e2;

	BOOST_CHECK_EQUAL_COLLECTIONS(b1, e1, b2, e2);
}

struct imageFixture
{
	imageFixture()
		:fileName("test.txt"),
		width(100),
		height(100),
		history(),
		image(fileName, width, height, history)
	{}
	string fileName;
	int width;
	int height;
	CHistory history;
	CImage image;
};

BOOST_FIXTURE_TEST_SUITE(CImage_, imageFixture)

	BOOST_AUTO_TEST_SUITE(after_construction)
		BOOST_AUTO_TEST_CASE(copy_source_image_to_images_catalog)
		{
			CompareTxtFiles(fileName, string("images\\" + fileName));
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_CASE(can_get_width_and_height)
	{
		BOOST_CHECK_EQUAL(image.GetWidth(), width);
		BOOST_CHECK_EQUAL(image.GetHeight(), height);
	}
	BOOST_AUTO_TEST_CASE(can_get_relative_path)
	{
		BOOST_CHECK_EQUAL(image.GetPath(), string("images/" + fileName));
	}
	BOOST_AUTO_TEST_SUITE(after_destruction)
		BOOST_AUTO_TEST_CASE(must_be_deleted_if_Must_Delete_value_turn_in_true)
		{
			image.MustDelete(true);
			image.~CImage();
			ifstream file(string("images\\" + fileName));
			BOOST_CHECK(!file.is_open());
		}
		BOOST_AUTO_TEST_CASE(must_not_be_deleted_if_Must_Delete_value_turn_in_false)
		{
			image.MustDelete(false);
			image.~CImage();
			ifstream file(string("images\\" + fileName));
			BOOST_CHECK(file.is_open());
		}
	BOOST_AUTO_TEST_SUITE_END()
	
	BOOST_AUTO_TEST_SUITE(Resize_function)
		BOOST_AUTO_TEST_CASE(can_resize_image)
		{
			image.Resize(200, 200);
			BOOST_CHECK_EQUAL(image.GetWidth(), 200);
			BOOST_CHECK_EQUAL(image.GetHeight(), 200);
		}
		BOOST_AUTO_TEST_CASE(can_undo)
		{
			image.Resize(200, 200);
			image.Resize(300, 300);
			history.Undo();
			BOOST_CHECK_EQUAL(image.GetWidth(), 200);
			BOOST_CHECK_EQUAL(image.GetHeight(), 200);
			history.Undo();
			BOOST_CHECK_EQUAL(image.GetWidth(), 100);
			BOOST_CHECK_EQUAL(image.GetHeight(), 100);
		}
		BOOST_AUTO_TEST_CASE(can_redo)
		{
			image.Resize(200, 200);
			image.Resize(300, 300);
			history.Undo();
			history.Undo();
			history.Redo();
			BOOST_CHECK_EQUAL(image.GetWidth(), 200);
			BOOST_CHECK_EQUAL(image.GetHeight(), 200);
			history.Redo();
			BOOST_CHECK_EQUAL(image.GetWidth(), 300);
			BOOST_CHECK_EQUAL(image.GetHeight(), 300);
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()