#version 450 core

layout(location = 0) out vec4 fragColor;

struct VertexOutput
{
    vec4 color;
    vec2 texCoord;
};

layout (location = 0) in VertexOutput Input;
layout (location = 3) in flat float v_textureSlot;

uniform sampler2D u_Textures[32];

void main()
{
    //   fragColor = Input.color * texture(u_Textures[int(v_textureSlot)], Input.texCoord);
    vec4 color = Input.color;

    switch(int(v_textureSlot))
    {
        case  0: color *= texture(u_Textures[ 0], Input.texCoord); break;
        case  1: color *= texture(u_Textures[ 1], Input.texCoord); break;
        case  2: color *= texture(u_Textures[ 2], Input.texCoord); break;
        case  3: color *= texture(u_Textures[ 3], Input.texCoord); break;
        case  4: color *= texture(u_Textures[ 4], Input.texCoord); break;
        case  5: color *= texture(u_Textures[ 5], Input.texCoord); break;
        case  6: color *= texture(u_Textures[ 6], Input.texCoord); break;
        case  7: color *= texture(u_Textures[ 7], Input.texCoord); break;
        case  8: color *= texture(u_Textures[ 8], Input.texCoord); break;
        case  9: color *= texture(u_Textures[ 9], Input.texCoord); break;
        case 10: color *= texture(u_Textures[10], Input.texCoord); break;
        case 11: color *= texture(u_Textures[11], Input.texCoord); break;
        case 12: color *= texture(u_Textures[12], Input.texCoord); break;
        case 13: color *= texture(u_Textures[13], Input.texCoord); break;
        case 14: color *= texture(u_Textures[14], Input.texCoord); break;
        case 15: color *= texture(u_Textures[15], Input.texCoord); break;
        case 16: color *= texture(u_Textures[16], Input.texCoord); break;
        case 17: color *= texture(u_Textures[17], Input.texCoord); break;
        case 18: color *= texture(u_Textures[18], Input.texCoord); break;
        case 19: color *= texture(u_Textures[19], Input.texCoord); break;
        case 20: color *= texture(u_Textures[20], Input.texCoord); break;
        case 21: color *= texture(u_Textures[21], Input.texCoord); break;
        case 22: color *= texture(u_Textures[22], Input.texCoord); break;
        case 23: color *= texture(u_Textures[23], Input.texCoord); break;
        case 24: color *= texture(u_Textures[24], Input.texCoord); break;
        case 25: color *= texture(u_Textures[25], Input.texCoord); break;
        case 26: color *= texture(u_Textures[26], Input.texCoord); break;
        case 27: color *= texture(u_Textures[27], Input.texCoord); break;
        case 28: color *= texture(u_Textures[28], Input.texCoord); break;
        case 29: color *= texture(u_Textures[29], Input.texCoord); break;
        case 30: color *= texture(u_Textures[30], Input.texCoord); break;
        case 31: color *= texture(u_Textures[31], Input.texCoord); break;
    }

    fragColor = color;
}
