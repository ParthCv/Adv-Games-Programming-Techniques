//
// Created by parth on 9/16/2025.
//

#ifndef ADV_GAME_PROG_TECH_ENTITY_H
#define ADV_GAME_PROG_TECH_ENTITY_H
#include <array>
#include <bitset>
#include <cstddef>

#include "ComponentType.h"

// constant expression computed at start,32 componets fit in 32-bit integers
constexpr std::size_t MAX_COMPONENTS = 32;

// bt set is array with values being 1 or 0, cuz bit opertion are fast
using ComponentBitSet = std::bitset<MAX_COMPONENTS>;
// fixed array size, each index is a component, and index is component type ID
using ComponentArray = std::array<void*, MAX_COMPONENTS>;

class Entity {
    bool active = true;
    ComponentBitSet componentBitSet{};
    ComponentArray componentArray{};
public:
    bool isActive() {
        return active;
    }
    void destroy() {
        active = false;
    }

    template<typename T>
    bool hasComponent() {
        return componentBitSet[getComponentTypeID<T>()];
    }

    template<typename T, typename... nArgs>
    T& addComponent(nArgs&&... args) {
        // perfect forwarding
        T* component = new T(std::forward<nArgs>(args)...);
        componentArray[getComponentTypeID<T>()] = component;
        componentBitSet[getComponentTypeID<T>()] = true;

        return *component;
    }

    template<typename T>
    T& getComponent() {
        auto ptr(componentArray[getComponentTypeID<T>()]);
        return *static_cast<T*>(ptr);
    }

    template<typename T>
    void deactivateComponent() {
        componentBitSet[getComponentTypeID<T>()] = false;
    }

};

#endif //ADV_GAME_PROG_TECH_ENTITY_H
