#pragma once

#include <cstdint>
#include <array>
#include <memory>

#include "jays6502.h"	// CPU Chip
#include "jays2C02.h"	// PPU Chip
#include "Cartridge.h"	// Game Cartridge

class Bus
{
public:
	Bus();
	~Bus();

	jays6502 cpu;

	jays2C02 ppu;

	std::array<uint8_t, 2048> cpuRam;

	// The Cartridge or "Game Pak"
	std::shared_ptr<Cartridge> cart;

public: // Bus Read & Write
	void cpuWrite(uint16_t addr, uint8_t data);
	uint8_t cpuRead(uint16_t addr, bool bReadOnly = false);

public: // System Interface
	void insertCartridge(const std::shared_ptr<Cartridge>& cartridge);
	void reset();
	void clock();

private:
	// A count of how many clocks have passed
	uint32_t nSystemClockCounter = 0;
};

