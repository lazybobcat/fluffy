//
// fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 17/04/18.
//

#include <bandit/bandit.h>
#include <fluffy/fluffy_utils.hpp>
#include <fstream>

using namespace bandit;
using namespace snowhouse;

struct UltimateQuestionSerializable : public Fluffy::Serializable
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
    describe("Serialization utils", [&](){

        describe("serialize to json", [&]() {
            it("should serialize to json", [&]() {
                UltimateQuestionSerializable object;
                std::string json;
                std::string expected = "{\"answer\":42,\"proposal\":[0,1,42,365],\"question\":\"What is the answer to the ultimate question of life, the universe and everything?\"}\n";

                bool r = Fluffy::JsonSerializer::serializeToString(object, json);

                AssertThat(json, Equals(expected));
                AssertThat(r, Equals(true));
            });
        });

        describe("deserialize from json", [&]() {
            it("should deserialize from json", [&]() {
                UltimateQuestionSerializable object;
                std::string json = "{\"answer\":365,\"proposal\":[10,20,30,365],\"question\":\"What is the number of days in a year?\"}\n";

                bool r = Fluffy::JsonSerializer::deserializeFromString(json, object);

                AssertThat(object.question, Equals(std::string("What is the number of days in a year?")));
                AssertThat(object.answer, Equals(365));
                AssertThat(object.proposal.size(), Equals(static_cast<unsigned int>(4)));
                AssertThat(object.proposal[0], Equals(10));
                AssertThat(object.proposal[1], Equals(20));
                AssertThat(object.proposal[2], Equals(30));
                AssertThat(object.proposal[3], Equals(365));
                AssertThat(r, Equals(true));
            });

            it("should not alter object and return false if unable to parse json", [&]() {
                UltimateQuestionSerializable object;
                std::string json = "{\"answer\":365,}";

                bool r = Fluffy::JsonSerializer::deserializeFromString(json, object);

                AssertThat(object.question, Equals(std::string("What is the answer to the ultimate question of life, the universe and everything?")));
                AssertThat(object.answer, Equals(42));
                AssertThat(object.proposal.size(), Equals(static_cast<unsigned int>(4)));
                AssertThat(object.proposal[0], Equals(0));
                AssertThat(object.proposal[1], Equals(1));
                AssertThat(object.proposal[2], Equals(42));
                AssertThat(object.proposal[3], Equals(365));
                AssertThat(r, Equals(false));
            });
        });

        describe("serialize to file", [&]() {
            it("should serialize to file", [&]() {
                UltimateQuestionSerializable object;
                std::string filename = "test.json";
                std::string expected = "{\"answer\":42,\"proposal\":[0,1,42,365],\"question\":\"What is the answer to the ultimate question of life, the universe and everything?\"}\n";

                bool r = Fluffy::JsonSerializer::serializeToFile(object, filename);

                std::ifstream file;
                file.open(filename);

                AssertThat(file.is_open(), Equals(true));

                std::string content;
                content.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
                file.close();

                AssertThat(content, Equals(expected));
                AssertThat(r, Equals(true));
            });
        });

        describe("deserialize from json", [&]() {
            it("should deserialize from file", [&]() {
                UltimateQuestionSerializable object;
                std::string filename = "test.json";
                std::string json = "{\"answer\":365,\"proposal\":[10,20,30,365],\"question\":\"What is the number of days in a year?\"}\n";

                std::ofstream file;
                file.open(filename);

                AssertThat(file.is_open(), Equals(true));

                file << json;
                file.close();

                bool r = Fluffy::JsonSerializer::deserializeFromFile(filename, object);

                AssertThat(object.question, Equals(std::string("What is the number of days in a year?")));
                AssertThat(object.answer, Equals(365));
                AssertThat(object.proposal.size(), Equals(static_cast<unsigned int>(4)));
                AssertThat(object.proposal[0], Equals(10));
                AssertThat(object.proposal[1], Equals(20));
                AssertThat(object.proposal[2], Equals(30));
                AssertThat(object.proposal[3], Equals(365));
                AssertThat(r, Equals(true));
            });

//            it("should not alter object and return false if unable to parse file", [&]() {
//                UltimateQuestionSerializable object;
//                std::string filename = "test.json";
//                std::string json = "{\"answer\":365,\"proposal\":[10,20,30,365],\"question\":\"What is the number of days in a year?\"";
//
//                std::ofstream file;
//                file.open(filename);
//
//                AssertThat(file.is_open(), Equals(true));
//
//                file << json;
//                file.close();
//
//                bool r = Fluffy::utils::JsonSerializer::deserializeFromFile(filename, object);
//
//                AssertThat(object.question, Equals(std::string("What is the answer to the ultimate question of life, the universe and everything?")));
//                AssertThat(object.answer, Equals(42));
//                AssertThat(object.proposal.size(), Equals(4));
//                AssertThat(object.proposal[0], Equals(0));
//                AssertThat(object.proposal[1], Equals(1));
//                AssertThat(object.proposal[2], Equals(42));
//                AssertThat(object.proposal[3], Equals(365));
//                AssertThat(r, Equals(false));
//            });
        });

    });
});