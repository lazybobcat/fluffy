//
// fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 16/04/18.
//

#include <Fluffy/Scene/Scene.hpp>
#include <Fluffy/Utility/JsonSerializer.hpp>
#include <Fluffy/Utility/String.hpp>

using namespace Fluffy::Scene;
using namespace Fluffy::Utility;

Scene::Scene(SceneNode::Ptr root)
  : mRootNode(std::move(root))
{
}

SceneNode* Scene::root() const
{
    return mRootNode.get();
}

SceneNode* Scene::find(std::string&& path) const
{
    if (path == mRootNode->path()) {
        return mRootNode.get();
    }

    auto node_names = split(path.substr(1), '/');
    auto node       = mRootNode.get();
    for (auto i = 1; i < node_names.size(); ++i) {
        auto child = node->findChildWithName(node_names[i]);

        if (nullptr == child) {
            return nullptr;
        }

        node = child;
    }

    return node;
}

bool Scene::saveToFile(std::string&& filepath)
{
    return Fluffy::Utility::JsonSerializer::serializeToFile(*this, filepath);
}

void Scene::serializeSceneNode(SceneNode& node, Json::Value& json)
{
    node.serialize(json);

    for (auto child : node.children()) {
        Json::Value childJson;
        serializeSceneNode(*child, childJson);
        json["children"].append(childJson);
    }
}

void Scene::serialize(Json::Value& to)
{
    Json::Value root;
    serializeSceneNode(*mRootNode, root);

    to["root"] = root;
}

void Scene::deserialize(Json::Value& from)
{
    throw std::runtime_error("Scene::deserialize is not available yet");
}
