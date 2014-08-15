#version 330

smooth in float cosAngIncidence;
in vec2 textureCoords;

uniform sampler2D textureImage;

out vec4 outputColour;

void main()
{

outputColour =  cosAngIncidence * 0.8 * texture(textureImage, textureCoords);
}
