#pragma once

#include <cstdint>
#include <memory>

#include "Cartridge.h"

#include "olcPixelGameEngine.h"

class jays2C02
{

public:
	
	jays2C02();

private:
	uint8_t tblName[2][1024];
	uint8_t tblPalette[32];
	uint8_t tblPattern[2][4096]; // for fun later, see olc

public:

	void cpuWrite(uint16_t addr, uint8_t data);
	uint8_t cpuRead(uint16_t addr, bool bReadOnly = false);

	void ppuWrite(uint16_t addr, uint8_t data);
	uint8_t ppuRead(uint16_t addr, bool bReadOnly = false);

private:
	// The Cartridge or "Game Pak"
	std::shared_ptr<Cartridge> cart;

public:
	// Interface
	void ConnectCartridge(const std::shared_ptr<Cartridge>& cartridge);
	void clock();

private:
	olc::Pixel	palScreen[0x40];
	olc::Sprite sprScreen = olc::Sprite(256, 240);
	olc::Sprite sprNameTable[2] = { olc::Sprite(256, 240), olc::Sprite(256, 240)};
	olc::Sprite sprPatternTable[2] = { olc::Sprite(128, 128), olc::Sprite(128, 128) };

public:
	// For Debugging
	olc::Sprite& GetScreen();
	olc::Sprite& GetNameTable(uint8_t i);
	olc::Sprite& GetPatternTable(uint8_t i);
	bool frame_complete = false;

private:
	uint16_t scanLine = 0;
	uint16_t cycle = 0;
};

