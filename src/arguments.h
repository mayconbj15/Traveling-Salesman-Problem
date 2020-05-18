#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>
#include <locale>
#include <memory>

#include "TSP.h"
#include "algorithms/branchAndBound.h"
#include "algorithms/bruteForce.h"
#include "algorithms/dynamicProgramming.h"
#include "algorithms/geneticAlgorithm.h"

using namespace std;

int csvOutput = 0;

int readAlgorithms(int argc, char **argv, int i, vector<unique_ptr<TSP>> &algorithms)
{
    string branch = "branchandbound";
    string brute = "bruteforce";
    string dynamic = "dynamicprogramming";
    string genetic = "geneticalgorithm";
    string arg = string(argv[i]);
    transform(arg.begin(), arg.end(), arg.begin(), [](char c){
        return tolower(c);
    });

    if (branch.find(arg) != string::npos)
        algorithms.push_back(make_unique<BranchAndBound>());

    else if (brute.find(arg) != string::npos)
        algorithms.push_back(make_unique<BruteForce>());

    else if (dynamic.find(arg) != string::npos)
        algorithms.push_back(make_unique<DynamicProgramming>());

    else if (genetic.find(arg) != string::npos)
        algorithms.push_back(make_unique<GeneticAlgorithm>());

    return i;
}

void showHelp()
{
    printf("-------- TRAVELLING SALESMAN PROBLEM --------\n");
    puts("");
    printf("USAGE: main.exe [-h|--help] [branch|brute|dynamic|genetic]...\n");
    puts("");
    printf("EXAMPLE: main.exe -h\n");
    printf("EXAMPLE: main.exe branch genetic\n");
}

void readArgs(int argc, char **argv, vector<unique_ptr<TSP>> &algorithms)
{
    for (size_t i = 1; i < argc; i++)
    {
        if (argv[i][0] != '-') i = readAlgorithms(argc, argv, i, algorithms);
        else if (strcmp(argv[i], "--csv") == 0) csvOutput = 1;
        else if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0)
        {
            showHelp();
            exit(0);
        }
    }
}
