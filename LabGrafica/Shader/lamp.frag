#version 330 core
out vec4 outColor;
  
in vec3 Color;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    // Carga la textura sin aplicar descarte por alpha
    outColor = texture(ourTexture, TexCoord);
}