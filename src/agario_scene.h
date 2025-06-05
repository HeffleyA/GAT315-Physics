#pragma once
#include "scene.h"

struct Body;

class AgarioScene : public Scene
{
public:
	AgarioScene(const std::string& title, int width, int height, const Color& background = BLACK) :
		Scene(title, width, height, background)
	{
		//
	}

	void Initialize() override;
	void Update() override;
	void FixedUpdate() override;
	void Draw() override;
	void DrawGUI() override;

private:
	Body* m_playerbody{ nullptr };

	float timer = 2.0f;
	float score = 0.0f;
};