#vertex

#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec4 vertexColor;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;
out vec4 VertexColor;


uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 inverseModel;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1);
	TexCoord = texCoord;
	
	vec4 worlNormal = inverseModel * vec4(normal, 1.0f);
	Normal = normalize(worlNormal.xyz);
	//Normal = normal;
	
	FragPos = vec3(model * vec4(position, 1.0f));
	VertexColor = vertexColor;
};


#fragment

#version 330 core

struct Material
{
	vec3 baseColor;
	vec3 ambientColor;
	float specularValue;
	float shininess;
};

struct Light
{
	vec3 position;
	vec3 direction;
	vec3 baseColor;
	vec3 ambientColor;
	vec4 atten;								// x = constant, y = linear, z = quadratic, w = DistanceCutOff
	vec4 type_innerAngle_outerAngle_w;		// x = lightType, y = inner angle, z = outer angle, w = TBD
											// 0 = pointlight
											// 1 = spot light
											// 2 = directional light
	vec4 param2;							// x = 0 for off, 1 for on
};

out vec4 color;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in vec4 VertexColor;

uniform Material material;

const int POINT_LIGHT_TYPE = 0;
const int SPOT_LIGHT_TYPE = 1;
const int DIRECTIONAL_LIGHT_TYPE = 2;

const int NUMBEROFLIGHTS = 10;

uniform Light[NUMBEROFLIGHTS] lights;

//uniform vec3 ambient_Specular;
//uniform vec3 lightColor;
//uniform vec3 lightPos;

uniform vec3 viewPos;


uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

vec3 CalcDirLight(Light light, vec3 texColor, vec3 ambientColor, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(Light light, vec3 texColor, vec3 ambientColor, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(Light light, vec3 texColor, vec3 ambientColor, vec3 normal, vec3 fragPos, vec3 viewDir);

vec3 CalculateLightContrib(vec3 normal, vec3 fragPos, vec3 viewDir );


void main()
{
	//color = mix(texture(texture_diffuse1, TexCoord), texture(overlayTex, TexCoord), 0f);
	vec3 normalizedNormal = normalize(Normal.xyz);
	vec3 viewDir = normalize(viewPos - FragPos);
	
	vec3 result = CalculateLightContrib(normalizedNormal,FragPos,viewDir);
	
    //color = vec4(specular, 1.0);
	color = vec4(result.xyz , 1.0);
};


vec3 CalculateLightContrib(vec3 normal, vec3 fragPos, vec3 viewDir )
{

	vec3 result = vec3(0.0);
	
	//Tex Color
	vec3 diffuseColor = texture(texture_diffuse1, TexCoord).xyz;
	
	vec3 texColor = diffuseColor * VertexColor.xyz * material.baseColor;
	
	for(int i = 0; i < NUMBEROFLIGHTS; i++)
	{
		if(lights[i].param2.x == 0.0)
		{
			continue; 			//Light is off
		}
		
	
		//Ambient
		vec3 ambientColor = lights[i].ambientColor * material.ambientColor;
		ambientColor *= texColor;
		
		int type = int(lights[i].type_innerAngle_outerAngle_w.x);
		
		if(type == POINT_LIGHT_TYPE)
		{
				result += CalcPointLight(lights[i], texColor, ambientColor, normal,FragPos, viewDir);
		}
		else if(type == SPOT_LIGHT_TYPE)
		{
			result += CalcSpotLight(lights[i], texColor, ambientColor, normal, FragPos, viewDir);
		}
		else if(type == DIRECTIONAL_LIGHT_TYPE)
		{
			result += CalcDirLight(lights[i], texColor, ambientColor, normal, viewDir);
		}
	}
	
	return result;
}

vec3 CalcDirLight(Light light, vec3 texColor, vec3 ambientColor, vec3 normal, vec3 viewDir)
{
	//Diffuse
	
	vec3 lightDir = normalize(- light.direction);
	float diffValue = max(dot(normal,lightDir),0.0);
	
	vec3 diffuse = diffValue * light.baseColor;
	diffuse *= texColor;
	
	//Specular
	vec3 specularColor = texture(texture_specular1, TexCoord).xyz;
	vec3 reflectDir = reflect(-lightDir,normal);
	
	float specularValue = pow(max(dot(reflectDir, viewDir),0.0),material.shininess);
	vec3 specular = specularValue * material.specularValue * light.baseColor * (specularColor.r);
	
	return (ambientColor + diffuse + specular) ;
}


vec3 CalcPointLight(Light light, vec3 texColor, vec3 ambientColor, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	//Attenuation 
	// x = constant, y = linear, z = quadratic, w = DistanceCutOff
	
	float _distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.atten.x + light.atten.y * _distance + light.atten.z * (_distance * _distance));   
	
	//Ambient
	ambientColor *= attenuation;
	
	//Diffuse
	
	vec3 lightDir = normalize(light.position - fragPos);
	float diffValue = max(dot(normal,lightDir),0.0);
	vec3 diffuse = diffValue * light.baseColor;
	diffuse *= texColor * attenuation;
	
	//Specular
	vec3 specularColor = texture(texture_specular1, TexCoord).xyz;
	vec3 reflectDir = reflect(-lightDir,normal);
	
	float specularValue = pow(max(dot(reflectDir, viewDir),0.0),material.shininess);
	vec3 specular = specularValue * material.specularValue * light.baseColor * (specularColor.r);
	specular *= attenuation;
	
	return (ambientColor + diffuse + specular) ;
}


vec3 CalcSpotLight(Light light, vec3 texColor, vec3 ambientColor, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	
	//Attenuation 
	// x = constant, y = linear, z = quadratic, w = DistanceCutOff
	
	vec3 lightDir = normalize(light.position - fragPos);
	
	float _distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.atten.x + light.atten.y * _distance + light.atten.z * (_distance * _distance));   
	
	// spotlight intensity
	float outerConeAngleCos = cos(radians(light.type_innerAngle_outerAngle_w.z));
	float innerConeAngleCos = cos(radians(light.type_innerAngle_outerAngle_w.y));
	
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = innerConeAngleCos - outerConeAngleCos;
    float intensity = clamp((theta - outerConeAngleCos) / epsilon, 0.0, 1.0);
	
	//Ambient
	ambientColor *= attenuation * intensity;
	
	//Diffuse
	
	float diffValue = max(dot(normal,lightDir),0.0);
	vec3 diffuse = diffValue * light.baseColor;
	diffuse *= texColor * attenuation * intensity;
	
	
	//Specular
	vec3 specularColor = texture(texture_specular1, TexCoord).xyz;
	vec3 reflectDir = reflect(-lightDir,normal);
	
	float specularValue = pow(max(dot(reflectDir, viewDir),0.0),material.shininess);
	vec3 specular = specularValue * material.specularValue * light.baseColor * (specularColor.r);
	specular *= attenuation * intensity;
	
	return (ambientColor + diffuse + specular) ;
}