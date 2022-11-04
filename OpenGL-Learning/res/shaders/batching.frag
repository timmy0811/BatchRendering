#shader fragment
#version 330 core

layout(location = 0) out vec4 o_Color;

in vec4 v_Color;

uniform vec2 u_ImgSize;
uniform float u_Time;

void main()
{
	// vec2 uv = vec2(v_TexCoord.x / u_ImgSize.x, v_TexCoord.y / u_ImgSize);
	o_Color = v_Color;
};