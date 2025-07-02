//
// Created by jimmy on 2025/6/28.
//

#include <catch2/catch_test_macros.hpp>
#include <trompeloeil.hpp>

#include "MockModelLoader.h"
#include "MockTextureLoader.h"
#include "../../include/Resources/ResourceManager.h"

class ResourceManagerTestFixture {
protected:
    std::shared_ptr<MockModelLoader> mockModelLoader;
    std::shared_ptr<MockTextureLoader> mockTextureLoader;

    ResourceManagerTestFixture() {
        ResourceManager::shutdown();

        mockModelLoader = std::make_shared<MockModelLoader>();
        mockTextureLoader = std::make_shared<MockTextureLoader>();

        ResourceManager::setModelLoader(mockModelLoader);
        ResourceManager::setTextureLoader(mockTextureLoader);
    }
};

TEST_CASE_METHOD(ResourceManagerTestFixture, "ResourceManager Model loading and caching", "[ResourceManager]") {
    std::string path = "models/sample.obj";

    Model dummyModel;
    dummyModel.name = path;

    // 設定 mock
    REQUIRE_CALL(*mockModelLoader, LoadFromOBJ(path))
        .TIMES(1)
        .RETURN(dummyModel);

    auto model1 = ResourceManager::loadModel(path);
    REQUIRE(model1 != nullptr);
    REQUIRE(model1->name == path);

    // 第二次載入用快取
    auto model2 = ResourceManager::loadModel(path);
    REQUIRE(model2 == model1);

    auto fetched = ResourceManager::getModel(path);
    REQUIRE(fetched == model1);

    auto notLoaded = ResourceManager::getModel("unknown.obj");
    REQUIRE(notLoaded == nullptr);
}

TEST_CASE_METHOD(ResourceManagerTestFixture, "ResourceManager Texture loading and caching", "[ResourceManager]") {
    std::string path = "textures/sample.png";

    Texture dummyTexture;
    dummyTexture.width = 256;
    dummyTexture.height = 256;
    dummyTexture.channels = 4;
    dummyTexture.pixels = std::vector<unsigned char>(256*256*4, 255);

    // 設定 mock
    REQUIRE_CALL(*mockTextureLoader, LoadFromFile(path))
        .TIMES(1)
        .RETURN(dummyTexture);

    auto tex1 = ResourceManager::loadTexture(path);
    REQUIRE(tex1 != nullptr);
    REQUIRE(tex1->width == 256);

    // 第二次載入用快取
    auto tex2 = ResourceManager::loadTexture(path);
    REQUIRE(tex2 == tex1);

    auto fetched = ResourceManager::getTexture(path);
    REQUIRE(fetched == tex1);

    auto notLoaded = ResourceManager::getTexture("missing.png");
    REQUIRE(notLoaded == nullptr);
}

TEST_CASE_METHOD(ResourceManagerTestFixture, "ResourceManager Shutdown clears cache", "[ResourceManager]") {
    std::string modelPath = "models/sample.obj";
    std::string texPath = "textures/sample.png";

    Model dummyModel;
    dummyModel.name = modelPath;

    Texture dummyTexture;
    dummyTexture.width = 256;
    dummyTexture.height = 256;
    dummyTexture.channels = 4;
    dummyTexture.pixels = std::vector<unsigned char>(256*256*4, 255);

    // 設定 mock
    REQUIRE_CALL(*mockModelLoader, LoadFromOBJ(modelPath))
        .TIMES(1)
        .RETURN(dummyModel);

    REQUIRE_CALL(*mockTextureLoader, LoadFromFile(texPath))
        .TIMES(1)
        .RETURN(dummyTexture);

    auto model = ResourceManager::loadModel(modelPath);
    auto tex = ResourceManager::loadTexture(texPath);

    REQUIRE(ResourceManager::getModel(modelPath) != nullptr);
    REQUIRE(ResourceManager::getTexture(texPath) != nullptr);

    ResourceManager::shutdown();

    REQUIRE(ResourceManager::getModel(modelPath) == nullptr);
    REQUIRE(ResourceManager::getTexture(texPath) == nullptr);
}