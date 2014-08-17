#version 330

smooth in float cosAngIncidence;
in vec2 textureCoords;

uniform sampler2D textureImage;

out vec4 outputColour;

void main()
{

outputColour =  cosAngIncidence * 0.8 * texture(textureImage, textureCoords);
//outputColour =  cosAngIncidence * 0.8 * texture(textureImage, vec2(0.154297, 0.765625));
}
