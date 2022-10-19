#ifndef SHAPE_H
#define SHAPE_H
#include "export/export.h"
#include "Entity2D.h"

class Shape : public Entity2D
{
private:
	float VertexTriangle[18] = {
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,// X,Y,Z  R,G,B
	 0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f,
	 0.0f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f
	};

	unsigned int IndexTriangle[3] = {
		0, 1, 2
	};
public:
	Shape();
	Shape(Renderer* renderer);
	void Draw();
};

#endif 