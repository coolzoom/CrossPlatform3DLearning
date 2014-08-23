#version 120

varying float cosAngIncidence;
varying vec2 textureCoords;
uniform sampler2D textureImage;

void main()
{

gl_FragColor = cosAngIncidence * 0.8 * texture2D(textureImage, textureCoords);

}
