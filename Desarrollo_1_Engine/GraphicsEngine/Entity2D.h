#ifndef ENTITY2D_H
#define ENTITY2D_H
#include "export.h"
#include "Entity.h"

class Entity2D : public Entity
{
public:
	Entity2D();
	Entity2D(Renderer* renderer);
};

#endif