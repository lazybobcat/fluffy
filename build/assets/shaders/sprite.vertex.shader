#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;
uniform vec4 u_Color;

out vec2 texCoord;

void main()
{
    texCoord = aTexCoord;
    gl_Position = u_ViewProjection * u_Transform * vec4(aPos, 1.0); // see how we directly give a vec3 to vec4's constructor
}
