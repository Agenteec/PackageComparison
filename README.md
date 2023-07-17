# PackageComparison

This utility compares packages between two branches and provides information about packages that are only in one branch, packages with higher versions in one branch, etc.

## Installation

1. Clone the repository:
  git clone https://github.com/Agenteec/PackageComparison.git
2. Change to the project directory:
  cd package-comparison
3. Build the utility:
  cmake -B build
  cmake --build build
4. Install the utility:
  sudo make -C build install

## Usage

To compare packages between two branches, run the following command:
pkgcompare_cli <branch1> <branch2> <path/filename>
    <branch1>: Name of the first branch
    <branch2>: Name of the second branch
    <path/filename>: Path and filename to save the comparison result JSON file (optional)
For example, to compare packages between branches "p10" and "p9" and save the result to "C:/output.json":
pkgcompare_cli p10 p9 C:/output
The utility will display the packages only in each branch and packages with higher versions in the first branch.
