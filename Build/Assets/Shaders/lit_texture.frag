#version 430

//input attributes from vertex shader
in layout(location = 0) vec3 fposition;
in layout(location = 1) vec3 fnormal;
in layout(location = 2) vec2 ftextcoord;

//outputs color for final drawing
out layout(location = 0) vec4 ocolor;

//the actual texture
layout(binding = 0) uniform sampler2D tex;

//material properties
uniform struct Material{
	vec3 diffuse;
	vec3 specular;
	float shininess;
	vec2 offset;
	vec2 tiling;
} material;

//light properties
uniform struct Light{
	vec3 position;
	vec3 color;
} light;

//ambient light
uniform vec3 ambientLight;

void main()
{
//ambient lighting - computes the color of each fragment with ambient lighting applied
	vec3 ambient = ambientLight * material.diffuse;

//diffuse lighting
	//normalizing the fnormal just in case
	vec3 normal = normalize(fnormal);
	//calculates light direction
	vec3 lightDir = normalize(light.position - fposition);
	//calculates intensity of diffuse light, and makes sure it's at least 0
	float diff = max(dot(normal, lightDir), 0.0);
	//calculates the diffuse color based on the intensity and the material
	vec3 diffuse = diff * light.color * material.diffuse;

//specular lighting
	//calculates the view direction
	vec3 viewDir = normalize(-fposition);
	//calculates where the light would go after reflecting off the material
	vec3 reflectDir = reflect(-lightDir, normal);
	//finds the angle between the view direction and the light direction, then makes sure it's at least 0, then raises it to the power of the material's shininess
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	//calculates the specular color based on the intensity and the material
	vec3 specular = spec * light.color * material.specular;

	//smashing everything together into one result
	vec3 result = (ambient + diffuse + specular) * texture(tex, ftextcoord * material.tiling + material.offset).rgb;

	//final color :))
	ocolor = vec4(result, 1.0);

}
