#include "Graphics.h"


void Gameboy::input() {

	if (GetKey(olc::Key::ENTER).bReleased)
		ready = true;

	if (GetKey(olc::Key::BACK).bHeld && Macro != 'm') {
		ready = true;
	}

	if (GetKey(olc::Key::M).bReleased)
		Macro = 'm';



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


/* does not work
void Gameboy::RenderBackground() {

	uint16_t tileRegion = 0;
	uint16_t bgRegion = 0;
	bool unsignedIndexing = true;

	uint8_t scY = cpu.ram[0xFF42];
	uint8_t scX = cpu.ram[0xFF43];
	uint8_t wY = cpu.ram[0xFF4A];
	uint8_t wX = cpu.ram[0xFF4B] - 7;

	bool windowEnabled = false;


	//cehck if window is enabled
	if (cpu.get_bit(cpu.LCDC, 5) == 1) {
		if (wY <= cpu.ram[0xFF44])
			windowEnabled = true;
	}

	//check for tile region
	if (cpu.get_bit(cpu.LCDC, 4) == 1) {
		tileRegion = 0x8000;
	}
	else {
		tileRegion = 0x8800;
		unsignedIndexing = false;
	}

	//check for background region

	if (windowEnabled == false) {
		if (cpu.get_bit(cpu.LCDC, 3) == 1) {
			bgRegion = 0x9C00;
		}
		else {
			bgRegion = 0x9800;
		}
	}
	else {
		if (cpu.get_bit(cpu.LCDC, 6)) {
			bgRegion = 0x9C00;
		}
		else
			bgRegion = 0x9800;
	}

	uint8_t y = 0;

	if (!windowEnabled)
		y = scY + cpu.ram[0xFF44];
	else
		y = cpu.ram[0xFF44] - wY;

	uint16_t tileRow = (((uint8_t)(y / 8)) * 32); //calc current row of tiles

	for (int pixel = 0; pixel < 160; pixel++) {

		uint8_t x = pixel + scX;

		if (windowEnabled)
			if (pixel >= wX)
				x = pixel - wX;


		uint16_t tileCol = (x / 8);

		int16_t tileIdx;


		uint16_t tileAddress = bgRegion + tileRow + tileCol;

		if (unsignedIndexing)
			tileIdx = (uint8_t)(cpu.ram[tileAddress]);
		else
			tileIdx = (int8_t)(cpu.ram[tileAddress]);


		uint16_t tileAdress = tileRegion;

		if (unsignedIndexing)
			tileAdress += tileIdx * 16;
		else
			tileAdress += (tileIdx+128) * 16;

		uint8_t line = y % 8;
		line *= 2;
		uint8_t high_byte = cpu.ram[tileIdx + line];
		uint8_t low_byte = cpu.ram[tileIdx + line + 1];

		int colorBit = x % 8;
		colorBit -= 7;
		colorBit *= -1;

		int color = checkBit(low_byte, colorBit);
		color += checkBit(high_byte, colorBit)*10;
		if(color != 0)
		cout << "COLOR VAL: " << color << endl;


		if (color == 00)
			pixels[cpu.ram[0xFF44]][pixel] = olc::Pixel(0, 0, 0, 0);
		else if (color == 01)
			pixels[cpu.ram[0xFF44]][pixel] = olc::DARK_GREEN;
		else if (color == 10)
			pixels[cpu.ram[0xFF44]][pixel] = olc::GREEN;
		else if (color == 11)
			pixels[cpu.ram[0xFF44]][pixel] = olc::WHITE;


	}
}
*/


void Gameboy::RenderBackground() {

	uint16_t tiledata;
	uint16_t tilemap;

	bool signed_addressing = false;

	uint8_t SCY = cpu.ram[0xFF42];
	uint8_t SCX = cpu.ram[0xFF43];
	uint8_t WY = cpu.ram[0xFF4A];
	uint8_t WX = cpu.ram[0xFF4B] - 7;

	//checking if LCDC.4 is set 
	if (checkBit(cpu.LCDC, 4) == 1) {
		tiledata = 0x8000;
	}
	else {
		tiledata = 0x8800;
		signed_addressing = true;
	}

	bool window_on = false;

	if (checkBit(cpu.LCDC, 5) && WY <= cpu.ram[0xFF44])
		window_on = true;

	//default tilemap
	tilemap = 0x9800;


	if (!window_on && checkBit(cpu.LCDC, 3))
		tilemap = 0x9C00;
	else if (window_on && checkBit(cpu.LCDC, 6))
		tilemap = 0x9C00;

	uint8_t tile = 0;

	if (window_on)
		tile = cpu.ram[0xFF44] - WY;
	else
		tile = cpu.ram[0xFF44] + SCY;

	uint16_t row = (((uint8_t)(tile / 8)) * 32);


	for (int pixel = 0; pixel < 160; pixel++) {
		uint8_t pixel_x = pixel + SCX;

		if (window_on && pixel >= WX) {
			pixel_x = pixel - WX;
		}

		uint16_t col = (pixel_x / 8);
		int16_t tile_n;


		uint16_t tile_address = tilemap + row + col;

		if (signed_addressing)
			tile_n = (int8_t)cpu.ram[tile_address];
		else
			tile_n = (uint8_t)cpu.ram[tile_address];

		uint16_t tile_location = tiledata;

		if (signed_addressing)
			tile_location += (tile_n + 128) * 16;
		else
			tile_location += tile_n * 16;

		uint8_t line = tile % 8;
		line *= 2;

		uint8_t datalow = cpu.ram[tile_location + line];
		uint8_t datahigh = cpu.ram[tile_location + line + 1];

		int color_bit = pixel_x % 8;
		color_bit -= 7;
		color_bit *= -1;

		int color_num = checkBit(datahigh, color_bit);
		color_num <<= 1;
		color_num |= checkBit(datalow, color_bit);
		//cout << "COLOR_NUM: " << color_num << endl;

		olc::Pixel color = olc::WHITE;

		if (color_num == 11)
			color == olc::BLUE;
		else if (color_num == 10)
			color == olc::GREEN;
		else if (color_num == 01)
			pixels[cpu.ram[0xFF44]][pixel] = olc::GREEN;
		else if (color_num == 00)
			pixels[cpu.ram[0xFF44]][pixel] = olc::WHITE;

		//pixels[pixel][cpu.ram[0xFF44]] = color;
	}

}

void Gameboy::RenderSprites() {

	bool doubleTiles = false;

	if (checkBit(cpu.LCDC, 2) == 1)
		doubleTiles = true;

	for (int sprite = 0; sprite < 40; sprite++) {

		uint8_t index = sprite * 4;
		uint8_t y = cpu.ram[0xFE00 + index] - 16;
		uint8_t x = cpu.ram[0xFE00 + index + 1] - 8;
		uint8_t tileLocation = cpu.ram[0xFE00 + index + 2];
		uint8_t attribs = cpu.ram[0xFE00 + index + 3];

		bool xFlip = cpu.get_bit(attribs, 5);
		bool yFlip = cpu.get_bit(attribs, 6);

		int ly = cpu.ram[0xFF44];
		/*cout << endl;
		cout << "ly: " << ly << endl;
		cout << "sY:" << y << endl;
		cout << endl;*/


		int ySize = 8;

		if (doubleTiles) ySize = 16;

		// check if sprite intercepts current scanline (ly)
		if ((ly >= y) && (ly < (y + ySize))) {

			int line = ly - y; //line of current sprite   

			if (yFlip); //TBI

			uint16_t tileAddress = (0x8000 + (tileLocation * 16)) + line;
			uint8_t high_byte = cpu.ram[tileAddress];
			uint8_t low_byte = cpu.ram[tileAddress + 1];

			for (int bit = 7; bit >= 0; bit--) {
				int color = checkBit(high_byte, bit) + (checkBit(low_byte, bit) * 10);



				int xPix = 0 - bit;
				xPix += 7;

				int pixelPos = x + xPix;

				//cout << "COLOR: " << color << endl;

				if (color == 00)
					pixels[pixelPos][ly] = olc::Pixel(0, 0, 0, 0);
				else if (color == 01)
					pixels[pixelPos][ly] = olc::DARK_GREEN;
				else if (color == 10)
					pixels[pixelPos][ly] = olc::GREEN;
				else if (color == 11)
					pixels[pixelPos][ly] = olc::WHITE;

			}

		}
	}


}

int current_cycles = 0;

/*
F0
00
F0
00
FC
00
FC
00
FC
00
FC
00
F3
00
F3
00


*/


bool Gameboy::OnUserUpdate(float fElapsedTime) {


	//DrawTile(MakeTile(check), 50, 50);
	//DrawLogo();

	


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

	
	/*if (ready) {

		cpu.opcode = cpu.ram[cpu.pc];
		cpu.lookup();
		cpu.scanline_cycles += cpu.op_cycles;
		cpu.graphics();
		cpu.interrupts();
		cpu.timers();

		if (cpu.scanline_cycles >= 69905) {
			cpu.scanline_cycles = 0;
			cpu.render_scanline();
		}
	}*/
	cpu.cycle();

	/*if (Mode == "breakpoints") {
		while (cpu.pc != dbreakPoint) {
			cpu.opcode = cpu.ram[cpu.pc];
			cpu.lookup();
			cpu.scanline_cycles += cpu.op_cycles;
			cpu.passed_cycles += cpu.op_cycles;
			cpu.graphics();
			cpu.interrupts();
			cpu.timers();

			if (cpu.scanline_cycles >= 69905) {
				cpu.scanline_cycles = 0;
				cpu.render_scanline();
			}
			Debugger();
		}
		Mode = "play";
	}*/


	//actual screen


	if (cpu.ram[0xFF44] != last_ly) {
		Clear(olc::BLUE);
		for (int ly = 0; ly < 144; ly++) {
			for (int lx = 0; lx < 160; lx++) {
				Draw(olc::vi2d(lx + 300, ly + 300), cpu.display[ly][lx]);
			}
		}
		last_ly = cpu.ram[0xFF44];
	}

	return true;
}