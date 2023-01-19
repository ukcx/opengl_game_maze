#version 330 core
struct Material
{
    float ambient;
    float diffuse;
    float specular;

};
// Outputs colors in RGBA
out vec4 FragColor;

in vec3 vs_position;
// Inputs the color from the Vertex Shader
in vec3 normal;
// Inputs the texture coordinates from the Vertex Shader
in vec2 texCoord;
in vec3 color;
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
    float ambient = material.ambient;
    vec3 norm=normalize(normal);
    vec3 lightdirection=normalize(lightPos - vs_position);
    float diffuse=max(dot(norm,lightdirection),0)*material.diffuse;
    float specular_light=0.50f;
    // specular lighting
    float specularLight = material.specular;
    vec3 viewDirection = normalize(camPos - vs_position);
    vec3 reflectionDirection = reflect(-lightdirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
    float specular = specAmount *specularLight;
    vec4 green = vec4(0.0, 1.0, 0.0, 1.0);
    vec4 myColor4 = vec4(color, 1.0);
    FragColor = myColor4 * (lightColor*(diffuse+specular+ambient));
}