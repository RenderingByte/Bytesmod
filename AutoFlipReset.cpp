#include "pch.h"
#include "Bytesmod.h"
#include "bakkesmod/plugin/bakkesmodplugin.h"

Vector CPosI;
Vector CPos2;
Vector NPosI = { 0,-8,0 };
Vector NPos2 = { 5,0,0 };

Vector CVelI;
Vector NVel = { 5,0,0 };

Rotator CRotI;

int VelDiv = 2;

void Bytesmod::AutoFlipReset()
{
	if (!BytesmodEnabled) { return; }
	if (!gameWrapper->IsInGame()) { return; }
	if (!cvarManager->getCvar("ByteAutoFlipResetEnabled").getBoolValue()) { return; }

	ServerWrapper game = gameWrapper->GetGameEventAsServer();
	ServerWrapper Server = gameWrapper->GetCurrentGameState();
	BallWrapper Ball = Server.GetBall();

	if (Server.IsNull()) { return; }
	if (Ball.IsNull()) { return; }

	auto cars = game.GetCars();
	if (cars.Count() == 0) { return; }
	auto car = cars.Get(0);

	if (car.IsOnGround() || car.IsOnWall()) { return; }

	CPosI = car.GetLocation();
	CVelI = car.GetVelocity();
	CRotI = car.GetRotation();

	Ball.SetLocation({ CPosI + NPosI });

	gameWrapper->SetTimeout([this](...)
	{
		CorrectNewBPos();
	}, 0.1);

	CVelI = car.GetVelocity();
	Ball.SetVelocity(CVelI + NVel);

	car.SetLocation(CPosI);
	car.SetRotation(CRotI);
}

void Bytesmod::CorrectNewBPos()
{
	if (!BytesmodEnabled) { return; }
	if (!gameWrapper->IsInGame()) { return; }
	if (!cvarManager->getCvar("ByteAutoFlipResetEnabled").getBoolValue()) { return; }

	ServerWrapper Server = gameWrapper->GetCurrentGameState();
	if (Server.IsNull()) { return; }

	BallWrapper Ball = Server.GetBall();
	if (Ball.IsNull()) { return; }

	CVelI.X = CVelI.X / VelDiv;
	CVelI.Y = CVelI.Y / VelDiv;
	CVelI.Z = CVelI.Z / VelDiv;

	CPos2 = {CPosI + CVelI};

	Ball.SetLocation({CPos2 + NPos2});
}

// big math moment tho