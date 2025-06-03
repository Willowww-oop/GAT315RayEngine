#pragma once

#include "raylib.h"
#include "world.h"
#include "scene.h"

class GUI
{
public:
	static void Update();
	static void Draw();
	static struct Body* GetBodyInteract(const Vector2& position, bodies_t& bodies, SceneCamera& camera);

public:
	inline static bool mouseOverGUI = false;

    inline static Vector2 anchor01 = { 40, 56 };
    inline static Vector2 anchor02 = { 40, 56 };

    inline static bool PhysicsWindowBoxActive = true;
    inline static float MassPhysicsSliderValue = 2.0f;
    inline static float SizePhysicsSliderValue = 1.0f;
    inline static bool TypePhysicsDropdownEditMode = false;
    inline static int TypePhysicsDropdownActive = 0;
    inline static float GravityScaleSliderValue = 2.5f;
    inline static float DampingPhysicsSliderValue = 1.0f;
    inline static float RestitutionPhysicsSliderValue = 0.2f;
    inline static float WorldGravityPhysicsSliderValue = -9.8f;
    inline static float GravitationPhysicsSliderValue = 0.5f;
    inline static float StiffnessPhysicsSliderValue = 5.0f;
    inline static bool SimulateButtonPressed = false;
};