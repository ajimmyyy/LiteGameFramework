//
// Created by jimmy on 2025/6/28.
//

#pragma once

#include "Entity.h"
#include <unordered_map>
#include <cstdint>

class EntityManager {
public:
    Entity createEntity();

    template<typename T>
    void addComponent(Entity entity, T component);

    template<typename T>
    void removeComponent(Entity entity);

    template<typename T>
    T& getComponent(Entity entity);

    template<typename T>
    std::unordered_map<uint32_t, T>& getComponentMap();

private:
    uint32_t nextId = 1;
};

#include "EntityManager.inl"

