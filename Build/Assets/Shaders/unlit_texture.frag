#version 430

in layout(location = 0) vec3 color;
in layout(location = 1) vec2 textcoord;

out layout(location = 0) vec4 ocolor;

//uniform float time;

uniform vec2 offset;
uniform vec2 tiling;
layout(binding = 0) uniform sampler2D tex;

void main()
{
	//vec3 ncolor = vec3(color.r * (sin(time) + 1) * 0.5, color.g, color.b);
	//vec3 ncolor = vec3((color.r + color.g + color.b)/3);

	vec3 texcolor = texture(tex, (textcoord * tiling) + offset).rgb;

	ocolor = vec4(texcolor, 1);
}
