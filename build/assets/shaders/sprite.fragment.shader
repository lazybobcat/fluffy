#version 330 core
in vec2 texCoord;
in vec4 spriteColor;
in float texSlot;

uniform sampler2D u_Textures[32];

out vec4 fragColor;

void main()
{
   fragColor = spriteColor * texture(u_Textures[int(texSlot)], texCoord);
}
