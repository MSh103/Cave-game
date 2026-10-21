#pragma once

#include <Atlas.h>
#include <Atlas/Renderer.h>

#include "Block.h"

struct Vertex
{
	glm::vec3 pos;
	glm::vec2 uv;
	float brightness;
};

struct MeshCPU
{
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	void pushVertex(const Vertex& vertex);
	void pushIndex(const uint32_t& index);
	void addMesh(const MeshCPU& other);
	void addMeshPosition(const MeshCPU& other, const glm::vec3& pos);
	void addFace(BlockFace face, Block block, const glm::vec3& pos);

	void ClearMesh();
};

struct MeshGPU
{
	std::unique_ptr<Atlas::VertexArray> vertexArray;

	void addMeshCPU(MeshCPU& cpu);
	void render(Atlas::Shader& shader);
};

