#include "Game.h"

Game::Game()
{
	/*shape = Shape(ShapeType::Triangle);
	squareAuto = Shape(ShapeType::Square);*/

}

void Game::Play()
{
	EngineInit(800, 600, "MY EPIC GAME");
	UpdateEngine();
}

void Game::Start()
{
	/*shape.SetPosition(1.0f, 0.0f, 0.0f);
	squareAuto.SetPosition(1.0f, 0.0f, 0.0f);*/
	padoru = Sprite("Res/Sprites/padoru.png");
	test = Sprite("Res/Sprites/R.png");

	test.SetPosition(-0.5f, 0.0f, -1.0f);
	test.Scale(1.0f, 1.0f, 1.0f);

	padoru.SetPosition(-0.5f, 0.0f, -1.0f);
	padoru.Scale(1.0f, 1.0f, 1.0f);
}
float a = 1.0f;
float cameraX = 0.1f;
float cameraY = 0.1f;
float cameraZ = 0.1f;

void Game::Update()
{
	a += 0.0001;
	////shape.Rotate(0, 0, a);
	///*shape.Scale(0.1 + a, 1, 1);
	//shape.SetPosition(-1 + a, 0, 0);
	//squareAuto.Draw();*/

	//CameraMove(cameraX, cameraY, cameraZ);

	//squareAuto.Rotate(0.0f, 0.0f, 0.0f + a);

	//squareAuto.Draw();
	//shape.Draw();
	test.Draw();
	padoru.Draw();
}