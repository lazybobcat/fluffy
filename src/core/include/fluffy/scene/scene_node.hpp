#pragma once

#include <fluffy/pch.hpp>
#include <fluffy/serialization/serializable.hpp>

#define SCENE_NODE(_type) \
    std::string type() const { return #_type; }

namespace Fluffy {

class Scene;

class SceneNode : public Fluffy::Serializable
{
public:
    virtual std::string type() const = 0;

    typedef std::unique_ptr<SceneNode> Ptr;
    static constexpr char              path_separator = '/';

public:
    SceneNode(std::string&& name);
    virtual ~SceneNode() = default;

    std::string name() const;
    std::string path();

    void attach(Ptr child);
    Ptr  detach(const SceneNode& child);

    std::vector<SceneNode*> children() const;

    void serialize(Json::Value& to) final;
    void deserialize(Json::Value& from) final;

protected:
    virtual void serializeData(Json::Value& to);
    virtual void deserializeData(Json::Value& from);

    bool       hasChildWithName(const std::string& name);
    SceneNode* findChildWithName(const std::string& name);

private:
    friend Scene;

private:
    std::string      mName;
    std::string      mPath;
    std::vector<Ptr> mChildren;
    SceneNode*       mParent = nullptr;
};
}
