//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 21/05/17.
//

#include <Fluffy/ECS/EntityManager.hpp>

using namespace Fluffy::ECS;
using namespace Fluffy::Utility;

//template <typename... Types>
//EntityComponentView<Types...> EntityManager::each()
//{
//    typename EntityComponentView<Types...>::Iterator first(this, 0, false);
//    typename EntityComponentView<Types...>::Iterator last(this, size(), false);
//
//    return EntityComponentView<Types...>(first, last);
//}