#ifndef GLOBALS_H_
#define GLOBALS_H_

#include "../GameLog.h"
#include "../Configuration.h"
#include <boost/smart_ptr.hpp>

using namespace AvoidTheBug3D;

typedef struct Globals {
	boost::shared_ptr<GameLog> log;
	boost::shared_ptr<Configuration> cfg;
} Globals;

extern Globals *globals;

#endif