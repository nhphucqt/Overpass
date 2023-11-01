#include "ResourceManager.hpp"

template <typename Resource, typename Identifier>
inline void ResourceManager<Resource, Identifier>::load(Identifier id, const std::string &filename)
{
    std::unique_ptr<Resource> resource(new Resource());
    if (!resource->loadFromFile(filename))
        throw std::runtime_error("ResourceManager::load - Failed to load " + filename);
    auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second);
}

template <typename Resource, typename Identifier>
inline Resource &ResourceManager<Resource, Identifier>::get(Identifier id)
{
    auto found = mResourceMap.find(id);
    assert(found != mResourceMap.end());
    return *found->second;
}

template <typename Resource, typename Identifier>
inline const Resource &ResourceManager<Resource, Identifier>::get(Identifier id) const
{
    auto found = mResourceMap.find(id);
    assert(found != mResourceMap.end());
    return *found->second;
}