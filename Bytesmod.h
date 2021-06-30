#pragma once
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"
#include "version.h"

constexpr auto plugin_version = stringify(VERSION_MAJOR) "." stringify(VERSION_MINOR) "." stringify(VERSION_PATCH) "." stringify(VERSION_BUILD);

class Bytesmod: public BakkesMod::Plugin::BakkesModPlugin, public BakkesMod::Plugin::PluginWindow
{
	//std::shared_ptr<bool> enabled; pointer moment
public:
	virtual void onLoad();
	virtual void onUnload();

	bool isWindowOpen_ = false;
	bool isMinimized_ = false;
	std::string menuTitle_ = "Bytesmod";

	virtual void Render() override;
	virtual std::string GetMenuName() override;
	virtual std::string GetMenuTitle() override;
	virtual void SetImGuiContext(uintptr_t ctx) override;
	virtual bool ShouldBlockInput() override;
	virtual bool IsActiveOverlay() override;
	virtual void OnOpen() override;
	virtual void OnClose() override;
private:
	void DisplayCommands();
	void LoadGUI();
	void AutoFlipReset(std::vector<std::string> params);
};
