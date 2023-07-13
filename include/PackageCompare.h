#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>


struct PackageComparisonResult {
    std::vector<std::string> packagesOnlyInBranch1;
    std::vector<std::string> packagesOnlyInBranch2;
    std::vector<std::string> packagesWithHigherVersionInBranch1;
};

class PackageComparison {
public:
    PackageComparison();

    PackageComparisonResult comparePackages(const std::string& branch1, const std::string& branch2);

private:
    std::vector<std::string> getPackageList(const std::string& branch);
};