#version 430 core

in vec2 texCoord;         

out vec4 finalColor;

uniform vec4 squareColor;

uniform sampler2D texture0;

uniform bool isTexValid;  

void main()  
{

    if (isTexValid)
    {
        vec2 rotatedTexCoord = vec2(1.0 - texCoord.x, 1.0 - texCoord.y);

        vec4 texColor = texture(texture0, rotatedTexCoord);

        finalColor = mix(squareColor, texColor, texColor.a);
    }
    else 
    {
        finalColor = squareColor;
    }
}