#define BOOST_TEST_MODULE range_test_module

#include "lib.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(range_test_suite)

BOOST_AUTO_TEST_CASE(range_test_version)
{
    BOOST_CHECK(version() > 0);
}

BOOST_AUTO_TEST_SUITE_END()
