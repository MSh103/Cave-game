#include "Texture.h"

#include <Atlas/Renderer/Core/OpenGLEssentials.h>

#include "stb_image.h"

Texture2D::Texture2D(const std::filesystem::path& path)
{
	GLCall(glGenTextures(1, &m_RendererID));
	Atlas::Log::Core::Trace("Generated Texture: {}", m_RendererID);
	
	m_FilePath = path;

	if (!std::filesystem::exists(path))
	{
		Atlas::Log::Core::Error("Failed to load texture: {}", path.string());
		return;
	}

	unsigned char* data = stbi_load(m_FilePath.string().c_str(), &m_Image.width, &m_Image.height, &m_Image.nrChannels, 0);

	if (!data)
	{
		Atlas::Log::Core::Error("STB_Image failed to load image: {}", std::filesystem::absolute(path).string());
	}

	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Image.width, m_Image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
	GLCall(glGenerateMipmap(GL_TEXTURE_2D));

	stbi_image_free(data);

	Atlas::Log::Core::Trace("Created texture: {}x{}, {}", m_Image.width, m_Image.height, m_FilePath.string());
}

Texture2D::~Texture2D()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture2D::Use()
{
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}
