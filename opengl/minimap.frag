#version 330 core

in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D mapTexture;
uniform vec2 mapSize;
uniform vec2 minimapSize;
uniform vec2 minimapPosition;
uniform vec2 playerPosition;

void main()
{
    // Calculate the world position of the current fragment
    vec2 minimapWorldPos = vec2(TexCoords.x * minimapSize.x, TexCoords.y * minimapSize.y) + minimapPosition;

    // Shift the world position so that the player is at the center of the minimap
    minimapWorldPos -= playerPosition;

    // Clamp the world position to the bounds of the map
    minimapWorldPos = clamp(minimapWorldPos, vec2(0.0, 0.0), mapSize);

    // Convert the world position to texture coordinates
    vec2 texCoords = minimapWorldPos / mapSize;

    // Sample the map texture using the calculated texture coordinates
    //FragColor = texture(mapTexture, texCoords);
    FragColor = vec4(0.5,1.0,0.5,1.0);

}