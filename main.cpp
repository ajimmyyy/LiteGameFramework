#include "include/Core/Game.h"
#include "include/ECS/Components/CameraComponent.h"
#include "include/ECS/Components/RenderComponent.h"
#include "include/ECS/Tags/MainCameraTag.h"

int main(int argc, char** argv) {
    // init
    Game* game = new Game;
    game->init();

    ECSWorld world = game->getECSWorld();
    EntityManager entityManager = world.getEntityManager();

    // create entity
    auto teapot_e = entityManager.createEntity();
    auto teapot_c = RenderComponent(
        ResourceManager::loadModel("../assets/models/teapot.obj")
    );
    entityManager.addComponent(teapot_e, teapot_c);

    auto camera_e = entityManager.createEntity();
    auto camera_c = CameraComponent();
    entityManager.addComponent(camera_e, camera_c);
    entityManager.addComponent(camera_e, MainCameraTag{});

    game->run();
}
