//
// fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright (c) 2019. All rights reserved.
// File created by loic on 28/04/2019.
//

#include <bandit/bandit.h>
#include <fluffy/state/state.hpp>
#include <fluffy/state/state_stack.hpp>

using namespace bandit;
using namespace snowhouse;

class TestState : public Fluffy::State<TestState>
{

};

// @todo refactor all tests

//go_bandit([](){
//    describe("State", [&](){
//        ServiceContainer serviceContainer;
//        StateStack stateStack(serviceContainer);
//
//        describe("StateStack", [&]() {
//            it("should be empty at initialization", [&]() {
//                AssertThat(stateStack.isEmpty(), Equals(true));
//                AssertThat(stateStack.pendingListSize(), Equals(static_cast<unsigned int>(0)));
//            });
//
//            it("should add pending change when state is pushed", [&]() {
//                stateStack.push<TestState>();
//
//                AssertThat(stateStack.factoriesSize(), Equals(static_cast<unsigned int>(1)));
//                AssertThat(stateStack.pendingListSize(), Equals(static_cast<unsigned int>(1)));
//            });
//        });
//    });
//});