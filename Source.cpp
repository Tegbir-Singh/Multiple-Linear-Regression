//Main file for testing model

#include <iostream>
#include "pbPlots.hpp"
#include "supportLib.hpp"
#include "vector"
#include "Engine.h"
#include "LinAlgebra.h"
#include <conio.h>

int main() {
	//Driver code for testing
	
	//Example for multiple Linear Regression function
	
	//Enter csv file location
	std::vector<double> Func = Engine::Parse_Multiple_Linear_Regression("C:/Data/Data.csv");
	bool exit{false};

	while (!exit) {
		
		char inChar{};
		std::cout << std::endl;
		std::cout << "To continue press y, to exit on the next iteration press x" << std::endl;
		std::cin >> inChar;

		if (inChar == 'x') {
			exit = true;
		}

		std::cout << "For testing the model, please add in your inputs:" << std::endl;
		
		double predict{};
		double input;
		for (int i = 1; i < Func.size(); ++i) {

			std::cout << "Enter x" << i << " :"; 
			std::cin >> input;
			std::cout<< std::endl;
			predict += Func[i] * input;
		}
		predict += Func[0];

		std::cout << "The model predicts a value of : " << predict << std::endl;

	}
	

	//Example for single Linear Regression function

	//these are feature and label entries
	std::vector <double> x{0.9,1,1.1,1.2,1.3,1.4,1.5,1.6,1.6,1.7,1.7,1.9,2.0};
	std::vector <double> y{7,2,3,9,8,17,2,-1,2,-5,3,1,2};

	//generate function and points through Engine Functions 
	std::vector <double>func = Engine::Least_Square_Regression(x, y);
	std::vector <double> func_points = Engine::GenratePoints(func, x);

	//plot data on 2d plane, using pbPlots:
	RGBABitmapImageReference* imgRef = CreateRGBABitmapImageReference();
	StringReference* error = new StringReference();

	//Draw given data as points
	ScatterPlotSeries* Given_Data = GetDefaultScatterPlotSeriesSettings();
	Given_Data->xs = &x;
	Given_Data->ys = &y;
	Given_Data->pointType = toVector(L"dots");
	Given_Data->color = CreateRGBColor(255, 0, 60);
	Given_Data->linearInterpolation = false;
	
	//Function from Regression
	ScatterPlotSeries* Func_Regression = GetDefaultScatterPlotSeriesSettings();
	Func_Regression->xs = &x;
	Func_Regression->ys = &func_points;
	Func_Regression->lineType = toVector(L"solid");
	Func_Regression->lineThickness = 1;
	Func_Regression->color = CreateRGBColor(0, 0, 1);
	Func_Regression->linearInterpolation = true;


	ScatterPlotSettings* Plot = GetDefaultScatterPlotSettings();
	Plot->scatterPlotSeries->push_back(Given_Data);
	Plot->scatterPlotSeries->push_back(Func_Regression);
	Plot->width = 1920;
	Plot->height = 1080;
	Plot->autoBoundaries = true;
	Plot->autoPadding = true;
	Plot->title = toVector(L"Single Linear Regression Function");
	Plot->xLabel = toVector(L"Input Data (X)");
	Plot->yLabel = toVector(L"Output (Y)");

	DrawScatterPlotFromSettings(imgRef, Plot, error);

	std::vector<double>* pngdata = ConvertToPNG(imgRef->image);
	WriteToFile(pngdata, "Regression.png");
	DeleteImage(imgRef->image);

	return 0;

}
