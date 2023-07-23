#pragma once
#include "../core/BaseGame.h"
#include "../core/Constants.h"
#include "../graphics/Camera.h"

typedef struct VoxelType
{
	glm::vec4 color;
} VoxelType;

extern VoxelType GRASS;

extern VoxelType DIRT;

extern VoxelType STONE;
