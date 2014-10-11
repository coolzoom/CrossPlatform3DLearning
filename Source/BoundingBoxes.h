#ifndef BOUNDINGBOXES_H_
#define BOUNDINGBOXES_H_

#include <boost/smart_ptr.hpp>
#include "Configuration.h"
#include "GameLog.h"
#include <vector>


using namespace std;

namespace AvoidTheBug3D {

	/**
	 * @struct	BoundingBoxes
	 *
	 * @brief	Bounding boxes for a model. Even though the loading logic is similar
	 * 			to that of the Model class, BoundingBoxes is a separate class with
	 * 			a separate loading function, because it loads a Wavefront file
	 * 			exported with a different set of options (see Assets/README).
	 * 			Even though there can be more than one bounding boxes, these are
	 * 			not separated into different structures because each has a set of
	 * 			six faces and this fact can be used to separate them at runtime.
	 *
	 * @author	Dimitri Kourkoulis
	 * @date	Oct 10, 2014
	 */

	struct BoundingBoxes {
	private:
		boost::shared_ptr<Configuration> cfg;
		boost::shared_ptr<GameLog> log;

		int numBoxes;

	public:

		/**
		 * Constructor
		 * @param	cfg	The configuration
		 * @param	log	The log
		 */

		BoundingBoxes(const boost::shared_ptr<Configuration> cfg,
			const boost::shared_ptr<GameLog> log);

		/**
		 * Destructor
		 */
		~BoundingBoxes();

		/**
		 * @brief	Vertex coordinates read from Wavefront .obj file
		 */

		vector<float*> *vertices;

		/**
		 * @brief	Faces vertex indexes read from Wavefront .obj file
		 */

		vector<int*> *facesVertexIndexes;

		/**
		 * Load the bounding boxes from a Wavefront file.
		 * 
		 * @param	fileLocation	The file location, relative to the game's
		 * 							execution directory
		 */

		void loadFromFile(string fileLocation);

		/**
		 * Check if a point collides (or is inside) any of the boxes
		 * assuming that they are in a given offset and have a certain rotation
		 *
		 * @param	pointX		 	The point x coordinate.
		 * @param	pointY		 	The point y coordinate.
		 * @param	pointZ		 	The point z coordinate.
		 * @param	boxesX		 	The boxes x coordinate.
		 * @param	boxesY		 	The boxes y coordinate.
		 * @param	boxesZ		 	The boxes z coordinate.
		 * @param	boxesRotation	The boxes rotation.
		 *
		 * @return	true if it succeeds, false if it fails.
		 */

		bool pointCollides(const float &pointX, const float &pointY, const float &pointZ, 
			const float &boxesX, const float &boxesY, const float &boxesZ, const float &boxesRotation);

	};
}

#endif /* BOUNDINGBOXES_H_ */