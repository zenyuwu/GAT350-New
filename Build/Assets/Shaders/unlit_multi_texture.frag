#version 430

in layout(location = 1) vec2 textcoord;

out layout(location = 0) vec4 ocolor;

uniform vec4 color;
uniform vec2 offset;
uniform vec2 tiling;
layout(binding = 0) uniform sampler2D tex1;
layout(binding = 1) uniform sampler2D tex2;

void main()
{
	vec4 texcolor1 = texture(tex1, (textcoord * tiling) + offset);
	vec4 texcolor2 = texture(tex2, (textcoord * tiling) + offset);

	vec4 texcolor = mix(texcolor1, texcolor2, 0.5);

	ocolor = texcolor * color;
}
