#include "stdafx.h"
#include "../DocumentEditor/Image.h"
#include <boost/filesystem.hpp>
#include "CompareFiles.h"
#include "VerifyExceptions.h"

using namespace std;
using namespace boost;

struct imageFixture
{
	imageFixture()
		:fileName("testImage.txt"),
		width(100),
		height(100),
		image(string("src\\" + fileName), width, height)
	{}
	string fileName;
	int width;
	int height;
	CImage image;
};

BOOST_FIXTURE_TEST_SUITE(CImage_, imageFixture)
	BOOST_AUTO_TEST_SUITE(while_construct)
		BOOST_AUTO_TEST_CASE(throw_exception_if_source_image_is_not_accessible)
		{
			VerifyException<invalid_argument>([]() {
				CImage("C:\\oops.png", 100, 100); },
				"Invalid file path or not accessible file");
		
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(after_construction)
		BOOST_AUTO_TEST_CASE(copy_source_image_to_images_catalog)
		{
			ifstream source("src\\" + fileName);
			ifstream out("images\\" + fileName);
			CompareTxtFiles(source, out);
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
			{
				CImage temp(string("src\\" + fileName), width, height);
				temp.MustDelete(true);
			}
			ifstream file(string("images\\" + fileName));
			BOOST_CHECK(!file.is_open());
		}
		BOOST_AUTO_TEST_CASE(must_not_be_deleted_if_Must_Delete_value_turn_in_false)
		{
			{
				CImage temp(string("src\\" + fileName), width, height);
				temp.MustDelete(false);
			}
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
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()