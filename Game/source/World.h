#pragma once

#define NO_CHUNKS_X 5
#define NO_CHUNKS_Y 5
#define NO_CHUNKS_Z 5

#include <Atlas/Renderer.h>
#include <vector>

class Chunk;
class Camera;
class Texture2D;


class World
{
public:
	World();
	~World();

	bool IsAir(const glm::vec3& pos);

	void Render(Camera& camera, Texture2D& atlas, Atlas::Shader& shader);

private:
	std::vector<Chunk*> m_Chunks;
};

