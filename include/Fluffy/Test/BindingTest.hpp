//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by lo-x on 28/12/15.
//

#ifndef FLUFFY_BINDINGTEST_HPP
#define FLUFFY_BINDINGTEST_HPP

#include <Fluffy/ECS/EntityManager.hpp>
#include <Fluffy/Lua/Bindable.hpp>

namespace Fluffy
{
namespace Test
{

class BindingTest
{
public:
    sel::State state;
    ECS::EntityManager em;

public:
    BindingTest();

    void    testCreateEntity();
};

}
}

#endif //FLUFFY_BINDINGTEST_HPP
