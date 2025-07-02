//
// Created by jimmy on 2025/6/28.
//

#pragma once

#include "IRenderSystem.h"
#include "../EntityManager.h"
#include "../Components/RenderComponent.h"
#include "../../Renderer/IRenderer.h"

class RenderSystem : public IRenderSystem {
public:
    RenderSystem(IRenderer* renderer, EntityManager* entityManager);

    void render(float alpha) override;

private:
    IRenderer* renderer;
    EntityManager* entityManager;
};