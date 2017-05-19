//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by lo-x on 28/12/15.
//

#include <Fluffy/Test/BindingTest.hpp>
#include <Fluffy/definitions.hpp>
#include <cassert>
#include <iostream>

using namespace Fluffy::Test;
using namespace Fluffy::Lua;
using namespace Fluffy::ECS;

BindingTest::BindingTest()
:   state(true),
    em()
{
    em.bind(state);
}

void BindingTest::testCreateEntity()
{
    em.clear();

    auto ent = state["CreateEntity"]();
    assert(ent == FLUFFY_ECS_FIRST_ID);
}