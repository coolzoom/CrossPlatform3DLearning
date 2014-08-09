#include <boost/test/unit_test.hpp>

#include "../Configuration.h"
#include "../GameLog.h"
#include "../Image.h"

#include <boost/smart_ptr.hpp>

using namespace std;
using namespace AvoidTheBug3D;

BOOST_AUTO_TEST_SUITE(GameLogTestSuite)
BOOST_AUTO_TEST_CASE( imageTest ) {
	GameLog *logPtr = new GameLog(cout);
	boost::shared_ptr<GameLog> log(logPtr);

	Configuration *cfgPtr = new Configuration(log);
	boost::shared_ptr<Configuration> cfg(cfgPtr);

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
			unsigned short *colour = &(imageData[y * image->getWidth() * 3
					+ x * 3]);

			BOOST_CHECK_GE(colour[0], 0);
			BOOST_CHECK_LT(colour[0], 256);
			BOOST_CHECK_GE(colour[1], 0);
			BOOST_CHECK_LT(colour[1], 256);
			BOOST_CHECK_GE(colour[2], 0);
			BOOST_CHECK_LT(colour[2], 256);

//			if (colour[0] + colour[1] + colour[2] > 0 ) {
//				cout << "At (" << x << ", " << y << "): " << "R:" << colour[0]
//						<< " G:" << colour[1] << " B:" << colour[2] << endl;
//			}
			++x;
		}
		++y;
	}
}
BOOST_AUTO_TEST_SUITE_END()
