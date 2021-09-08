#include "jays6502.h"
#include "Bus.h"

jays6502::jays6502()
{
	using a = jays6502;
	lookup =
	{
		{ "BRK", &a::BRK, &a::IMM, 7},{ "ORA", &a::ORA, &a::IZX, 6},{ "???", &a::XXX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "ORA", &a::ORA, &a::ZP0, 3},{ "ASL", &a::ASL, &a::ZP0, 5},{ "???", &a::XXX, &a::IMP, 2},{ "PHP", &a::PHP, &a::IMP, 3},{ "ORA", &a::ORA, &a::IMM, 2},{ "ASL", &a::ASL, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "ORA", &a::ORA, &a::ABS, 4},{ "ASL", &a::ASL, &a::ABS, 6},{ "???", &a::XXX, &a::IMP, 2},
		{ "BPL", &a::BPL, &a::REL, 2},{ "ORA", &a::ORA, &a::IZY, 5},{ "???", &a::XXX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "ORA", &a::ORA, &a::ZPX, 4},{ "ASL", &a::ASL, &a::ZPX, 6},{ "???", &a::XXX, &a::IMP, 2},{ "CLC", &a::PHP, &a::IMP, 2},{ "ORA", &a::ORA, &a::ABY, 4},{ "???", &a::XXX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "ORA", &a::ORA, &a::ABX, 4},{ "ASL", &a::ASL, &a::ABX, 7},{ "???", &a::XXX, &a::IMP, 2},
		{ "JSR", &a::JSR, &a::ABS, 6},{ "AND", &a::AND, &a::INX, 6},{ "???", &a::XXX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "BIT", &a::BIT, &a::ZP0, 3},{ "AND", &a::AND, &a::ZP0, 3},{ "ROL", &a::ROL, &a::ZP0, 5},{ "???", &a::XXX, &a::IMP, 2},{ "PLP", &a::PLP, &a::IMP, 4},{ "AND", &a::AND, &a::IMM, 2},{ "ROL", &a::ROL, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "BIT", &a::BIT, &a::ABS, 4},{ "AND", &a::AND, &a::ABS, 4},{ "ROL", &a::ROL, &a::ABS, 6},{ "???", &a::XXX, &a::IMP, 2},
		{ "BMI", &a::BMI, &a::REL, 2},{ "AND", &a::AND, &a::INY, 5},{ "???", &a::XXX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "AND", &a::AND, &a::ZPX, 4},{ "ROL", &a::ROL, &a::ZPX, 6},{ "???", &a::XXX, &a::IMP, 2},{ "SEC", &a::SEC, &a::IMP, 2},{ "AND", &a::AND, &a::ABY, 4},{ "???", &a::XXX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "AND", &a::AND, &a::ABX, 4},{ "ROL", &a::ROL, &a::ABX, 7},{ "???", &a::XXX, &a::IMP, 2},
		{ "RTI", &a::RTI, &a::IMP, 6},{ "EOR", &a::EOR, &a::INX, 5},{ "???", &a::XXX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "EOR", &a::EOR, &a::ZP0, 3},{ "LSR", &a::LSR, &a::ZP0, 5},{ "???", &a::XXX, &a::IMP, 2},{ "PHA", &a::PHA, &a::IMP, 3},{ "EOR", &a::EOR, &a::IMM, 2},{ "LSR", &a::LSR, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "JMP", &a::JMP, &a::ABS, 3},{ "EOR", &a::EOR, &a::ABS, 4},{ "LSR", &a::LSR, &a::ABS, 6},{ "???", &a::XXX, &a::IMP, 2},
		{ "BVC", &a::BVC, &a::REL, 2},{ "EOR", &a::EOR, &a::INY, 5},{ "???", &a::XXX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "EOR", &a::EOR, &a::ZPX, 4},{ "LSR", &a::LSR, &a::ZPX, 6},{ "???", &a::XXX, &a::IMP, 2},{ "CLI", &a::CLI, &a::IMP, 2},{ "EOR", &a::EOR, &a::ABY, 4},{ "???", &a::XXX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "EOR", &a::EOR, &a::ABX, 4},{ "LSR", &a::LSR, &a::ABX, 7},{ "???", &a::XXX, &a::IMP, 2},
		{ "RTS", &a::RTS, &a::IMP, 6},{ "ADC", &a::ADC, &a::INX, 6},{ "???", &a::XXX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "ADC", &a::ADC, &a::ZP0, 3},{ "ROR", &a::ROR, &a::ZP0, 5},{ "???", &a::XXX, &a::IMP, 2},{ "PLA", &a::PLA, &a::IMP, 4},{ "ADC", &a::ADC, &a::IMM, 2},{ "ROR", &a::ROR, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "JMP", &a::JMP, &a::IND, 5},{ "ADC", &a::ADC, &a::ABS, 4},{ "ROR", &a::ROR, &a::ABS, 6},{ "???", &a::XXX, &a::IMP, 2},
		{ "BVS", &a::BVS, &a::REL, 2},{ "ADC", &a::ADC, &a::INY, 5},{ "???", &a::XXX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "ADC", &a::ADC, &a::ZPX, 4},{ "ROR", &a::ROR, &a::ZPX, 6},{ "???", &a::XXX, &a::IMP, 2},{ "SEI", &a::SEI, &a::IMP, 2},{ "ADC", &a::ADC, &a::ABY, 4},{ "???", &a::XXX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "ADC", &a::ADC, &a::ABX, 4},{ "ROR", &a::ROR, &a::ABX, 7},{ "???", &a::XXX, &a::IMP, 2},
		{ "???", &a::XXX, &a::IMP, 2},{ "STA", &a::STA, &a::INX, 6},{ "???", &a::XXX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "STY", &a::STY, &a::ZP0, 3},{ "STA", &a::STA, &a::ZP0, 3},{ "STX", &a::STX, &a::ZP0, 3},{ "???", &a::XXX, &a::IMP, 2},{ "DEY", &a::DEY, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "TXA", &a::TXA, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "STY", &a::STY, &a::ABS, 4},{ "STA", &a::STA, &a::ABS, 4},{ "STX", &a::STX, &a::ABS, 4},{ "???", &a::XXX, &a::IMP, 2},
		{ "BCC", &a::BCC, &a::REL, 2},{ "STA", &a::STA, &a::INY, 6},{ "???", &a::XXX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "STY", &a::STY, &a::ZPX, 4},{ "STA", &a::STA, &a::ZPX, 4},{ "STX", &a::STX, &a::ZPY, 4},{ "???", &a::XXX, &a::IMP, 2},{ "TYA", &a::TYA, &a::IMP, 2},{ "STA", &a::STA, &a::ABY, 5},{ "TXS", &a::TXS, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "STA", &a::STA, &a::ABX, 5},{ "???", &a::XXX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},
		{ "LDY", &a::LDY, &a::IMM, 2},{ "LDA", &a::LDA, &a::INX, 6},{ "LDX", &a::LDX, &a::IMM, 2},{ "???", &a::XXX, &a::IMP, 2},{ "LDY", &a::LDY, &a::ZP0, 3},{ "LDA", &a::LDA, &a::ZP0, 3},{ "LDX", &a::LDX, &a::ZP0, 3},{ "???", &a::XXX, &a::IMP, 2},{ "TAY", &a::TAY, &a::IMP, 2},{ "LDA", &a::LDA, &a::IMM, 2},{ "TAX", &a::TAX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "LDY", &a::LDY, &a::ABS, 4},{ "LDA", &a::LDA, &a::ABS, 4},{ "LDX", &a::LDX, &a::ABS, 4},{ "???", &a::XXX, &a::IMP, 2},
		{ "BCS", &a::BCS, &a::REL, 2},{ "LDA", &a::LDA, &a::INY, 5},{ "???", &a::XXX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "LDY", &a::LDY, &a::ZPX, 4},{ "LDA", &a::LDA, &a::ZPX, 4},{ "LDX", &a::LDX, &a::ZPY, 4},{ "???", &a::XXX, &a::IMP, 2},{ "CLV", &a::CLV, &a::IMP, 2},{ "LDA", &a::LDA, &a::ABY, 4},{ "TSX", &a::TSX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "LDY", &a::LDY, &a::ABX, 4},{ "LDA", &a::LDA, &a::ABX, 4},{ "LDX", &a::LDX, &a::ABY, 4},{ "???", &a::XXX, &a::IMP, 2},
		{ "CPY", &a::CPY, &a::IMM, 2},{ "CMP", &a::CMP, &a::INX, 6},{ "???", &a::XXX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "CPY", &a::CPY, &a::ZP0, 3},{ "CMP", &a::CMP, &a::ZP0, 3},{ "DEC", &a::DEC, &a::ZP0, 5},{ "???", &a::XXX, &a::IMP, 2},{ "INY", &a::INY, &a::IMP, 2},{ "CMP", &a::CMP, &a::IMM, 2},{ "DEX", &a::DEX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "CPY", &a::CPY, &a::ABS, 4},{ "CMP", &a::CMP, &a::ABS, 4},{ "DEC", &a::DEC, &a::ABS, 6},{ "???", &a::XXX, &a::IMP, 2},
		{ "BNE", &a::BNE, &a::REL, 2},{ "CMP", &a::CMP, &a::INY, 5},{ "???", &a::XXX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "CMP", &a::CMP, &a::ZPX, 4},{ "DEC", &a::DEC, &a::ZPX, 6},{ "???", &a::XXX, &a::IMP, 2},{ "CLD", &a::CLD, &a::IMP, 2},{ "CMP", &a::CMP, &a::ABY, 4},{ "???", &a::XXX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "CMP", &a::CMP, &a::ABX, 4},{ "DEC", &a::DEC, &a::ABX, 7},{ "???", &a::XXX, &a::IMP, 2},
		{ "CPX", &a::CPX, &a::IMM, 2},{ "SBC", &a::SBC, &a::INX, 6},{ "???", &a::XXX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "CPX", &a::CPX, &a::ZP0, 3},{ "SBC", &a::SBC, &a::ZP0, 3},{ "INC", &a::INC, &a::ZP0, 5},{ "???", &a::XXX, &a::IMP, 2},{ "INX", &a::INX, &a::IMP, 2},{ "SBC", &a::SBC, &a::IMM, 2},{ "NOP", &a::NOP, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "CPX", &a::CPX, &a::ABS, 4},{ "SBC", &a::SBC, &a::ABS, 4},{ "INC", &a::INC, &a::ABS, 6},{ "???", &a::XXX, &a::IMP, 2},
		{ "BEQ", &a::BEQ, &a::REL, 2},{ "SBC", &a::SBC, &a::INY, 5},{ "???", &a::XXX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "SBC", &a::SBC, &a::ZPX, 4},{ "INC", &a::INC, &a::ZPX, 6},{ "???", &a::XXX, &a::IMP, 2},{ "SED", &a::SED, &a::IMP, 2},{ "SBC", &a::SBC, &a::ABY, 4},{ "???", &a::XXX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "???", &a::XXX, &a::IMP, 2},{ "SBC", &a::SBC, &a::ABX, 4},{ "INC", &a::INC, &a::ABX, 7},{ "???", &a::XXX, &a::IMP, 2},
	};
}

