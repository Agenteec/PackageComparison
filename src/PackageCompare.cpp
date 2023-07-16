#include "PackageCompare.h"
// pkgcompare.cpp

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

PackageComparison::PackageComparison() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

std::vector<Package> PackageComparison::getPackageList(const std::string& branch) {

    std::string url = "https://rdb.altlinux.org/api/export/branch_binary_packages/" + branch;
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

            std::cout <<std::endl << "Error executing cURL request: " << curl_easy_strerror(res) << std::endl;
        }
        else
        {
            std::cout << std::endl << "Successful executing cURL request: "<< url << std::endl;
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
    std::vector<Package> packageList;
    const Json::Value& packages = root["packages"];
    for (const auto& package : packages) {
        const std::string& packageName = (package["name"].asString());
        const std::string& packageVersion = (package["version"].asString());
        packageList.push_back(Package(packageName, packageVersion));
    }
    return packageList;
}

bool PackageComparison::saveJson(const Json::Value& jsonValue, const std::string& name = "output")
{
    std::ofstream outputFile(name+".json");
    Json::StreamWriterBuilder writerBuilder;
    std::unique_ptr<Json::StreamWriter> jsonWriter(writerBuilder.newStreamWriter());

    jsonWriter->write(jsonValue, &outputFile);

    outputFile.close();

    std::cout << "JSON file saved successfully." << std::endl;
    return true;
}

std::vector<std::string> PackageComparison::splitVersion(const std::string& version)
{
    std::vector<std::string> result;
    std::istringstream iss(version);
    std::string segment;
    while (std::getline(iss, segment, '.')) {
        result.push_back(segment);
    }
    return result;
}

int PackageComparison::compareVersions(const std::string& version1, const std::string& version2)
{
    std::vector<std::string> v1 = splitVersion(version1);
    std::vector<std::string> v2 = splitVersion(version2);

    // Добавляем нули, чтобы выровнять количество компонент версий
    while (v1.size() < v2.size()) {
        v1.push_back("0");
    }
    while (v2.size() < v1.size()) {
        v2.push_back("0");
    }

    // Постоянное сравнение компонент версий
    for (size_t i = 0; i < v1.size(); i++) {
        if (v1[i] < v2[i]) {
            return -1;
        }
        else if (v1[i] > v2[i]) {
            return 1;
        }
    }

    return 0; // Версии равны
}

Json::Value PackageComparison::convertVectorToJsonArray(const std::vector<std::string>& vec) {
    Json::Value jsonArray(Json::arrayValue);

    for (const auto& item : vec) {
        jsonArray.append(item);
    }

    return jsonArray;
}

PackageComparisonResult PackageComparison::comparePackages(const std::string& branch1, const std::string& branch2, std::string path = "") {
    // Создание результата сравнения
    PackageComparisonResult result;
    // Получение списков пакетов для двух веток
    std::vector<Package> packageList1 = getPackageList(branch1);
    std::vector<Package> packageList2 = getPackageList(branch2);
    std::vector<std::string> packagesInBothBranches;
   

    // Поиск пакетов, которые есть только в первой ветке
    for (size_t i = 0; i < packageList1.size(); i++) {
        bool notExists = true;
        for (size_t j = 0; j < packageList2.size();j++) {
            if (packageList1[i].name == packageList2[j].name) {
                // Поиск пакетов с более высокой версией в первой ветке
                packagesInBothBranches.push_back(packageList1[i].name);
                if (compareVersions(packageList1[i].version, packageList2[j].version) > 0) {
                    result.packagesWithHigherVersionInBranch1.push_back(packageList1[i].name);
                }
                notExists = false;
                break;
            }

        }
        if (notExists)
        {
            result.packagesOnlyInBranch1.push_back(packageList1[i].name);
        }
    }
    // Поиск пакетов, которые есть только во второй ветке
    for (const auto& package : packageList2) {
        auto it = std::find_if(packageList1.begin(), packageList1.end(), [&package](const Package& p) {
            return p.name == package.name;
            });

        if (it == packageList1.end()) {
            result.packagesOnlyInBranch2.push_back(package.name);
        }
    }
    if (path != "")
    {
        Json::Value root;
        root["packagesOnlyInBranch "+ branch1] = convertVectorToJsonArray(result.packagesOnlyInBranch1);
        root["packagesOnlyInBranch "+ branch2] = convertVectorToJsonArray(result.packagesOnlyInBranch2);
        root["packagesWithHigherVersion"] = convertVectorToJsonArray(result.packagesWithHigherVersionInBranch1);
        saveJson(root, path);
    }
    return result;
}