#pragma once
#include <filesystem>
#include "Shaddock/Renderer/Texture.h"

namespace Shaddock {
	class ContentBrowserPanel
	{
	public:
		ContentBrowserPanel();
		void OnImGuiRender();
	private:
		std::filesystem::path m_CurrentDirectory;

		Ref<Texture2D> m_DirectoryIcon;
		Ref<Texture2D> m_FileIcon;
	};
}