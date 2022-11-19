#include "GraphicsEngine/BaseGame.h"

class Game : public BaseGame
{
private:
	Shape shape;
	Shape squareAuto;
	Sprite padoru;
	Sprite test;
	void Update();
	bool Input(int keycode, float& variable, float modif);
	void Start();
public:
	Game();
	void Play();
};