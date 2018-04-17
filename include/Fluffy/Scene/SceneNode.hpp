//
// fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 16/04/18.
//

#ifndef FLUFFY_SCENENODE_HPP
#define FLUFFY_SCENENODE_HPP

#include <SFML/Graphics/Transformable.hpp>
#include <memory>

namespace Fluffy {
namespace Scene {

class SceneNode : public sf::Transformable
{
public:
    typedef std::unique_ptr<SceneNode> Ptr;

public:
    SceneNode()          = default;
    virtual ~SceneNode() = default;

    void attach(Ptr child);
    Ptr detach(const SceneNode& child);

    sf::Transform         worldTransform() const;
    sf::Vector2f          worldPosition() const;
    virtual sf::FloatRect boundingRect() const;

private:
    std::vector<Ptr> mChildren;
    SceneNode*       mParent = nullptr;
};
}
}

#endif //FLUFFY_SCENENODE_HPP
