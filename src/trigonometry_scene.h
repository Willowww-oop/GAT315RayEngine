#pragma once

#include "scene.h"

class trigonometry_scene : public Scene
{
public:
	trigonometry_scene(const std::string& title, int width, int height, const Color& background = BLACK) :
		Scene(title, width, height, background)
	{

	}

private:


	// Inherited via Scene
	void Initialize() override;

	void Update() override;

	void Draw() override;

	void DrawGUI() override;

};