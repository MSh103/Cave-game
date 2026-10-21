#version 460 core

out vec4 FragColor;

flat in float v_Brightness;
in vec2 v_TextureUV;

uniform sampler2D textureAtlas;

void main()
{
    vec4 texColor = texture(textureAtlas, v_TextureUV);
    float brightness = float(v_Brightness) / 255.0;

    FragColor = vec4(texColor.rgb * brightness, texColor.a);
}