#include "pch.h"
#include "GarageRandomizer.h"
#include <filesystem>

namespace fs = std::filesystem;

// Don't call this yourself, BM will call this function with a pointer to the current ImGui context
void GarageRandomizer::SetImGuiContext(uintptr_t ctx)
{
	ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
}

// Name of the plugin to be shown on the f2 -> plugins list
std::string GarageRandomizer::GetPluginName()
{
	return "GarageRandomizer";
}
std::string CurrentProfile;

void GarageRandomizer::RenderSettings() {
	ImGui::TextUnformatted("");
	/*
	if (ImGui::Button("Ball On Top")) {
		gameWrapper->Execute([this](GameWrapper* gw) { cvarManager->executeCommand("CoolerBallOnTop"); });
	}

	if (ImGui::IsItemHovered()) {
		ImGui::SetTooltip("Activate Ball On Top");
	}
	*/




		int FileCount = 0;
		std::string path = "./bakkesmod/plugins/settings/GarageRandomizer/";
		for (const auto& entry : fs::directory_iterator(path)) {
			FileCount++;

		}

		static bool* toggles = new bool[FileCount];

		int count = 0;
		std::vector<std::string> names;
		for (const auto& entry : fs::directory_iterator(path)) {
			names.emplace_back(entry.path().string().erase(0, 46));
			toggles[count] = false;
			count++;
		}

		//std::string* names = &directory_contents[0];




		static int selectedProfile = -1;
		//const char* names[] = { "Bream", "Haddock", "Mackerel", "Pollock", "Tilefish" };
		//static bool toggles[] = { true, false, false, false, false };

		// Simple selection popup (if you want to show the current selection inside the Button itself,
		// you may want to build a string using the "###" operator to preserve a constant ID with a variable label)
		if (ImGui::Button("Select profile"))
			ImGui::OpenPopup("my_select_popup");
		ImGui::SameLine();
		ImGui::TextUnformatted(selectedProfile == -1 ? "<None>" : names[selectedProfile].c_str());
		if (ImGui::BeginPopup("my_select_popup"))
		{
			ImGui::Text("Profiles:");
			ImGui::Separator();
			for (int i = 0; i < FileCount; i++) {
				if (ImGui::Selectable(names[i].c_str())) {
					selectedProfile = i;
					CurrentProfile = names[i];
				}
			}
			ImGui::EndPopup();
		}


	//RandomizerLaunch

		if (ImGui::Button("RandomizerLaunch")) {
			gameWrapper->Execute([this](GameWrapper* gw) { cvarManager->executeCommand("RandomizerLaunch"); });
		}

		if (ImGui::IsItemHovered()) {
			ImGui::SetTooltip("Activate Randomizer");
		}

/*

	CVarWrapper enableCvar = cvarManager->getCvar("cool_enabled");

	if (!enableCvar) {
		return;
	}

	bool enabled = enableCvar.getBoolValue();

	if (ImGui::Checkbox("Enable plugin", &enabled)) {
		enableCvar.setValue(enabled);
	}
	if (ImGui::IsItemHovered()) {
		ImGui::SetTooltip("Toggle Cool Plugin");
	}

	CVarWrapper distanceCvar = cvarManager->getCvar("cool_distance");

	if (!distanceCvar) {
		return;
	}

	float distance = distanceCvar.getFloatValue();
	if (ImGui::SliderFloat("Distance", &distance, 0.0, 500.0)) {
		distanceCvar.setValue(distance);
	}
	if (ImGui::IsItemHovered()) {
		std::string hoverText = "distance is " + std::to_string(distance);
		ImGui::SetTooltip(hoverText.c_str());
	}
	*/
}

/*
// Do ImGui rendering here
void GarageRandomizer::Render()
{
	if (!ImGui::Begin(menuTitle_.c_str(), &isWindowOpen_, ImGuiWindowFlags_None))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}
	ImGui::End();
	if (!isWindowOpen_)
	{
		cvarManager->executeCommand("togglemenu " + GetMenuName());
	}
}
// Name of the menu that is used to toggle the window.
std::string GarageRandomizer::GetMenuName()
{
	return "GarageRandomizer";
}
// Title to give the menu
std::string GarageRandomizer::GetMenuTitle()
{
	return menuTitle_;
}
// Don't call this yourself, BM will call this function with a pointer to the current ImGui context
void GarageRandomizer::SetImGuiContext(uintptr_t ctx)
{
	ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
}
// Should events such as mouse clicks/key inputs be blocked so they won't reach the game
bool GarageRandomizer::ShouldBlockInput()
{
	return ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantCaptureKeyboard;
}
// Return true if window should be interactive
bool GarageRandomizer::IsActiveOverlay()
{
	return true;
}
// Called when window is opened
void GarageRandomizer::OnOpen()
{
	isWindowOpen_ = true;
}
// Called when window is closed
void GarageRandomizer::OnClose()
{
	isWindowOpen_ = false;
}
*/