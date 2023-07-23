#pragma once

#include <functional>
#include "core/BaseGame.h"
#include "core/Constants.h"
#include "graphics/Camera.h"
#include "VoxelType.h"

#define VOXEL_COMPUTE_LOCAL_SIZE 10

#define CHUNK_SIZE 100

struct MarchingCubesConfig
{
	using DensityFunc = std::function<float(glm::vec3)>;
	using TypeFunc = std::function<VoxelType(glm::vec3)>;

	glm::ivec3 size{100};
	float scale = 1.0f;
	float isoValue = 0.0f;
	DensityFunc densityFunc;
	TypeFunc typeFunc;
};

class VoxelMesh
{
	glm::ivec3 position;

	struct Triangle
	{
		glm::vec4 points[3];
		glm::vec4 normals[3];
		unsigned int idx;
	};

	struct DrawArraysIndirectCommand
	{
		unsigned int count;
		unsigned int instanceCount;
		unsigned int first;
		unsigned int baseInstance;
	};

	// TODO: use glBufferStorage for SSBOs (maybe by inheriting from Buffer?)
	using TriangleBuffer = Buffer<GL_SHADER_STORAGE_BUFFER, Triangle, GL_DYNAMIC_COPY>;
	using FloatBuffer = Buffer<GL_SHADER_STORAGE_BUFFER, float, GL_DYNAMIC_DRAW>;
	using ColorBuffer = Buffer<GL_SHADER_STORAGE_BUFFER, glm::vec4, GL_DYNAMIC_DRAW>;
	using AtomicCounter = Buffer<GL_ATOMIC_COUNTER_BUFFER, unsigned, GL_DYNAMIC_DRAW>;
	using TriLUTBuffer = Buffer<GL_SHADER_STORAGE_BUFFER, int[16], GL_STATIC_DRAW>;
	using IndirectBuffer =
		Buffer<GL_DRAW_INDIRECT_BUFFER, DrawArraysIndirectCommand, GL_DYNAMIC_COPY>;

	TriangleBuffer m_TriangleBuffer;
	AtomicCounter m_AtomicCounter;
	FloatBuffer m_DensityBuffer;
	ColorBuffer m_ColorBuffer;
	TriLUTBuffer m_TriLUTBuffer;
	IndirectBuffer m_IndirectBuffer;

	Shader m_VoxelCompute;
	Shader m_IndirectCounter;
	std::shared_ptr<Material> m_Material;

	float m_Scale;

public:
	VoxelMesh(MarchingCubesConfig mcConfig, glm::ivec3 chunkPosition);

	void Regenerate(MarchingCubesConfig mcConfig);

	void Draw();

	inline std::shared_ptr<Material> GetMaterial() const { return m_Material; }
};
