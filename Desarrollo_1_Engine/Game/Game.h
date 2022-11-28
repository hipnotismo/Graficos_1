#include "GraphicsEngine/BaseGame.h"
#include "GraphicsEngine/Animation.h"

class Game : public BaseGame
{
private:
	Shape shape;
	Shape squareAuto;
	Sprite padoru;
	Sprite test;
	Sprite link;

	void Update();
	bool Input(int keycode, float& variable, float modif);
	void Start();
	void Delete();

	Animation* leftAnim;
	Animation* rightAnim;
	Animation* upAnim;
	Animation* downAnim;
	Animation* idleRightAnim;
	Animation* idleUpAnim;
	Animation* idleLeftAnim;
	Animation* idleDownAnim;
public:
	Game();
	void Play();
};