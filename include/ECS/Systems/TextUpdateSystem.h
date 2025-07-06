//
// Created by jimmy on 2025/7/4.
//

#pragma once

#include "ISystem.h"
#include "../Components/TextComponent.h"
#include "../EntityManager.h"

class TextUpdateSystem : public ISystem {
public:
    TextUpdateSystem(EntityManager* em)
        : entityManager(em) {}

    void update(float deltaTime) override;

private:
    EntityManager* entityManager;
};
