#pragma once
#include "olcPixelGameEngine.h"
#include <stdint.h>
#include <string>
#include <iostream>

using namespace std;


class Processor {

    //defines
public: //should be private
    //LCD registers
#define LCDC ram[0xFF40]
#define STAT ram[0xFF41]

//Timers 
#define CLOCKRATE 4194304
#define DIV ram[0xFF04]
#define TIMA ram[0xFF05]
#define TMA ram[0xFF06]
#define TAC ram[0xFF07]

//Interrupts
#define IE ram[0xFFFF]
#define IF ram[0xFF0F]

//JOYPAD register
#define JOYP ram[0xFF00]

#define ROM_MAX 0x200000
#define FRAME_CYCLES 69905


//end of defines

public: //should be private

    Processor() {
        ram = new uint8_t[0xFFFF]{ 0 };
        AF = 0;
        BC = 0;
        DE = 0;
        HL = 0;
        SP = 0;
    }

    uint16_t AF, BC, DE, HL, SP;

    enum REG {
        // NONE = 0,
        // AF = 1,
        // BC = 2,
        // DE = 3,
        // HL = 4
    };

    enum FLAG {
        NONE = -1,
        NC = 0,
        NH = 1,
        NN = 2,
        NZ = 3,
        C = 4,
        H = 5,
        N = 6,
        Z = 7
    };

    enum INT {
        VBLANK = 0,
        LCDSTAT = 1,
        TIMER = 2,
        SERIAL = 3,
        JOYPAD = 4
    };

    uint8_t rom_memory[ROM_MAX]{ 0 };

    uint8_t* ram; //console's memory

    olc::Pixel display[144][160];

    bool draw_flag = false;

    uint16_t pc;
    int opcode;
    int op_cycles;
    int scanline_cycles = 0;

    int passed_cycles = 0;

    int IME;

    int timer_counter;
    int div_counter;

    int scanline;

    bool mbc1 = false;
    bool mbc2 = false;
    bool no_mbc = false;
    int current_bank;
    bool booted = false;

    //CORE FUNCTIONS
    
    void load_boot_routine();

    void load_rom(const char* filename);

    void write_mem(uint16_t addr, uint8_t value);

    uint8_t read_mem(uint16_t addr);

    void cycle();

    void lookup();

    void timers();

    void set_interrupt(int n);

    void interrupts();

    void joypad();

    void LCD();

    void graphics();

    void render_scanline();

    void render_tiles();

    void render_sprites();

    void launch_DMA(uint8_t data);

    void manage_banking();

    void initialization();

    //UTILITY FUNCTIONS

    int get_bit(uint8_t obj, int nbit);

    int get_bit(uint16_t obj, int nbit);

    void set_bit(uint8_t& obj, int nbit, int val = 1);

    uint16_t get_reg16(REG reg);

    void set_reg(uint16_t& reg, char hilo, uint8_t value);

    int get_flag(FLAG f);

    void set_flag(FLAG f, int value = 1);

    int8_t unsigned_to_signed(uint8_t u);

    std::string get_hex(int n);


    //CPU INSTRUCTIONS

    //miscellaneous
    void NOP();
    void STOP();
    void HALT();

    void DI();
    void EI();

    void DAA();
    void SCF();
    void CPL();
    void CCF();

    //LD instructions

    void LD8(uint16_t& dst, char hilo, uint16_t* src, char srchilo);
    void LD16(uint16_t* reg, uint16_t* src);


    //INC DEC instructions

    void INC8(uint16_t &reg, char hilo);
    void INC16(uint16_t& inc);

    void DEC8(uint16_t &reg, char hilo);
    void DEC16(uint16_t& reg);


    //Arithmetic instructions

    void ADD8(uint16_t* reg, char hilo);
    void ADD16(uint16_t* src);
    void ADC8(uint16_t* reg, char hilo);

    void SUB8(uint16_t* reg, char hilo);
    void SBC8(uint16_t* reg, char hilo);

    void AND(uint16_t* reg, char hilo);
    void XOR(uint16_t* reg, char hilo);
    void OR(uint16_t* reg, char hilo);

    void CP(uint16_t* reg, char hilo);

    void RLA();
    void RLCA();

    void RRCA();
    void RRA();

    //Stack instructions

    void POP(uint16_t& reg);
    void PUSH(const uint16_t& reg);

    //Jumps and Calls

    void CALL(FLAG f);
    void JR(FLAG f);
    void JP(FLAG f);

    void RET(FLAG f);
    void RETI();

    void RST();


    //Extended xCB instructions

    void RES(uint16_t* reg, char hilo, int bit);
    void SET(uint16_t* reg, char hilo, int bit);

    void RLC(uint16_t& reg, char hilo);
    void RRC(uint16_t& reg, char hilo);

    void RL(uint16_t& reg, char hilo);
    void RR(uint16_t& reg, char hilo);

    void SLA(uint16_t& reg, char hilo);
    void SRA(uint16_t& reg, char hilo);
    void SRL(uint16_t& reg, char hilo);

    void SWAP(uint16_t* reg, char hilo);

    void BIT(uint16_t* reg, char hilo, int bit);

};
