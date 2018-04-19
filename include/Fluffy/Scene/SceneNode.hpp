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

#define SCENE_NODE(_type) \
    std::string type() const { return #_type; }

namespace Fluffy {
namespace Scene {

class Scene;

class SceneNode : public sf::Transformable, public Fluffy::Utility::Serializable
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
    Ptr detach(const SceneNode& child);

    std::vector<SceneNode*> children() const;

    sf::Transform         worldTransform() const;
    sf::Vector2f          worldPosition() const;
    virtual sf::FloatRect boundingRect() const;

    void serialize(Json::Value& to) final;
    void deserialize(Json::Value& from) final;

protected:
    virtual void serializeData(Json::Value& to);
    virtual void deserializeData(Json::Value& from);

    bool hasChildWithName(const std::string& name);
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
}

#endif //FLUFFY_SCENENODE_HPP
