
#include <iostream>
#include <sstream>

#include "Bus.h"
#include "jays6502.h"

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"



class Demo_jays6502 : public olc::PixelGameEngine
{
public:
	Demo_jays6502() { sAppName = "jays6502 Demonstration"; }

	std::shared_ptr<Cartridge> cart;
	Bus nes;
	std::map<uint16_t, std::string> mapAsm;

	bool bEmulationRun = false;
	float fResidualTime = 0.0f;

	uint8_t nSelectedPalette = 0x00;

	std::string hex(uint32_t n, uint8_t d)
	{
		std::string s(d, '0');
		for (int i = d - 1; i >= 0; i--, n >>= 4)
			s[i] = "0123456789ABCDEF"[n & 0xF];
		return s;
	};

	void DrawRam(int x, int y, uint16_t nAddr, int nRows, int nColumns)
	{
		int nRamX = x, nRamY = y;
		for (int row = 0; row < nRows; row++)
		{
			std::string sOffset = "$" + hex(nAddr, 4) + ":";
			for (int col = 0; col < nColumns; col++)
			{
				sOffset += " " + hex(nes.cpuRead(nAddr, true), 2);
				nAddr += 1;
			}
			DrawString(nRamX, nRamY, sOffset);
			nRamY += 10;
		}
	}

	void DrawCpu(int x, int y)
	{
		std::string status = "STATUS: ";
		DrawString(x, y, "STATUS:", olc::WHITE);
		DrawString(x + 64, y, "N", nes.cpu.status & jays6502::N ? olc::GREEN : olc::RED);
		DrawString(x + 80, y, "V", nes.cpu.status & jays6502::V ? olc::GREEN : olc::RED);
		DrawString(x + 96, y, "-", nes.cpu.status & jays6502::U ? olc::GREEN : olc::RED);
		DrawString(x + 112, y, "B", nes.cpu.status & jays6502::B ? olc::GREEN : olc::RED);
		DrawString(x + 128, y, "D", nes.cpu.status & jays6502::D ? olc::GREEN : olc::RED);
		DrawString(x + 144, y, "I", nes.cpu.status & jays6502::I ? olc::GREEN : olc::RED);
		DrawString(x + 160, y, "Z", nes.cpu.status & jays6502::Z ? olc::GREEN : olc::RED);
		DrawString(x + 178, y, "C", nes.cpu.status & jays6502::C ? olc::GREEN : olc::RED);
		DrawString(x, y + 10, "PC: $" + hex(nes.cpu.pc, 4));
		DrawString(x, y + 20, "A: $" + hex(nes.cpu.a, 2) + "  [" + std::to_string(nes.cpu.a) + "]");
		DrawString(x, y + 30, "X: $" + hex(nes.cpu.x, 2) + "  [" + std::to_string(nes.cpu.x) + "]");
		DrawString(x, y + 40, "Y: $" + hex(nes.cpu.y, 2) + "  [" + std::to_string(nes.cpu.y) + "]");
		DrawString(x, y + 50, "Stack P: $" + hex(nes.cpu.stkp, 4));
	}

	void DrawCode(int x, int y, int nLines)
	{
		auto it_a = mapAsm.find(nes.cpu.pc);
		int nLineY = (nLines >> 1) * 10 + y;
		if (it_a != mapAsm.end())
		{
			DrawString(x, nLineY, (*it_a).second, olc::CYAN);
			while (nLineY < (nLines * 10) + y)
			{
				nLineY += 10;
				if (++it_a != mapAsm.end())
				{
					DrawString(x, nLineY, (*it_a).second);
				}
			}
		}

		it_a = mapAsm.find(nes.cpu.pc);
		nLineY = (nLines >> 1) * 10 + y;
		if (it_a != mapAsm.end())
		{
			while (nLineY > y)
			{
				nLineY -= 10;
				if (--it_a != mapAsm.end())
				{
					DrawString(x, nLineY, (*it_a).second);
				}
			}
		}
	}

	bool OnUserCreate()
	{
		// Load Cartridge
		cart = std::make_shared<Cartridge>("nestest.nes");

		// Insert into NES
		nes.insertCartridge(cart);

		// Extract disassemble
		mapAsm = nes.cpu.disassemble(0x0000, 0xFFFF);

		// Reset NES
		nes.reset();

		return true;
	}

	bool OnUserUpdate(float fElapsedTime)
	{
		Clear(olc::DARK_BLUE);

		if (bEmulationRun)
		{
			if (fResidualTime > 0.f)
			{
				fResidualTime -= fElapsedTime;
			}
			else
			{
				fResidualTime += (1.f / 60.f) - fElapsedTime;
				do { nes.clock(); } while (!nes.ppu.frame_complete);
				nes.ppu.frame_complete = false;
			}

		}
		else
		{
			if (GetKey(olc::Key::C).bPressed)
			{
				do { nes.clock(); } while (!nes.cpu.complete());
				do { nes.clock(); } while (nes.cpu.complete());
			}

			if (GetKey(olc::Key::F).bPressed)
			{
				do { nes.clock(); } while (!nes.ppu.frame_complete);
				do { nes.clock(); } while (!nes.cpu.complete());
				nes.ppu.frame_complete = false;
			}

		}
		if (GetKey(olc::Key::R).bPressed) nes.reset();
		if (GetKey(olc::Key::SPACE).bPressed) bEmulationRun = !bEmulationRun;

		if (GetKey(olc::Key::P).bPressed) (++nSelectedPalette) &= 0x07;

		DrawCpu(516, 2);
		DrawCode(516, 72, 26);

		const int nSwatchSize = 6;
		for (int p = 0; p < 8; p++)
		{
			for (int s = 0; s < 4; s++)
			{
				FillRect(516 + p * (nSwatchSize * 5) + s * nSwatchSize, 340,
					nSwatchSize, nSwatchSize, nes.ppu.GetColourFromPaletteRam(p,s));
			}
		}

		DrawRect(516 + nSelectedPalette * (nSwatchSize * 5) -1, 339, (nSwatchSize * 4), nSwatchSize, olc::WHITE);

		DrawSprite(516, 348, &nes.ppu.GetPatternTable(0, nSelectedPalette));
		DrawSprite(648, 348, &nes.ppu.GetPatternTable(1, nSelectedPalette));

		DrawSprite(0, 0, &nes.ppu.GetScreen(), 2);
		
		return true;
	}
};



int main()
{
	Demo_jays6502 demo;
	demo.Construct(780, 480, 2, 2);
	demo.Start();
	return 0;
}