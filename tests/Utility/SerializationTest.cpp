//
// fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 17/04/18.
//

#include <bandit/bandit.h>
#include <Fluffy/Utility/JsonSerializer.hpp>

using namespace bandit;
using namespace snowhouse;

struct UltimateQuestionSerializable : public Fluffy::Utility::Serializable
{
    UltimateQuestionSerializable() = default;

    std::string question = "What is the answer to the ultimate question of life, the universe and everything?";
    int answer = 42;
    std::array<int, 4> proposal = {{0, 1, 42, 365}};

    void serialize(Json::Value &to) override {
        to["question"] = question;
        to["answer"] = answer;
        for (auto p : proposal) {
            to["proposal"].append(p);
        }
    }

    void deserialize(Json::Value &from) override {
        question = from["question"].asString();
        answer = from["answer"].asInt();
        for (int i = 0; i < 4; ++i) {
            proposal[i] = from["proposal"][i].asInt();
        }
    }
};

go_bandit([](){
    describe("Serialization Utility", [&](){

        it("should generate the correct json", [&](){
            UltimateQuestionSerializable object;
            std::string json;
            std::string expected = "{\"answer\":42,\"proposal\":[0,1,42,365],\"question\":\"What is the answer to the ultimate question of life, the universe and everything?\"}\n";

            Fluffy::Utility::JsonSerializer::serializeToString(object, json);

            AssertThat(json, Equals(expected));
        });

    });
});