#pragma once

#include <Scenes/Scene.hpp>
#include <Inputs/ButtonCompound.hpp>
#include <Uis/UiStartLogo.hpp>
#include "Uis/Panels.hpp"
#include "Uis/OverlayDebug.hpp"

using namespace acid;

namespace test
{
class Scene1 :
	public Scene
{
public:
	Scene1();

	void Start() override;

	void Update() override;

	bool IsPaused() const override;

	void TogglePause();

private:
	ButtonCompound m_buttonPause;

	UiStartLogo m_uiStartLogo;
	OverlayDebug m_overlayDebug;
	Panels m_uiPanels;
};
}
