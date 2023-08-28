#pragma once
#include <map>
#include <memory>
#include <string>
#include "Resource.h"
#include "Framework/Singleton.h"

#define GET_RESOURCE(type, filename, ...) kda::ResourceManager::Instance().Get<type>(filename, __VA_ARGS__)

namespace kda
{
	class ResourceManager : public Singleton<ResourceManager>
	{
	public:
		template<typename T, typename ... TArgs>
		std::shared_ptr<T> Get(const std::string& filename, TArgs ... args);
	private:
		std::map<std::string, std::shared_ptr<Resource>> m_resources;
	};

	template<typename T, typename ...TArgs>
	inline std::shared_ptr<T> ResourceManager::Get(const std::string& filename, TArgs ...args)
	{
		if (m_resources.find(filename) != m_resources.end())
		{
			return std::dynamic_pointer_cast<T>(m_resources[filename]);
		}

		res_t<T> resource = std::make_shared<T>();
		if (!resource->Create(filename, args...))
		{
			WARNING_LOG("Could not create resource: " << filename);
			return res_t<T>();
		}

		m_resources[filename] = resource;
		return resource;
	}

}