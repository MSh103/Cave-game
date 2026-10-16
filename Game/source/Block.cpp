#include "Block.h"

#include "Mesh.h"

MeshCPU getBlockFace(const BlockFace& face)
{
	switch (face)
	{
	case BlockFace::Front:
		return {
			{
				{{-0.5f, 0.5f, 0.5f }, { 0.14f, 0.84f, 0.14f }}, // FTL
				{{-0.5f,-0.5f, 0.5f }, { 0.14f, 0.84f, 0.14f }}, // FBL
				{{ 0.5f,-0.5f, 0.5f }, { 0.14f, 0.84f, 0.14f }}, // FBR
				{{ 0.5f, 0.5f, 0.5f }, { 0.14f, 0.84f, 0.14f }}, // FTR
			},
			{
				///   TR->BR->BL      BL->TL->TR 
					0, 1, 2,	2, 3, 0
			}
		}; break;

	case BlockFace::Top:
		return {
			{
				{{ 0.5f, 0.5f, 0.5f }, { 0.15f, 0.85f, 0.15f }}, // TTR
				{{ 0.5f, 0.5f,-0.5f }, { 0.15f, 0.85f, 0.15f }}, // TBR
				{{-0.5f, 0.5f,-0.5f }, { 0.15f, 0.85f, 0.15f }}, // TBL
				{{-0.5f, 0.5f, 0.5f }, { 0.15f, 0.85f, 0.15f }}, // TTL
			},
			{
				///   TR->BR->BL      BL->TL->TR 
					0, 1, 2,	2, 3, 0
			}
		}; break;

	case BlockFace::Back:
		return {
			{
				{{ 0.5f, 0.5f,-0.5f }, { 0.05f, 0.75f, 0.05f }}, // BTR
				{{ 0.5f,-0.5f,-0.5f }, { 0.05f, 0.75f, 0.05f }}, // BBR
				{{-0.5f,-0.5f,-0.5f }, { 0.05f, 0.75f, 0.05f }}, // BBL
				{{-0.5f, 0.5f,-0.5f }, { 0.05f, 0.75f, 0.05f }}, // BTL
			},
			{
				///   TR->BR->BL      BL->TL->TR 
					0, 1, 2,	2, 3, 0
			}
		}; break;

	case BlockFace::Bottom:
		return {
			{
				{{-0.5f,-0.5f, 0.5f }, { 0.02f, 0.72f, 0.02f }}, // TTL
				{{-0.5f,-0.5f,-0.5f }, { 0.02f, 0.72f, 0.02f }}, // TBL
				{{ 0.5f,-0.5f,-0.5f }, { 0.02f, 0.72f, 0.02f }}, // TBR
				{{ 0.5f,-0.5f, 0.5f }, { 0.02f, 0.72f, 0.02f }}, // TTR
			},
			{
				///   TR->BR->BL      BL->TL->TR 
					0, 1, 2,	2, 3, 0
			}
		}; break;

	case BlockFace::Left:
		return {
			{
				{{-0.5f, 0.5f,-0.5f }, { 0.1f, 0.8f, 0.1f }}, // TTL
				{{-0.5f,-0.5f,-0.5f }, { 0.1f, 0.8f, 0.1f }}, // TBL
				{{-0.5f,-0.5f, 0.5f }, { 0.1f, 0.8f, 0.1f }}, // TBR
				{{-0.5f, 0.5f, 0.5f }, { 0.1f, 0.8f, 0.1f }}, // TTR
			},
			{
				///   TR->BR->BL      BL->TL->TR 
					0, 1, 2,	2, 3, 0
			}
		}; break;

	case BlockFace::Right:
		return {
			{
				{{ 0.5f, 0.5f, 0.5f }, { 0.13f, 0.83f, 0.13f }}, // TTR
				{{ 0.5f,-0.5f, 0.5f }, { 0.13f, 0.83f, 0.13f }}, // TBR
				{{ 0.5f,-0.5f,-0.5f }, { 0.13f, 0.83f, 0.13f }}, // TBL
				{{ 0.5f, 0.5f,-0.5f }, { 0.13f, 0.83f, 0.13f }}, // TTL
			},
			{
				///   TR->BR->BL      BL->TL->TR 
					0, 1, 2,	2, 3, 0
			}
		}; break;

	}


	return {};
}