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
#include "Image.h"
#include <glm/glm.hpp>

using namespace std;

namespace AvoidTheBug3D
{
/**
 * A world object
 */
class WorldObject
{
private:
    boost::shared_ptr<GameLog> log;
    boost::shared_ptr<Configuration> cfg;
    boost::shared_ptr<Model> model;
    boost::shared_ptr<Image> texture;
    string name;
    boost::shared_ptr<glm::vec3> colour;
    boost::shared_ptr<glm::vec3> offset;
    boost::shared_ptr<glm::vec3> rotation;

    void initPropVectors();

public:

    /**
     * Constructor for object without texture
     * @param name The name of the object
     * @param modelPath The path to the file containing the object's model
     * @param cfg The game configuration file
     * @param log The game log
     */
    WorldObject(string name, string modelPath,
                boost::shared_ptr<Configuration> cfg,
                boost::shared_ptr<GameLog> log);

    /**
     * Constructor for object with texture
     * @param name The name of the object
     * @param modelPath The path to the file containing the object's model
     * @param texturePath The path to the file containing the object's texture
     * @param cfg The game configuration file
     * @param log The game log
     */
    WorldObject(string name, string modelPath, string texturePath,
                boost::shared_ptr<Configuration> cfg,
                boost::shared_ptr<GameLog> log);

    /**
     * Destructor
     */
    virtual ~WorldObject();

    /**
     * Get the object's model
     * @return The object's model
     */
    const boost::shared_ptr<Model>& getModel() const;

    /**
     * Get the object's texture
     * @return The object's texture
     */
    const boost::shared_ptr<Image>& getTexture() const;

    /**
    /* Get the name of the object
    */
    const string getName();

    /**
    * Get the object's colour.
    * @return The object's colour.
    */
    const boost::shared_ptr<glm::vec3>& getColour();

    /**
     * Set the object's colour. This will only have an effect if the
     * object is not textured.
     * @param r The red component
     * @param g The green component
     * @param b The blue component
     */
    void setColour(const float &r, const float &g, const float &b);


    /**
     * Get the offset of the object's position
     * @return The offset
     */
    const boost::shared_ptr<glm::vec3>& getOffset() const;

    /**
     * Set the offset of the object's position
     * @param x The offset's x coordinate
     * @param y The offset's y coordinate
     * @param z The offset's z coordinate
     */
    void setOffset(const float &x, const float &y, const float &z);

    /**
     * Get the object's rotation
     * @return
     */
     const boost::shared_ptr<glm::vec3>& getRotation() const;

    /**
     * Set the object's rotation
     * @param x The orientation's x rotation
     * @param y The orientation's y rotation
     * @param z The orientation's z rotation
     */
    void setRotation(const float &x, const float &y, const float &z);

};

}
#endif /* WORLDOBJECT_H_ */
