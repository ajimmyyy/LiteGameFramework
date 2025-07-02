//
// Created by jimmy on 2025/6/28.
//

#pragma once

#include <memory>
#include <vector>

#include "EntityManager.h"
#include "Entity.h"
#include "Systems/ISystem.h"
#include "Systems/IRenderSystem.h"
#include "../Renderer/IRenderer.h"

class ECSWorld {
public:
    ECSWorld();

    void init(IRenderer* renderer);

    Entity createEntity();

    template<typename T>
    void addComponent(Entity entity, T component);

    template<typename T>
    T& getComponent(Entity entity);

    void addUpdateSystem(const std::shared_ptr<ISystem>& system);

    void addRenderSystem(const std::shared_ptr<IRenderSystem>& system);

    void update(float deltaTime) const;

    void render(float alpha) const;

    EntityManager& getEntityManager();

private:
    EntityManager entityManager;
    std::vector<std::shared_ptr<ISystem>> updateSystems;
    std::vector<std::shared_ptr<IRenderSystem>> renderSystems;
};

#include "ECSWorld.inl"