// main.cpp

#include "PackageCompare.h"
#include <iostream>
#include <chrono>
#include <thread>


bool loading = true;
void showLoadingIndicator() {
    const std::string animation = "|/-\\";
    int animationIndex = 0;

    while (loading) {

        std::cout << "\r";

        std::cout << ANSI_COLOR_YELLOW<< "Loading " << animation[animationIndex];

        animationIndex = (animationIndex + 1) % animation.size();
        std::cout << ANSI_COLOR_RESET;

        std::this_thread::sleep_for(std::chrono::milliseconds(200));

    }
    std::cout << "\r" << ANSI_COLOR_GREEN<< "Loading Complete!" << std::endl;
    std::cout << ANSI_COLOR_RESET;
}

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


#pragma region Debug
//std::thread loadingThread(showLoadingIndicator);
//loading = false;
//loadingThread.join();
//std::cout << "Packages only in branch1:" << std::endl;
//for (const std::string& package : result.packagesOnlyInBranch1) {
//    std::cout << package << std::endl;

//}
//std::cout << "Packages only in branch2:" << std::endl;
//for (const std::string& package : result.packagesOnlyInBranch2) {
//    std::cout << package << std::endl;
//}

//std::cout << "Packages with higher version in branch1:" << std::endl;
//for (const std::string& package : result.packagesWithHigherVersionInBranch1) {
//    std::cout << package << std::endl;
//}
#pragma endregion