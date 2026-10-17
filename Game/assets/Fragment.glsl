#version 460 core

out vec4 FragColor;

in vec3 v_Color;
in vec2 v_TextureUV;

uniform sampler2D textureAtlas;

void main()
{
    FragColor = texture(textureAtlas, v_TextureUV) * vec4(v_Color, 1.0);
}