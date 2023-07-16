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
}

int main(int argc, char* argv[]) {
    std::thread loadingThread(showLoadingIndicator);
    PackageComparison pkgComparison;
    PackageComparisonResult result;
    result = pkgComparison.comparePackages("sisyphus", "p10", "123");
    loading = false;
    loadingThread.join();
    std::cout << "Packages only in branch1:" << std::endl;
    for (const std::string& package : result.packagesOnlyInBranch1) {
        std::cout << package << std::endl;

    }
    std::cout << "Packages only in branch2:" << std::endl;
    for (const std::string& package : result.packagesOnlyInBranch2) {
        std::cout << package << std::endl;
    }

    std::cout << "Packages with higher version in branch1:" << std::endl;
    for (const std::string& package : result.packagesWithHigherVersionInBranch1) {
        std::cout << package << std::endl;
    }
    return 0;
}