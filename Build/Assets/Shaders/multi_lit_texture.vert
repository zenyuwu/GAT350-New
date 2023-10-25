#version 430

//input attributes from VBO
in layout(location = 0) vec3 vposition;
in layout(location = 1) vec2 vtexcoord;
in layout(location = 2) vec3 vnormal;

//output attributes sent to the fragment shader
out layout(location = 0) vec3 oposition;
out layout(location = 1) vec3 onormal;
out layout(location = 2) vec2 otexcoord;

//uniform variables set in World04.cpp
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

//material properties
uniform struct Material{
	vec3 diffuse;
	vec3 specular;
	float shininess;

	vec2 offset;
	vec2 tiling;
} material;

void main()
{
	//combines model and view for future calculations
	mat4 modelView = view * model;

	//converts position and normal to world-view space
	oposition = vec3(modelView * vec4(vposition, 1));
	//puts vnormal in world-view space then normalizes it
	onormal = normalize(mat3(modelView) * vnormal);
	//modifies the texture coordinates based on tiling and offset
	otexcoord = (vtexcoord * material.tiling) + material.offset;

	//makes the model/view/projection matrix for future calculations
	mat4 mvp = projection * view * model;

	//calculates final positions of vertices
	gl_Position = mvp * vec4(vposition, 1.0);
}
