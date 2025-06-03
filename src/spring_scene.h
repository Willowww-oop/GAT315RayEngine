#pragma once
#include "scene.h"

struct Body;

class spring_scene : public Scene
{
public:
	spring_scene(const std::string& title, int width, int height, const Color& background = BLACK) :
		Scene(title, width, height, background)
	{

	}

	// Inherited via Scene
	void Initialize() override;

	void Update() override;

	void FixedUpdate() override;

	void Draw() override;

	void DrawGUI() override;

private:
	Body* m_selectedBody{ nullptr };
	Body* m_connectBody{ nullptr };

};