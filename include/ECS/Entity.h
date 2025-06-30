//
// Created by jimmy on 2025/6/28.
//

#pragma once
#include <cstdint>

class Entity {
public:
    explicit Entity(std::uint32_t id = 0) : id(id) {}
    [[nodiscard]] uint32_t getId() const { return id; }

    bool operator==(const Entity& other) const { return id == other.id; }

private:
    uint32_t id;
};

