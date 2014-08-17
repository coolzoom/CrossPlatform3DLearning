#include <boost/test/unit_test.hpp>
#include "globals.h"
#include "../Configuration.h"
#include "../GameLog.h"
#include "../Image.h"

#include <boost/smart_ptr.hpp>
#include <iomanip>

using namespace std;
using namespace AvoidTheBug3D;

BOOST_AUTO_TEST_SUITE(GameLogTestSuite)
	BOOST_AUTO_TEST_CASE( imageTest ) {

		boost::shared_ptr<GameLog> log = globals->log;

		boost::shared_ptr<Configuration> cfg = globals->cfg;

		boost::scoped_ptr<Image> image(
			new Image(
			"/Game/Data/UnspecifiedAnimal/UnspecifiedAnimalWithTextureRed.png",
			cfg, log));

		BOOST_CHECK_NE(0, image->getWidth());
		BOOST_CHECK_NE(0, image->getHeight());

		cout << "Image width " << image->getWidth() << ", height " << image->getHeight() << endl;

		float *imageData = image->getData();

		int x = 0, y = 1000;

		while (y < image->getHeight()) {
			x = 0;
			while (x < image->getWidth()) {

				float *colour = &imageData[4 * y * image->getWidth() + 4 * x];

				BOOST_CHECK_GE(colour[0], 0.0f);
				BOOST_CHECK_LE(colour[0], 1.0f);
				BOOST_CHECK_GE(colour[1], 0.0f);
				BOOST_CHECK_LE(colour[1], 1.0f);
				BOOST_CHECK_GE(colour[2], 0.0f);
				BOOST_CHECK_LE(colour[2], 1.0f);
				BOOST_CHECK_EQUAL(colour[3], 1.0f);
				
				/*cout << "At (" << x << ", " << y << ") R: " << setprecision( 2 ) << colour[0] << endl;
				cout << "At (" << x << ", " << y << ") G: " << setprecision( 2 ) << colour[1] << endl;
				cout << "At (" << x << ", " << y << ") B: " << setprecision( 2 ) << colour[2] << endl;*/

				++x;
			}
			++y;
		}
}
BOOST_AUTO_TEST_SUITE_END()
