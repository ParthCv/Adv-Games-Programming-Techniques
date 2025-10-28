//
// Created by parth on 10/2/2025.
//

#ifndef ADV_GAME_PROG_TECH_EVENTMANAGER_H
#define ADV_GAME_PROG_TECH_EVENTMANAGER_H
#include <functional>

#include "Entity.h"

struct CollisionEvent {
    Entity* entityA = nullptr;
    Entity* entityB = nullptr;
};

class EventManager {
public:
    // template<typename EventType>
    // void emit(const EventType& event) {
    //     auto& listeners = getListeners<EventType>();
    //     for (auto& listener : listeners) {
    //         listener(event);
    //     }
    // }

    void emit(const CollisionEvent& event) const {
        for (const auto& listener: collisionListeners) {
            listener(event);
        }
    }

    // template<typename EventType>
    // void subscribe(std::function<void(const EventType&)> callback) {
    //     getListeners<EventType>().push_back(callback);
    // }

    void subscribe(std::function<void(const CollisionEvent&)> callback) {
        collisionListeners.emplace_back(callback);
    }

private:
    // template<typename EventType>
    // std::vector<std::function<void(const EventType&)>>& getListeners() {
    //     static std::vector<std::function<void(const EventType&)>> listeners;
    //     return listeners;
    // }

    std::vector<std::function<void(const CollisionEvent&)>> collisionListeners;
};

#endif //ADV_GAME_PROG_TECH_EVENTMANAGER_H