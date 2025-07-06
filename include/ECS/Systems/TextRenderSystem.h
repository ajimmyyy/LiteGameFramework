//
// Created by jimmy on 2025/7/4.
//

#pragma once

#include "IRenderSystem.h"
#include "../EntityManager.h"
#include "../Components/TextComponent.h"
#include "../../Renderer/IRenderer.h"

class TextRenderSystem : public IRenderSystem {
public:
    TextRenderSystem(IRenderer* renderer, EntityManager* entityManager);

    void render(float alpha) override;

private:
    IRenderer* renderer;
    EntityManager* entityManager;
};
