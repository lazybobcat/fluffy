#version 330 core
in vec2 texCoord;
in vec4 spriteColor;

uniform sampler2D u_Texture;

out vec4 fragColor;

void main()
{
   fragColor = texture(u_Texture, texCoord) * spriteColor;
//    fragColor = vec4(texCoord.x, texCoord.y, 0.f, 1.f);
}
