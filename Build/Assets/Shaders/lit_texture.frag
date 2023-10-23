#version 430

#define POINT 0 
#define DIRECTIONAL 1
#define SPOT 2


//input attributes from vertex shader
in layout(location = 0) vec3 fposition;
in layout(location = 1) vec3 fnormal;
in layout(location = 2) vec2 ftextcoord;

//outputs color for final drawing
out layout(location = 0) vec4 ocolor;

//the actual texture

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
	int type;
	vec3 position;
	vec3 direction;

	vec3 color;
	float cutoff;
} light;

//ambient light
uniform vec3 ambientLight;

layout(binding = 0) uniform sampler2D tex;

vec3 ads(in vec3 position, in vec3 normal){
	//AMBIENT
	vec3 ambient = ambientLight;

	//DIFFUSE
	vec3 lightDir = (light.type == DIRECTIONAL) ? normalize(-light.direction) : normalize(light.position - fposition);
	float spotIntensity = 1;
	if(light.type == SPOT){
		float angle = acos(dot(light.direction, -lightDir));
		if(angle > light.cutoff) spotIntensity = 0;
	}

	float intensity = max(dot(lightDir, normal), 0);
	vec3 diffuse = material.diffuse * (light.color * intensity * spotIntensity);

	//SPECULAR
	vec3 specular = vec3(0);
	if(intensity > 0){
		vec3 reflectDir = reflect(-lightDir, normal);
		vec3 viewDir = normalize(-fposition);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
		vec3 specular = spec * light.color * material.specular;
	}

	return ambient + diffuse + specular;
}

void main()
{
	//smashing everything together into one result
	vec3 result = ads(light.position, fnormal) * texture(tex, ftextcoord * material.tiling + material.offset).rgb;

	//final color :))
	ocolor = vec4(result, 1.0);
}

