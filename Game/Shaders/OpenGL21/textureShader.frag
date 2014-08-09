#version 120

smooth in float cosAngIncidence;

uniform sampler2D textureImage;

out vec4 outputColour;

void main()
{

//outputColour =  cosAngIncidence * 0.8 * vec4(1.0, 1.0, 1.0, 1.0);
outputColour = texture(textureImage, vec2(0.2, 0.2));
}
