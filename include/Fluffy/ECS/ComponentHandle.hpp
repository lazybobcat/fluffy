//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 20/05/17.
//

#ifndef FLUFFY_COMPONENTHANDLE_HPP
#define FLUFFY_COMPONENTHANDLE_HPP

namespace Fluffy
{
namespace ECS
{

template <typename T>
class ComponentHandle
{
public:
    ComponentHandle();
    ComponentHandle(T* component);

    T* operator->() const;
    operator bool() const;
    T& get();
    bool isValid() const;

private:
    T*  mComponent;
};

}
}

#include <Fluffy/ECS/ComponentHandle.inl>

#endif //FLUFFY_COMPONENTHANDLE_HPP
