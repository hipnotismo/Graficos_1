#include "Shape.h"

Shape::Shape() : Entity2D()
{
}

void Shape::Draw()
{
	renderer->Draw(VertexTriangle, IndexTriangle, model);
}