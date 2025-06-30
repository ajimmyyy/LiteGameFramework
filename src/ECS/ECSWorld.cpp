//
// Created by jimmy on 2025/6/28.
//

#include "../../include/ECS/ECSWorld.h"

ECSWorld::ECSWorld() = default;

Entity ECSWorld::createEntity() {
    return entityManager.createEntity();
}

void ECSWorld::addSystem(const std::shared_ptr<System>& system) {
    systems.push_back(system);
}

void ECSWorld::update() {
    for (auto& sys : systems) {
        sys->update();
    }
}

EntityManager& ECSWorld::getEntityManager() {
    return entityManager;
}
