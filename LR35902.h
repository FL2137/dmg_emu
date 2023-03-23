#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <functional>
#include <vector>
using namespace std;

class LR35902 {
	//placeholding memory arrays

public:
	uint16_t AF = 0x0000;
	uint16_t BC = 0x0000;
	uint16_t DE = 0x3322;
	uint16_t HL = 0x5511;

	enum FLAG {
		NONE = 0,
		Z = 1,
		NZ = 2,
		N = 3,
		NN = 4,
		H = 5,
		NH = 6,
		C = 7,
		NC = 8,
	};



	bool IME;
	bool IE;

	int dot_count;

	int cycles_done = 0;

	int opcode;
	void lookup();

	uint8_t* oam_scan();

	uint8_t* get_tile(int index);

	uint8_t* stat;
	uint8_t* lcdc;

	
	uint16_t stkp = 0xFFFE;
	uint16_t pc = 0x0000;

	uint8_t* ram;


	int get_bit(uint8_t obj, int nbit) {
		return (obj & (1 << nbit)) >> nbit;
	}

	void set_bit(uint8_t& obj, int nbit) {
		if (nbit >= 8 || nbit < 0)
			throw out_of_range("nbit out of range");

		obj = (obj | (1 << nbit));
	}


	bool check_flag(FLAG f);
	void set_flag(FLAG f, int val = 1);
	void print_flags();
	
	void set_reg(uint16_t& reg, char hilo, uint8_t val);


	void dummy_init() {
		ram = new uint8_t[0xFFFF+1]{0};
		for (int i = 0; i <= 0xFFFF; i++)
			ram[i] = 0x00;

		stat = &ram[0xFF41];
		lcdc = &ram[0xFF40];

		*lcdc = 0x00;
		*stat = 0x00;

		AF = 0x01B0;
		BC = 0x0013;
		DE = 0x00D8;
		HL = 0x014D;
		pc = 0x100;

		stkp = 0xFFFE;

		ram[0xFF00] = 0xFF;
		ram[0xFF05] = 0x00;
		ram[0xFF06] = 0x00;
		ram[0xFF07] = 0x00;
		ram[0xFF10] = 0x80;
		ram[0xFF11] = 0xBF;
		ram[0xFF12] = 0xF3;
		ram[0xFF14] = 0xBF;
		ram[0xFF16] = 0x3F;
		ram[0xFF17] = 0x00;
		ram[0xFF19] = 0xBF;
		ram[0xFF1A] = 0x7F;
		ram[0xFF1B] = 0xFF;
		ram[0xFF1C] = 0x9F;
		ram[0xFF1E] = 0xBF;
		ram[0xFF20] = 0xFF;
		ram[0xFF21] = 0x00;
		ram[0xFF22] = 0x00;
		ram[0xFF23] = 0xBF;
		ram[0xFF24] = 0x77;
		ram[0xFF25] = 0xF3;
		ram[0xFF26] = 0xF1;
		ram[0xFF40] = 0x91;
		ram[0xFF42] = 0x00;
		ram[0xFF43] = 0x00;
		ram[0xFF45] = 0x00;
		ram[0xFF47] = 0xFC;
		ram[0xFF48] = 0xFF;
		ram[0xFF49] = 0xFF;
		ram[0xFF4A] = 0x00;
		ram[0xFF4B] = 0x00;
		ram[0xFFFF] = 0x00;




	}
	void cycle();

	void load_rom(const char* filename, string mbc);
	void load_bootrom();
	void init();


private:

	

	string address = " ";

	
	void NOP() {
		cout << "NOP\n";
		pc++;
	}


	using instruction = void (LR35902::*)();
	instruction instructions[256]{ &LR35902::NOP };

	int cycle_timer = 0;


	int get_addr(uint8_t len);
	

	void JP(FLAG f);
	void JR(FLAG f);


	void CALL(FLAG f);
	void RET(FLAG f);
		
	
	void HALT();

	void DI();
	void EI();



	void LD8(uint16_t& dst, char hilo, uint16_t* src, char hilo_src);
	void LD16(uint16_t& reg, uint16_t* src);
	void LD_MEM(uint16_t& reg, uint16_t src);


	void LDH(uint16_t reg, uint16_t src);
	void LDHT(uint8_t& regm, uint8_t src);



	void INC16(uint16_t& reg);
	void DEC16(uint16_t& reg);


	void INC8(uint16_t& reg, char hilo);
	void DEC8(uint16_t& reg, char hilo);


	void ADD16(uint16_t& dst, uint16_t src);


	void ADD8(uint16_t src, char hilo);

	void SUB(uint8_t reg);

	void ADC(uint8_t* src);


	void XOR(uint16_t reg, char hilo);
	void OR(uint16_t reg, uint16_t half);
	void AND(uint16_t reg, uint16_t half);
	void CP(uint16_t reg, char hilo);

	void SCF();



	//CB PREFIXED FUNCTIONS
	void SLA(uint16_t& reg, uint16_t half);
	void RL(uint16_t& reg, char hilo);
	void RLC(uint16_t& reg, char hilo);

	void BIT(uint8_t bit, uint16_t reg, uint16_t half);

	void POP(uint16_t& reg);
	void PUSH(const uint16_t &reg);

	void RES(uint16_t& reg, char hilo, uint8_t bit);
	void SET(uint16_t& reg, char hilo, uint8_t bit);

public:

	LR35902();


	~LR35902() {
		delete[] ram;
	}

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


};
