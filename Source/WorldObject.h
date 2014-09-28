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
    Model* model;
	bool animating;
	int frameDelay;
	int currentFrame;
	int framesWaited;
	int numFrames;
    boost::shared_ptr<Image> texture;
    string name;
    boost::shared_ptr<glm::vec4> colour;
    boost::shared_ptr<glm::vec3> offset;
    boost::shared_ptr<glm::vec3> rotation;

    void initPropVectors();

public:

    /**
     * Constructor for object with texture
     * @param name The name of the object
     * @param modelPath The path to the file containing the object's model
     * @param cfg The game configuration file
     * @param log The game log
	 * @param texturePath The path to the file containing the object's texture. If the object
	 * 					  is animated, it has to be the path up to the name part of the model.
	 * 					  The program will append an underscore, a 6-digit index number and the
	 * 					  .obj suffix for each frame. (e.g. goatAnim will become goatAnim_000001.obj,
	 * 					  goatAnim_000002.obj, etc.)
	 * @param numFrames The number of frames, if the object is animated. A single animation
	 * 					sequence is supported per object and the first frame is considered to
	 * 					be the non-moving state.
     */
    WorldObject(const string &name, const string &modelPath,
                const boost::shared_ptr<Configuration> cfg,
                const boost::shared_ptr<GameLog> log, const int &numFrames = 1, const string &texturePath = "");

    /**
     * Destructor
     */
    virtual ~WorldObject();

    /**
     * Get the object's model
     * @return The object's model
     */
    Model& getModel() const;

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
    const boost::shared_ptr<glm::vec4>& getColour();

    /**
     * Set the object's colour. This will only have an effect if the
     * object is not textured.
     * @param r The red component
     * @param g The green component
     * @param b The blue component
     * @param a The alpha component
     */
    void setColour(const float &r, const float &g, const float &b, const float &a);


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

	/**
	 * Start animating the object
	 */
	void startAnimating();

	/**
	 * Stop animating the object
	 */
	void stopAnimating();

	/**
	 * Reset the animation sequence (go to first frame)
	 */
	void resetAnimation();

	/**
	 * Set the animation speed
	 * @param delay The delay between each animation frame, expressed in number of game frames
	 */
	void setFrameDelay(const int &delay);

	/**
	 * Process animation (progress current frame if necessary)
	 */
	void animate();

};

}
#endif /* WORLDOBJECT_H_ */
