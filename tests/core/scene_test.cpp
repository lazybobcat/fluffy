//
// fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 18/04/18.
//

#include <bandit/bandit.h>
#include <fluffy/scene/scene_node.hpp>
#include <fluffy/scene/scene.hpp>
#include <fluffy/serialization/json_serializer.hpp>
#include <fstream>

using namespace bandit;
using namespace snowhouse;

struct RootNode : public Fluffy::SceneNode
{
    SCENE_NODE(RootNode)

    RootNode(std::string&& name) : Fluffy::SceneNode(std::move(name)) {}
};

struct TestNode : public Fluffy::SceneNode
{
    SCENE_NODE(TestNode)

    TestNode(std::string&& name) : Fluffy::SceneNode(std::move(name)) {}

    std::string attack = "High Kick";
    int damage = 6;

    void serializeData(Json::Value &to) override {
        to["attack"] = attack;
        to["damage"] = damage;
    }

    void deserializeData(Json::Value &from) override {
        attack = from["attack"].asString();
        damage = from["damage"].asInt();
    }
};

go_bandit([](){
    describe("Scene", [&](){
        describe("serialize", [&]() {
            it("should serialize the root node", [&]() {
                Fluffy::SceneNode::Ptr root(new RootNode("root"));
                Fluffy::Scene scene(std::move(root));

                Json::Value sceneJson;
                std::string result;
                std::string expected = "{\"root\":{\"data\":null,\"name\":\"root\",\"path\":\"/root\",\"type\":\"RootNode\"}}\n";

                Fluffy::JsonSerializer::serializeToString(scene, result);

                AssertThat(result, Equals(expected));
            });

            it("should serialize the node tree", [&]() {
                Fluffy::SceneNode::Ptr root(new RootNode("root"));
                Fluffy::SceneNode::Ptr child1(new TestNode("child1"));
                Fluffy::SceneNode::Ptr child2(new TestNode("child2"));
                Fluffy::SceneNode::Ptr child21(new TestNode("child21"));
                Fluffy::SceneNode::Ptr child22(new TestNode("child22"));
                child2->attach(std::move(child21));
                child2->attach(std::move(child22));
                root->attach(std::move(child1));
                root->attach(std::move(child2));
                Fluffy::Scene scene(std::move(root));

                Json::Value sceneJson;
                std::string result;
                std::string expected = "{\"root\":{\"children\":[{\"data\":{\"attack\":\"High Kick\",\"damage\":6},\"name\":\"child1\",\"path\":\"/root/child1\",\"type\":\"TestNode\"},{\"children\":[{\"data\":{\"attack\":\"High Kick\",\"damage\":6},\"name\":\"child21\",\"path\":\"/root/child2/child21\",\"type\":\"TestNode\"},{\"data\":{\"attack\":\"High Kick\",\"damage\":6},\"name\":\"child22\",\"path\":\"/root/child2/child22\",\"type\":\"TestNode\"}],\"data\":{\"attack\":\"High Kick\",\"damage\":6},\"name\":\"child2\",\"path\":\"/root/child2\",\"type\":\"TestNode\"}],\"data\":null,\"name\":\"root\",\"path\":\"/root\",\"type\":\"RootNode\"}}\n";

                Fluffy::JsonSerializer::serializeToString(scene, result);

                AssertThat(result, Equals(expected));
            });
        });

        describe("saveToFile", [&]() {
            it("should serialize and save the node tree in a file", [&]() {
                Fluffy::SceneNode::Ptr root(new RootNode("root"));
                Fluffy::SceneNode::Ptr child1(new TestNode("child1"));
                Fluffy::SceneNode::Ptr child2(new TestNode("child2"));
                Fluffy::SceneNode::Ptr child21(new TestNode("child21"));
                Fluffy::SceneNode::Ptr child22(new TestNode("child22"));
                child2->attach(std::move(child21));
                child2->attach(std::move(child22));
                root->attach(std::move(child1));
                root->attach(std::move(child2));
                Fluffy::Scene scene(std::move(root));

                scene.saveToFile("scene.jsc");

                std::ifstream file("scene.jsc");

                AssertThat(file.good(), Equals(true));
                AssertThat(file.is_open(), Equals(true));

                std::string content;
                std::string expected = "{\"root\":{\"children\":[{\"data\":{\"attack\":\"High Kick\",\"damage\":6},\"name\":\"child1\",\"path\":\"/root/child1\",\"type\":\"TestNode\"},{\"children\":[{\"data\":{\"attack\":\"High Kick\",\"damage\":6},\"name\":\"child21\",\"path\":\"/root/child2/child21\",\"type\":\"TestNode\"},{\"data\":{\"attack\":\"High Kick\",\"damage\":6},\"name\":\"child22\",\"path\":\"/root/child2/child22\",\"type\":\"TestNode\"}],\"data\":{\"attack\":\"High Kick\",\"damage\":6},\"name\":\"child2\",\"path\":\"/root/child2\",\"type\":\"TestNode\"}],\"data\":null,\"name\":\"root\",\"path\":\"/root\",\"type\":\"RootNode\"}}\n";
                content.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
                file.close();

                AssertThat(content, Equals(expected));
            });
        });

        it("should find nodes by paths", [&]() {
            Fluffy::SceneNode::Ptr root(new RootNode("root"));
            Fluffy::SceneNode::Ptr child1(new TestNode("child1"));
            Fluffy::SceneNode::Ptr child2(new TestNode("child2"));
            Fluffy::SceneNode::Ptr child3(new TestNode("child3"));
            child2->attach(std::move(child3));
            root->attach(std::move(child1));
            root->attach(std::move(child2));

            Fluffy::Scene scene(std::move(root));

            AssertThat(scene.find("/root"), Is().Not().EqualTo(nullptr));
            AssertThat(scene.find("/root/child1"), Is().Not().EqualTo(nullptr));
            AssertThat(scene.find("/root/child2"), Is().Not().EqualTo(nullptr));
            AssertThat(scene.find("/root/child2/child3"), Is().Not().EqualTo(nullptr));
            AssertThat(scene.find("/root/child2/childX"), IsNull());
        });
    });

    describe("SceneNode", [&]() {
        it("should throw exception when attaching two nodes with the same name", [&]() {
            Fluffy::SceneNode::Ptr root(new RootNode("root"));
            Fluffy::SceneNode::Ptr child1(new TestNode("child1"));
            Fluffy::SceneNode::Ptr child2(new TestNode("child1"));
            root->attach(std::move(child1));

            AssertThrows(std::logic_error, root->attach(std::move(child2)));
        });

        it("should compute the correct paths", [&]() {
            Fluffy::SceneNode::Ptr root(new RootNode("root"));
            Fluffy::SceneNode::Ptr child1(new TestNode("child1"));
            Fluffy::SceneNode::Ptr child2(new TestNode("child2"));
            Fluffy::SceneNode::Ptr child3(new TestNode("child3"));
            child2->attach(std::move(child3));
            root->attach(std::move(child1));
            root->attach(std::move(child2));

            Fluffy::Scene scene(std::move(root));

            AssertThat(scene.find("/root")->path(), Equals("/root"));
            AssertThat(scene.find("/root/child1")->path(), Equals("/root/child1"));
            AssertThat(scene.find("/root/child2")->path(), Equals("/root/child2"));
            AssertThat(scene.find("/root/child2/child3")->path(), Equals("/root/child2/child3"));
        });
    });
});