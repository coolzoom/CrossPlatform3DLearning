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

    vec4 lightDirectionCameraSpace = perspectiveMatrix * vec4(lightDirection, 1.0);
    
    vec4 normalCameraSpace = normalize(perspectiveMatrix * vec4(normal, 1.0));

    fragColour = dot(vec3(normalCameraSpace.x, normalCameraSpace.y, normalCameraSpace.z), vec3(lightDirectionCameraSpace.x, lightDirectionCameraSpace.y, lightDirectionCameraSpace.z)) * vec4(1.0, 1.0, 1.0, 1.0);
}
