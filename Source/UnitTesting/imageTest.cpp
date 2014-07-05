#include <boost/test/unit_test.hpp>

#include "../Configuration.h"
#include "../GameLog.h"
#include "../Image.h"

#include <boost/smart_ptr.hpp>

using namespace std;
using namespace AvoidTheBug3D;

BOOST_AUTO_TEST_SUITE(GameLogTestSuite)
BOOST_AUTO_TEST_CASE( imageTest )
{
	GameLog *logPtr = new GameLog(cout);
	boost::shared_ptr<GameLog> log(logPtr);

	Configuration *cfgPtr = new Configuration(log);
	boost::shared_ptr<Configuration> cfg(cfgPtr);

	boost::scoped_ptr<Image> image(new Image("/Game/Data/UnspecifiedAnimal/UnspecifiedAnimalWithTexture.png", cfg, log));

}
BOOST_AUTO_TEST_SUITE_END()
