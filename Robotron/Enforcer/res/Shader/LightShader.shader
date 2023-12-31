#vertex

#version 330 core

layout(location = 0) in vec3 position;


uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 inverseModel;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1);
};


#fragment

#version 330 core

out vec4 color;

uniform vec3 lightColor;


void main()
{
    color = vec4(lightColor.xyz, 1.0);
};