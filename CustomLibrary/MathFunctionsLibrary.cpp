#include "MathFunctionsLibrary.h"
#include <iostream>
#include <string>


void MathFunctionsLibrary::MinsteKvadratersMetode(const Eigen::VectorXd x, const Eigen::VectorXd y, std::vector<Vertex>& VertVector, std::vector<Vertex>& FunctionVertVector)
{
	int n = x.size();

	// Build the matrix A
	Eigen::MatrixXd A(n, 3);
	A.col(0) = x.array().square();
	A.col(1) = x;
	A.col(2) = Eigen::VectorXd::Ones(n);

	// Solve the least squares problem: Ax = B
	Eigen::VectorXd coefficients = A.jacobiSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(y);

	// Extract the coefficients
	double a = coefficients(0);
	double b = coefficients(1);
	double c = coefficients(2);

	// Print the results
	std::cout << "Fitted parabola function: y = " << a << "x^2 + " << b << "x + " << c << std::endl;

	// Adding points to vector
	std::cout << "Original data points:" << std::endl;
	std::cout << "x\t y" << std::endl; for (int i = 0; i < n; i++)
	{
		Vertex TempVert;
		TempVert.mPosition.x = x(i);
		TempVert.mPosition.y = y(i);
		std::cout << x(i) << "\t" << y(i) << std::endl;
		VertVector.emplace_back(glm::vec3{TempVert.mPosition.x, TempVert.mPosition.y, 1}, glm::vec3{1, 0.8, 0.2}, glm::vec2{0, 0});
	}

	// Calculate the fitted y values
	Eigen::VectorXd fittedY = A * coefficients;

	// Print the original and fitted data
	std::cout << "Fitted data points:" << std::endl;
	std::cout << "x\t Fitted y" << std::endl;
	for (int i = 0; i < n; ++i)
	{
		Vertex TempVert;
		TempVert.mPosition.x = x(i);
		TempVert.mPosition.y = fittedY(i);
		std::cout << x(i) << "\t" << fittedY(i) << std::endl;
		FunctionVertVector.emplace_back(glm::vec3{TempVert.mPosition.x, TempVert.mPosition.y, 1}, glm::vec3{1, 0.8, 0.2}, glm::vec2{0, 0});
	}
}

void MathFunctionsLibrary::Interpolasjon(float StartVerdi, float SluttVerdi, float opplosning, std::vector<Vertex>& VertVector)
{
	// Define the known values
	Eigen::MatrixXd A(4, 4);
	Eigen::VectorXd b(4);

	// Populate the matrix A and vector b
	A << pow(-2, 3), pow(-2, 2), -2, 1,
		pow(0, 3), pow(0, 2), 0, 1,
		pow(2, 3), pow(2, 2), 2, 1,
		pow(4, 3), pow(4, 2), 4, 1;

	b << 2, -4, 4, -1;

	// Solve the system of equations
	Eigen::VectorXd x = A.colPivHouseholderQr().solve(b);

	// Output the coefficients
	std::cout << "Coefficients: " << std::endl;
	std::cout << "a: " << x(0) << std::endl;
	std::cout << "b: " << x(1) << std::endl;
	std::cout << "c: " << x(2) << std::endl;
	std::cout << "d: " << x(3) << std::endl;

	// Using function to add points into vector to draw the curve
	for (float i = StartVerdi; i <= SluttVerdi; i+=opplosning)
	{
		Vertex TempVec;
		TempVec.mPosition.y = x(0)*pow(i,3) + x(1)*pow(i,2) + x(2)*i + x(3);
		std::cout << "x: " << i << ", y: " << x(0)*pow(i,3) + x(1)*pow(i,2) + x(2)*i + x(3) << "\n";
		VertVector.emplace_back(glm::vec3{i, TempVec.mPosition.y, 1}, glm::vec3{0, .3, .7}, glm::vec2{0, 0});
	}
}