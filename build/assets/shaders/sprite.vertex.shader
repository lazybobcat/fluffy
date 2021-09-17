#version 450 core

layout (location = 0) in vec3 a_vertexPosition;
layout (location = 1) in vec2 a_textureCoord;
layout (location = 2) in vec4 a_color;
layout (location = 3) in float a_textureSlot;

uniform mat4 u_ViewProjection;

struct VertexOutput
{
    vec4 color;
    vec2 texCoord;
};

layout (location = 0) out VertexOutput Output;
layout (location = 3) out flat float v_textureSlot;

void main()
{
    Output.color = a_color;
    Output.texCoord = a_textureCoord;
    v_textureSlot = a_textureSlot;

    gl_Position = u_ViewProjection * vec4(a_vertexPosition, 1.0);
}
