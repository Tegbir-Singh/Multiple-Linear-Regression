//Engine header file for Engine class containing all ML models

#pragma once

#include <vector>
#include "LinAlgebra.h"

class Engine {

public:

static std::vector<double>Least_Square_Regression(std::vector<double> xPoints, std::vector<double> YPoints);
static std::vector<double>GenratePoints(std::vector<double> function, std::vector<double> xPoints);
static std::vector<double> Multiple_Linear_Regression(std::vector<std::vector<double>> matrix, std::vector<double> target);
static std::vector<double> Parse_Multiple_Linear_Regression(const char*);


Engine() {

}
~Engine() {

}
};