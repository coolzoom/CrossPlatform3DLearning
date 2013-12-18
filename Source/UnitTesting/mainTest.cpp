#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MyTest
#include <boost/test/unit_test.hpp>
#include "../GameCharacter.h"

BOOST_AUTO_TEST_CASE( my_test )
{
	GameCharacter *gc = new GameCharacter();
#ifdef _WIN32
	gc->LoadFromFile("../../../Game/Data/UnspecifiedAnimal/UnspecifiedAnimal.obj");
#else
	gc->LoadFromFile("../../Game/Data/UnspecifiedAnimal/UnspecifiedAnimal.obj");
#endif
	delete gc;

    BOOST_CHECK( 1 == 1 );
    BOOST_REQUIRE( 1 == 1);
    BOOST_CHECK_MESSAGE(1 == 2, "Ooops! Just testing :)");
    BOOST_CHECK_EQUAL(2, 1);
    BOOST_ERROR("Testing again");
    BOOST_FAIL("Testing FAIL, and here it stops");
    BOOST_CHECK_MESSAGE(1 == 2, "This should not appear (execution stops on BOOST_FAIL)");
}
