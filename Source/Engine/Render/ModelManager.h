#pragma once
#include "Model.h"
#include <string>
#include <map>
#include <memory>

namespace kda
{
	class ModelManager
	{
	public:
		std::shared_ptr<Model> get(const std::string& filename);

	private:
		std::map<std::string, std::shared_ptr<Model>> m_models;
	};

	extern ModelManager g_manager;
}