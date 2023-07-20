# PackageComparison

This utility compares packages between two branches and provides information about packages that are only in one branch, packages with higher versions in one branch, etc.

## Dependencies

1. JsonCpp: https://github.com/open-source-parsers/jsoncpp/
2. CURL
3. Threads

## Installation

1. Clone the repository:
  git clone https://github.com/Agenteec/PackageComparison.git
2. Change to the project directory:
  cd package-comparison
3. Create a "build" directory in the project's root folder:
 mkdir build
 cd build
4. Run CMake to create project files:
cmake ..
5. Start building the library and utility:
cmake --build .
6. Install the library and utility (by default, they will be installed in /usr/local/lib and /usr/local/bin respectively):
sudo cmake --install .

7. Please note that to install the library and utility on Linux, you may need superuser rights (sudo).
After completing these steps, your library and utility should be installed on the system. You can use the pkgcompare_cli utility to perform package comparisons.

## Usage

To compare packages between two branches, run the following command:
pkgcompare_cli <branch1> <branch2> <path/filename>
    <branch1>: Name of the first branch
    <branch2>: Name of the second branch
    <path/filename>: Path and filename to save the comparison result JSON file (optional)
For example, to compare packages between branches "p10" and "p9" and save the result to "C:/output.json":
pkgcompare_cli p10 p9 C:/output
The utility will display the packages only in each branch and packages with higher versions in the first branch.
