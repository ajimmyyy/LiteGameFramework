//
// Created by jimmy on 2025/6/28.
//

#pragma once

#include <memory>
#include "../../resources/Model.h"
#include "../../resources/Texture.h"

struct RenderComponent {
    std::shared_ptr<Model> model;
    std::shared_ptr<Texture> texture;
};