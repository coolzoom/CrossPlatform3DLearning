#version 330

smooth in float cosAngIncidence;

uniform sampler2D textureImage;

out vec4 outputColour;

void main()
{

//outputColour =  cosAngIncidence * 0.8 * vec4(1.0, 1.0, 1.0, 1.0);
outputColour = texture(textureImage, vec2(243, 1001));
}
