#ifndef BOUNDINGBOXES_H_
#define BOUNDINGBOXES_H_

#include <boost/smart_ptr.hpp>
#include "Configuration.h"
#include "GameLog.h"


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
	public:
		BoundingBoxes(const boost::shared_ptr<Configuration> cfg,
			const boost::shared_ptr<GameLog> log);
		~BoundingBoxes();

	};
}

#endif /* BOUNDINGBOXES_H_ */