jays6502::~jays6502()
{

}

void jays6502::clock()
{
	if (cycles == 0)
	{
		opcode = read(pc);
		pc++;

		cycles = lookup[opcode].cycles;

		uint8_t additional_cycle1 = (this->*lookup[opcode].addrmode)();
		uint8_t additional_cycle2 = (this->*lookup[opcode].operate)();

		cycles += (additional_cycle1 + additional_cycle2);
	}
	cycles--;
}

uint8_t jays6502::read(uint16_t a)
{
	if (bus != nullptr)
		return bus->read(a, false);

	return 0x00;
}

void jays6502::write(uint16_t a, uint8_t d)
{
	bus->write(a, d);
}

void jays6502::SetFlag(FLAGS6502 f, bool v)
{
	if (v)
	{
		status |= f;
	}
	else
	{
		status &= ~f;
	}
}

// Addressing Modes

uint8_t jays6502::IMP()
{
	fetched = a;
	return 0;
}

uint8_t jays6502::IMM()
{
	addr_abs = pc++;
	return 0;
}

uint8_t jays6502::ZP0()
{
	addr_abs = read(pc);
	pc++;
	addr_abs &= 0x00FF;
	return 0;
}

uint8_t jays6502::ZPX()
{
	addr_abs = (read(pc) + x);
	pc++;
	addr_abs &= 0x00FF;
	return 0;
}

