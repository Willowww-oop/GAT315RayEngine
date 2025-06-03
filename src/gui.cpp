#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "gui.h"

Body* GUI::GetBodyInteract(const Vector2& position, bodies_t& bodies, SceneCamera& camera)
{
	for (auto body : bodies)
	{
		if (CheckCollisionPointCircle(position, body->position, body->size))
		{
			return body;
		}
	}

	return nullptr;
}

void GUI::Update()
{
	mouseOverGUI = PhysicsWindowBoxActive && CheckCollisionPointRec(GetMousePosition(),
		{ anchor01.x + 0, anchor01.y + 0, 208, 624});

	 if (IsKeyPressed(KEY_TAB)) PhysicsWindowBoxActive = !PhysicsWindowBoxActive;
}

void GUI::Draw()
{
	if (PhysicsWindowBoxActive)
	{
        PhysicsWindowBoxActive = !GuiWindowBox(Rectangle { anchor01.x + 0, anchor01.y + 0, 208, 624 }, "Physics");
        GuiLabel(Rectangle { anchor01.x + 32, anchor01.y + 440, 120, 24 }, "World Gravity");
        GuiSliderBar(Rectangle { anchor01.x + 32, anchor01.y + 456, 120, 16 }, NULL, NULL, & World::gravity.y, -20, 20);
        GuiLabel(Rectangle { anchor01.x + 32, anchor01.y + 488, 120, 24 }, "Gravitation");
        GuiSliderBar(Rectangle { anchor01.x + 32, anchor01.y + 504, 120, 16 }, NULL, NULL, & World::gravitation, 0, 1);
        GuiLabel(Rectangle { anchor01.x + 32, anchor01.y + 536, 120, 24 }, "Stiffness");
        GuiSliderBar(Rectangle { anchor01.x + 32, anchor01.y + 552, 120, 16 }, NULL, NULL, & World::springStifnessMultiplier, 0, 5);
        GuiToggle(Rectangle { anchor01.x + 32, anchor01.y + 592, 120, 24 }, "Simulate", &World::simulate);
        if (GuiDropdownBox(Rectangle { 72, 408, 120, 24 }, "Dymanic;Kinematic;Static", & TypePhysicsDropdownActive, TypePhysicsDropdownEditMode)) TypePhysicsDropdownEditMode = !TypePhysicsDropdownEditMode;
        GuiGroupBox(Rectangle { anchor02.x + 16, anchor02.y + 48, 176, 312 }, "Bodys");
        GuiLabel(Rectangle { anchor02.x + 32, anchor02.y + 72, 120, 24 }, "Mass");
        GuiSliderBar(Rectangle { anchor02.x + 32, anchor02.y + 88, 120, 16 }, NULL, NULL, & MassPhysicsSliderValue, 0, 10);
        GuiLabel(Rectangle { anchor02.x + 32, anchor02.y + 120, 120, 24 },   "Size");
        GuiSliderBar(Rectangle { anchor02.x + 32, anchor02.y + 136, 120, 16 }, NULL, NULL, & SizePhysicsSliderValue, 0.1f, 5.0f);
        GuiLabel(Rectangle { anchor02.x + 32, anchor02.y + 168, 120, 24 }, "Gravity Scale");
        GuiSliderBar(Rectangle { anchor02.x + 32, anchor02.y + 184, 120, 16 }, NULL, NULL, & GravityScaleSliderValue, 0, 5);
        GuiLabel(Rectangle { anchor02.x + 32, anchor02.y + 216, 120, 24 }, "Damping");
        GuiSliderBar(Rectangle { anchor02.x + 32, anchor02.y + 232, 120, 16 }, NULL, NULL, & DampingPhysicsSliderValue, 0, 1);
        GuiLabel(Rectangle { anchor02.x + 32, anchor02.y + 264, 120, 24 }, "Restitution");
        GuiSliderBar(Rectangle { anchor02.x + 32, anchor02.y + 280, 120, 16 }, NULL, NULL, & RestitutionPhysicsSliderValue, 0, 1);
	}

	GuiUnlock();
}