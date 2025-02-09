#version 460 core

layout (std140, binding = 0) uniform ViewProjection
{
	mat4 view;
	mat4 projection;
};

struct Triangle
{
	vec4 points[3];
	vec4 normals[3];
	uint idx;
};

layout(std430, binding = 4) buffer TriangleBuffer
{
	Triangle triangles[];
};

layout(std430, binding = 9) readonly buffer ColorBuffer
{
	vec4 colors[];
};

out vec3 FragPos;
out vec3 Normal;
out vec4 objectColor;

uniform mat4 model = mat4(1.0f);

uniform mat3 normalMat;

void main()
{
	Triangle tri = triangles[gl_VertexID / 3];
	vec4 pos = tri.points[gl_VertexID % 3];
	vec4 normal = tri.normals[gl_VertexID % 3];
	
	FragPos = vec3(model * pos);
	Normal = mat3(transpose(inverse(model))) * normal.xyz;
	objectColor = colors[tri.idx];
	
	gl_Position = projection * view * vec4(FragPos, 1.0);
}
