#version 330

smooth in vec4 fragColour;
uniform sampler2D texture;

out vec4 outputColour;

void main()
{
outputColour = fragColour;
}
