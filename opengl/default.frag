#version 330 core
struct Material{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

}
// Outputs colors in RGBA
out vec4 FragColor;

in vec3 vs_position;
// Inputs the color from the Vertex Shader
in vec3 color;
// Inputs the texture coordinates from the Vertex Shader
in vec2 texCoord;
in vec3 normal;
// Gets the Texture Unit from the main function
uniform sampler2D tex0;
uniform vec4 lightColor;
// Gets the position of the light from the main function
uniform vec3 lightPos;
uniform vec3 camPos;
uniform Material material;
void main()
{
	// ambient lighting
	float ambient = materia.ambient;
    vec3 norm=normalize(normal);
	vec3 lightdirection=normalize(lightPos - vs_position);
	float diffuse=max(dot(norm,lightdirection),0)*material.diffuse;
	float specular_light=material.specular;
	// specular lighting
	float specularLight = material.diffuse;
	vec3 viewDirection = normalize(camPos - vs_position);
	vec3 reflectionDirection = reflect(-lightdirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	float specular = specAmount * specularLight;
	FragColor = texture(tex0, texCoord) * (lightColor*(diffuse+ambient+specular));
	//FragColor = texture(tex0, texCoord) * 1);
	

}