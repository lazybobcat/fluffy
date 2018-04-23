//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 20/04/18.
//

#ifndef FLUFFY_ASSETHOLDER_HPP
#define FLUFFY_ASSETHOLDER_HPP

#include <map>
#include <memory>
#include <string>

namespace Fluffy {
namespace Asset {

template <typename Resource, typename Identifier>
class AssetHolder
{
public:
    void load(Identifier id, const std::string& filename);

    template <typename... Args>
    void load(Identifier id, const std::string& filename, Args&&... args);

    Resource& get(Identifier id);
    const Resource& get(Identifier id) const;

private:
    void insertResource(Identifier id, std::unique_ptr<Resource> resource);

private:
    std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

#include <Fluffy/Asset/AssetHolder.inl>
}
}

#endif //FLUFFY_ASSETHOLDER_HPP
