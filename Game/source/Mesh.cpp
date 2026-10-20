#include "Mesh.h"

void MeshCPU::pushVertex(const Vertex& vertex)
{
	vertices.push_back(vertex);
}

void MeshCPU::pushIndex(const uint32_t& index)
{
	indices.push_back(index);
}

void MeshCPU::addMesh(const MeshCPU& other)
{
	size_t vertexOffset = vertices.size();

	for (size_t i = 0; i < other.vertices.size(); i++)
		vertices.push_back(other.vertices[i]);
	
	for (size_t i = 0; i < other.indices.size(); i++)
		indices.push_back(other.indices[i] + vertexOffset);
}

void MeshCPU::addMeshPosition(const MeshCPU& other, const glm::vec3& pos)
{
	size_t vertexOffset = vertices.size();

	for (size_t i = 0; i < other.vertices.size(); i++)
		vertices.push_back({ pos +  other.vertices[i].pos, other.vertices[i].uv, other.vertices[i].color});

	for (size_t i = 0; i < other.indices.size(); i++)
		indices.push_back(other.indices[i] + vertexOffset);
}

void MeshCPU::addFace(BlockFace face, Block block, const glm::vec3& pos)
{
	auto [uvMin, uvMax] = getAtlasTile(block, face);
	const uint32_t baseIndex = static_cast<uint32_t>(vertices.size());

	switch (face)
	{
	case BlockFace::Front:
	{
		vertices.push_back({ glm::vec3(-0.5f, 0.5f, 0.5f) + pos, { uvMin.x, uvMin.y }, glm::vec3(0.9f) });
		vertices.push_back({ glm::vec3(-0.5f,-0.5f, 0.5f) + pos, { uvMin.x, uvMax.y }, glm::vec3(0.9f) });
		vertices.push_back({ glm::vec3(0.5f,-0.5f, 0.5f) + pos, { uvMax.x, uvMax.y }, glm::vec3(0.9f) });
		vertices.push_back({ glm::vec3(0.5f, 0.5f, 0.5f) + pos, { uvMax.x, uvMin.y }, glm::vec3(0.9f) });
		indices.push_back(baseIndex + 0);
		indices.push_back(baseIndex + 1);
		indices.push_back(baseIndex + 2);
		indices.push_back(baseIndex + 2);
		indices.push_back(baseIndex + 3);
		indices.push_back(baseIndex + 0);
		break;
	}
	case BlockFace::Top:
	{
		vertices.push_back({glm::vec3( 0.5f, 0.5f, 0.5f) + pos, { uvMin.x, uvMin.y }, glm::vec3(1.f)});
		vertices.push_back({glm::vec3( 0.5f, 0.5f,-0.5f) + pos, { uvMin.x, uvMax.y }, glm::vec3(1.f)});
		vertices.push_back({glm::vec3(-0.5f, 0.5f,-0.5f) + pos, { uvMax.x, uvMax.y }, glm::vec3(1.f)});
		vertices.push_back({glm::vec3(-0.5f, 0.5f, 0.5f) + pos, { uvMax.x, uvMin.y }, glm::vec3(1.f)});
		indices.push_back(baseIndex + 0);
		indices.push_back(baseIndex + 1);
		indices.push_back(baseIndex + 2);
		indices.push_back(baseIndex + 2);
		indices.push_back(baseIndex + 3);
		indices.push_back(baseIndex + 0);
		break;
	}
	case BlockFace::Back:
	{
		vertices.push_back({ glm::vec3( 0.5f, 0.5f,-0.5f) + pos, { uvMin.x, uvMin.y }, glm::vec3(0.6f) });
		vertices.push_back({ glm::vec3( 0.5f,-0.5f,-0.5f) + pos, { uvMin.x, uvMax.y }, glm::vec3(0.6f) });
		vertices.push_back({ glm::vec3(-0.5f,-0.5f,-0.5f) + pos, { uvMax.x, uvMax.y }, glm::vec3(0.6f) });
		vertices.push_back({ glm::vec3(-0.5f, 0.5f,-0.5f) + pos, { uvMax.x, uvMin.y }, glm::vec3(0.6f) });
		indices.push_back(baseIndex + 0);
		indices.push_back(baseIndex + 1);
		indices.push_back(baseIndex + 2);
		indices.push_back(baseIndex + 2);
		indices.push_back(baseIndex + 3);
		indices.push_back(baseIndex + 0);
		break;
	}
	case BlockFace::Bottom:
	{
		vertices.push_back({glm::vec3(-0.5f,-0.5f, 0.5f) + pos, { uvMin.x, uvMin.y }, glm::vec3(0.5f)});
		vertices.push_back({glm::vec3(-0.5f,-0.5f,-0.5f) + pos, { uvMin.x, uvMax.y }, glm::vec3(0.5f)});
		vertices.push_back({glm::vec3( 0.5f,-0.5f,-0.5f) + pos, { uvMax.x, uvMax.y }, glm::vec3(0.5f)});
		vertices.push_back({glm::vec3( 0.5f,-0.5f, 0.5f) + pos, { uvMax.x, uvMin.y }, glm::vec3(0.5f)});
		indices.push_back(baseIndex + 0);
		indices.push_back(baseIndex + 1);
		indices.push_back(baseIndex + 2);
		indices.push_back(baseIndex + 2);
		indices.push_back(baseIndex + 3);
		indices.push_back(baseIndex + 0);
		break;
	}
	case BlockFace::Left:
	{
		vertices.push_back({ glm::vec3(-0.5f, 0.5f,-0.5f) + pos, { uvMin.x, uvMin.y }, glm::vec3(0.7f) });
		vertices.push_back({ glm::vec3(-0.5f,-0.5f,-0.5f) + pos, { uvMin.x, uvMax.y }, glm::vec3(0.7f) });
		vertices.push_back({ glm::vec3(-0.5f,-0.5f, 0.5f) + pos, { uvMax.x, uvMax.y }, glm::vec3(0.7f) });
		vertices.push_back({ glm::vec3(-0.5f, 0.5f, 0.5f) + pos, { uvMax.x, uvMin.y }, glm::vec3(0.7f) });
		indices.push_back(baseIndex + 0);
		indices.push_back(baseIndex + 1);
		indices.push_back(baseIndex + 2);
		indices.push_back(baseIndex + 2);
		indices.push_back(baseIndex + 3);
		indices.push_back(baseIndex + 0);
		break;
	}
	case BlockFace::Right:
	{
		vertices.push_back({ glm::vec3(0.5f, 0.5f, 0.5f) + pos, { uvMin.x, uvMin.y }, glm::vec3(0.8f) });
		vertices.push_back({ glm::vec3(0.5f,-0.5f, 0.5f) + pos, { uvMin.x, uvMax.y }, glm::vec3(0.8f) });
		vertices.push_back({ glm::vec3(0.5f,-0.5f,-0.5f) + pos, { uvMax.x, uvMax.y }, glm::vec3(0.8f) });
		vertices.push_back({ glm::vec3(0.5f, 0.5f,-0.5f) + pos, { uvMax.x, uvMin.y }, glm::vec3(0.8f) });
		indices.push_back(baseIndex + 0);
		indices.push_back(baseIndex + 1);
		indices.push_back(baseIndex + 2);
		indices.push_back(baseIndex + 2);
		indices.push_back(baseIndex + 3);
		indices.push_back(baseIndex + 0);
		break;
	}
	}
}

void MeshGPU::addMeshCPU(MeshCPU& cpu)
{
	vertexArray = std::make_unique<Atlas::VertexArray>();

	std::shared_ptr<Atlas::VertexBuffer> vbo = std::make_shared<Atlas::VertexBuffer>(cpu.vertices.data(), sizeof(Vertex) * cpu.vertices.size());
	vbo->Use();
	vbo->SetLayout({
		{Atlas::ShaderDataType::Float3, "a_Pos"},
		{Atlas::ShaderDataType::Float2, "a_TextureUV"},
		{Atlas::ShaderDataType::Float3, "a_Color"},
		});

	std::shared_ptr<Atlas::IndexBuffer> ibo = std::make_shared<Atlas::IndexBuffer>(cpu.indices.data(), cpu.indices.size());
	ibo->Use();

	vertexArray->Use();
	vertexArray->AddVertexBuffer(vbo);
	vertexArray->SetIndexBuffer(ibo);
}

void MeshGPU::render(Atlas::Shader& shader)
{
	vertexArray->Use();
	shader.Use();
	glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, (const void*)0);
}
