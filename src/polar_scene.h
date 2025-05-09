#pragma once
#include "scene.h"
#include "polar.h"

class polar_scene : public Scene
{
public:
	polar_scene(const std::string& title, int width, int height, const Color& background = BLACK) :
		Scene(title, width, height, background)
	{

	}
	
private:

	// Inherited via Scene
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void DrawGUI() override;

	void DrawArchSpiral(float a, float b, Color& color);
	void DrawCardioid(float a, Color& color);
	void Limacon(float a, float b, Color& color);
	void DrawRose(float a, float k, Color& color);
	void DrawCustom(float a, float b, Color& color);

};