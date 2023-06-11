#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in float type;
uniform sampler2D texture1;
in vec3 pos;

void main()
{
	if (type == 1.0f){
		if (TexCoord.y == 1.0f / 456.0f){
			FragColor = vec4(1.0f,0.f,0.f,1.0f);
			//return;
		}
		FragColor = texture(texture1, TexCoord);
		return;
	}
	FragColor = vec4(0.5,0.f,0.5,1.0f);
	
}