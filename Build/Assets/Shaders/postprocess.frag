#version 430

#define INVERT_MASK		(1 << 0)
#define GRAYSCALE_MASK	(1 << 1)
#define COLORTINT_MASK	(1 << 2)
#define GRAIN_MASK		(1 << 3)
#define SCANLINE_MASK	(1 << 4)
#define RAINBOW_MASK	(1 << 5)

in layout(location = 0) vec2 ftexcoord;

out layout(location = 0) vec4 ocolor;

uniform float blend = 1;
uniform uint params = 0;
uniform vec4 colortintcolor;
uniform vec2 resolution;

uniform float time;

layout(binding = 0) uniform sampler2D screenTexture;

vec4 invert(in vec4 color){
	return vec4(vec3(1)-color.rgb, color.a);
}

vec4 grayscale(in vec4 color){
	return vec4(vec3(0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b), color.a);
}

vec4 colortint(in vec4 color, in vec4 tint){
	tint.a = 0.1;
    return vec4(mix(color.rgb, tint.rgb, tint.a), color.a);
}

float rand(vec2 co){
	return fract(sin(dot(co.xy, vec2(12.9898,78.233))) * 43758.5453);
}

vec4 grain(in vec4 color){
	float noise = rand(ftexcoord * time);
	vec4 grain = vec4(vec3(noise),1.0);
	return mix(color, grain, 0.1);
}

vec4 scanline(in vec4 color){
	float pos = gl_FragCoord.y / resolution.y;
	float scanline = sin(pos * resolution.y * 0.1 + time) * 0.2 + 0.8;
	color.rgb *= scanline;
	return color;
}

vec4 rainbow(in vec4 color){
	vec2 uv = gl_FragCoord.xy / resolution.xy; 

	vec3 colors[6];
    colors[0] = vec3(0.9, 0.0, 0.0); // Red
    colors[1] = vec3(0.9, 0.4, 0.0); // Orange
    colors[2] = vec3(0.9, 0.9, 0.0); // Yellow
    colors[3] = vec3(0.0, 0.9, 0.0); // Green
    colors[4] = vec3(0.0, 0.0, 0.9); // Blue
    colors[5] = vec3(0.4, 0.0, 0.4); // Purple

	float wavy = sin(uv.x * 6.28318 + time) * cos(uv.y * 6.28318 + time);
    int index = int(mod(uv.x * 6.0 + wavy * 4.0, 6.0));

    vec3 rainbowColor = colors[index];

    return mix(color, vec4(rainbowColor, 1.0), 0.1);
}


void main()
{
	vec4 basecolor = texture(screenTexture, ftexcoord);
	vec4 postprocess = basecolor;

	if (bool(params & INVERT_MASK)) postprocess = invert(postprocess);
	if (bool(params & GRAYSCALE_MASK)) postprocess = grayscale(postprocess);
	if (bool(params & COLORTINT_MASK)) postprocess = colortint(postprocess, colortintcolor);
	if (bool(params & GRAIN_MASK)) postprocess = grain(postprocess);
	if (bool(params & SCANLINE_MASK)) postprocess = scanline(postprocess);
	if (bool(params & RAINBOW_MASK)) postprocess = rainbow(postprocess);

	ocolor = mix(basecolor, postprocess, blend);
}