uint8_t jays6502::ZPY()
{
	addr_abs = (read(pc) + y);
	pc++;
	addr_abs &= 0x00FF;
	return 0;
}

uint8_t jays6502::ABS()
{
	uint16_t lo = read(pc);
	pc++;
	uint16_t hi = read(pc);
	pc++;

	addr_abs = (hi << 8) | lo;
	return 0;
}

uint8_t jays6502::ABX()
{
	uint16_t lo = read(pc);
	pc++;
	uint16_t hi = read(pc);
	pc++;

	addr_abs = (hi << 8) | lo;
	addr_abs += x;

	if ((addr_abs & 0xFF00) != (hi << 8))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

uint8_t jays6502::ABY()
{
	uint16_t lo = read(pc);
	pc++;
	uint16_t hi = read(pc);
	pc++;

	addr_abs = (hi << 8) | lo;
	addr_abs += y;

	if ((addr_abs & 0xFF00) != (hi << 8))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

uint8_t jays6502::IND()
{
	uint16_t ptr_lo = read(pc);
	pc++;
	uint16_t ptr_hi = read(pc);
	pc++;

	uint16_t ptr = (ptr_hi << 8) | ptr_lo;

	if (ptr_lo == 0x00FF)
	{
		addr_abs = (read(ptr + 0xFF00) << 8) | read(ptr + 0);
	}
	else
	{
		addr_abs = (read(ptr + 1) << 8) | read(ptr + 0);
	}

	return 0;
}

uint8_t jays6502::IZY()
{
	uint16_t t = read(pc);
	pc++;

	uint16_t lo = read(t  & 0x00FF);
	uint16_t hi = read((t + 1) & 0x00FF);

	addr_abs = (hi << 8) | lo;
	addr_abs += y;

	if ((addr_abs & 0xFF00) != (hi << 8))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

uint8_t jays6502::IZX()
{
	uint16_t t = read(pc);
	pc++;

	uint16_t lo = read((uint16_t)(t + (uint16_t)x) & 0x00FF);
	uint16_t hi = read((uint16_t)(t + (uint16_t)x + 1) & 0x00FF);

	addr_abs = (hi << 8) | lo;
	return 0;
}

uint8_t jays6502::REL()
{
	addr_rel = read(pc);
	pc++;
	if (addr_rel & 0x80)
	{
		addr_rel |= 0xFF00;
	}
	return 0;
}

// Instructions
