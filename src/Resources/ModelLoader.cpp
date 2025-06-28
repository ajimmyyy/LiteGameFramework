//
// Created by jimmy on 2025/6/26.
//

#include "../../include/Resources/ModelLoader.h"

#include <sstream>
#include <fstream>
#include <unordered_map>
#include <glm/glm.hpp>

Model ModelLoader::LoadFromOBJ(const std::string& path, ReadTextFunc readFunc) {
    std::string content = readFunc(path);
    std::istringstream stream(content);

    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texCoords;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    std::unordered_map<std::string, unsigned int> uniqueVertexMap;

    std::string line;
    while (std::getline(stream, line)) {
        std::istringstream linestream(line);
        std::string prefix;
        linestream >> prefix;

        if (prefix == "v") {
            glm::vec3 pos;
            linestream >> pos.x >> pos.y >> pos.z;
            positions.push_back(pos);
        } else if (prefix == "vt") {
            glm::vec2 uv;
            linestream >> uv.x >> uv.y;
            texCoords.push_back(uv);
        } else if (prefix == "vn") {
            glm::vec3 normal;
            linestream >> normal.x >> normal.y >> normal.z;
            normals.push_back(normal);
        } else if (prefix == "f") {
            std::vector<std::string> faceVertices;
            std::string vertexStr;
            while (linestream >> vertexStr) {
                faceVertices.push_back(vertexStr);
            }

            if (faceVertices.size() < 3) continue; // 異常跳過

            // triangle fan
            for (size_t i = 1; i + 1 < faceVertices.size(); ++i) {
                std::string v0 = faceVertices[0];
                std::string v1 = faceVertices[i];
                std::string v2 = faceVertices[i + 1];

                for (const std::string& vStr : {v0, v1, v2}) {
                    if (uniqueVertexMap.find(vStr) == uniqueVertexMap.end()) {
                        std::istringstream vss(vStr);
                        std::string v, t, n;
                        std::getline(vss, v, '/');
                        std::getline(vss, t, '/');
                        std::getline(vss, n, '/');

                        int vi = std::stoi(v) - 1;
                        int ti = !t.empty() ? std::stoi(t) - 1 : -1;
                        int ni = !n.empty() ? std::stoi(n) - 1 : -1;

                        Vertex vertex{};
                        vertex.position = positions[vi];
                        if (ti >= 0) vertex.texCoord = texCoords[ti];
                        if (ni >= 0) vertex.normal = normals[ni];

                        vertices.push_back(vertex);
                        uniqueVertexMap[vStr] = vertices.size() - 1;
                    }

                    indices.push_back(uniqueVertexMap[vStr]);
                }
            }
        }
    }

    // 包裝成 Model 結構
    Mesh mesh;
    mesh.vertices = vertices;
    mesh.indices = indices;

    Model model;
    model.name = path;
    model.meshes.push_back(mesh);
    return model;
}
