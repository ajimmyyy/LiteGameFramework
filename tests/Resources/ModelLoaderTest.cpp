//
// Created by jimmy on 2025/6/26.
//

#include <catch2/catch_test_macros.hpp>
#include <trompeloeil.hpp>

#include "MockModelLoader.h"
#include "../../include/Resources/ModelLoader.h"
#include "../../include/Resources/ResourceManager.h"

TEST_CASE("ResourceManager ModelLoader Test", "[ModelLoader][Trompeloeil]") {
    ResourceManager::Shutdown();

    // 建立假的模型資料
    Model fakeModel;
    fakeModel.name = "dummy.obj";

    Mesh mesh;
    Vertex v0, v1, v2;
    v0.position = glm::vec3(0.0f, 0.0f, 0.0f);
    v1.position = glm::vec3(1.0f, 0.0f, 0.0f);
    v2.position = glm::vec3(0.0f, 1.0f, 0.0f);

    v0.texCoord = glm::vec2(0.0f, 0.0f);
    v1.texCoord = glm::vec2(1.0f, 0.0f);
    v2.texCoord = glm::vec2(0.0f, 1.0f);

    v0.normal = v1.normal = v2.normal = glm::vec3(0.0f, 0.0f, 1.0f);

    mesh.vertices = {v0, v1, v2};
    mesh.indices = {0, 1, 2};

    fakeModel.meshes.push_back(mesh);

    // 建立 mock 並設定預期行為
    auto mockLoader = std::make_shared<MockModelLoader>();
    REQUIRE_CALL(*mockLoader, LoadFromOBJ("dummy.obj"))
        .TIMES(1)
        .RETURN(fakeModel);

    // 注入 mock
    ResourceManager::SetModelLoader(mockLoader);

    // 執行測試
    auto modelPtr = ResourceManager::LoadModel("dummy.obj");

    REQUIRE(modelPtr != nullptr);
    REQUIRE(modelPtr->meshes.size() == 1);

    const Mesh& resultMesh = modelPtr->meshes[0];

    REQUIRE(resultMesh.vertices.size() == 3);
    REQUIRE(resultMesh.indices.size() == 3);

    CHECK(resultMesh.vertices[0].position == glm::vec3(0.0f, 0.0f, 0.0f));
    CHECK(resultMesh.vertices[1].position == glm::vec3(1.0f, 0.0f, 0.0f));
    CHECK(resultMesh.vertices[2].position == glm::vec3(0.0f, 1.0f, 0.0f));

    CHECK(resultMesh.vertices[0].texCoord == glm::vec2(0.0f, 0.0f));
    CHECK(resultMesh.vertices[1].texCoord == glm::vec2(1.0f, 0.0f));
    CHECK(resultMesh.vertices[2].texCoord == glm::vec2(0.0f, 1.0f));

    CHECK(resultMesh.vertices[0].normal == glm::vec3(0.0f, 0.0f, 1.0f));
    CHECK(resultMesh.vertices[1].normal == glm::vec3(0.0f, 0.0f, 1.0f));
    CHECK(resultMesh.vertices[2].normal == glm::vec3(0.0f, 0.0f, 1.0f));

    CHECK(resultMesh.indices == std::vector<unsigned>{0, 1, 2});
}