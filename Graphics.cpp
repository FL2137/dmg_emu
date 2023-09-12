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

	if (Macro == 'm') {

		if (GetKey(olc::Key::K1).bReleased)
			steps += 1;

		if (GetKey(olc::Key::K0).bReleased)
			steps *= 10;

		if (GetKey(olc::Key::BACK).bReleased)
			steps = 0;

		if (GetKey(olc::Key::N).bReleased)
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

int current_cycles = 0;

void Gameboy::ShowVram() {
	const int VRAM_ADDRESS = 0x8000;
	const int TILE_SIZE = 16;

	const int N_TILES = 16 * 8 * 2;

	int ly = 0, lx = 0;

	//olc::Pixel vram[N_TILES][8][8] = { olc::WHITE };

	auto vram = new olc::Pixel[N_TILES][8][8];

	int c = 0;

	int vram_index = 0;

	for (int tile_index = 0x000; tile_index < 0xFF0; tile_index += 0x10) {
		
		for (int tile_byte = 0; tile_byte < 16; tile_byte += 2) {


			uint16_t address = VRAM_ADDRESS | (tile_index + tile_byte);
			cout << cpu.get_hex(address) << endl;

			
			uint8_t byte1 = cpu.ram[address];
			uint8_t byte2 = cpu.ram[address + 1];

			for (int nbit = 7; nbit >= 0; nbit--) {
				
				int colornum = (((byte1 >> nbit) & 1) * 10) + ((byte2 >> nbit) & 1);

				if (colornum == 10) {
					vram[vram_index][ly][lx].r = 136;
					vram[vram_index][ly][lx].g = 192;
					vram[vram_index][ly][lx].b = 112;
				}
				else if (colornum == 11) {
					vram[vram_index][ly][lx].r = 224;
					vram[vram_index][ly][lx].g = 248;
					vram[vram_index][ly][lx].b = 208;
				}
				else if (colornum == 01) {
					vram[vram_index][ly][lx].r = 52;
					vram[vram_index][ly][lx].g = 104;
					vram[vram_index][ly][lx].b = 86;
				}
				else if (colornum == 00) {
					vram[vram_index][ly][lx].r = 00;
					vram[vram_index][ly][lx].g = 00;
					vram[vram_index][ly][lx].b = 00;
				}
				
				lx++;
			}
			lx = 0;
			ly++;
		}
		vram_index++;
		ly = 0;
	}

	int offset_x = 450, offset_y = 450;

	for (int tile = 0; tile < N_TILES; tile++) {
		for (int ly = 0; ly < 8; ly++) {
			for (int lx = 0; lx < 8; lx++) {
				Draw(olc::vi2d(ly + offset_y, lx + offset_x), vram[tile][lx][ly]);
			}
		}
		offset_x += 8;
		if (tile % 7 == 0) {
			offset_y += 8;
			offset_x = 450;
		}
	}
}


bool Gameboy::OnUserUpdate(float fElapsedTime) {



	input();

	//cpu.cycle();

	//if (cpu.draw_flag) {
	//	uint8_t lcdc = cpu.LCDC;
	//	if (cpu.get_bit(lcdc, 0))
	//		RenderBackground();

	//	/*if (cpu.get_bit(lcdc, 1));
	//		RenderSprites();*/
	//	cpu.ram[0xFF44]++;
	//}

	//Debugger();

	if (ready) {

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
		ready = false;
	}
	
	//if(ready)
	//cpu.cycle();
	//
	
	// 06test breakpoint for loading font - 0xC876



	if (Mode == "breakpoints") {
		if (cpu.pc != dbreakPoint) {
			cpu.opcode = cpu.ram[cpu.pc];
			cpu.lookup();
			cpu.scanline_cycles += cpu.op_cycles;
			cpu.passed_cycles += cpu.op_cycles;
			cpu.graphics();
			cpu.interrupts();
			cpu.timers();

			if (cpu.scanline_cycles >= 70224) {
				cpu.scanline_cycles = 0;
				cpu.render_scanline();
				Clear(olc::BLUE);
				Debugger();
			}
		}
		else {
			Mode = "play";
		}
	}
	
	

	//actual screen

	if (Mode != "breakpoints") {
		Clear(olc::BLUE);
		Debugger();
		for (int ly = 0; ly < 144; ly++) {
			for (int lx = 0; lx < 160; lx++) {
				Draw(olc::vi2d(lx + 300, ly + 300), cpu.display[ly][lx]);
			}
		}


		if (displayVram) {
			ShowVram();
		}
	}


	return true;
}