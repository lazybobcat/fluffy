#include <fluffy/assert.hpp>
#include <fluffy/resources/resource_metadata.hpp>

using namespace Fluffy;

void ResourceMetadata::serialize(Json::Value& to)
{
    for (const auto& it : mConfigurations) {
        if (isInteger(it.second)) {
            to[it.first] = getInt(it.first);
        } else if (isNumber(it.second)) {
            to[it.first] = getFloat(it.first);
        } else {
            to[it.first] = it.second;
        }
        // @todo handle arrays of strings?
    }
}

void ResourceMetadata::deserialize(Json::Value& from)
{
    if (from.isObject()) {
        for (const auto& it : from.getMemberNames()) {
            set(it, from[it].asString());
        }
        mLoaded = true;
    }
}

bool ResourceMetadata::has(const String& key)
{
    return mConfigurations.find(key) != mConfigurations.end();
}

void ResourceMetadata::erase(const String& key)
{
    auto it = mConfigurations.find(key);
    if (it != mConfigurations.end()) {
        mConfigurations.erase(it);
    }
}

void ResourceMetadata::set(String key, String value)
{
    auto it = mConfigurations.find(key);
    if (it != mConfigurations.end()) {
        it->second = std::move(value);
    } else {
        mConfigurations[std::move(key)] = std::move(value);
    }
}
void ResourceMetadata::set(String key, const char* value)
{
    set(std::move(key), String(value));
}

void ResourceMetadata::set(String key, bool value)
{
    set(std::move(key), value ? "true" : "false");
}

void ResourceMetadata::set(String key, int value)
{
    set(std::move(key), toString(value));
}

void ResourceMetadata::set(String key, float value)
{
    set(std::move(key), toString(value));
}

String ResourceMetadata::getString(const String& key)
{
    auto it = mConfigurations.find(key);
    FLUFFY_ASSERT(it != mConfigurations.end(), printString("Key '{}' not found in resource data", key).c_str());

    return it->second;
}
bool ResourceMetadata::getBool(const String& key)
{
    return getString(key) == "true";
}
int ResourceMetadata::getInt(const String& key)
{
    return std::stoi(getString(key));
}
float ResourceMetadata::getFloat(const String& key)
{
    return std::stof(getString(key));
}

bool ResourceMetadata::operator==(const ResourceMetadata& rhs) const
{
    return mConfigurations == rhs.mConfigurations;
}
bool ResourceMetadata::operator!=(const ResourceMetadata& rhs) const
{
    return mConfigurations == rhs.mConfigurations;
}

bool ResourceMetadata::isLoaded() const
{
    return mLoaded;
}
