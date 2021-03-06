#version 460 core

in vec2 TexCoords;
out vec4 color; 

uniform sampler2D image;
uniform vec3 spriteColour; 

void main()
{
    color = vec4(spriteColour, 1.0) * texture(image, TexCoords);
}