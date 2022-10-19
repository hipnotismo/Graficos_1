#ifndef BASEGAME_H
#define BASEGAME_H
#include "renderer.h"
#include "window.h"
#include "Shape.h"

struct GLFWmonitor;
struct GLFWwindow;

class BaseGame
{
protected:
	Window* window;
	Renderer* renderer;
private:
	void UpdateBegin();
	void UpdateEnd();
	void EngineEnd();
public:
	BaseGame();
	~BaseGame();
	int EngineInit(int width, int height, const char* title);// GLFWmonitor* monitor, GLFWwindow* share);
	int WindowInit(int width, int height, const char* title);
	void RendererInit();

	bool Running();
	void UpdateEngine();
	void virtual Update() = 0;
	void virtual Start() = 0;
};
#endif
