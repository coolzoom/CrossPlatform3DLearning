#version 330

smooth in float cosAngIncidence;
in vec2 textureCoords;
uniform sampler2D textureImage;
uniform vec4 colour;

out vec4 outputColour;

void main()
{
if (colour != vec4(0, 0, 0, 0)) {
    outputColour = cosAngIncidence * 0.8 * colour;
}
else {
  outputColour =  cosAngIncidence * 0.8 * texture(textureImage, textureCoords);
}

}
