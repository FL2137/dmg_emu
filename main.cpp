#define OLC_PGE_APPLICATION
#include "Graphics.h"
#include "LR35902.h"

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

int len = 1;
bool testing = false;

void set_reg(uint16_t& reg, char hilo, uint8_t val) {
	if (hilo == 'h') {
		reg &= 0x00FF;
		reg |= val << 8;
	}
	else if (hilo == 'l') {
		reg &= 0xFF00;
		reg |= val;
	}
	else
		cout << "INCORRECT REGISTER\n";
}


void test(uint8_t a) {

	uint8_t A = 0x3E;
	uint8_t reg = 0x50;
	cout <<"A:" << (uint32_t)A << endl;

	//TO JEST NIE SPRAWDZONE W ŻADNYM STOPNIU
	if (
		((A & 16) >> 4) == 1 && (((A + reg) & 16) >> 4) == 0
		||
		((A & 16) >> 4) == 0 && (((A + reg) & 16) >> 4) == 1
		)
		cout << "1\n";//set_flag(FLAG::H);
	else
		cout << "0\n";//set_flag(FLAG::H, 0);


	if (reg > A) {
		A = 256 - ((A-reg)*(-1));
		cout << show_hex(A) << endl;
		//set_flag(C,1);
	}



		




	getchar();
		
}
void ADC(uint8_t* src) {
	cout << show_hex(*src) << endl;
}


//TO CONSIDER
//IS 'hilo' REALLY BETTER THAN PASSING A UINT8 FROM A STRUCTURE


#include <map>
#include <functional>

class Instruction {
public:
	uint8_t *r1;
	uint8_t *r2;

	uint16_t *r16;
	
	std::function<void(uint8_t, uint8_t, uint16_t)> foo;
};



void example(uint8_t a, uint8_t b, uint16_t db) {

}

//🤔
void sraka(int a){}

typedef void (*generic_op)(void);

typedef void (*ex)(uint8_t, uint8_t, uint16_t);


int get_bit(uint8_t obj, int nbit) {
	return (obj & (1 << nbit)) >> nbit;
}

int main() {


	/*generic_op optab[2] = {
		generic_op(example),
		generic_op(sraka)
	};

	((ex)optab[0])(1, 1, 1);*/

	/*uint8_t rel = 0x12;

	ADC(&rel);
	getchar();
	return -11;

	if (testing) test(-257);
	return 1;*/

	LR35902 cpu;
	cpu.dummy_init();
	Gameboy gb(cpu);

	//cpu.load_rom("Testers/LD8.gb", "INIT");
	string rom = "tetris.gb";
	//cout << "Podaj rom\n";
	//cin >> rom;
	cpu.load_rom(rom.c_str(), "INIT");

	if (gb.Construct(160*5, 144*5, 1, 1))
		gb.Start();

	if (testing == false) {

		for (int i = 0; i < len; i++)
			cpu.cycle();
		getchar();
	}
	else test(-1);
	

	
	return 0;
}