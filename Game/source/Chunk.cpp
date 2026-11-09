#include "Chunk.h"

#include "Camera.h"

#include "Debug/Timer.h"

Chunk::Chunk(glm::vec3 pos)
{
	m_Position = pos;

	m_Model = glm::translate(glm::mat4(1.0f), { 
		m_Position.x * CHUNK_WIDTH, 
		m_Position.y * CHUNK_HEIGHT, 
		m_Position.z * CHUNK_DEPTH	
	});
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
				if(y == CHUNK_HEIGHT-1)
					m_Blocks[y][z][x] = Block::Grass;
				else
					m_Blocks[y][z][x] = Block::Dirt;
			}
		}
	}

	
	m_MeshCPU.vertices.reserve(49152);
	m_MeshCPU.indices.reserve(73728);
}

void Chunk::BuildMesh()
{
	ScopedTimer timer("Chunk::BuildMesh()");

	m_MeshCPU.clearMesh();

	for (int y = 0; y < CHUNK_HEIGHT; y++)
	{
		for (int z = 0; z < CHUNK_DEPTH; z++)
		{
			for (int x = 0; x < CHUNK_WIDTH; x++)
			{
				if (m_Blocks[y][z][x] == Block::Air)
					continue;

				if (IsAir({ x - 1, y, z }))
					m_MeshCPU.addFace(BlockFace::Left, m_Blocks[y][z][x], {x, y, z});
				if (IsAir({ x + 1, y, z }))
					m_MeshCPU.addFace(BlockFace::Right, m_Blocks[y][z][x], { x, y, z });

				if (IsAir({ x, y - 1, z }))
					m_MeshCPU.addFace(BlockFace::Bottom, m_Blocks[y][z][x], { x, y, z });
				if (IsAir({ x, y + 1, z }))
					m_MeshCPU.addFace(BlockFace::Top, m_Blocks[y][z][x], { x, y, z });

				if (IsAir({ x, y, z - 1 }))
					m_MeshCPU.addFace(BlockFace::Back, m_Blocks[y][z][x], { x, y, z });
				if (IsAir({ x, y, z + 1 }))
					m_MeshCPU.addFace(BlockFace::Front, m_Blocks[y][z][x], { x, y, z });
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

bool Chunk::IsAir(glm::ivec3 pos)
{
	if (pos.x < 0 || pos.x >= CHUNK_WIDTH
		|| pos.z < 0 || pos.z >= CHUNK_DEPTH
		|| pos.y < 0 || pos.y >= CHUNK_HEIGHT)
		return true;
	
	if (m_Blocks[pos.y][pos.z][pos.x] == Block::Air)
		return true;

	return false;
}

