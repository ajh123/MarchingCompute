#pragma once

#include "terrain/VoxelTerrain.h"

VoxelType GRASS = {
	glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)
};

VoxelType DIRT = {
	glm::vec4(1.0f, 0.65f, 0.0f, 1.0f)
};

VoxelType STONE = {
	glm::vec4(0.65f, 0.65f, 0.65f, 1.0f)
};