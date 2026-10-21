#include "Chunk.h"

#include "Camera.h"

#include "Debug/Timer.h"

Chunk::Chunk(glm::vec2 pos)
{
	m_Position = pos;

	m_Model = glm::translate(glm::mat4(1.0f), { m_Position.x * CHUNK_WIDTH, 0.f, m_Position.y * CHUNK_DEPTH });
}

void Chunk::Generate()
{
	ScopedTimer timer("Chunk::Generate()");

	for (size_t x = 0; x < CHUNK_WIDTH; x++)
	{
		for (size_t z = 0; z < CHUNK_DEPTH; z++)
		{
			for (size_t y = 0; y < CHUNK_HEIGHT; y++)
			{
				int index = x + 16 * (z + 16 * y);

				if (y == 255)
					m_Blocks[index] = Block::Grass;
				else if (y <= 254 && y >= 250)
					m_Blocks[index] = Block::Dirt;
				else if (y <= 245 && y >= 240)
					m_Blocks[index] = Block::Air;
				else if (y <= 238 && y >= 230)
					m_Blocks[index] = Block::Air;
				else if (y == 239)
					m_Blocks[index] = Block::DiamondOre;
				else
					m_Blocks[index] = Block::Stone;
			}
		}
	}

	
	m_MeshCPU.vertices.reserve(70000);
	m_MeshCPU.indices.reserve(105000);
}

void Chunk::BuildMesh()
{
	ScopedTimer timer("Chunk::BuildMesh()");

	m_MeshCPU.ClearMesh();

	for (int y = 0; y < CHUNK_HEIGHT; y++)
	{
		for (int z = 0; z < CHUNK_DEPTH; z++)
		{
			for (int x = 0; x < CHUNK_WIDTH; x++)
			{
				const int index = x + CHUNK_WIDTH * (z + CHUNK_DEPTH* y);

				if (m_Blocks[index] == Block::Air)
					continue;

				if (IsAir(m_Blocks.data(), { x - 1, y, z }))
					m_MeshCPU.addFace(BlockFace::Left, m_Blocks[index], { x, y, z });
				if (IsAir(m_Blocks.data(), { x + 1, y, z }))
					m_MeshCPU.addFace(BlockFace::Right, m_Blocks[index], { x, y, z });

				if (IsAir(m_Blocks.data(), { x, y - 1, z }))
					m_MeshCPU.addFace(BlockFace::Bottom, m_Blocks[index], { x, y, z });
				if (IsAir(m_Blocks.data(), { x, y + 1, z }))
					m_MeshCPU.addFace(BlockFace::Top, m_Blocks[index], { x, y, z });

				if (IsAir(m_Blocks.data(), { x, y, z - 1 }))
					m_MeshCPU.addFace(BlockFace::Back, m_Blocks[index], { x, y, z });
				if (IsAir(m_Blocks.data(), { x, y, z + 1 }))
					m_MeshCPU.addFace(BlockFace::Front, m_Blocks[index], { x, y, z });
			}
		}
	}

	Atlas::Log::Core::Trace("VertSize: {}, IndicesSize: {}, VertCapacity: {}, IndicesCapacity: {}", m_MeshCPU.vertices.size(), m_MeshCPU.indices.size(), m_MeshCPU.vertices.capacity(), m_MeshCPU.indices.capacity());
}

void Chunk::UploadMesh()
{
	ScopedTimer timer("Chunk::UploadMesh()");
	m_MeshGPU.addMeshCPU(m_MeshCPU);
}

void Chunk::Render(Camera& camera, Texture2D& atlas, Atlas::Shader& shader)
{
	shader.Use();
	shader.Upload("u_Model", m_Model);
	shader.Upload("u_View", camera.GetViewMatrix());
	shader.Upload("u_Projection", camera.GetProjectionMatrix());
	atlas.Use();
	m_MeshGPU.render(shader);
}

bool Chunk::IsAir(Block* blocks, glm::ivec3 pos)
{
	if (pos.x < 0 || pos.x >= 16
		|| pos.z < 0 || pos.z >= 16
		|| pos.y < 0 || pos.y >= 256)
		return true;

	int index = pos.x + 16 * (pos.z + 16 * pos.y);
	if (blocks[index] == Block::Air)
		return true;

	return false;
}

