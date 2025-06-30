//
// Created by jimmy on 2025/6/27.
//

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <string>
#include <stdexcept>
#include <vector>

#include "../../include/Resources/TextureLoader.h"
#include "../../include/Resources/Texture.h"

Texture LoadFromFile(const std::string& path) {
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

    if (!data)
        throw std::runtime_error("Failed to load image: " + path);

    std::vector<unsigned char> pixels(data, data + (width * height * channels));
    stbi_image_free(data);

    return { width, height, channels, std::move(pixels), path };
}
