//
// fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 16/04/18.
//

#ifndef FLUFFY_SCENE_HPP
#define FLUFFY_SCENE_HPP

#include <Fluffy/Scene/SceneNode.hpp>

namespace Fluffy {
namespace Scene {

class Scene : public Fluffy::Utility::Serializable
{
public:
    explicit Scene(SceneNode::Ptr root);

    SceneNode& root() const;

    bool saveToFile(std::string&& filepath);

    void serialize(Json::Value &to) override;
    void deserialize(Json::Value &from) override;

private:
    void serializeSceneNode(SceneNode& node, Json::Value& json);

private:
    SceneNode::Ptr mRootNode;
};
}
}

#endif //FLUFFY_SCENE_HPP
