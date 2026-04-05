#include "Graphics.h"


void Gameboy::input() {

	if (GetKey(olc::Key::P).bReleased) {
		ready = !ready;
	}

	if (GetKey(olc::Key::DEL).bHeld && Macro != 'm') {
		ready = true;
	}

	if (GetKey(olc::Key::M).bReleased) {
		Macro = 'm';
	}

	if (GetKey(olc::Key::V).bReleased) {
		displayVram = !displayVram;
	}

	if (GetKey(olc::Key::Z).bReleased) {
		int address;
		cin >> hex >> address;

		for (int i = address; i >= address - 100; i--) {
			cout << show_hex(address) << " : " << cpu.ram[i] << endl;
		}
		system("CLS");

		for (int i = address; i <= address + 300; i++) {
			cout << show_hex(i) << " : " << show_hex(cpu.ram[i]) << endl;
		}
		//for (int i = 0; i < 10; i++) {

		//}
	}

	if (GetKey(olc::Key::B).bReleased) {
		cin >> hex >> dbreakPoint;
		sbreakPoint = show_hex(dbreakPoint);

		Mode = "breakpoints";
	}

	if (GetKey(olc::Key::Q).bReleased) {
		Mode = (Mode == "Debug") ? "Play" : "Debug";
	}

	if (GetKey(olc::Key::NP1).bReleased) {
		steps = 23000;
		Macro = 'n';
	}
	
	if (GetKey(olc::Key::NP2).bReleased) {
		steps = 28739;
		Macro = 'n';
	}

	//actual game input

	//set interrupts when keys are either pressed or released
	if (GetKey(olc::Key::A).bPressed) {
		cpu.set_interrupt(cpu.INT::JOYPAD);
	}
	if (GetKey(olc::Key::A).bReleased) {
		cpu.set_interrupt(cpu.INT::JOYPAD);
	}

	if (GetKey(olc::Key::S).bPressed) {
		cpu.set_interrupt(cpu.INT::JOYPAD);
	}
	if (GetKey(olc::Key::S).bReleased) {
		cpu.set_interrupt(cpu.INT::JOYPAD);
	}

	if (GetKey(olc::Key::LEFT).bPressed) {
		cpu.set_interrupt(cpu.INT::JOYPAD);
	}
	if (GetKey(olc::Key::LEFT).bReleased) {
		cpu.set_interrupt(cpu.INT::JOYPAD);
	}

	if (GetKey(olc::Key::RIGHT).bPressed) {
		cpu.set_interrupt(cpu.INT::JOYPAD);
	}
	if (GetKey(olc::Key::RIGHT).bReleased) {
		cpu.set_interrupt(cpu.INT::JOYPAD);
	}

	if (GetKey(olc::Key::UP).bPressed) {
		cpu.set_interrupt(cpu.INT::JOYPAD);
	}
	if (GetKey(olc::Key::UP).bReleased) {
		cpu.set_interrupt(cpu.INT::JOYPAD);
	}

	if (GetKey(olc::Key::DOWN).bPressed) {
		cpu.set_interrupt(cpu.INT::JOYPAD);
	}
	if (GetKey(olc::Key::DOWN).bReleased) {
		cpu.set_interrupt(cpu.INT::JOYPAD);
	}

	if (GetKey(olc::Key::ENTER).bPressed) {
		cpu.set_interrupt(cpu.INT::JOYPAD);
	}
	if (GetKey(olc::Key::ENTER).bReleased) {
		cpu.set_interrupt(cpu.INT::JOYPAD);
	}

	if (GetKey(olc::Key::BACK).bPressed) {
		cpu.set_interrupt(cpu.INT::JOYPAD);
	}
	if (GetKey(olc::Key::BACK).bReleased) {
		cpu.set_interrupt(cpu.INT::JOYPAD);
	}
}

bool Gameboy::OnUserCreate() {

	Clear(olc::BLUE);
	Debugger();

	for (int i = 0; i < 144; i++) {
		for (int j = 0; j < 160; j++) {
			pixels[i][j] = olc::WHITE;
		}
	}


	return true;
}

int Gameboy::checkBit(uint8_t obj, int nbit) {
	return (obj & (1 << nbit)) >> nbit;
}

bool Gameboy::OnUserUpdate(float fElapsedTime) {
	input();

	cpu.opcode = cpu.ram[cpu.pc];
	cpu.lookup();
	cpu.scanline_cycles += cpu.op_cycles;
	cpu.graphics();
	cpu.interrupts();
	cpu.timers();

	if (cpu.scanline_cycles >= 70224) {
		cpu.scanline_cycles = 0;
		cpu.render_scanline();
	}

	Clear(olc::BLUE);

	for (int ly = 0; ly < 144; ly++) {
		for (int lx = 0; lx < 160; lx++) {
			Draw(olc::vi2d(lx + 300, ly + 300), cpu.display[ly][lx]);
		}
	}

	if (displayVram) {
		ShowVram();
	}

	return true;
}