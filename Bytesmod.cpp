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
	cvarManager->log("Bytesmod Has Been Loaded Successfully!\nType: Bytesmod_Help For A List Of Commands.");

	cvarManager->registerCvar("LoadByteGUI", "0", "Loads The Bytesmod Plugin GUI.", true, false, 0, false, 0, false);
	cvarManager->registerNotifier("LoadByteGUI", [this](std::vector<std::string> params) { LoadGUI(); }, "Loads The Bytesmod Plugin GUI.", PERMISSION_ALL);

	cvarManager->registerCvar("Bytesmod_Help", "0", "Displays A List Of All Current Bytesmod Commands.", true, false, 0, false, 0, false);
	cvarManager->registerNotifier("Bytesmod_Help", [this](std::vector<std::string> params) { DisplayCommands(); }, "Displays A List Of All Current Bytesmod Commands.", PERMISSION_ALL);

	cvarManager->registerCvar("ByteAutoFlipReset", "0", "Automatically Places The Ball Under Your Car To Grant A Flip Reset.", true, true, 0, true, 1, false);
	cvarManager->registerNotifier("ByteAutoFlipReset", [this](std::vector<std::string> params) { AutoFlipReset(params); }, "Automatically Places The Ball Under Your Car To Grant A Flip Reset.", PERMISSION_ALL);
}

void Bytesmod::onUnload() {} // bruh

void Bytesmod::DisplayCommands()
{
	if (!gameWrapper->IsInGame()) { return; }
	cvarManager->log("\n--------[[BYTESMOD COMMANDS]]--------\n\nBytesmod_Help - Displays this message.\nLoadByteGUI - Loads the Bytesmod Plugin GUI.\nByteAutoFlipReset - Automatically Places The Ball Under Your Car To Grant A Flip Reset. | Keybind: L | Usage: [cmd] 0 = Off, [cmd] 1 = On\n\n-----------------------------------------------------");
}

void Bytesmod::LoadGUI()
{
	if (!gameWrapper->IsInGame()) { return; }
	Render();
}

void Bytesmod::AutoFlipReset(std::vector<std::string> params)
{
	if (!gameWrapper->IsInGame()) { return; }
	if (params.at(1) != "0" || "1") { return; }
	cvarManager->log("ur bad " + params.at(1));
}