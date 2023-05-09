#pragma once
#include "olcPixelGameEngine.h"
#include "LR35902.h"
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;



class Gameboy : public olc::PixelGameEngine{
public:

	std::string show_hex(int n) {
		std::string result = "";
		const char* digits = "0123456789ABCDEF";
		while (n > 0) {
			result = digits[n % 16] + result;
			n /= 16;
		}
		result = "0x" + result;
		return result;
	}

	

	LR35902 _cpu;
	int startX = 50;
	int startY = 50;
	int *check;
	int ti[4][64];
	
	const int offset = 300;

	olc::Pixel pixels[160][144] = { olc::WHITE };

	char Macro = '-';
	int steps = 0;
	string Mode = "Debug";
	string sbreakPoint = "";
	int dbreakPoint = -1;


	void RenderTiles();
	 
	int  checkBit(uint8_t obj, int nbit);

	bool ready = false;

	void Debugger() {
		string
			AF = "AF:" + show_hex(_cpu.AF),
			BC = "BC:" + show_hex(_cpu.BC),
			DE = "DE:" + show_hex(_cpu.DE),
			HL = "HL:" + show_hex(_cpu.HL),
			SP = "SP:" + show_hex(_cpu.stkp),
			PC = "PC:" + show_hex(_cpu.pc),
			lcdc = "lcdc:"+show_hex(_cpu.LCDC),
			stat = "stat:" + show_hex(_cpu.STAT);

		DrawString(olc::vi2d(10, 10), AF,olc::WHITE,2);
		DrawString(olc::vi2d(10, 30), BC, olc::WHITE, 2);
		DrawString(olc::vi2d(10, 50), DE, olc::WHITE, 2);
		DrawString(olc::vi2d(10, 70), HL, olc::WHITE, 2);
		DrawString(olc::vi2d(10, 90), SP, olc::WHITE, 2);
		DrawString(olc::vi2d(10, 110), lcdc, olc::WHITE, 2);
		DrawString(olc::vi2d(10, 130), stat, olc::WHITE, 2);
		DrawString(olc::vi2d(10, 150), PC, olc::WHITE, 2);

		DrawString(olc::vi2d(10, 170), "Steps:"+to_string(steps), olc::WHITE, 2);
		auto op = _cpu.ram[_cpu.pc];
		DrawString(olc::vi2d(10, 190), "Opcode:" + show_hex(op), olc::WHITE, 2);
		DrawString(olc::vi2d(10, 210), "Cycles passed: " + to_string(_cpu.cycles_done), olc::WHITE, 2);
		DrawString(olc::vi2d(200, 10), "Breakpoint: " + sbreakPoint, olc::WHITE, 2);
	
	
		DrawString(olc::vi2d(200, 30), "LY: " + to_string(_cpu.ram[0xFF44]), olc::WHITE, 2);
	
	}




	void RenderBackground();
		
	void tmp() {

		uint16_t tileArea = 0x8000;
		uint16_t backgroundTilemap = 0;

		bool unsignedIndexing = true;
		bool windowEnabled = false;

		int ly = _cpu.ram[0xFF44];

		uint8_t scY = _cpu.ram[0xFF42];
		uint8_t scX = _cpu.ram[0xFF43];
		uint8_t wY = _cpu.ram[0xFF4A];
		uint8_t wX = _cpu.ram[0xFF4B] - 7;


		if (checkBit(_cpu.LCDC, 5) == 1 && wY <= ly)
				windowEnabled = true;

		if (checkBit(_cpu.LCDC, 4) == 1) {
			tileArea = 0x8000;
		}
		else {
			tileArea = 0x8800;
			unsignedIndexing = false;
		}


		if (windowEnabled == false) {
			if (checkBit(_cpu.LCDC, 3) == 1)
				backgroundTilemap = 0x9C00;
			else
				backgroundTilemap = 0x9800;
		}

		uint8_t tileY = 0;


		if (!windowEnabled)
			tileY = scY + ly;
		else
			tileY = ly - wY;


	}

	void RenderSprites();

	void input();

	Gameboy(const LR35902 &cpu):_cpu(cpu) {
		sAppName = "DMG01";
	}

public:
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
};