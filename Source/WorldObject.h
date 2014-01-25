/*
 * WorldObject.h
 *
 *  Created on: Dec 26, 2013
 *      Author: Dimitri Kourkoulis
 */

#ifndef WORLDOBJECT_H_
#define WORLDOBJECT_H_

#include <vector>
#include "Model.h"
#include <boost/smart_ptr.hpp>
#include "GameLog.h"
#include "Configuration.h"

using namespace std;

namespace AvoidTheBug3D {
/**
 * A world object
 */
class WorldObject {
private:
	boost::shared_ptr<GameLog> log;
	boost::shared_ptr<Configuration> cfg;
	vector<float> location;
	vector<float> orientation;
	boost::shared_ptr<Model> model;
	string name;
public:
	/**
	 * Default constructor
	 */
	WorldObject(string name, string modelPath, boost::shared_ptr<Configuration> cfg,
			boost::shared_ptr<GameLog> log);

	/**
	 * Destructor
	 */
	virtual ~WorldObject();

	const vector<float>& getLocation() const;

	void setLocation(const float &x, const float &y, const float &z);

	const boost::shared_ptr<Model>& getModel() const;

	void setModel(const boost::shared_ptr<Model>& model);

	const vector<float>& getOrientation() const;

	void setOrientation(const float &x, const float &y, const float &z);
};

}
#endif /* WORLDOBJECT_H_ */
