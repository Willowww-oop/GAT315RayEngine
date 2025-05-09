#pragma once
#include "scene.h"

struct Body;

class vector_scene : public Scene
{
public:
	vector_scene(const std::string& title, int width, int height, const Color& background = BLACK) :
		Scene(title, width, height, background)
	{

	}

	// Inherited via Scene
	void Initialize() override;

	void Update() override;

	void Draw() override;

	void DrawGUI() override;

private:
	Body* m_head{ nullptr };
	Body* m_player{ nullptr };
};