//
// Created by jimmy on 2025/6/28.
//

#pragma once

#include "EntityManager.h"
#include "Entity.h"
#include "System.h"
#include <memory>
#include <vector>

class ECSWorld {
public:
    ECSWorld();

    Entity createEntity();

    template<typename T>
    void addComponent(Entity entity, T component);

    template<typename T>
    T& getComponent(Entity entity);

    void addSystem(const std::shared_ptr<System>& system);

    void update();

    EntityManager& getEntityManager();

private:
    EntityManager entityManager;
    std::vector<std::shared_ptr<System>> systems;
};

#include "ECSWorld.inl"