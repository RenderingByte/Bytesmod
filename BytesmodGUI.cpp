#include "pch.h"
#include "Bytesmod.h"
#include "imgui/imgui_internal.h"
#include "IMGUI/imgui_searchablecombo.h"

void Bytesmod::Render()
{
	if (!ImGui::Begin(menuTitle_.c_str(), &isWindowOpen_)) { ImGui::End(); return; }

	ImGui::TextUnformatted("Bytesmod Settings");
	ImGui::Checkbox("Plugin Enabled", &BytesmodEnabled);
	ImGui::TextUnformatted("Auto Flip Reset");
	bool BAFRE = cvarManager->getCvar("ByteAutoFlipResetEnabled").getBoolValue(); if (ImGui::Checkbox("Enabled", &BAFRE)) { cvarManager->getCvar("ByteAutoFlipResetEnabled").setValue(BAFRE); }
	ImGui::End();

	if (!isWindowOpen_) { cvarManager->executeCommand("togglemenu " + GetMenuName()); }
}

// Name of the menu that is used to toggle the window.
std::string Bytesmod::GetMenuName()
{
	return "Bytesmod";
}

// Title to give the menu
std::string Bytesmod::GetMenuTitle()
{
	return menuTitle_;
}

// Don't call this yourself, BM will call this function with a pointer to the current ImGui context
void Bytesmod::SetImGuiContext(uintptr_t ctx)
{
	ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
}

// Should events such as mouse clicks/key inputs be blocked so they won't reach the game
bool Bytesmod::ShouldBlockInput()
{
	return ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantCaptureKeyboard;
}

// Return true if window should be interactive
bool Bytesmod::IsActiveOverlay()
{
	return true;
}

// Called when window is opened
void Bytesmod::OnOpen()
{
	isWindowOpen_ = true;
}

// Called when window is closed
void Bytesmod::OnClose()
{
	isWindowOpen_ = false;
}
