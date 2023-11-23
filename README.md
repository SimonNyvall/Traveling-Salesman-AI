# Genetic Algorithm vs Brute Force Comparison [![C++ Build Workflow](https://github.com/SimonNyvall/Traveling-Salesman-AI/actions/workflows/build.yml/badge.svg)](https://github.com/SimonNyvall/Traveling-Salesman-AI/actions/workflows/build.yml)

## Project overview
This project, developed as part of my gymnasium (high school) studies, demonstrates a comparison between a Genetic Algorithm (GA) and a Brute Force method. The primary aim is to analyze and compare the efficiency and effectiveness of these two approaches in solving optimization problems, such as the Traveling Salesman Problem.

## Features
* Implementation of a Genetic Algorithm for optimization.
* Brute Force approach for comparison.
* Performance analysis between the two methods.
* Use of high-resolution timer for accurate performance measurement.

## Requirements
* C++ Compiler (e.g., GCC, Clang, MSVC)
* C++ Standard: C++11 or later (due to usage of <chrono> and other features)

## Installation

Clone the repository to your local machine:

```bash
git clone https://github.com/SimonNyvall/Traveling-Salesman-AI.git
```

### Usage

Compile the C++ file using your preferred C++ compiler. For example, using g++:
```bash
g++ -o ga_comparison AI/SalemanAI.cpp
```

Run the compiled program:

```bash
./ga_comparison
```

## Implementation Details
* `Genetic Algorithm`: The GA is implemented to optimize the solution by evolving over generations.
* `Brute Force Method`: A straightforward approach is implemented for comparison.
* `Timer Class`: Used for measuring the execution time of both methods.
* `Population and City Initialization`: Sets up the initial state for the GA.
* `Mutation and Fitness Calculation`: Core components of the GA for evolving solutions.

