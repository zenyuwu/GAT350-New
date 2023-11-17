#version 430

in layout(location = 1) vec2 ftexcoord;

out layout(location = 0) vec4 ocolor;

uniform struct Material{
	vec3 albedo;

	vec2 offset;
	vec2 tiling;
} material;

layout(binding = 0) uniform sampler2D tex;

void main()
{
	vec4 texcolor = texture(tex, ftexcoord);

	if(texcolor.a < 0.5) discard;
	ocolor = texcolor * vec4(material.albedo, 1);
}
