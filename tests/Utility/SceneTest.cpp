//
// fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 18/04/18.
//

#include <bandit/bandit.h>
#include <Fluffy/Scene/SceneNode.hpp>
#include <Fluffy/Scene/Scene.hpp>
#include <Fluffy/Utility/JsonSerializer.hpp>
#include <fstream>

using namespace bandit;
using namespace snowhouse;

struct TestNode : public Fluffy::Scene::SceneNode
{
    TestNode(std::string&& name) : name(name) {}

    std::string name;
    std::string data = "value";

    void serialize(Json::Value &to) override {
        to["name"] = name;
        to["data"] = data;
    }

    void deserialize(Json::Value &from) override {
        name = from["name"].asString();
        data = from["data"].asString();
    }
};

go_bandit([](){
    describe("Scene", [&](){

        describe("serialize", [&]() {
            it("should serialize the root node", [&]() {
                Fluffy::Scene::SceneNode::Ptr root(new TestNode("/root"));
                Fluffy::Scene::Scene scene(std::move(root));

                Json::Value sceneJson;
                std::string result;
                std::string expected = "{\"root\":{\"data\":\"value\",\"name\":\"/root\"}}\n";

                Fluffy::Utility::JsonSerializer::serializeToString(scene, result);

                AssertThat(result, Equals(expected));
            });

            it("should serialize the node tree", [&]() {
                Fluffy::Scene::SceneNode::Ptr root(new TestNode("/root"));
                Fluffy::Scene::SceneNode::Ptr child1(new TestNode("/root/child1"));
                Fluffy::Scene::SceneNode::Ptr child2(new TestNode("/root/child2"));
                Fluffy::Scene::SceneNode::Ptr child21(new TestNode("/root/child21"));
                Fluffy::Scene::SceneNode::Ptr child22(new TestNode("/root/child22"));
                child2->attach(std::move(child21));
                child2->attach(std::move(child22));
                root->attach(std::move(child1));
                root->attach(std::move(child2));
                Fluffy::Scene::Scene scene(std::move(root));

                Json::Value sceneJson;
                std::string result;
                std::string expected = "{\"root\":{\"children\":[{\"data\":\"value\",\"name\":\"/root/child1\"},{\"children\":[{\"data\":\"value\",\"name\":\"/root/child21\"},{\"data\":\"value\",\"name\":\"/root/child22\"}],\"data\":\"value\",\"name\":\"/root/child2\"}],\"data\":\"value\",\"name\":\"/root\"}}\n";

                Fluffy::Utility::JsonSerializer::serializeToString(scene, result);

                AssertThat(result, Equals(expected));
            });
        });

        describe("saveToFile", [&]() {
            it("should serialize and save the node tree in a file", [&]() {
                Fluffy::Scene::SceneNode::Ptr root(new TestNode("/root"));
                Fluffy::Scene::SceneNode::Ptr child1(new TestNode("/root/child1"));
                Fluffy::Scene::SceneNode::Ptr child2(new TestNode("/root/child2"));
                Fluffy::Scene::SceneNode::Ptr child21(new TestNode("/root/child21"));
                Fluffy::Scene::SceneNode::Ptr child22(new TestNode("/root/child22"));
                child2->attach(std::move(child21));
                child2->attach(std::move(child22));
                root->attach(std::move(child1));
                root->attach(std::move(child2));
                Fluffy::Scene::Scene scene(std::move(root));

                scene.saveToFile("scene.jsc");

                std::ifstream file("scene.jsc");

                AssertThat(file.good(), Equals(true));
                AssertThat(file.is_open(), Equals(true));

                std::string content;
                std::string expected = "{\"root\":{\"children\":[{\"data\":\"value\",\"name\":\"/root/child1\"},{\"children\":[{\"data\":\"value\",\"name\":\"/root/child21\"},{\"data\":\"value\",\"name\":\"/root/child22\"}],\"data\":\"value\",\"name\":\"/root/child2\"}],\"data\":\"value\",\"name\":\"/root\"}}\n";
                content.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
                file.close();

                AssertThat(content, Equals(expected));
            });
        });
    });
});