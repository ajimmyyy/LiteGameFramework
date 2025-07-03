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
#include "../Platform/IWindow.h"

class ECSWorld {
public:
    ECSWorld();

    void init(IWindow* window, IRenderer* renderer);

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