#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;

smooth out vec4 fragColour;

uniform uint multiColourBool;
uniform vec3 offset;
uniform mat4 perspectiveMatrix;

uniform mat4 xRotationMatrix;
uniform mat4 yRotationMatrix;
uniform mat4 zRotationMatrix;

uniform vec3 lightDirection;

void main()
{
    vec4 cameraPos = position * xRotationMatrix 
			* yRotationMatrix
			* zRotationMatrix
			+ vec4(offset.x, offset.y, offset.z, 0.0);
    
    gl_Position = perspectiveMatrix * cameraPos;

    vec4 normalCameraSpace = normalize(perspectiveMatrix * vec4(normal, 1));
    
    vec4 lightDirectionCameraSpace = perspectiveMatrix * vec4(lightDirection, 1);

    float cosAngIncidence = clamp(dot(normalCameraSpace, lightDirectionCameraSpace), 0, 1);

    fragColour = cosAngIncidence * vec4(1.0, 1.0, 1.0, 1.0);
}
