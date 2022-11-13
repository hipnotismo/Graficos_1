#include "GraphicsEngine/BaseGame.h"

class Game : public BaseGame
{
private:
	Shape shape;
	Shape squareAuto;

	void Update();
	void Start();
public:
	Game();
	void Play();
};