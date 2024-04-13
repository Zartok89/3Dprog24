#pragma once

///Includes
#include <vector>
#include <Vertex.h>
#include "Eigen/Dense"

class MathFunctionsLibrary : public Vertex
{
	float a = 0;
	float b = 0;
	float c = 0;
	float x = 0;
	float y = 0;
	float z = 0;
	float u = 0;
	float v = 0;

public:
	std::vector<Vertex> VerticesVector;

	void MinsteKvadratersMetode (const Eigen::VectorXd x,const Eigen::VectorXd y, std::vector<Vertex>& VertVector, std::vector<Vertex>& FunctionVertVector);

	void Interpolasjon(float x, float y, float opplosning, std::vector<Vertex>& VertVector);
};
