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
	 * @brief	Bounding boxes for a model
	 *
	 * @author	Dimitri Kourkoulis
	 * @date	Oct 10, 2014
	 */

	struct BoundingBoxes {
	private:
		boost::shared_ptr<Configuration> cfg;
		boost::shared_ptr<GameLog> log;

		// Basic data read from .obj file
		vector<float*> *vertices;
		vector<int*> *facesVertexIndexes;

	public:
		BoundingBoxes(const boost::shared_ptr<Configuration> cfg,
			const boost::shared_ptr<GameLog> log);
		~BoundingBoxes();

	};
}

#endif /* BOUNDINGBOXES_H_ */