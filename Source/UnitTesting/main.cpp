#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
using namespace boost::unit_test;

void my_test_function()
{
    int a = 5;
}


test_suite* init_unit_test_suite ( int argc, char* argv[] )
{
    test_suite* test = BOOST_TEST_SUITE( "Master test suite" );

    test->add( BOOST_TEST_CASE( &my_test_function ) );

    return test;
}
