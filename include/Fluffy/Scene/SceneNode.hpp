//
// fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 16/04/18.
//

#ifndef FLUFFY_SCENENODE_HPP
#define FLUFFY_SCENENODE_HPP

#include <Fluffy/Utility/Serializable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <memory>

namespace Fluffy {
namespace Scene {

class SceneNode : public sf::Transformable, public Fluffy::Utility::Serializable
{
public:
    typedef std::unique_ptr<SceneNode> Ptr;

public:
    SceneNode()          = default;
    virtual ~SceneNode() = default;

    void attach(Ptr child);
    Ptr detach(const SceneNode& child);

    std::vector<SceneNode*> children() const;

    sf::Transform         worldTransform() const;
    sf::Vector2f          worldPosition() const;
    virtual sf::FloatRect boundingRect() const;

    void serialize(Json::Value& to) override;
    void deserialize(Json::Value& from) override;

private:
    std::vector<Ptr> mChildren;
    SceneNode*       mParent = nullptr;
};
}
}

#endif //FLUFFY_SCENENODE_HPP
