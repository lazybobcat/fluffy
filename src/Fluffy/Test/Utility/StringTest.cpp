//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 20/05/17.
//

#include <bandit/bandit.h>
#include <Fluffy/Utility/String.hpp>

using namespace bandit;
using namespace snowhouse;

struct UltimateQuestionOfLifeTheUniverseAndEverything
{
    UltimateQuestionOfLifeTheUniverseAndEverything() {}

    int answer = 42;
};

std::ostream& operator<<(std::ostream& os, const UltimateQuestionOfLifeTheUniverseAndEverything& question)
{
    os << question.answer;

    return os;
}

go_bandit([](){
    describe("String Utility", [](){

        describe("replaceAll function", [&]() {

            it("should replace an occurrence", [&](){
                std::string base = "The password is %password%!";
                std::string expected = "The password is Banana!";
                std::string pattern = "%password%", replacement = "Banana", result = base;

                Fluffy::Utility::replaceAll(result, pattern, replacement);
                AssertThat(result, Equals(expected));
            });

            it("should replace several occurrences", [&](){
                std::string base = "The password is %password% because I like %password%!";
                std::string expected = "The password is Banana because I like Banana!";
                std::string pattern = "%password%", replacement = "Banana", result = base;

                Fluffy::Utility::replaceAll(result, pattern, replacement);
                AssertThat(result, Equals(expected));
            });

        });

        describe("printString function", [&]() {

            it("should replace all placeholders", [&](){
                std::string base = "The password is %1 because I like %2... and %1!";
                std::string expected = "The password is Banana because I like Kiwi... and Banana!";

                auto result = Fluffy::Utility::printString(base, {"Banana", "Kiwi"});
                AssertThat(result, Equals(expected));
            });

            it("shouldn't infinite loop replace on itself", [&](){
                std::string base = "The password is %1 because I like %2... and %1!";
                std::string expected = "The password is Banana because I like %1... and Banana!";

                auto result = Fluffy::Utility::printString(base, {"Banana", "%1"});
                AssertThat(result, Equals(expected));
            });

        });

        describe("toString function", [&]() {

            it("should return numeric as string", [&](){
                AssertThat(Fluffy::Utility::toString(42), Equals("42"));
                AssertThat(Fluffy::Utility::toString(42.3), Equals("42.3"));
                AssertThat(Fluffy::Utility::toString(42.f), Equals("42"));

                UltimateQuestionOfLifeTheUniverseAndEverything question;
                AssertThat(Fluffy::Utility::toString(question), Equals("42"));
            });

        });
    });
});