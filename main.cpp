// main.cpp

#include "PackageCompare.h"
#include <iostream>

int main() {
    std::cout << "Processing..." << std::endl;
    PackageComparison pkgComparison;
    PackageComparisonResult result = pkgComparison.comparePackages("sisyphus", "p10");

    std::cout << "Packages only in branch1:" << std::endl;
    for (const auto& package : result.packagesOnlyInBranch1) {
        std::cout << package << std::endl;
    }

    std::cout << "Packages only in branch2:" << std::endl;
    for (const auto& package : result.packagesOnlyInBranch2) {
        std::cout << package << std::endl;
    }

    std::cout << "Packages with higher version in branch1:" << std::endl;
    for (const auto& package : result.packagesWithHigherVersionInBranch1) {
        std::cout << package << std::endl;
    }

    return 0;
}