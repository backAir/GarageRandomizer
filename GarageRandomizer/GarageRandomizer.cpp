#include "pch.h"
#include "GarageRandomizer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include <filesystem>

namespace fs = std::filesystem;


class ProductWrapper;
class OnlineProductWrapper;

BAKKESMOD_PLUGIN(GarageRandomizer, "Garage Randomizer", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;
bool coolEnabled = false;



void GarageRandomizer::onLoad()
{
	_globalCvarManager = cvarManager;

	cvarManager->log("Hello I'm GarageRandomizer B)");
	cvarManager->registerNotifier("CoolerBallOnTop", [this](std::vector<std::string> args) {
		ballOnTop();
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("RandomizerLaunch", [this](std::vector<std::string> args) {
		Randomizer();
		}, "", PERMISSION_ALL);

	cvarManager->registerCvar("cool_enabled", "0", "Enable Cool", true, true, 0, true, 1)
		.addOnValueChanged([this](std::string oldValue, CVarWrapper cvar) {
		coolEnabled = cvar.getBoolValue();
			});
	CurrentProfile = "?";
	cvarManager->registerCvar("cool_distance", "200.0", "Distance to place the ball above");
	//cvarManager->log("Plugin loaded!");

	//cvarManager->registerNotifier("my_aweseome_notifier", [&](std::vector<std::string> args) {
	//	cvarManager->log("Hello notifier!");
	//}, "", 0);

	//auto cvar = cvarManager->registerCvar("template_cvar", "hello-cvar", "just a example of a cvar");
	//auto cvar2 = cvarManager->registerCvar("template_cvar2", "0", "just a example of a cvar with more settings", true, true, -10, true, 10 );

	//cvar.addOnValueChanged([this](std::string cvarName, CVarWrapper newCvar) {
	//	cvarManager->log("the cvar with name: " + cvarName + " changed");
	//	cvarManager->log("the new value is:" + newCvar.getStringValue());
	//});

	//cvar2.addOnValueChanged(std::bind(&GarageRandomizer::YourPluginMethod, this, _1, _2));

	// enabled decleared in the header
	//enabled = std::make_shared<bool>(false);
	//cvarManager->registerCvar("TEMPLATE_Enabled", "0", "Enable the TEMPLATE plugin", true, true, 0, true, 1).bindTo(enabled);

	//cvarManager->registerNotifier("NOTIFIER", [this](std::vector<std::string> params){FUNCTION();}, "DESCRIPTION", PERMISSION_ALL);
	//cvarManager->registerCvar("CVAR", "DEFAULTVALUE", "DESCRIPTION", true, true, MINVAL, true, MAXVAL);//.bindTo(CVARVARIABLE);
	//gameWrapper->HookEvent("FUNCTIONNAME", std::bind(&TEMPLATE::FUNCTION, this));
	//gameWrapper->HookEventWithCallerPost<ActorWrapper>("FUNCTIONNAME", std::bind(&GarageRandomizer::FUNCTION, this, _1, _2, _3));
	//gameWrapper->RegisterDrawable(bind(&TEMPLATE::Render, this, std::placeholders::_1));


	//gameWrapper->HookEvent("Function TAGame.Ball_TA.Explode", [this](std::string eventName) {
	//	cvarManager->log("Your hook got called and the ball went POOF");
	//});
	// You could also use std::bind here
	//gameWrapper->HookEvent("Function TAGame.Ball_TA.Explode", std::bind(&GarageRandomizer::YourPluginMethod, this);
}

void GarageRandomizer::onUnload()
{
	cvarManager->log("I was too cool for this world B'(");
}


void GarageRandomizer::ballOnTop() {
	if (!gameWrapper->IsInFreeplay()) { return; }
	ServerWrapper server = gameWrapper->GetCurrentGameState();
	if (!server) { return; }

	if (!coolEnabled) { return; }

	CVarWrapper distanceCVar = cvarManager->getCvar("cool_distance");
	if (!distanceCVar) { return; }
	float distance = distanceCVar.getFloatValue();

	BallWrapper ball = server.GetBall();
	if (!ball) { return; }
	CarWrapper car = gameWrapper->GetLocalCar();
	if (!car) { return; }

	Vector carVelocity = car.GetVelocity();
	ball.SetVelocity(carVelocity);

	Vector carLocation = car.GetLocation();
	float ballRadius = ball.GetRadius();
	ball.SetLocation(carLocation + Vector{ 0, 0, distance });
}


void GarageRandomizer::Randomizer() {

	
	//std::ofstream o("./bakkesmod/plugins/settings/tamer.txt");

	//o << "Hello, World\n" << std::endl;
	if (CurrentProfile== "?") { return; }
	int number_of_lines = 0;
	std::string line;
	std::ifstream myfile("./bakkesmod/plugins/settings/GarageRandomizer/"+ CurrentProfile);

	while (std::getline(myfile, line))
		++number_of_lines;
	std::cout << "Number of lines in text file: " << number_of_lines << "\n";

	if (number_of_lines == 0) { return; }
	string* LineList = new string[number_of_lines];

	int a = 0;
	ifstream file("./bakkesmod/plugins/settings/GarageRandomizer/" +CurrentProfile);
	if (file.is_open())
	{
		string line;
		while (getline(file, line))
		{
			// note that the newline character is not included
			// in the getline() function
			//cout << line << endl;
			LineList[a] = line;
			a++;


		}
	}
	file.close();

	int RandIndex = rand() % number_of_lines;
	
	//cvarManager->executeCommand("omg_preset_equip '"+ LineList[RandIndex]+"'");
	cvarManager->executeCommand("omg_preset_equip '" + LineList[RandIndex] + "'");
	cvarManager->log(LineList[RandIndex]);
	/*
	CarWrapper car = gameWrapper->GetLocalCar();
	cvarManager->log(typeid(car).name());
	*/
}



void GarageRandomizer::RefreshList() {


	}
