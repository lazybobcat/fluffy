//
// fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright (c) 2019. All rights reserved.
// File created by loic on 26/04/2019.
//

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

            it("should generate an valid float", [&](){
                for (int i = 0; i < 100; ++i) {
                    float r = Fluffy::rand<float>(2.4589, 2.46);
                    AssertThat(r, IsGreaterThanOrEqualTo(2.4589));
                    AssertThat(r, IsLessThanOrEqualTo(2.46));
                }
            });

        });
    });
});