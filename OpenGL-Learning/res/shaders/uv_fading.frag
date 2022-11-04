#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform vec4 u_Color;
uniform vec2 u_ImgSize;
uniform float u_Time;

void main()
{
	// vec2 uv = vec2(v_TexCoord.x / u_ImgSize.x, v_TexCoord.y / u_ImgSize);
	color = vec4(sin(v_TexCoord.x * u_Time) / 2.f + 1, cos(v_TexCoord.y * u_Time) / 2.f + 1, sin(u_Time), 1.f);
};