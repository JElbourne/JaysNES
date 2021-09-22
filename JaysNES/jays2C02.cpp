#include "jays2C02.h"

jays2C02::jays2C02()
{

}

void jays2C02::cpuWrite(uint16_t addr, uint8_t data)
{
	switch (addr)
	{
	case 0x000: // Control
		break;
	case 0x001: // Mask
		break;
	case 0x002: // Status
		break;
	case 0x003: // OAM Address
		break;
	case 0x004: // OAM Data
		break;
	case 0x005: // Scroll
		break;
	case 0x006: // PPU Address
		break;
	case 0x007: // PPU Data
		break;
	}
}

uint8_t jays2C02::cpuRead(uint16_t addr, bool bReadOnly /*= false*/)
{
	uint8_t data = 0x00;

	switch (addr)
	{
	case 0x000: // Control
		break;
	case 0x001: // Mask
		break;
	case 0x002: // Status
		break;
	case 0x003: // OAM Address
		break;
	case 0x004: // OAM Data
		break;
	case 0x005: // Scroll
		break;
	case 0x006: // PPU Address
		break;
	case 0x007: // PPU Data
		break;
	}

	return data;
}

void jays2C02::ppuWrite(uint16_t addr, uint8_t data)
{
	addr &= 0x3FFF;

	if (cart->ppuWrite(addr, data))
	{

	}
}

uint8_t jays2C02::ppuRead(uint16_t addr, bool bReadOnly /*= false*/)
{
	uint8_t data = 0x00;
	addr &= 0x3FFF;

	if (cart->ppuRead(addr, data))
	{

	}

	return data;
}

void jays2C02::ConnectCartridge(const std::shared_ptr<Cartridge>& cartridge)
{
	this->cart = cartridge;
}

void jays2C02::clock()
{

}
