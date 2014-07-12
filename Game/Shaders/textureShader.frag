#version 330

smooth in vec4 fragColour;
uniform sampler2D textureImage;

out vec4 outputColour;

void main()
{
vec2 coord = vec2(236, 982);
outputColour = texture(textureImage, coord); //vec4(200, 200, 200, 0);
}
