//Header file for LinearAlgebra class

#pragma once
#include <vector>
class LinearAlgebra {
public:
	LinearAlgebra() {

	}
	~LinearAlgebra() {

	}

	static std::vector<std::vector<double>> Transpose(std::vector<std::vector<double>>);
	static std::vector<std::vector<double>> Inverse(std::vector<std::vector<double>>);
	static std::vector<double> Matrix_Vector_Product(std::vector<std::vector<double>> matrix, std::vector<double> vec);
	static std::vector<std::vector<double>> Matrix_Matrix_Product(std::vector<std::vector<double>> matrix1, std::vector<std::vector<double>> matrix2);
};