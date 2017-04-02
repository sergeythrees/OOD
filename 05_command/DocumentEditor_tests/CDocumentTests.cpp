#include "stdafx.h"
#include "../DocumentEditor/Document.h"
#include "CompareFiles.h"
#include "VerifyExceptions.h"

using namespace std;

struct documentFixture
{
	documentFixture()
		:document()
	{}
	CDocument document;
};

BOOST_FIXTURE_TEST_SUITE(CDocument_, documentFixture)
	BOOST_AUTO_TEST_SUITE(after_construction)
		BOOST_AUTO_TEST_CASE(has_empty_title)
		{
			BOOST_CHECK_EQUAL(document.GetTitle(), "");
		}
		BOOST_AUTO_TEST_CASE(is_empty)
		{
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 0);
		}
		BOOST_AUTO_TEST_CASE(do_not_change_history)
		{
			BOOST_CHECK(!document.CanUndo());
			BOOST_CHECK(!document.CanRedo());
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(SetTitle_function)
		BOOST_AUTO_TEST_CASE(can_set_title)
		{
			document.SetTitle("new");
			BOOST_CHECK_EQUAL(document.GetTitle(), "new");
		}
		BOOST_AUTO_TEST_CASE(can_undo)
		{
			document.SetTitle("new");
			document.Undo();
			BOOST_CHECK_EQUAL(document.GetTitle(), "");
		}
		BOOST_AUTO_TEST_CASE(can_redo)
		{
			document.SetTitle("new");
			document.SetTitle("new new");
			document.Undo();
			document.Undo();
			document.Redo();
			BOOST_CHECK_EQUAL(document.GetTitle(), "new");
			document.Redo();
			BOOST_CHECK_EQUAL(document.GetTitle(), "new new");
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(InsertParagraph_function)
		BOOST_AUTO_TEST_CASE(can_insert_paragraphs_in_any_positions)
		{
			auto p1 = document.InsertParagraph("paragraph1");
			document.InsertParagraph("paragraph2");
			document.InsertParagraph("paragraph3",1);
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 3);
			BOOST_CHECK_EQUAL(p1->GetText(), "paragraph1");
			BOOST_CHECK_EQUAL(
				document.GetItem(2).GetParagraph()->GetText(), 
				"paragraph2");
			BOOST_CHECK_EQUAL(
				document.GetItem(1).GetParagraph()->GetText(),
				"paragraph3");

		}
		BOOST_AUTO_TEST_CASE(can_undo_and_redo)
		{
			auto p1 = document.InsertParagraph("paragraph1");
			auto p2 = document.InsertParagraph("paragraph2", 0);
			document.Undo();
			document.Undo();
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 0);
			document.Redo();
			document.Redo();
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 2);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(InsertImage_function)
		BOOST_AUTO_TEST_CASE(can_insert_images_in_any_positions)
		{
			auto p1 = document.InsertImage("src/image1.txt", 100, 100);
			auto p2 = document.InsertImage("src/image2.txt", 200, 200, 0);
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 2);
			BOOST_CHECK_EQUAL(p1->GetWidth(), 100);
			BOOST_CHECK_EQUAL(
				document.GetItem(0).GetImage()->GetWidth(), 
				200);
		}
		BOOST_AUTO_TEST_CASE(can_undo_and_redo)
		{
			auto p1 = document.InsertImage("src/image1.txt", 100, 100);
			auto p2 = document.InsertImage("src/image2.txt", 200, 200, 0);
			document.Undo();
			document.Undo();
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 0);
			document.Redo();
			document.Redo();
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 2);
		}
	BOOST_AUTO_TEST_SUITE_END()
			
	BOOST_AUTO_TEST_SUITE(ResizeImage_function)
		BOOST_AUTO_TEST_CASE(can_resize_images)
		{
			auto p1 = document.InsertImage("src/image1.txt", 50, 50);
			document.ResizeImage(0, 100, 200);
			BOOST_CHECK_EQUAL(p1->GetWidth(), 100);
			BOOST_CHECK_EQUAL(p1->GetHeight(), 200);
		}
		BOOST_AUTO_TEST_CASE(can_undo_and_redo)
		{
			auto p1 = document.InsertImage("src/image1.txt", 100, 100);
			document.ResizeImage(0, 200, 200);
			document.ResizeImage(0, 300, 300);
			document.Undo();
			document.Undo();
			BOOST_CHECK_EQUAL(p1->GetWidth(), 100);
			BOOST_CHECK_EQUAL(p1->GetHeight(), 100);
			document.Redo();
			document.Redo();
			BOOST_CHECK_EQUAL(p1->GetWidth(), 300);
			BOOST_CHECK_EQUAL(p1->GetHeight(), 300);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(ReplaceText_function)
		BOOST_AUTO_TEST_CASE(can_replace_text_in_paragraphs)
		{
			auto p1 = document.InsertParagraph("paragraph1");
			document.ReplaceText(0, "new");
			BOOST_CHECK_EQUAL(p1->GetText(), "new");

		}
		BOOST_AUTO_TEST_CASE(can_undo_and_redo)
		{
			auto p1 = document.InsertParagraph("paragraph1");
			document.ReplaceText(0, "new");
			document.ReplaceText(0, "new1");
			document.Undo();
			document.Undo();
			document.Redo();
			document.Redo();
			BOOST_CHECK_EQUAL(p1->GetText(), "new1");
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(DeleteItem_function)
		BOOST_AUTO_TEST_CASE(can_delete_one_or_several_images)
		{
			document.InsertImage("src/image1.txt", 100, 100);
			document.InsertParagraph("text");
			document.DeleteItem(0);
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 1);
			document.DeleteItem(0);
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 0);
		}
		BOOST_AUTO_TEST_CASE(can_undo_and_redo)
		{
			document.InsertImage("src/image1.txt", 100, 100);
			document.InsertParagraph("text");
			document.DeleteItem(0);
			document.DeleteItem(0);
			document.Undo();
			document.Undo();
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 2);
			document.Redo();
			document.Redo();
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 0);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(GetItem_function)
		BOOST_AUTO_TEST_CASE(can_give_access_to_any_element)
		{
			auto p1 = document.InsertParagraph("paragraph1");
			auto p2 = document.InsertImage("src/image2.txt", 200, 200);
			BOOST_CHECK(p1 == document.GetItem(0).GetParagraph());
			BOOST_CHECK(p2 == document.GetItem(1).GetImage());
		}
		BOOST_AUTO_TEST_CASE(can_give_const_access_to_any_element)
		{
			document.InsertParagraph("paragraph1");
			document.InsertImage("src/image2.txt", 200, 200);
			CDocument const*  constDoc = &document;

			constDoc->GetItem(0).GetParagraph();
			constDoc->GetItem(1).GetImage();
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(Save_function)
		BOOST_AUTO_TEST_CASE(can_save_document)
		{
			stringstream expectedresult;
			string imagePath1;
			string imagePath2;
			{
				CDocument tempDoc;
				tempDoc.InsertParagraph("paragraph1");
				auto img1 = tempDoc.InsertImage("src/realImage.png", 200, 200);
				imagePath1 = img1->GetPath();
				auto img2 = tempDoc.InsertImage("src/realImage2.png", 200, 200);	
				imagePath2 = img2->GetPath();
				tempDoc.DeleteItem(2);
				tempDoc.Save("test/test.html");
			}
			BOOST_CHECK(boost::filesystem::exists("test/" + imagePath1));
			BOOST_CHECK(!boost::filesystem::exists("test/" + imagePath2));
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_CASE(should_throw_exceptions_if_item_index_is_out_of_range)
	{
		string expectedMess("Position is out of range");
		VerifyException<out_of_range>([&]() {
			document.InsertParagraph("paragraph1", 3); },
			expectedMess);
		VerifyException<out_of_range>([&]() {
			document.InsertImage("src/realImage.png", 200, 200, 5); },
			expectedMess);
		VerifyException<out_of_range>([&]() {
			document.ReplaceText(0,""); },
			expectedMess);
		VerifyException<out_of_range>([&]() {
			document.ResizeImage(0, 200, 200); },
			expectedMess);
		VerifyException<out_of_range>([&]() {
			document.DeleteItem(0);},
			expectedMess);
		VerifyException<out_of_range>([&]() {
			document.GetItem(1); },
			expectedMess);
		VerifyException<out_of_range>([]() {
			CHistory hist;
			const CDocument doc;
			doc.GetItem(1); },
			expectedMess);
	}
BOOST_AUTO_TEST_SUITE_END()