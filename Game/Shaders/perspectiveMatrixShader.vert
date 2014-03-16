#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 colour;

smooth out vec4 fragColour;

uniform vec3 offset;
uniform mat4 perspectiveMatrix;

uniform mat4 xRotationMatrix;
uniform mat4 yRotationMatrix;
uniform mat4 zRotationMatrix;

void main()
{
    vec4 cameraPos = position * xRotationMatrix 
			* yRotationMatrix
			* zRotationMatrix
			+ vec4(offset.x, offset.y, offset.z, 0.0);
    
    gl_Position = perspectiveMatrix * cameraPos;

    fragColour = colour;
}
