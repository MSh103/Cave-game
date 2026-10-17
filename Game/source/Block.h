#pragma once

#include <Atlas.h>
#include <Atlas/Renderer.h>

struct MeshCPU;

enum class Block : int
{
	Air = 0,
	Grass = 1,
	Dirt = 2,
	Stone = 3,
	DiamondOre = 4,
};

enum class BlockFace : int
{
	Top = 0,
	Bottom = 1,
	Left = 2,
	Right = 3,
	Front = 4,
	Back = 5,
};

MeshCPU getBlockFace(const BlockFace& face, Block block);
