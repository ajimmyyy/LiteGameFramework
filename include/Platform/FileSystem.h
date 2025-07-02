//
// Created by jimmy on 2025/6/26.
//

#pragma once
#include <string>
#include <vector>

class FileSystem {
public:
    // 讀取純文字檔（例如 .obj, .mtl, .txt）
    static std::string readTextFile(const std::string& path);

    // 讀取二進位檔（例如 .png, .wav）
    static std::vector<char> readBinaryFile(const std::string& path);

    // 檢查檔案是否存在
    static bool exists(const std::string& path);

    // 取得資料夾內的檔案清單
    static std::vector<std::string> listFiles(const std::string& directory);

    // 設定並解析基底資源路徑
    static void setBasePath(const std::string& base);
    static std::string resolvePath(const std::string& relative);

private:
    static std::string basePath;
};
