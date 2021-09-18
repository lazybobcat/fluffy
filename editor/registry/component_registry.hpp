#pragma once

#include <fluffy/definitions.hpp>
#include <fluffy/graphics/texture.hpp>
#include <fluffy/pch.hpp>
#include <fluffy/scene/entity.hpp>

namespace Fluffy {

struct ComponentData
{
    String                      name;
    Ref<Texture2D>              icon;
    std::function<void(Entity)> addComponentFct;
    std::function<void(Entity)> drawComponentFct;

    bool operator<(const ComponentData& other) const
    {
        return name < other.name;
    }
};

class ComponentRegistry
{
public:
    using Iterator      = std::vector<ComponentData>::iterator;
    using ConstIterator = std::vector<ComponentData>::const_iterator;

public:
    void addComponentData(const ComponentData& data);

    Iterator      begin() { return mData.begin(); }
    ConstIterator begin() const { return mData.begin(); }
    Iterator      end() { return mData.end(); }
    ConstIterator end() const { return mData.end(); }

private:
    void sort();

private:
    std::vector<ComponentData> mData;
};

}
