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

	if (GetKey(olc::Key::Q).bReleased)
		Mode = (Mode == "Debug") ? "Play" : "Debug";

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


bool Gameboy::OnUserUpdate(float fElapsedTime) {
	int c = 0;
	
	
	Clear(olc::BLUE);
	//DrawTile(MakeTile(check), 50, 50);
	//DrawLogo();

	


	
	input();
	if (ready) {
		_cpu.cycle();
		sprites = _cpu.oam_scan();
		uint8_t bg = 


		ready = false;
	}
	
	if (Mode == "Debug") {
		if (Macro == 'n') {
			for (int i = 0; i < steps; i++) {
				_cpu.cycle();
				Debugger();
			}
			Macro = '-';
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

		for (int i = address; i <= address+300; i++) {
			cout << show_hex(i) << " : " << show_hex(_cpu.ram[i]) << endl;
		}


		Mode = "Debug";
		//ready = true;
	}


	//actual screen
	for (int ly = 0; ly < 144; ly++) {
		for (int lx = 0; lx < 160; lx++) {
			Draw(olc::vi2d(ly+300, lx+300));
		}
	}



	return true;
}