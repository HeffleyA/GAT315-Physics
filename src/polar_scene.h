#pragma once
#include "scene.h"

class polarScene : public Scene
{
public:
	polarScene(const std::string& title, int width, int height, const Color& background = BLACK) :
		Scene(title, width, height, background)
	{
		//
	}

	void Initialize() override;
	void Update() override;
	void FixedUpdate() override;
	void Draw() override;
	void DrawGUI() override;

protected:
	void DrawArchimedeanSpiral(float radius, float spacing, int steps);
	void DrawCardioid(float size, int steps);
	void DrawLimacon(float loop, float dimple, int steps);
	void DrawRoseCurve(float size, float petals, int steps);
	void DrawLemniscate(float magnitude, int steps);

};