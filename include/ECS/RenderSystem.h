//
// Created by jimmy on 2025/6/28.
//

#pragma once

#include "System.h"
#include "EntityManager.h"
#include "RenderComponent.h"
#include "../Renderer/IRenderer.h"

class RenderSystem : public System {
public:
    RenderSystem(IRenderer* renderer, EntityManager* entityManager);

    void update() override;

private:
    IRenderer* renderer;
    EntityManager* entityManager;
};