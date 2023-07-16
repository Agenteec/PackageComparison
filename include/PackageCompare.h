#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <curl/curl.h>
#include <json/json.h>
// ”правл€ющие последовательности ANSI дл€ цветов
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
struct PackageComparisonResult {
    std::vector<std::string> packagesOnlyInBranch1;
    std::vector<std::string> packagesOnlyInBranch2;
    std::vector<std::string> packagesWithHigherVersionInBranch1;
    void operator=(const PackageComparisonResult& other)
    {
        packagesOnlyInBranch1 = other.packagesOnlyInBranch1;
        packagesOnlyInBranch2 = other.packagesOnlyInBranch2;
        packagesWithHigherVersionInBranch1 = other.packagesWithHigherVersionInBranch1;
    }
};
struct Package
{
    const std::string name;
    const std::string version;
    Package(const std::string& name, const std::string& version):
        name(name),
        version(version)
    {}
};

class PackageComparison {
public:
    PackageComparison();

    PackageComparisonResult comparePackages(const std::string& branch1, const std::string& branch2, std::string path);

private:
    std::vector<Package> getPackageList(const std::string& branch);
    bool saveJson(const Json::Value& jsonValue, const std::string& name);

    // ‘ункци€ дл€ сравнени€ двух версий
    int compareVersions(const std::string& version1, const std::string& version2);
    Json::Value convertVectorToJsonArray(const std::vector<std::string>& vec);
    std::vector<std::string> splitVersion(const std::string& version);
};