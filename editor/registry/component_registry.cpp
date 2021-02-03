#include "component_registry.hpp"

using namespace Fluffy;

void ComponentRegistry::addComponentData(const ComponentData& data)
{
    mData.push_back(std::move(data));
    sort();
}

void ComponentRegistry::sort()
{
    std::sort(mData.begin(), mData.end(), [](const ComponentData& a, const ComponentData& b) {
        return a < b;
    });
}
