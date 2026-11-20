#pragma once
#include "OpenGL.h"
#include <filesystem>
#include "json.hpp"

List<char> LevelData;
using json = nlohmann::json;

void LoadLevel(int nLevel) {
	LevelData.clear();

	std::string directory = "Levels\\level" + std::to_string(nLevel) + ".data";
	std::cout << directory << endl;
	std::ifstream file(directory);

	if (!file.is_open())
	{
		std::cout << "Failed to open file!\n";
		assert(0);
	}

	char c;

	while (file.get(c))
	{
		LevelData.append(c);
	}

	std::cout << "Level " << nLevel << " has been loaded sucessfully\n";
	file.close();
}

void createBox(List<Object>& Boxes, vec2 position) {
	Object box;
	box.scale = vec3(2.0f);
	box.position = vec3(9 - 2 * position.x, 0.5f, 10 + position.y * 2);
	Boxes.append(box);
}

void createLevel(List<Object>& Boxes) {
	Boxes.clear();
	int x = 0;
	int y = 0;
	for (int i = 0; i < LevelData.get_size(); i++) {
		int block = LevelData.get(i);
		//std::cout << "Index : " << i << " >> ( " << x << ", " << y << " )" << endl << "Character : " << block << endl;
		if (block == -1) {
			i += 5;
			y += 1;
			x = -1;
		}
		else if (block == -120) {
			createBox(Boxes, vec2(x, y));
		}
		x += 1;
	}
}

int ScreenWidth = 1280;
int ScreenHeight = 720;
bool fullscreen = false;
int Level = 1;
int maxLevel = 1;
bool vsync = false;
bool software = false;

void LoadConfiguration() {
	std::string directory = "settings.conf";
	std::ifstream file(directory);

	if (!file.is_open())
	{
		std::cout << "Failed to open settings.conf!\n";
		assert(0);
	}

	json data;
	file >> data;

	ScreenWidth = data["ScreenWidth"];
	ScreenHeight = data["ScreenHeight"];
	fullscreen = data["fullscreen"];
	vsync = data["vsync"];
	maxLevel = data["maxLevel"];
	Level = data["level"];
	software = data["software"];
	file.close();
}

void setMaxLevel(int NewMaxLevel) {
	json data =
	{
		{"ScreenWidth", ScreenWidth},
		{"ScreenHeight", ScreenHeight},
		{"fullscreen", fullscreen},
		{"vsync", vsync},
		{"maxLevel", NewMaxLevel},
		{"level", Level},
		{"software", software}
	};

	std::ofstream file("settings.conf");

	if (file.is_open()) {
		// Use std::setw(4) to pretty-print with 4 spaces of indentation
		file << std::setw(4) << data << std::endl;
		file.close();
	}
	else {
		std::cerr << "Error: Could not open file for writing.\n";
	}
}

