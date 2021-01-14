#version 330 core
out vec4 fragColor;

in vec2 texCoord;
in vec4 spriteColor;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
   fragColor = texture(u_Texture, texCoord) * u_Color;
//    fragColor = vec4(texCoord.x, texCoord.y, 0.f, 1.f);
}
