#version 430

in layout(location = 0) vec3 position;
in layout(location = 1) vec3 color;
in layout(location = 2) vec2 textcoord;

out layout(location = 0) vec3 ocolor;
out layout(location = 1) vec3 otextcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
//uniform float time;

void main()
{
	ocolor = color;
	mat4 mvp = projection * view * model;

	//float xo = sin(time * 3 + position.y) * 0.5;

	//gl_Position = vec4(position + vec3(xo,0,0), 1.0);
	gl_Position = mvp * vec4(position, 1.0);
}
