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
		else {
			Mode = "runView";
		}
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
	
	logo_data =new int[16*3] {
		 0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D,
		 0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E, 0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99,
		 0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC, 0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E
	};
	Debugger();

	for (int i = 0; i < 160; i++) {
		for (int j = 0; j < 144; j++) {
			pixels[i][j] = olc::WHITE;
		}
	}
	

	return true;
}

void Gameboy::DrawLogo() {

	int startX = 100, startY = 100;
	int c = 0;

	auto drawByte = [&](int byte) {
		for (int i = 7; i >= 0; i--) {
			if (i >= 4) {
				if (((byte & (1 << i)) >> i) == 1)
					FillRect(olc::vi2d(startX + 3 - i, startY), olc::vi2d(1, 2), olc::BLACK);
				else
					FillRect(olc::vi2d(startX + 3 - i, startY), olc::vi2d(1, 2), olc::WHITE);

			}
			else {
				if (((byte & (1 << i)) >> i) == 1)
					FillRect(olc::vi2d(startX - i - 1, startY + 1), olc::vi2d(1, 2), olc::BLACK);
				else
					FillRect(olc::vi2d(startX - i - 1, startY + 1), olc::vi2d(1, 2), olc::WHITE);

			}
		}
	};

	int flag = 0;
	for (int i = 0; i < 48; i++) {
		if (flag == 0) {
			drawByte(logo_data[i]);
			startY += 3;
			flag++;
		}
		else if (flag == 1) {
			drawByte(logo_data[i]);
			startY -= 3;
			startX += 4;
			flag--;
		}

		if (i == 23) {
			startX = 40;
			startY += 6;
			flag = 0;
		}

	}
	
	/*for (int i = 24; i < 48; i++) {
		if (flag == 0) {
			drawByte(logo_data[i]);
			startY += 3;
			flag++;
		}
		else if (flag == 1) {
			drawByte(logo_data[i]);
			startY -= 3;
			startX += 4;
			flag--;
		}

	}*/


	/*drawByte(logo_data[0]);
	startY += 3;
	drawByte(logo_data[1]);
	startY -= 3;

	startX += 4;

	drawByte(logo_data[2]);
	startY += 3;
	drawByte(logo_data[3]);
	startY -= 3;*/


	/*for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			drawByte(logo_data[c]);
		}
		c++;
	}*/


	/*int c = 0;
	for (int i = 0; i < 48;i++) {
		for (int j = 0; j < 2; j++) {

			if (j == 0) 
				for (int p = 7; p >= 0; p--) {

					if (p >= 4) {
						if(((logo_data[c] & (1 << p)) >> p) == 1 )
							DrawRect(olc::vi2d(startX + 3 - p, startY), olc::vi2d(1, 2), olc::BLACK);
						else if (((logo_data[c] & (1 << p)) >> p) == 0)
							DrawRect(olc::vi2d(startX + 3 - p, startY), olc::vi2d(1, 2), olc::WHITE);
					}
					else {
						if (((logo_data[c] & (1 << p)) >> p) == 1)
							DrawRect(olc::vi2d(startX + 3 - p, startY+3), olc::vi2d(1, 2), olc::BLACK);
						else if (((logo_data[c] & (1 << p)) >> p) == 0)
							DrawRect(olc::vi2d(startX + 3 - p, startY+3), olc::vi2d(1, 2), olc::WHITE);
					}


				}
			else
				for (int p = 7; p >= 0; p--) {

					if (p >= 4) {
						if (((logo_data[c] & (1 << p)) >> p) == 1)
							DrawRect(olc::vi2d(startX + 3 - p, startY+3), olc::vi2d(1, 2), olc::BLACK);
						else if (((logo_data[c] & (1 << p)) >> p) == 0)
							DrawRect(olc::vi2d(startX + 3 - p, startY+3), olc::vi2d(1, 2), olc::WHITE);
					}
					else {
						if (((logo_data[c] & (1 << p)) >> p) == 1)
							DrawRect(olc::vi2d(startX + 3 - p, startY + 6), olc::vi2d(1, 2), olc::BLACK);
						else if (((logo_data[c] & (1 << p)) >> p) == 0)
							DrawRect(olc::vi2d(startX + 3 - p, startY + 6), olc::vi2d(1, 2), olc::WHITE);
					}


				}



			c++;
		}
		startX += 2;
		if (i==23) {
			startY += 9;
			startX = 40;
		}
	}*/
}

