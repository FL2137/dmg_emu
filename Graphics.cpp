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
		if (Mode != "ramView") {
			Mode = "ramView";
		}
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

	for (int i = 0; i < 160; i++) {
		for (int j = 0; j < 144; j++) {
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

	uint8_t scY = _cpu.ram[0xFF42];
	uint8_t scX = _cpu.ram[0xFF43];
	uint8_t wY = _cpu.ram[0xFF4A];
	uint8_t wX = _cpu.ram[0xFF4B] - 7;

	bool windowEnabled = false;


	//cehck if window is enabled
	if (_cpu.get_bit(_cpu.LCDC, 5) == 1) {
		if (wY <= _cpu.ram[0xFF44])
			windowEnabled = true;
	}

	//check for tile region
	if (_cpu.get_bit(_cpu.LCDC, 4) == 1) {
		tileRegion = 0x8000;
	}
	else {
		tileRegion = 0x8800;
		unsignedIndexing = false;
	}

	//check for background region

	if (windowEnabled == false) {
		if (_cpu.get_bit(_cpu.LCDC, 3) == 1) {
			bgRegion = 0x9C00;
		}
		else {
			bgRegion = 0x9800;
		}
	}
	else {
		if (_cpu.get_bit(_cpu.LCDC, 6)) {
			bgRegion = 0x9C00;
		}
		else
			bgRegion = 0x9800;
	}

	uint8_t y = 0;

	if (!windowEnabled)
		y = scY + _cpu.ram[0xFF44];
	else
		y = _cpu.ram[0xFF44] - wY;

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
			tileIdx = (uint8_t)(_cpu.ram[tileAddress]);
		else
			tileIdx = (int8_t)(_cpu.ram[tileAddress]);


		uint16_t tileAdress = tileRegion;

		if (unsignedIndexing)
			tileAdress += tileIdx * 16;
		else
			tileAdress += (tileIdx+128) * 16;

		uint8_t line = y % 8;
		line *= 2;
		uint8_t high_byte = _cpu.ram[tileIdx + line];
		uint8_t low_byte = _cpu.ram[tileIdx + line + 1];

		int colorBit = x % 8;
		colorBit -= 7;
		colorBit *= -1;

		int color = checkBit(low_byte, colorBit);
		color += checkBit(high_byte, colorBit)*10;
		if(color != 0)
		cout << "COLOR VAL: " << color << endl;

		
		if (color == 00)
			pixels[_cpu.ram[0xFF44]][pixel] = olc::Pixel(0, 0, 0, 0);
		else if (color == 01)
			pixels[_cpu.ram[0xFF44]][pixel] = olc::DARK_GREEN;
		else if (color == 10)
			pixels[_cpu.ram[0xFF44]][pixel] = olc::GREEN;
		else if (color == 11)
			pixels[_cpu.ram[0xFF44]][pixel] = olc::WHITE;
		
		
	}
}
*/


void Gameboy::RenderBackground() {

}

void Gameboy::RenderSprites() {

	bool doubleTiles = false;

	if (checkBit(_cpu.LCDC, 2) == 1)
		doubleTiles = true;

	for (int sprite = 0; sprite < 40; sprite++) {

		uint8_t index = sprite * 4;
		uint8_t y = _cpu.ram[0xFE00 + index] - 16;
		uint8_t x = _cpu.ram[0xFE00 + index + 1] - 8;
		uint8_t tileLocation = _cpu.ram[0xFE00 + index + 2];
		uint8_t attribs = _cpu.ram[0xFE00 + index + 3];

		bool xFlip = _cpu.get_bit(attribs, 5);
		bool yFlip = _cpu.get_bit(attribs, 6);

		int ly = _cpu.ram[0xFF44];
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
			uint8_t high_byte = _cpu.ram[tileAddress];
			uint8_t low_byte = _cpu.ram[tileAddress+1];

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




bool Gameboy::OnUserUpdate(float fElapsedTime) {
	int c = 0;
	
	
	//DrawTile(MakeTile(check), 50, 50);
	//DrawLogo();

	Clear(olc::BLUE);
	
	
	input();

	/*
	_cpu.cycle();

	if (_cpu.draw_flag) {
		cout << "cycliong\n";
		uint8_t lcdc = _cpu.LCDC;
		if (_cpu.get_bit(lcdc, 0))
			//RenderBackground();
			RenderTiles();

		if (_cpu.get_bit(lcdc, 1))
			RenderSprites();
		_cpu.ram[0xFF44]++;
	}

	Debugger();
	*/

	if (ready) {
		_cpu.cycle();

		//LCD and PPU turned on
		if (checkBit(_cpu.LCDC, 7) == 1) {
			if (_cpu.ram[0xFF44] < 144) {
				if (checkBit(_cpu.LCDC, 0) == 1) {
					RenderBackground();
					//RenderTiles();
				}
				//cout << "LCDC.7=1" << endl;
				if (checkBit(_cpu.LCDC, 0) == 1) {
					//cout << "LCDC.1=1" << endl;
					//RenderSprites();
				}
				_cpu.ram[0xFF44]++;
			}
		}
		ready = false;
	}
		Debugger();



	//}
	//
	//if (Mode == "Debug") {
	//	if (Macro == 'n') {
	//		for (int i = 0; i < steps; i++) {
	//			_cpu.cycle();
	//			Debugger();
	//		}
	//		Macro = '-';
	//		Debugger();
	//	}
	//	Debugger();
	//}
	//else if (Mode == "Play") {
	//	//DrawLogo();
	//	int address;
	//	cin >> hex >> address;

	//	/*for (int i = address; i >= address - 100; i--) {
	//		cout <<show_hex(address)<< " : " << _cpu.ram[i] << endl;
	//	}*/
	//	system("CLS");

	//	for (int i = address; i <= address+300; i++) {
	//		cout << show_hex(i) << " : " << show_hex(_cpu.ram[i]) << endl;
	//	}


	//	Mode = "Debug";
	//	//ready = true;
	//}
	//else if (Mode == "breakpoints") {
	//	while (_cpu.pc != dbreakPoint) {
	//		_cpu.cycle();
	//		Debugger();
	//	}
	//		

	//	Mode = "Debug";
	//}

	//actual screen
	for (int ly = 0; ly < 160; ly++) {
		for (int lx = 0; lx < 144; lx++) {
			Draw(olc::vi2d(lx + 300, ly + 300), pixels[ly][lx]);
		}
	}
	
	return true;
}