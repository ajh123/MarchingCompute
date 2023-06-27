#version 460 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec4 objectColor;

uniform struct DirLight {
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
} dirLight;

// uniform vec3 objectColor;

void main()
{
	float diffuse = max(dot(normalize(Normal), -dirLight.direction), 0.0);
	FragColor = vec4((dirLight.ambient + dirLight.diffuse * diffuse), 1.0) * objectColor;
}