void Gameboy::DrawTile(int tile_data[64], int x, int y, int size) {
	int idx = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (tile_data[idx] == 00) 
				FillRect(olc::vi2d(x + j, y + i), olc::vi2d(1, 1), olc::BLACK);
			else if (tile_data[idx] == 11)
				FillRect(olc::vi2d(x + j, y + i), olc::vi2d(1, 1), olc::WHITE);
			else if (tile_data[idx] == 01)
				FillRect(olc::vi2d(x + j, y + i), olc::vi2d(1, 1), olc::DARK_GREEN);
			else if (tile_data[idx] == 10)
				FillRect(olc::vi2d(x + j, y + i), olc::vi2d(1, 1), olc::GREEN);
			idx++;
		}
	}
	//cout << idx << endl;
}

void readTileData(int address) {

}

void Gameboy::drawSprite(uint8_t data[4]) {
	int y = data[0];
	int x = data[1];
	int index = data[2];
	uint8_t tile[16];


	//_cpu.
}


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
	if (_cpu.get_bit(*(_cpu.lcdc), 5) == 1) {
		if (wY <= _cpu.ram[0xFF44])
			windowEnabled = true;
	}

	//check for tile region
	if (_cpu.get_bit(*(_cpu.lcdc), 4) == 1) {
		tileRegion = 0x8000;
	}
	else {
		tileRegion = 0x8800;
		unsignedIndexing = false;
	}

	//check for background region

	if (windowEnabled == false) {
		if (_cpu.get_bit(*(_cpu.lcdc), 3) == 1) {
			bgRegion = 0x9C00;
		}
		else {
			bgRegion = 0x9800;
		}
	}
	else {
		if (_cpu.get_bit(*(_cpu.lcdc), 6)) {
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

		int color_bit = x % 8;
		color_bit -= 7;
		color_bit *= -1;
	
		pixels[_cpu.ram[0xFF44]][pixel] = olc::DARK_GREEN;
		
	}
	_cpu.ram[0xFF44]++;
}

bool Gameboy::OnUserUpdate(float fElapsedTime) {
	int c = 0;
	
	
	//DrawTile(MakeTile(check), 50, 50);
	//DrawLogo();

	Clear(olc::BLUE);
	



	
	input();
	if (ready) {
		_cpu.cycle();

		cout << "LCDC.7: " << _cpu.get_bit(*(_cpu.lcdc), 7) << endl;


		//LCD and PPU turned on
		if (_cpu.get_bit(*(_cpu.lcdc), 7) == 1) {
			
			if (_cpu.get_bit(*(_cpu.lcdc), 0) == 1) {
				cout << "should be renderin\n";
				RenderBackground();
			}
		}
		ready = false;

	}
	
	if (Mode == "Debug") {
		if (Macro == 'n') {
			for (int i = 0; i < steps; i++) {
				_cpu.cycle();
				Debugger();
			}
			Macro = '-';
			Debugger();
		}
		Debugger();
	}
	else if (Mode == "Play") {
		//DrawLogo();
		int address;
		cin >> hex >> address;
		

		/*for (int i = address; i >= address - 100; i--) {
			cout <<show_hex(address)<< " : " << _cpu.ram[i] << endl;
		}*/
		system("CLS");

		for (int i = address; i <= address+300; i++) {
			cout << show_hex(i) << " : " << show_hex(_cpu.ram[i]) << endl;
		}


		Mode = "Debug";
		//ready = true;
	}

	//actual screen
	for (int ly = 0; ly < 160; ly++) {
		for (int lx = 0; lx < 144; lx++) {
			Draw(olc::vi2d(lx + 300, ly + 300), pixels[ly][lx]);
		}
	}
	


	return true;
}