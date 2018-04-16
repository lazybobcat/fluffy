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

class Scene
{
public:
    explicit Scene(SceneNode::Ptr root);

    SceneNode& root() const;

private:
    SceneNode::Ptr mRootNode;
};
}
}

#endif //FLUFFY_SCENE_HPP
