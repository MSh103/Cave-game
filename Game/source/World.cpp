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
				Chunk* c = new Chunk({ x, y, z });
				c->Generate();
				c->BuildMesh();
				c->UploadMesh();
				m_Chunks.push_back(c);
			}
		}
	}
}

World::~World()
{
	for (auto& c : m_Chunks)
		delete c;
}

bool World::IsAir(const glm::vec3& pos)
{
	return false;
}

void World::Render(Camera& camera, Texture2D& atlas, Atlas::Shader& shader)
{
	for (auto& c : m_Chunks)
		c->Render(camera, atlas, shader);
}
