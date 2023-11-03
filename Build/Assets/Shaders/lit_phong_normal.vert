#version 430

//input attributes from VBO
in layout(location = 0) vec3 vposition;
in layout(location = 1) vec2 vtexcoord;
in layout(location = 2) vec3 vnormal;
in layout(location = 3) vec3 vtangent;

//output attributes sent to the fragment shader
out layout(location = 0) vec3 oposition;
out layout(location = 1) vec2 otexcoord;
out layout(location = 2) mat3 otbn;

//uniform variables set in World04.cpp
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

//material properties
uniform struct Material{
	uint params;
	vec3 albedo;
	vec3 specular;
	vec3 emissive;
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
	
	//calculate tbn matrix
	vec3 normal = normalize(mat3(modelView) * vnormal);
	vec3 tangent = normalize(mat3(modelView) * vtangent);
	vec3 bitangent = cross(normal, tangent);

	otbn = mat3(tangent, bitangent, normal);

	//makes the model/view/projection matrix for future calculations
	mat4 mvp = projection * view * model;

	otexcoord = vtexcoord;


	//calculates final positions of vertices
	gl_Position = mvp * vec4(vposition, 1.0);
}
