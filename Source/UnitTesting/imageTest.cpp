#include <boost/test/unit_test.hpp>
#include "globals.h"
#include "../Configuration.h"
#include "../GameLog.h"
#include "../Image.h"

#include <boost/smart_ptr.hpp>

using namespace std;
using namespace AvoidTheBug3D;

BOOST_AUTO_TEST_SUITE(GameLogTestSuite)
	BOOST_AUTO_TEST_CASE( imageTest ) {

		boost::shared_ptr<GameLog> log = globals->log;

		boost::shared_ptr<Configuration> cfg = globals->cfg;

		boost::scoped_ptr<Image> image(
			new Image(
			"/Game/Data/UnspecifiedAnimal/UnspecifiedAnimalWithTexture.png",
			cfg, log));

		BOOST_CHECK_NE(0, image->getWidth());
		BOOST_CHECK_NE(0, image->getHeight());

		cout << "Image width " << image->getWidth() << ", height " << image->getHeight() << endl;

		unsigned short *imageData = image->getData();

		int x = 0, y = 1000;

		while (y < image->getHeight()) {
			x = 0;
			while (x < image->getWidth()) {
				unsigned short colour = imageData[y * image->getWidth() + x];

				//BOOST_CHECK_GE(colour[0], 0);
				//BOOST_CHECK_LT(colour[0], 256);
				//BOOST_CHECK_GE(colour[1], 0);
				//BOOST_CHECK_LT(colour[1], 256);
				//BOOST_CHECK_GE(colour[2], 0);
				//BOOST_CHECK_LT(colour[2], 256);


				cout << "At (" << x << ", " << y << "): " << colour << endl;

				++x;
				if (x > 100) break;
			}
			++y;
		}
}
BOOST_AUTO_TEST_SUITE_END()
