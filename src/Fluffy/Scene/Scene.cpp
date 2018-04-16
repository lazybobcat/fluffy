//
// fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 16/04/18.
//

#include <Fluffy/Scene/Scene.hpp>

using namespace Fluffy::Scene;

Scene::Scene(SceneNode::Ptr root)
  : mRootNode(std::move(root))
{
}

SceneNode& Scene::root() const
{
    return *mRootNode.get();
}
