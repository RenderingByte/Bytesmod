#include "pch.h"
#include "Bytesmod.h"
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod\wrappers\GameEvent\TutorialWrapper.h"
#include "bakkesmod\wrappers\GameObject\CarWrapper.h"
#include "bakkesmod\wrappers\GameObject\BallWrapper.h"
#include "utils\parser.h"
#include <sstream>
#include <iomanip>

BAKKESMOD_PLUGIN(Bytesmod, "A Multi-Purpose Plugin For Bakkesmod Developed By Byte.", plugin_version, PLUGINTYPE_FREEPLAY)
std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

void Bytesmod::onLoad()
{
	_globalCvarManager = cvarManager;
	cvarManager->log("\nBytesmod Has Been Loaded Successfully!\nType: Bytesmod_Help For A List Of Commands.");

	cvarManager->registerCvar("ByteAutoFlipResetEnabled", "0", "Enables/Disables Auto Flip Reset Feature.", true, true, 0.f, true, 1.f, true);

	cvarManager->registerNotifier("Bytesmod_Help", [this](std::vector<std::string> params) { DisplayCommands(); }, "Displays A List Of All Current Bytesmod Commands.", PERMISSION_ALL);
	cvarManager->registerNotifier("LoadByteGUI", [this](std::vector<std::string> params) { LoadGUI(); }, "Loads The Bytesmod Plugin GUI.", PERMISSION_ALL);
	cvarManager->registerNotifier("ByteAutoFlipReset", [this](std::vector<std::string> params) { AutoFlipReset(); }, "Automatically Places The Ball Under Your Car To Grant A Flip Reset.", PERMISSION_ALL);

	cvarManager->executeCommand("bind XboxTypeS_LeftTrigger+XboxTypeS_RightTrigger ByteAutoFlipReset");
}

void Bytesmod::onUnload() {} // bruh

void Bytesmod::DisplayCommands()
{
	if (!gameWrapper->IsInGame()) { return; }
	cvarManager->log("\n--------[[BYTESMOD COMMANDS]]--------\n\nBytesmod_Help - Displays this message.\nLoadByteGUI - Loads the Bytesmod Plugin GUI.\n\n-----------------------------------------------------");
}

void Bytesmod::LoadGUI()
{
	if (!gameWrapper->IsInGame()) { return; }
	Render();
}