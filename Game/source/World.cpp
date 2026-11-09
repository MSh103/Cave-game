#include "World.h"

#include "Chunk.h"
#include "Texture.h"
#include "Camera.h"

World::World()
{
	for (std::size_t y = 0; y < NO_CHUNKS_Y; y++)
	{
		for (std::size_t z = 0; z < NO_CHUNKS_Z; z++)
		{
			for (std::size_t x = 0; x < NO_CHUNKS_X; x++)
			{ 
				auto c = std::make_unique<Chunk>(glm::vec3({ x, y, z }));
				c->Generate();
				m_Chunks.push_back(std::move(c));
			}
		}
	}

	for (auto& c : m_Chunks)
	{
		c->BuildMesh(this);
		c->UploadMesh();
	}
	
}

bool World::IsAir(const glm::vec3& pos)
{
	int x = (int)pos.x; // WORLD POS
	int y = (int)pos.y; // WORLD POS
	int z = (int)pos.z; // WORLD POS

	if (x >= (NO_CHUNKS_X * CHUNK_WIDTH)  || x < 0 ||
	    y >= (NO_CHUNKS_Y * CHUNK_HEIGHT) || y < 0 ||
	    z >= (NO_CHUNKS_Z * CHUNK_DEPTH)  || z < 0)
		return true;

	int cX = x / CHUNK_WIDTH;
	int cY = y / CHUNK_HEIGHT;
	int cZ = z / CHUNK_DEPTH;

	int lX = x % CHUNK_WIDTH;
	int lY = y % CHUNK_HEIGHT;
	int lZ = z % CHUNK_DEPTH;

	int index = cX + NO_CHUNKS_X * (cZ + NO_CHUNKS_Z * cY);

	return m_Chunks[index]->IsAir({ lX, lY, lZ });
}

void World::Render(Camera& camera, Texture2D& atlas, Atlas::Shader& shader)
{
	for (auto& c : m_Chunks)
		c->Render(camera, atlas, shader);
}
