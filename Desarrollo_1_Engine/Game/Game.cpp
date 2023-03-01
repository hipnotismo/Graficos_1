#include "Game.h"

static const char* s_MapTiles =
"WWWWWWWWWWWWWWWWWWWWWWWW"
"WGGWWWWWWWGGGGGGGGGGGGGW"
"WGGGGGWWGGGGGGGGGGGGGGGW"
"WGGGGGGGGGGGGGGGGGGGGGGW"
"WGGGGGGGGGGWWWWWGGGGGGGW"
"WGGGGGGGGGGGGGGGGGGGGGGW"
"WGGGGGGGGGGGGGGGGGGGGGGW"
"WGGWWGGGGGGGGGGGGGGGGGGW"
"WGGGGWWWWWWWGGGGGWWWGGGW"
"WGGGGGGGGGGGGGGWWWWGGGGW"
"WGGGWWWWGGGGGGGGGGGGGGGW"
"WWWWWWWWWWWWWWWWWWWWWWWW"
;

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
	
	char tileType = s_MapTiles[24];
	std::cout << tileType << std::endl;

	std::string tileMapPath = "Res/Sprites/letsTry.tmj";

	/*shape.SetPosition(1.0f, 0.0f, 0.0f);
	squareAuto.SetPosition(1.0f, 0.0f, 0.0f);*/
	padoru = Sprite("Res/Sprites/padoru.png");
	test = Sprite("Res/Sprites/map.png");
	link = Sprite("Res/Sprites/link.png");

	//tile = TileMap(tileMapPath);
	tile = TileMap(s_MapTiles,"Res/Sprites/map.png",24);

	test2 = new Animation();

	/*test2->AddFrame(-10, 0, 15, 15, 202, 185, 10);
	test.SetAnimation(test2);*/
	float tileX = 200.0f, tileY = -100.0f, _tileWidth = 43, _tileHeight = 43;
	int _imageWidth = 763, _imageHeight = 349;

	test.SetTextureCoordinate(tileX / _imageWidth, tileY / _imageHeight,
		(tileX + _tileWidth) / _imageWidth, tileY / _imageHeight,
		tileX / _imageWidth, (tileY + _tileHeight) / _imageHeight,
		(tileX + _tileWidth) / _imageWidth, (tileY + _tileHeight) / _imageHeight);


	test.SetPosition(-0.5f, 0.0f, -1.0f);
	test.Scale(1.0f, 1.0f, 1.0f);

	padoru.SetPosition(-1.5f, 0.0f, -1.0f);
	padoru.Scale(1.0f, 1.0f, 1.0f);
	padoru.weight = 90;

	padoru.canCollision = true;
	link.canCollision = true;
	link.strength = 0;

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
	link.SetPosition(1.0f, 2.0f, -1.0f);

}
float a = 1.0f;
float cameraX = 0.1f;
float cameraY = 0.1f;
float cameraZ = 0.1f;

const float valueModif = 0.001f;

float testX = -0.5f;
void Game::Update()
{
	a += 0.001;
	////shape.Rotate(0, 0, a);
	///*shape.Scale(0.1 + a, 1, 1);
	//shape.SetPosition(-1 + a, 0, 0);
	//squareAuto.Draw();*/

	CameraMove(cameraX, cameraY, cameraZ);

	//squareAuto.Rotate(0.0f, 0.0f, 0.0f + a);

	//squareAuto.Draw();
	//shape.Draw();

	//Input(KEYCODE_A, cameraX, -valueModif);

	Input(KEYCODE_1, testX, valueModif);

	if (GetKey(KEYCODE_A))
	{
		linkState = Sleft;
		link.SetAnimation(leftAnim);
		link.SetPosition(link.GetPositionX() - 0.1f, link.GetPositionY(), link.GetPositionZ());
	}
	else if (linkState == Sleft)
	{
		link.SetAnimation(idleLeftAnim);
	}
	if (GetKey(KEYCODE_D))
	{
		linkState = Sright;
		link.SetAnimation(rightAnim);
		link.SetPosition(link.GetPositionX() + 0.1f, link.GetPositionY(), link.GetPositionZ());
	}
	else if (linkState == Sright)
	{
		link.SetAnimation(idleRightAnim);
	}
	if (GetKey(KEYCODE_W))
	{
		linkState = Sup;
		link.SetAnimation(upAnim);
		link.SetPosition(link.GetPositionX(), link.GetPositionY() + 0.1f, link.GetPositionZ());
	}
	else if (linkState == Sup)
	{
		link.SetAnimation(idleUpAnim);
	}
	if (GetKey(KEYCODE_S))
	{
		linkState = Sdown;
		link.SetAnimation(downAnim);
		link.SetPosition(link.GetPositionX(), link.GetPositionY() - 0.1f, link.GetPositionZ());
	}
	else if (linkState == Sdown)
	{
		link.SetAnimation(idleDownAnim);
	}

	test.SetPosition(testX, 0.0f, -1.0f);

	tiles = tile.ReturnCollisions();

	int once = 0;
	if (once=0)
	{
		for (int i = 0; i < tiles.size(); i++) {

			std::cout << "there are" << std::endl;
		}
	}
	
	//link.Rotate(0, 0, a);
	//test.Draw();
	tile.draw();
	padoru.Draw();
	link.CheckCollisionAABB(padoru);
	link.Update();
	link.Draw();
	tile.CollisionTileMap(link);

	
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