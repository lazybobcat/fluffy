#pragma once

#include <fluffy/serialization/serializable.hpp>
#include <fluffy/text/string.hpp>

namespace Fluffy {

class ResourceMetadata : public Serializable
{
public:
    ResourceMetadata()                        = default;
    ResourceMetadata(const ResourceMetadata&) = default;
    ResourceMetadata(ResourceMetadata&&)      = default;
    ~ResourceMetadata()                       = default;

    ResourceMetadata& operator=(const ResourceMetadata& other) = default;
    ResourceMetadata& operator=(ResourceMetadata&& other) = default;
    bool              operator==(const ResourceMetadata& rhs) const;
    bool              operator!=(const ResourceMetadata& rhs) const;

    [[nodiscard]] bool isLoaded() const;

    void serialize(Json::Value& to) override;
    void deserialize(Json::Value& from) override;

    bool has(const String& key);
    void erase(const String& key);

    void set(String key, String value);
    void set(String key, const char* value);
    void set(String key, bool value);
    void set(String key, int value);
    void set(String key, float value);

    String getString(const String& key);
    bool   getBool(const String& key);
    int    getInt(const String& key);
    float  getFloat(const String& key);

private:
    std::map<String, String> mConfigurations;
    bool                     mLoaded = false;
};
}