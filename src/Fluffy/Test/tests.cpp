//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 20/05/17.
//

#include <bandit/bandit.h>
#include <bandit/assertion_frameworks/snowhouse/snowhouse/snowhouse.h>

using namespace bandit;
using namespace snowhouse;

go_bandit([](){
    describe("Our first test", [](){
        it("should fail", [&](){
            AssertThat(5, Equals(6));
        });
    });
});

int main(int argc, char* argv[])
{
    return bandit::run(argc, argv);
}