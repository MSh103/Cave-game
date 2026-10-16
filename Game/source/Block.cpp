#include "Block.h"

#include "Mesh.h"

static 



MeshCPU getBlockFace(const BlockFace& face)
{
	switch (face)
	{
	case BlockFace::Front:
		return {
			{
				{{ 0.5f, 0.5f, 0.5f }, { 0.1f, 0.8f, 0.1f }}, // FTR
				{{ 0.5f,-0.5f, 0.5f }, { 0.1f, 0.8f, 0.1f }}, // FBR
				{{-0.5f,-0.5f, 0.5f }, { 0.1f, 0.8f, 0.1f }}, // FBL
				{{-0.5f, 0.5f, 0.5f }, { 0.1f, 0.8f, 0.1f }}, // FTL
			},
			{
				///   TR->BR->BL      BL->TL->TR 
					0, 1, 2,	2, 3, 0
			}
		}; break;
	}

	return {};
}