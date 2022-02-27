//Source file for LinearAlgebra Class
//Functions definitions for transpose, Matrix-Matrix multiplication, Matrix-Vector multiplication and Inverse
//All functions return std::vector<double> or std::vector<std::vector<double>>

#include "LinAlgebra.h"
#include <iostream>
#include <Eigen/Dense>


std::vector<std::vector<double>> LinearAlgebra::Transpose(std::vector<std::vector<double>> matrix) {
	int n = matrix.size();
	int m = matrix[0].size();

	std::vector<std::vector<double>> ret(m, std::vector<double> (n));
	
	for (int i = 0; i < matrix[0].size(); ++i) {
		for (int j = 0; j < matrix.size(); ++j) {
			ret[i][j] = matrix[j][i];
		}
	}
	return ret;
}

 

 std::vector<std::vector<double>> LinearAlgebra::Matrix_Matrix_Product(std::vector<std::vector<double>> matrix1, std::vector<std::vector<double>> matrix2) {

	 int n = matrix1.size();
	 int m = matrix2[0].size();

	 std::vector<std::vector<double>> ret(n, std::vector<double>(m));

	 for (int i = 0; i < n; ++i) {

		 for (int j = 0; j < m; ++j) {

			 double val = 0;

			 for (int k = 0; k < matrix1[0].size(); ++k) {
				 val += matrix1[i][k] * matrix2[k][j];
			 }
			 
			 ret[i][j] = val;
		 }

	 }

	 return ret;

}


 std::vector<double> LinearAlgebra::Matrix_Vector_Product(std::vector<std::vector<double>> matrix, std::vector<double> vec) {

	 int n = matrix.size();
	 int m = vec.size();

	 std::vector<double> ret(n);

	 for (int i = 0; i < n; ++i) {
		 ret[i] = 0;

		 for (int j = 0; j < m; ++j) {

			 ret[i] += matrix[i][j]* vec[j];
		
		 }
	 }

	 return ret;
	
 }

 std::vector<std::vector<double>> LinearAlgebra::Inverse(std::vector<std::vector<double>> matrix) {

	 //Using Eigen Library to compute the inverse
	 //Will store the value and return in vector form after computation 
	 
	 int n = matrix.size();
	 int m = matrix[0].size();

	 if (n != m) {
		 std::cerr << "Error, not square matrix";
	 }

	 Eigen::MatrixXd invMatrix;
	 invMatrix = Eigen::MatrixXd::Zero(n, n);

	 for (int i = 0; i < n; ++i) {
		 for (int j = 0; j < n; ++j) {
			 invMatrix(i, j) = matrix[i][j];
		 }
	 }

	 invMatrix = invMatrix.inverse();

	 for (int i = 0; i < n; ++i) {
		 for (int j = 0; j < n; ++j) {
			 matrix[i][j] = invMatrix(i, j);
		 }
	 }
	 return matrix;
 }

