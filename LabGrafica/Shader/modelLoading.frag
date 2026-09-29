#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform vec4 overrideColor; // Permite teñir o reemplazar el color

void main()
{    
    vec4 texColor = texture(texture_diffuse1, TexCoords);
    if(texColor.a < 0.1)
        discard;
    
    // Si overrideColor tiene valor, lo aplicamos multiplicando o sustituyendo
    if(overrideColor.a > 0.0) {
        FragColor = texColor * overrideColor; 
    } else {
        FragColor = texColor;
    }
}
