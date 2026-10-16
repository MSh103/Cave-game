#include "Mesh.h"

void MeshCPU::pushVertex(const Vertex& vertex)
{
	vertices.push_back(vertex);
}

void MeshCPU::pushIndex(const uint32_t& index)
{
	indices.push_back(index);
}

void MeshGPU::addMeshCPU(MeshCPU* cpu)
{
	vertexArray = std::make_unique<Atlas::VertexArray>();

	std::shared_ptr<Atlas::VertexBuffer> vbo = std::make_shared<Atlas::VertexBuffer>(cpu->vertices.data(), sizeof(Vertex) * cpu->vertices.size());
	vbo->Use();
	vbo->SetLayout({
		{Atlas::ShaderDataType::Float3, "a_Pos"},
		{Atlas::ShaderDataType::Float3, "a_Color"},
		});

	std::shared_ptr<Atlas::IndexBuffer> ibo = std::make_shared<Atlas::IndexBuffer>(cpu->indices.data(), cpu->indices.size());
	ibo->Use();

	vertexArray->Use();
	vertexArray->AddVertexBuffer(vbo);
	vertexArray->SetIndexBuffer(ibo);
}

void MeshGPU::render(Atlas::Shader* shader)
{
	vertexArray->Use();
	shader->Use();
	glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, (const void*)0);
}
