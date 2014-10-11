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

	};
}

#endif /* BOUNDINGBOXES_H_ */