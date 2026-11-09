#pragma once

#include <Atlas.h>
#include <Atlas/Renderer.h>

#include "Mesh.h"
#include "Block.h"
#include "Texture.h"

#include <cstddef>

class Camera;

#include <array>

static constexpr std::size_t CHUNK_WIDTH  = 16;
static constexpr std::size_t CHUNK_DEPTH  = 16;
static constexpr std::size_t CHUNK_HEIGHT = 16;


class Chunk
{
public:
	Chunk(glm::vec3 pos);
	~Chunk() = default;

	void Generate();
	void BuildMesh();
	void UploadMesh();

	void Render(Camera& camera, Texture2D& atlas, Atlas::Shader& shader);

private:
	bool IsAir(glm::ivec3 pos);

private:
	//std::array<Block, CHUNK_WIDTH* CHUNK_DEPTH* CHUNK_HEIGHT> m_Blocks;
	std::array<std::array<std::array<Block, CHUNK_WIDTH>, CHUNK_DEPTH>, CHUNK_HEIGHT> m_Blocks;

	glm::vec3 m_Position;
	glm::mat4 m_Model;

	MeshCPU m_MeshCPU;
	MeshGPU m_MeshGPU;
};
