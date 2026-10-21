#include "Block.h"

#include "Mesh.h"

#include <array>
//
//std::array<glm::vec3, 6> getBlockColors(const Block& block)
//{
//	switch (block)
//	{
//	case Block::Grass:
//		return {
//			glm::vec3(0.17f, 0.87f, 0.17f),
//			glm::vec3(0.65f, 0.60f, 0.25f),
//			glm::vec3(0.68f, 0.63f, 0.28f),
//			glm::vec3(0.70f, 0.65f, 0.30f),
//			glm::vec3(0.75f, 0.70f, 0.35f),
//			glm::vec3(0.60f, 0.55f, 0.20f),
//		};
//		break;
//	case Block::Dirt:
//		return {
//			glm::vec3(0.72f, 0.67f, 0.32f),
//			glm::vec3(0.65f, 0.60f, 0.25f),
//			glm::vec3(0.68f, 0.63f, 0.28f),
//			glm::vec3(0.70f, 0.65f, 0.30f),
//			glm::vec3(0.75f, 0.70f, 0.35f),
//			glm::vec3(0.60f, 0.55f, 0.20f),
//		};
//		break;
//	}
//
//
//	return { glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.f) };
//}

std::array<glm::vec2, 2> getAtlasUV(int x, int y)
{
	constexpr float atlasSize = 256.f;
	constexpr float tileSize = 16.f;

	float u0 = x * tileSize / atlasSize;
	float v0 = y * tileSize / atlasSize;
	float u1 = u0 + tileSize / atlasSize;
	float v1 = v0 + tileSize / atlasSize;

	return { glm::vec2(u0, v0), glm::vec2(u1, v1) };
}

std::array<glm::vec2, 2> getAtlasTile(Block block, BlockFace face)
{
	switch (block)
	{
	case Block::Grass:
		if (face == BlockFace::Top)
			return getAtlasUV(0, 0);
		else if(face == BlockFace::Bottom)
			return getAtlasUV(2, 0);
		return getAtlasUV(3, 0);
		break;

	case Block::Dirt:
		return getAtlasUV(2, 0);
		break;

	case Block::Stone:
		return getAtlasUV(1, 0);
		break;
	

	case Block::DiamondOre:
		return getAtlasUV(2, 3);
		break;
	}


	return { glm::vec2(0.f), glm::vec2(0.f) };
}

