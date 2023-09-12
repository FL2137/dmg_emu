#include "olcPixelGameEngine.h"
#include "LR35902.h"
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

class Processor;

class Gameboy : public olc::PixelGameEngine {
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

	Processor cpu;

	int startX = 50;
	int startY = 50;
	int* check;
	int ti[4][64];

	const int offset = 300;

	olc::Pixel pixels[144][160] = { olc::WHITE };


	bool displayVram = false;

	char Macro = '-';
	int steps = 0;
	string Mode = "Debug";
	string sbreakPoint = "";
	int dbreakPoint = -1;


	int  checkBit(uint8_t obj, int nbit);

	bool ready = false;

	int last_ly = -1;


	void Debugger() {
		string
			AF = "AF:" + show_hex(cpu.AF),
			BC = "BC:" + show_hex(cpu.BC),
			DE = "DE:" + show_hex(cpu.DE),
			HL = "HL:" + show_hex(cpu.HL),
			SP = "SP:" + show_hex(cpu.SP),
			PC = "PC:" + show_hex(cpu.pc),
			lcdc = "lcdc:" + show_hex(cpu.ram[0xFF40]),
			stat = "stat:" + show_hex(cpu.ram[0xFF41]);

		DrawString(olc::vi2d(10, 10), AF, olc::WHITE, 2);
		DrawString(olc::vi2d(10, 30), BC, olc::WHITE, 2);
		DrawString(olc::vi2d(10, 50), DE, olc::WHITE, 2);
		DrawString(olc::vi2d(10, 70), HL, olc::WHITE, 2);
		DrawString(olc::vi2d(10, 90), SP, olc::WHITE, 2);
		DrawString(olc::vi2d(10, 110), lcdc, olc::WHITE, 2);
		DrawString(olc::vi2d(10, 130), stat, olc::WHITE, 2);
		DrawString(olc::vi2d(10, 150), PC, olc::WHITE, 2);

		DrawString(olc::vi2d(10, 170), "Steps:" + to_string(steps), olc::WHITE, 2);
		auto op = cpu.ram[cpu.pc];
		DrawString(olc::vi2d(10, 190), "Opcode:" + show_hex(op), olc::WHITE, 2);
		DrawString(olc::vi2d(10, 210), "Cycles passed: " + to_string(cpu.passed_cycles), olc::WHITE, 2);
		DrawString(olc::vi2d(200, 10), "Breakpoint: " + sbreakPoint, olc::WHITE, 2);


		DrawString(olc::vi2d(200, 30), "LY: " + to_string(cpu.ram[0xFF44]), olc::WHITE, 2);


		//LCDC
		for (int i = 7; i >= 0; i--)
			DrawString(olc::vi2d(350, 180 - i * 20), "LCDC." + to_string(i) + ": " + to_string((cpu.LCDC >> i) & 1), olc::WHITE, 2);

		//Flags
		DrawString(olc::vi2d(550, 40), "Flag.Z:" + to_string((cpu.AF >> 7) & 1), olc::WHITE, 2);
		DrawString(olc::vi2d(550, 60), "Flag.N:" + to_string((cpu.AF >> 6) & 1), olc::WHITE, 2);
		DrawString(olc::vi2d(550, 80), "Flag.H:" + to_string((cpu.AF >> 5) & 1), olc::WHITE, 2);
		DrawString(olc::vi2d(550, 100), "Flag.C:" + to_string((cpu.AF >> 4) & 1), olc::WHITE, 2);

	}

	static void CycleDebugger(const Processor &cpu, Gameboy &game) {
		string
			AF = "AF:" + game.show_hex(cpu.AF),
			BC = "BC:" + game.show_hex(cpu.BC),
			DE = "DE:" + game.show_hex(cpu.DE),
			HL = "HL:" + game.show_hex(cpu.HL),
			SP = "SP:" + game.show_hex(cpu.SP),
			PC = "PC:" + game.show_hex(cpu.pc),
			lcdc = "lcdc:" + game.show_hex(cpu.LCDC),
			stat = "stat:" + game.show_hex(cpu.STAT);

		game.DrawString(olc::vi2d(10, 10), AF, olc::WHITE, 2);
		game.DrawString(olc::vi2d(10, 30), BC, olc::WHITE, 2);
		game.DrawString(olc::vi2d(10, 50), DE, olc::WHITE, 2);
		game.DrawString(olc::vi2d(10, 70), HL, olc::WHITE, 2);
		game.DrawString(olc::vi2d(10, 90), SP, olc::WHITE, 2);
		game.DrawString(olc::vi2d(10, 110), lcdc, olc::WHITE, 2);
		game.DrawString(olc::vi2d(10, 130), stat, olc::WHITE, 2);
		game.DrawString(olc::vi2d(10, 150), PC, olc::WHITE, 2);

		game.DrawString(olc::vi2d(10, 170), "Steps:" + to_string(game.steps), olc::WHITE, 2);
		auto op = cpu.ram[cpu.pc];
		game.DrawString(olc::vi2d(10, 190), "Opcode:" + game.show_hex(op), olc::WHITE, 2);
		game.DrawString(olc::vi2d(10, 210), "Cycles passed: " + to_string(cpu.op_cycles), olc::WHITE, 2);
		game.DrawString(olc::vi2d(200, 10), "Breakpoint: " + game.sbreakPoint, olc::WHITE, 2);


		game.DrawString(olc::vi2d(200, 30), "LY: " + to_string(cpu.ram[0xFF44]), olc::WHITE, 2);


		//LCDC
		for (int i = 7; i >= 0; i--)
			game.DrawString(olc::vi2d(350, 180 - i * 20), "LCDC." + to_string(i) + ": " + to_string((cpu.LCDC >> i) & 1), olc::WHITE, 2);
		
		//Flags
		for (int i = 7; i >= 0; i--) 
			game.DrawString(olc::vi2d(400, 180 - i * 20), "F." + to_string(i) + ": " + to_string((cpu.AF >> i+8) & 1), olc::WHITE, 2);

	
	}




	void RenderBackground();

	void tmp() {

		uint16_t tileArea = 0x8000;
		uint16_t backgroundTilemap = 0;

		bool unsignedIndexing = true;
		bool windowEnabled = false;

		int ly = cpu.ram[0xFF44];

		uint8_t scY = cpu.ram[0xFF42];
		uint8_t scX = cpu.ram[0xFF43];
		uint8_t wY = cpu.ram[0xFF4A];
		uint8_t wX = cpu.ram[0xFF4B] - 7;


		if (checkBit(cpu.LCDC, 5) == 1 && wY <= ly)
			windowEnabled = true;

		if (checkBit(cpu.LCDC, 4) == 1) {
			tileArea = 0x8000;
		}
		else {
			tileArea = 0x8800;
			unsignedIndexing = false;
		}


		if (windowEnabled == false) {
			if (checkBit(cpu.LCDC, 3) == 1)
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

	void input();

	Gameboy(const Processor& cpu) :cpu(cpu) {
		sAppName = "DMG01";
	}
	
	void ShowVram();


public:
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
};
