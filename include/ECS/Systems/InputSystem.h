//
// Created by jimmy on 2025/7/3.
//

#pragma once
#include "ISystem.h"
#include "../EntityManager.h"
#include "../Components/InputComponent.h"
#include "../../Input/InputManager.h"

class InputSystem : public ISystem {
public:
    InputSystem(EntityManager* em, InputManager* im)
        : entityManager(em), inputManager(im) {}

    void update(float deltaTime) override;

private:
    EntityManager* entityManager;
    InputManager* inputManager;
};
