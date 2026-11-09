#pragma once

#define NO_CHUNKS_X 5
#define NO_CHUNKS_Y 5
#define NO_CHUNKS_Z 5

#include <Atlas/Renderer.h>
#include <vector>
#include <memory>

#include "Chunk.h"

class World
{
public:
	World();
	~World() = default;

	bool IsAir(const glm::vec3& pos);

	void Render(Camera& camera, Texture2D& atlas, Atlas::Shader& shader);

private:
	std::vector<std::unique_ptr<Chunk>> m_Chunks;
};

