//
// Created by jimmy on 2025/6/28.
//

#include "../../include/ECS/EntityManager.h"

Entity EntityManager::createEntity() {
    return Entity(nextId++);
}
