//
// Created by jimmy on 2025/6/28.
//

#pragma once

#include "Entity.h"

template<typename T>
void ECSWorld::addComponent(Entity entity, T component) {
    entityManager.addComponent<T>(entity, component);
}

template<typename T>
T& ECSWorld::getComponent(Entity entity) {
    return entityManager.getComponent<T>(entity);
}