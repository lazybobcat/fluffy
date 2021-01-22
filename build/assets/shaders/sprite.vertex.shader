#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec4 aColor;
layout (location = 3) in float aTexSlot;

uniform mat4 u_ViewProjection;

out vec2 texCoord;
out vec4 spriteColor;
out float texSlot;

void main()
{
    texCoord = aTexCoord;
    texSlot = aTexSlot;
    spriteColor = aColor;
    gl_Position = u_ViewProjection * vec4(aPos, 1.0);
}
