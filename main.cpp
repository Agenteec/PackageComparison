// main.cpp

#include "PackageCompare.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cout << "Usage: " << argv[0] << " <branch1> <branch2> <path/filename>" << std::endl;
        std::cout << "For example pkgcompare_cli p10 p9 C:/output" << std::endl;
        return 1;
    }

    std::string branch1 = argv[1];
    std::string branch2 = argv[2];
    std::string filename = argv[3];
    PackageComparison pkgComparison;
    PackageComparisonResult result;
    result = pkgComparison.comparePackages(branch1, branch2, filename);
    return 0;
}
