//
// Created by parth on 9/16/2025.
//

#ifndef ADV_GAME_PROG_TECH_COMPONENTTYPE_H
#define ADV_GAME_PROG_TECH_COMPONENTTYPE_H
#include <cstddef>

// alias component for size, size_t is long long unsigned
using ComponentTypeID = std::size_t;

// inline cuz everytime u include it evey component would hv its own version of this function
inline ComponentTypeID getComponentTypeID() {
    static ComponentTypeID id{0};
    return id++;
}

// template allows us to use generic typed
// overloaded function, template functons are inline by default
template <typename T>
ComponentTypeID getComponentTypeID() {
    static ComponentTypeID type_id = getComponentTypeID();
    return type_id;
}
#endif //ADV_GAME_PROG_TECH_COMPONENTTYPE_H
