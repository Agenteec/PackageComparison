#include "PackageCompare.h"
#include <curl/curl.h>
#include <json/json.h>
// pkgcompare.cpp

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

PackageComparison::PackageComparison() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    std::cout << "PackageComparison..." << std::endl;
}

std::vector<std::string> PackageComparison::getPackageList(const std::string& branch) {
    std::string url = "https://rdb.altlinux.org/api/export/branch_binary_packages/" + branch;
    //
    std::string response;
    CURL* curl = curl_easy_init();
    if (curl) {
        // Установка параметров запроса cURL
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        // Выполнение запроса cURL
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cout << "Error executing cURL request: " << curl_easy_strerror(res) << std::endl;
        }
        else
        {
            std::cout << "Successful executing cURL request"<< std::endl;
        }
        // Освобождение ресурсов cURL
        curl_easy_cleanup(curl);
    }

    // Обработка JSON-ответа с использованием jsoncpp
    Json::Value root;
    Json::CharReaderBuilder builder;
    std::string errs;
    std::istringstream iss(response);
    Json::parseFromStream(builder, iss, &root, &errs);

    // Извлечение списка пакетов из JSON-ответа
    std::vector<std::string> packageList;
    const Json::Value& packages = root["packages"];
    for (const auto& package : packages) {
        const std::string& packageName = package["name"].asString();
        packageList.push_back(packageName);
    }
    return packageList;
}

PackageComparisonResult PackageComparison::comparePackages(const std::string& branch1, const std::string& branch2) {
    // Получение списков пакетов для двух веток
    std::vector<std::string> packageList1 = getPackageList(branch1);
    std::vector<std::string> packageList2 = getPackageList(branch2);

    // Создание результата сравнения
    PackageComparisonResult result;

    // Поиск пакетов, которые есть только в первой ветке
    for (const auto& package : packageList1) {
        if (std::find(packageList2.begin(), packageList2.end(), package) == packageList2.end()) {
            result.packagesOnlyInBranch1.push_back(package);
            std::cout << package << std::endl;
        }
    }

    // Поиск пакетов, которые есть только во второй ветке
    for (const auto& package : packageList2) {
        if (std::find(packageList1.begin(), packageList1.end(), package) == packageList1.end()) {
            result.packagesOnlyInBranch2.push_back(package);
            std::cout << package << std::endl;
        }
    }

    // Поиск пакетов с более высокой версией в первой ветке
    for (const Json::Value& package1 : packageList1) {
        for (const Json::Value& package2 : packageList2) {
            if (package1 == package2) {
                const std::string& packageVersion1 = package1["version"].asString();
                const std::string& packageVersion2 = package2["version"].asString();
                std::cout << package1["version"].asString() << "//\\\\" << package2["version"].asString() << std::endl;
                if (packageVersion1 > packageVersion2) {
                    result.packagesWithHigherVersionInBranch1.push_back(packageVersion1);
                }
                break;
            }
        }
    }

    return result;
}
