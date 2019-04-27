//
// fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 16/04/18.
//

#pragma once

#include <fluffy/scene/scene_node.hpp>

namespace Fluffy {

class Scene : public Fluffy::Serializable
{
public:
    explicit Scene(SceneNode::Ptr root);

    SceneNode* root() const;
    SceneNode* find(std::string&& path) const;

    bool saveToFile(std::string&& filepath);

    void serialize(Json::Value& to) override;
    void deserialize(Json::Value& from) override;

private:
    void serializeSceneNode(SceneNode& node, Json::Value& json);

private:
    SceneNode::Ptr mRootNode;
};
}
