//
// fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 16/04/18.
//

#include <algorithm>
#include <cassert>
#include <fluffy/scene/scene_node.hpp>
#include <fluffy/text/string.hpp>

using namespace Fluffy;

SceneNode::SceneNode(std::string&& name)
  : mName(name)
{
}

void SceneNode::attach(Ptr child)
{
    const std::string cname = child->name();
    if (hasChildWithName(cname)) {
        throw std::logic_error(printString("A child node with name '%1' has already been attached to '%2'", { cname, name() }));
    }

    child->mParent = this;
    child->mPath.clear();
    mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detach(const SceneNode& child)
{
    auto found = std::find_if(mChildren.begin(), mChildren.end(), [&](Ptr& p) -> bool {
        return p.get() == &child;
    });

    assert(found != mChildren.end());

    Ptr result      = std::move(*found);
    result->mParent = nullptr;
    result->mPath.clear();
    mChildren.erase(found);

    return result;
}

void SceneNode::serialize(Json::Value& to)
{
    to["name"] = name();
    to["path"] = path();
    to["type"] = type();
    Json::Value data;
    serializeData(data);
    to["data"] = data;
}

void SceneNode::serializeData(Json::Value& to)
{
    // nothing to do here, override this method in child classes
}

void SceneNode::deserialize(Json::Value& from)
{
    if (!from["data"].isNull()) {
        deserializeData(from["data"]);
    }
}

void SceneNode::deserializeData(Json::Value& from)
{
    // nothing to do here, override this method in child classes
}

std::vector<SceneNode*> SceneNode::children() const
{
    auto results = std::vector<SceneNode*>();

    for (auto& child : mChildren) {
        results.push_back(child.get());
    }

    return results;
}

std::string SceneNode::path()
{
    if (mPath.empty()) {
        const SceneNode* node = this;
        while (node != nullptr) {
            mPath.insert(0, path_separator + node->name());
            node = node->mParent;
        }
    }

    return mPath;
}

std::string SceneNode::name() const
{
    return mName;
}

bool SceneNode::hasChildWithName(const std::string& name)
{
    return findChildWithName(name) != nullptr;
}

SceneNode* SceneNode::findChildWithName(const std::string& name)
{
    for (auto& child : mChildren) {
        if (child->name() == name) {
            return child.get();
        }
    }

    return nullptr;
}
