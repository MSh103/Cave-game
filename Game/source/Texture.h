#pragma once

#include <Atlas.h>
#include <Atlas/Renderer.h>

class Texture2D
{
public:
	Texture2D(const std::filesystem::path& path);

	void Use();

private:
	std::filesystem::path m_FilePath;

	struct Image
	{
		int width, height, nrChannels;
	} m_Image;

	uint32_t m_RendererID;
};
