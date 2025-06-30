//
// Created by jimmy on 2025/6/28.
//

#pragma once

template<typename T>
void EntityManager::addComponent(Entity entity, T component) {
    auto& map = getComponentMap<T>();
    map[entity.getId()] = component;
}

template<typename T>
T& EntityManager::getComponent(Entity entity) {
    auto& map = getComponentMap<T>();
    return map.at(entity.getId());
}

template<typename T>
std::unordered_map<uint32_t, T>& EntityManager::getComponentMap() {
    static std::unordered_map<uint32_t, T> map;
    return map;
}