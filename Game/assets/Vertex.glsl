#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TextureUV;
layout(location = 2) in float a_Brightness;

flat out float v_Brightness;
out vec2 v_TextureUV;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
	gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1.0f);
	v_Brightness = a_Brightness;
	v_TextureUV = a_TextureUV;
}
