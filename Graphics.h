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

	enum REG {
		LCDC=1,
		STAT=2,
	};
	

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


	uint8_t* sprites = nullptr;

	void RenderTiles();

	bool checkBit(REG r, int nbit);
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
			lcdc = "lcdc:"+show_hex(*_cpu.lcdc),
			stat = "stat:" + show_hex(*_cpu.stat);

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
	}


	void MakeTile(int data[16], int (&tile)[64]) {
		
		int count = 0;
		for (int t = 0; t < 16; t += 2) {
			for (int i = 7; i >= 0; i--) {
				int i1 = (data[t] & (1 << i)) >> i;
				int i2 = ((data[t+1] & (1 << i)) >> i)*10;
				int pixel = i1 + i2;
				tile[count] = pixel;
				count++;
			}
		}
		//cout << count << endl;
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


		if (checkBit(LCDC, 5) == 1 && wY <= ly)
				windowEnabled = true;

		if (checkBit(LCDC, 4) == 1) {
			tileArea = 0x8000;
		}
		else {
			tileArea = 0x8800;
			unsignedIndexing = false;
		}


		if (windowEnabled == false) {
			if (checkBit(LCDC, 3) == 1)
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


	void MakeTile(int data[8], int(&tile)[32]) {
		int count = 0;
		for (int t = 0; t < 8; t += 2) {
			for (int i = 7; i >= 0; i--) {
				int i1 = (data[t] & (1 << i)) >> i;
				int i2 = ((data[t + 1] & (1 << i)) >> i) * 10;
				int pixel = i1 + i2;
				tile[count] = pixel;
				count++;
			}
		}
		cout << count << endl;
	}

	void drw(int data[16], int x, int y);

	void input();

	void drawSprite(uint8_t data[4]);

	Gameboy(const LR35902 &cpu):_cpu(cpu) {
		sAppName = "DMG01";
	}
public:
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
};