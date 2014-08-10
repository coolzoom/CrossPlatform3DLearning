#version 330

smooth in float cosAngIncidence;
in vec2 textureCoords;

uniform sampler2D textureImage;

out vec4 outputColour;

void main()
{

//outputColour =  cosAngIncidence * 0.8 * vec4(1.0, 1.0, 1.0, 1.0);
outputColour = cosAngIncidence * 100 * texture(textureImage, textureCoords);
}
