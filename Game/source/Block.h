#pragma once

#include <Atlas.h>
#include <Atlas/Renderer.h>

struct MeshCPU;

enum class Block : int
{
	Air = 0,
	Grass = 1,
};

enum class BlockFace : int
{
	Top,
	Bottom,
	Left,
	Right,
	Front,
	Back,
};

MeshCPU getBlockFace(const BlockFace& face);
