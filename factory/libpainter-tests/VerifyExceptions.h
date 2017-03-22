#pragma once
namespace
{
	template <typename Ex, typename Fn>
	void VerifyException(Fn && fn, const string & expectedDescription)
	{
		BOOST_CHECK_EXCEPTION(fn(), Ex, [&](const Ex& e) {
			BOOST_CHECK_EQUAL(e.what(), expectedDescription);
			return e.what() == expectedDescription;
		});
	}
}