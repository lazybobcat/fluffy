#include <bandit/bandit.h>
#include <fluffy/fluffy_utils.hpp>

using namespace bandit;
using namespace snowhouse;

go_bandit([](){
    describe("Random utils", [](){

        describe("rand function", [&]() {

            it("should generate an valid int", [&](){
                for (int i = 0; i < 100; ++i) {
                    int r = Fluffy::rand<int>(2, 6);
                    AssertThat(r, IsGreaterThanOrEqualTo(2));
                    AssertThat(r, IsLessThanOrEqualTo(6));
                }
            });

        });
    });
});