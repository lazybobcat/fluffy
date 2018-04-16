//
// fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 16/04/18.
//

#include <Fluffy/Scene/SceneNode.hpp>
#include <cassert>

using namespace Fluffy::Scene;

void SceneNode::attach(Ptr child)
{
    child->mParent = this;
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
    mChildren.erase(found);

    return result;
}

sf::Transform SceneNode::worldTransform() const
{
    sf::Transform transform = sf::Transform::Identity;

    for (const SceneNode* node = this; node != nullptr; node = node->mParent) {
        transform = node->getTransform() * transform;
    }

    return transform;
}

sf::Vector2f SceneNode::worldPosition() const
{
    return worldTransform() * sf::Vector2f();
}

sf::FloatRect SceneNode::boundingRect() const
{
    return sf::FloatRect();
}
