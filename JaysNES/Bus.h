#pragma once

#include <cstdint>
#include <array>

#include "jays6502.h"

class Bus
{
public:
	Bus();
	~Bus();

	jays6502 cpu;

	std::array<uint8_t, 64 * 1024> ram;

	void write(uint16_t addr, uint8_t data);
	uint8_t read(uint16_t addr, bool bReadOnly = false);
};

