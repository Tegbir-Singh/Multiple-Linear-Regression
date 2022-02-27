//Source file for Engine Class
//All Linear Regression functions are based on least squares method to create function 

#include "Engine.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

//For data with only 1 feature (Output is only dependant on one input)
std::vector<double> Engine::Least_Square_Regression(std::vector<double> xPoints, std::vector<double> YPoints) {

	double MeanX{};
	double MeanY{};
	
	if (xPoints.size() != YPoints.size()) {
		std::cerr << "Error, mismatch in sizes";
	}

	
	for (int i = 0; i < xPoints.size(); ++i) {
		MeanX += xPoints[i];
		MeanY += YPoints[i];
	}
	MeanX /= xPoints.size();
	MeanY /= xPoints.size();


	double count{};
	double count2{};

	for (int i = 1; i < xPoints.size(); ++i) {
		double temp = (xPoints[i] - MeanX) * (YPoints[i] - MeanY);
		count += temp;
		temp = (xPoints[i] - MeanX) * (xPoints[i] - MeanX);
		count2 += temp;
	}

	double slope = count / count2;
	double intercept = MeanY - slope * MeanX;

	std::vector<double> ret(2);

	ret[1] = slope;
	ret[0] = intercept;
	std::cout << "Linear regression function: " << slope << "x + " << intercept << std::endl;

	return ret;

}

//Used to generate points in vector form for plotting using pbPlots library 
std::vector<double> Engine::GenratePoints(std::vector<double> function, std::vector<double> xPoints) {

	std::vector <double> ret(xPoints.size());

	for (int i = 0; i < xPoints.size(); ++i) {
		ret[i] = function[1] * xPoints[i] + function[0];
	}
	//ret[xPoints.size()] = function[xPoints[xPoints.size() - 1] + 3] + function[0];

	return ret;
}

//Will create Linear Regression function for an arbitrary amount of inputs 
std::vector<double> Engine::Multiple_Linear_Regression(std::vector<std::vector<double>> matrix, std::vector<double> target) {

	std::vector<std::vector<double>> vect1Transpose = LinearAlgebra::Transpose(matrix);

	std::vector<std::vector<double>> multi = LinearAlgebra::Matrix_Matrix_Product(vect1Transpose, matrix);

	std::vector<std::vector<double>> inv = LinearAlgebra::Inverse(multi);

	std::vector<double> multiVec = LinearAlgebra::Matrix_Vector_Product(vect1Transpose, target);

	std::vector<double> final = LinearAlgebra::Matrix_Vector_Product(inv, multiVec);
	
	return final;
}

//Will parse given csv file, input data to std::vector , call Engine::Multiple_Linear_Regression and return final function
//Input dataset can be of arbitrarly size
std::vector<double>  Engine::Parse_Multiple_Linear_Regression(const char* fileName) {

	std::ifstream file;
	file.open(fileName);

	std::string currLine{};

	std::vector<std::vector<double>> inputMatrix;

	
	std::string temp{};

	if (!file.is_open()) {

		std::cerr << "Unable to open file";
}


	std::getline(file, currLine);

	while (std::getline(file, currLine)) {

		std::vector <double> lineVec{};

		std::stringstream parseLine(currLine);
		
		while (std::getline(parseLine, temp, ',')) {
			lineVec.push_back(std::atof(temp.c_str()));
		}
		currLine = "";
		inputMatrix.push_back(lineVec);
	}


	std::vector <double> targetVec(inputMatrix.size());

	for (int i = 0; i < inputMatrix.size(); ++i) {
		targetVec[i] = inputMatrix[i][inputMatrix[0].size() - 1];
		
	}

	std::vector<std::vector<double>> RegressionMatrix(inputMatrix.size(), std::vector<double> (inputMatrix[0].size()));

	for (int i = 0; i < RegressionMatrix.size(); ++i) {
		RegressionMatrix[i][0] = 1;
		for (int j = 1; j < RegressionMatrix[0].size() ; ++j) {
			RegressionMatrix[i][j] = inputMatrix[i][j-1];
		}
	}



	std::vector <double> retVec = Multiple_Linear_Regression(RegressionMatrix, targetVec);

	if (retVec.size() > 0) {
		std::cout << "The multiple regression function is:" << std::endl;
		std::cout << "f(X) = " << retVec[0] << "  " ;

		for (int i = 1; i < retVec.size(); ++i) {
			std::cout << std::showpos << retVec[i] << std::noshowpos<< "x" << i << "  ";
		}
			

	}
	else {
		std::cerr << "Error in generating function";
	}

	return retVec;

}