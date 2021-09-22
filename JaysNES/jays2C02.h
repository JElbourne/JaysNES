#pragma once

#include <cstdint>
#include <memory>

#include "Cartridge.h"

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
};