//
//MeshCPU getBlockFace(const BlockFace& face, Block block)
//{
//	switch (face)
//	{
//		case BlockFace::Front:
//		{
//			auto [uvMin, uvMax] = getAtlasTile(block, BlockFace::Front);
//
//			return {
//				{
//					{{-0.5f, 0.5f, 0.5f }, { uvMin.x, uvMin.y }, glm::vec3(0.9f)}, // FTL	
//					{{-0.5f,-0.5f, 0.5f }, { uvMin.x, uvMax.y }, glm::vec3(0.9f)}, // FBL	
//					{{ 0.5f,-0.5f, 0.5f }, { uvMax.x, uvMax.y }, glm::vec3(0.9f)}, // FBR	
//					{{ 0.5f, 0.5f, 0.5f }, { uvMax.x, uvMin.y }, glm::vec3(0.9f)}, // FTR
//				},
//				{
//					///   TR->BR->BL      BL->TL->TR 
//						0, 1, 2,	2, 3, 0
//				}
//			}; break;
//		}
//		case BlockFace::Top:
//		{
//			auto [uvMin, uvMax] = getAtlasTile(block, BlockFace::Top);
//
//			return {
//				{
//					{{ 0.5f, 0.5f, 0.5f }, { uvMin.x, uvMin.y }, glm::vec3(1.f)}, // TTR
//					{{ 0.5f, 0.5f,-0.5f }, { uvMin.x, uvMax.y }, glm::vec3(1.f)}, // TBR
//					{{-0.5f, 0.5f,-0.5f }, { uvMax.x, uvMax.y }, glm::vec3(1.f)}, // TBL
//					{{-0.5f, 0.5f, 0.5f }, { uvMax.x, uvMin.y }, glm::vec3(1.f)}, // TTL
//				},
//				{
//					///   TR->BR->BL      BL->TL->TR 
//						0, 1, 2,	2, 3, 0
//				}
//			}; break;
//		}
//		case BlockFace::Back:
//		{
//			auto [uvMin, uvMax] = getAtlasTile(block, BlockFace::Back);
//
//			return {
//				{
//					{{ 0.5f, 0.5f,-0.5f }, { uvMin.x, uvMin.y }, glm::vec3(0.6f)}, // BTR
//					{{ 0.5f,-0.5f,-0.5f }, { uvMin.x, uvMax.y }, glm::vec3(0.6f)}, // BBR
//					{{-0.5f,-0.5f,-0.5f }, { uvMax.x, uvMax.y }, glm::vec3(0.6f)}, // BBL
//					{{-0.5f, 0.5f,-0.5f }, { uvMax.x, uvMin.y }, glm::vec3(0.6f)}, // BTL
//				},
//				{
//					///   TR->BR->BL      BL->TL->TR 
//						0, 1, 2,	2, 3, 0
//				}
//			}; break;
//		}
//		case BlockFace::Bottom:
//		{
//			auto [uvMin, uvMax] = getAtlasTile(block, BlockFace::Bottom);
//
//			return {
//				{
//					{{-0.5f,-0.5f, 0.5f }, { uvMin.x, uvMin.y }, glm::vec3(0.5f)}, // TTL
//					{{-0.5f,-0.5f,-0.5f }, { uvMin.x, uvMax.y }, glm::vec3(0.5f)}, // TBL
//					{{ 0.5f,-0.5f,-0.5f }, { uvMax.x, uvMax.y }, glm::vec3(0.5f)}, // TBR
//					{{ 0.5f,-0.5f, 0.5f }, { uvMax.x, uvMin.y }, glm::vec3(0.5f)}, // TTR
//				},
//				{
//					///   TR->BR->BL      BL->TL->TR 
//						0, 1, 2,	2, 3, 0
//				}
//			}; break;
//		}
//		case BlockFace::Left:
//		{
//			auto [uvMin, uvMax] = getAtlasTile(block, BlockFace::Left);
//
//			return {
//				{
//					{{-0.5f, 0.5f,-0.5f }, { uvMin.x, uvMin.y }, glm::vec3(0.7f)}, // TTL
//					{{-0.5f,-0.5f,-0.5f }, { uvMin.x, uvMax.y }, glm::vec3(0.7f)}, // TBL
//					{{-0.5f,-0.5f, 0.5f }, { uvMax.x, uvMax.y }, glm::vec3(0.7f)}, // TBR
//					{{-0.5f, 0.5f, 0.5f }, { uvMax.x, uvMin.y }, glm::vec3(0.7f)}, // TTR
//				},
//				{
//					///   TR->BR->BL      BL->TL->TR 
//						0, 1, 2,	2, 3, 0
//				}
//			}; break;
//		}
//		case BlockFace::Right:
//		{
//			auto [uvMin, uvMax] = getAtlasTile(block, BlockFace::Right);
//
//			return {
//				{
//					{{ 0.5f, 0.5f, 0.5f }, { uvMin.x, uvMin.y }, glm::vec3(0.8f)}, // TTR		   
//					{{ 0.5f,-0.5f, 0.5f }, { uvMin.x, uvMax.y }, glm::vec3(0.8f)}, // TBR		   
//					{{ 0.5f,-0.5f,-0.5f }, { uvMax.x, uvMax.y }, glm::vec3(0.8f)}, // TBL		   
//					{{ 0.5f, 0.5f,-0.5f }, { uvMax.x, uvMin.y }, glm::vec3(0.8f)}, // TTL
//				},
//				{
//					///   TR->BR->BL      BL->TL->TR 
//						0, 1, 2,	2, 3, 0
//				}
//			}; break;
//		}
//	}
//
//
//	return {};
//}