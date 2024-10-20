#version 430 core

layout(location = 0) in vec2 vertexPosition;

layout(location = 1) in vec2 vertexTexCoord;

out vec2 texCoord; 

uniform mat4 model;
uniform mat4 projection;

void main() 
{
    gl_Position = projection * model * vec4(vertexPosition, 0.0, 1.0);
    texCoord = vertexTexCoord;
}