#include "Game.h"

Game::Game()
{
	downAnim = nullptr;
	idleDownAnim = nullptr;
	leftAnim = nullptr;
	idleLeftAnim = nullptr;
	idleRightAnim = nullptr;
	rightAnim = nullptr;
	upAnim = nullptr;
	idleUpAnim = nullptr;
	/*shape = Shape(ShapeType::Triangle);
	squareAuto = Shape(ShapeType::Square);*/

}

void Game::Play()
{
	EngineInit(800, 600, "The tincho game");
	UpdateEngine();
}

enum State
{
	Sleft, Sright, Sup, Sdown
};
State linkState = Sdown;

void Game::Start()
{
	/*shape.SetPosition(1.0f, 0.0f, 0.0f);
	squareAuto.SetPosition(1.0f, 0.0f, 0.0f);*/
	padoru = Sprite("Res/Sprites/padoru.png");
	test = Sprite("Res/Sprites/R.png");
	link = Sprite("Res/Sprites/link.png");

	test.SetPosition(-0.5f, 0.0f, -1.0f);
	test.Scale(1.0f, 1.0f, 1.0f);

	padoru.SetPosition(-0.5f, 0.0f, -1.0f);
	padoru.Scale(1.0f, 1.0f, 1.0f);

	padoru.canCollision = true;
	link.canCollision = true;
	link.strength = 1;

	rightAnim = new Animation();
	rightAnim->AddFrame(0, 0, 96, 104, 961, 831, 0.001, 10);
	upAnim = new Animation();
	upAnim->AddFrame(0, 103, 96, 104, 961, 831, 0.001, 10);
	leftAnim = new Animation();
	leftAnim->AddFrame(2, 208, 96, 102, 961, 831, 0.001, 10);
	downAnim = new Animation();
	downAnim->AddFrame(2, 312, 96, 102, 961, 831, 0.001, 10);
	idleRightAnim = new Animation();
	idleRightAnim->AddFrame(2, 415, 96, 102, 961, 831, 0.007, 3);
	idleUpAnim = new Animation();
	idleUpAnim->AddFrame(2, 517, 96, 102, 961, 831, 0.007, 1);
	idleLeftAnim = new Animation();
	idleLeftAnim->AddFrame(2, 620, 96, 102, 961, 831, 0.007, 3);
	idleDownAnim = new Animation();
	idleDownAnim->AddFrame(2, 723, 96, 102, 961, 831, 0.007, 3);

	link.SetAnimation(idleDownAnim);
	link.SetPosition(1.05f, 0.0f, -1.0f);
	//link.Scale(1.0f, 1.0f, 1.0f);

}
float a = 1.0f;
float cameraX = 0.1f;
float cameraY = 0.1f;
float cameraZ = 0.1f;

const float valueModif = 0.01f;

float testX = -0.5f;
void Game::Update()
{
	a += 0.0001;
	////shape.Rotate(0, 0, a);
	///*shape.Scale(0.1 + a, 1, 1);
	//shape.SetPosition(-1 + a, 0, 0);
	//squareAuto.Draw();*/

	CameraMove(cameraX, cameraY, cameraZ);

	//squareAuto.Rotate(0.0f, 0.0f, 0.0f + a);

	//squareAuto.Draw();
	//shape.Draw();

	Input(KEYCODE_Z, cameraX, -valueModif);
	Input(KEYCODE_X, cameraY, -valueModif);
	Input(KEYCODE_C, cameraZ, -valueModif);

	Input(KEYCODE_V, cameraX, valueModif);
	Input(KEYCODE_B, cameraY, valueModif);
	Input(KEYCODE_N, cameraZ, valueModif);

	Input(KEYCODE_1, testX, valueModif);

	link.Rotate(0, 0, a);

	if (GetKey(KEYCODE_A))
	{
		linkState = Sleft;
		link.SetAnimation(leftAnim);
		link.SetPosition(link.GetPositionX() - 0.001f, link.GetPositionY(), link.GetPositionZ());
	}
	else if (linkState == Sleft)
	{
		link.SetAnimation(idleLeftAnim);
	}
	if (GetKey(KEYCODE_D))
	{
		linkState = Sright;
		link.SetAnimation(rightAnim);
		link.SetPosition(link.GetPositionX() + 0.001f, link.GetPositionY(), link.GetPositionZ());
	}
	else if (linkState == Sright)
	{
		link.SetAnimation(idleRightAnim);
	}
	if (GetKey(KEYCODE_W))
	{
		linkState = Sup;
		link.SetAnimation(upAnim);
		link.SetPosition(link.GetPositionX(), link.GetPositionY() + 0.001f, link.GetPositionZ());
	}
	else if (linkState == Sup)
	{
		link.SetAnimation(idleUpAnim);
	}
	if (GetKey(KEYCODE_S))
	{
		linkState = Sdown;
		link.SetAnimation(downAnim);
		link.SetPosition(link.GetPositionX(), link.GetPositionY() - 0.001f, link.GetPositionZ());
	}
	else if (linkState == Sdown)
	{
		link.SetAnimation(idleDownAnim);
	}

	test.SetPosition(testX, 0.0f, -1.0f);

	//link.Rotate(0, 0, a);
	test.Draw();
	padoru.Draw();
	link.CheckCollisionAABB(padoru);
	link.Update();
	link.Draw();

}

bool Game::Input(int keycode, float& variable, float modif)
{
	if (GetKey(keycode))
	{
		variable += modif;
		return true;
	}
	return false;
}

void Game::Delete()
{
	if (rightAnim) delete rightAnim;
	if (leftAnim) delete leftAnim;
	if (upAnim) delete upAnim;
	if (downAnim) delete downAnim;
	if (idleRightAnim) delete idleRightAnim;
	if (idleUpAnim) delete idleUpAnim;
	if (idleLeftAnim) delete idleLeftAnim;
	if (idleDownAnim) delete idleDownAnim;
}