#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in float Atype;

out vec2 TexCoord;
out float type;

uniform mat4 view;
uniform mat4 projection;
uniform vec2 change;


void main()
{
    vec3 pos = aPos;
    type = Atype;
    if (type == 1.0f){
        gl_Position = projection * view * vec4(pos, 1.0f);
        if (aTexCoord.y == 1.0f / 456.0f){
            TexCoord = vec2(aTexCoord.x,aTexCoord.y);
            return;
        }
        TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
        return;
    }
    pos *= change;
    gl_Position = vec4(pos.x,pos.y,-1, 1.0f);
    
}