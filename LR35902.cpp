#include "LR35902.h"

/*
#define AF 0x01
#define BC 0x02
#define DE 0x03
#define HL 0x04
*/


void LR35902::load_bootrom() {
    ifstream bootrom("dmg_boot.gb", ios::binary | ios::ate);
    if (bootrom.is_open()) {
    
        streamsize size = bootrom.tellg();
        char* buffer = new char[size];
        bootrom.seekg(0, ios::beg);
        bootrom.read(buffer, size);
        bootrom.close();
        cout << "BOOTROM SIZE:" << size << endl;
        for (int i = 0; i <= size; i++) {
            ram[i] = buffer[i];
        }
        delete[] buffer;
    }
}

void LR35902::load_rom(const char* filename, string mbc) {
    ifstream rom(filename, ios::binary | ios::ate);
    if (rom.is_open()) {
        streamsize size = rom.tellg();
        char* buffer = new char[size];
        rom.seekg(0, ios::beg);
        rom.read(buffer, size);
        rom.close();
        cout <<"ROM SIZE:" << show_hex(size) << endl;

        //if (mbc == "INIT") 
          //  size = 0xFFFF;

        for (long i = 0; i <= size; i++) {
            ram[i] = buffer[i];
        }
        cout << "ROM LOADED\n";
        delete[] buffer;
    }
    else
        cout << "CANT LOAD ROM\n";
    
    //load_bootrom();

}


bool LR35902::check_flag(FLAG f) {

    if (f == FLAG::Z) {
        return (bool)((AF & 0b0000000010000000) >> 7);
    }
    else if (f == FLAG::N) {
        return (bool)((AF & 0b0000000001000000) >> 6);
    }
    else if (f == FLAG::H) {
        return (bool)((AF & 0b0000000000100000) >> 5);
    }
    else if (f == FLAG::C) {
        return (bool)((AF & 0b0000000000010000) >> 4);
    }
    return 0;
}

void LR35902::set_flag(FLAG f, int val) {
    if (f == FLAG::Z)
        if (val == 1)
            AF = AF | 0b0000'0000'1000'0000;
        else
            AF = AF & (0b1111'1111'0111'1111);
    else if (f == FLAG::N)
        if (val == 1)
            AF = AF | 0b0000000001000000;
        else
            AF = AF & 0b1111'1111'1011'1111;
    else if (f == FLAG::H)
        if (val == 1)
            AF = AF | 0b0000'0000'0010'0000;
        else
            AF = AF & 0b1111'1111'1101'1111;
    else if (f == FLAG::C)
        if (val == 1)
            AF = AF | 0b000000000001'0000;
        else
            AF = AF & 0b1111'1111'1110'1111;
}

void LR35902::print_flags() {
    /*char FLAGS[4] = { 'C','H','N','Z' };
    string print = "";
    for (int f = 7; f >= 4; f--) {
        print += FLAGS[f - 4] + to_string((AF & (1 << f)) >> f);
    }
    cout << print << endl;*/

    int a = (AF & 0b0000000010000000 )>> 7;
    cout<<"FLAGS: "<< to_string(a) << endl;

}

uint8_t* LR35902::oam_scan() {

    int ly = get_bit(STAT, 2);

    uint8_t* sprites = new uint8_t[160];
    int j = 0;
    for (int it = 0xFE00; it <= 0xFE9F; it++) { //oam boundries
        sprites[j] = ram[it];
        j++;
    }
    return sprites; //memory leak if deletion of 'sprites' wont be handled elsewhere ;b
}

uint8_t* LR35902::get_tile(int index) {
    uint8_t tile[4];
    int i = 0;
    index = 0x8000 + (index * 4);
    for ( ; i < 4; i++, index++) {
        tile[i] = ram[index];
    }
    return tile;
}

void LR35902::DMA() {
    uint16_t address = ram[0xFF46] << 8;
    for (int i = 0; i < 0xA0; i++) 
        ram[0xFE00 + i] = ram[address + i];
}

void LR35902::LCD(int cycles) {
    set_lcd();

    //if LCD is enabled
    if (get_bit(LCDC, 7)) 
        scan_cycles -= cycles;
    else 
        return;


    if (scan_cycles <= 0) {
        ram[0xFF44]++;
        uint8_t ly = ram[0xFF44];
        scan_cycles = 456;

        //entering VBlank, requesting interrupt
        if (ly == 144) {
            set_bit(IF, 0);
            draw_flag = false;
        }

        //reset scanline count
        else if (ly > 153) {
            ram[0xFF44] = 0;
            draw_flag = false;
        }

        else if (ly < 144) {
            draw_flag = true;
        }
    }
}

void LR35902::set_lcd() {
    uint8_t status = ram[0xFF41];

    if (get_bit(LCDC, 7) == 0) {

        scan_cycles = 456;
        ram[0xFF44] = 0;
        status &= 252;
        set_bit(status, 0);
        ram[0xFF41] = status;
        return;
    }

    uint8_t ly = ram[0xFF44];
    uint8_t mode = status & 0x3;

    uint8_t new_mode = 0;
    bool request_interrupt = false;

    //if in VBlank, mode is always 1
    if (ly >= 144) {
        new_mode = 1;
        set_bit(status, 0);
        set_bit(status, 1, 0);
        request_interrupt = get_bit(status, 4);
    }
    else {
        int mode2bounds = 456 - 80;
        int mode3bounds = mode2bounds - 172;

        //check for mode 2 
        if (scan_cycles >= mode2bounds) {
            new_mode = 2;
            set_bit(status, 1);
            set_bit(status, 0, 0);
            request_interrupt = get_bit(status, 5);
        }
        //check for mode 3
        else if (scan_cycles >= mode3bounds) {
            new_mode = 3;
            set_bit(status, 1);
            set_bit(status, 0);
        }
        //check for mode 0
        else {
            new_mode = 0;
            set_bit(status, 1, 0);
            set_bit(status, 0, 0);
            request_interrupt = get_bit(status, 3);
        }
    }

    //request LCD interrupt
    if (request_interrupt && (new_mode != mode)) 
        set_bit(IF, 1);


    if (ly == ram[0xFF45]) {
        set_bit(status, 2);
        if (get_bit(status, 6)) 
            set_bit(IF, 1);
    }
    else {
        set_bit(status, 2, 0);
    }

    ram[0xFF41] = status;
}

LR35902::LR35902() {}

void LR35902::init() {}

void LR35902::lookup() {
    
    
    switch (opcode) {

    case 0x00: NOP(); break;

    //prefixed instructions
    case 0xCB: {

        opcode = ram[pc + 1];

        if (opcode == 0x23) {
            SLA(DE, 0xFF00);
        }
        else if (opcode == 0x10) {
            RL(BC, 'h');
        }
        else if (opcode == 0x11) {
            RL(BC, 'l');
        }
        else if (opcode == 0x12) {
            RL(DE, 'h');
        }
        else if (opcode == 0x13) {
            RL(DE, 'l');
        }
        else if (opcode == 0x14) {
            RL(HL, 'h');
        }
        else if (opcode == 0x15) {
            RL(HL, 'l');
        }
        else if (opcode == 0x16) {
            RL(HL, '-');
        }
        else if (opcode == 0x17) {
            RL(AF, 'h');
        }
        else if (opcode == 0x7C) {
            BIT(0x07, HL, 0xFF00);
        }
        else if (opcode == 0x87) {
            RES(AF, 'h', 0);
        }
        break;
    }


    case 0xC5: PUSH(BC); break;
    case 0xD5: PUSH(DE); break;
    case 0xE5: PUSH(HL); break;
    case 0xF5: PUSH(AF); break;

    case 0xE1: POP(HL); break;
    case 0xC1: POP(BC); break;


    case 0x76: HALT(); break;

    case 0xCD: CALL(FLAG::NONE); break;
    case 0xCC: CALL(FLAG::Z); break;
    case 0xDC: CALL(FLAG::C); break;
    case 0xC4: CALL(FLAG::NZ); break;
    case 0xD4: CALL(FLAG::NC); break;

    case 0xC9: RET(FLAG::NONE); break;
    case 0xC8: RET(FLAG::Z);    break;
    case 0xD8: RET(FLAG::C);    break;

    case 0xC0: RET(FLAG::NZ);   break;
    case 0xD0: RET(FLAG::NC);   break;

    case 0xC3: JP(FLAG::NONE); break; 
    case 0xC2: JP(FLAG::NZ); break;
    case 0xD2: JP(FLAG::NC); break;
    case 0xCA: JP(FLAG::Z); break;
    case 0xDA: JP(FLAG::C); break;

    case 0x20: JR(FLAG::NZ); break; 
    case 0x30: JR(FLAG::NC); break; 
    case 0x18: JR(FLAG::NONE); break;
    case 0x28: JR(FLAG::Z); break;

    case 0x17: RL(AF, 'h'); pc--; set_flag(Z, 0); break;//Xd

    case 0x06: LD8(BC, 'h', nullptr, 0); break;
    case 0x16: LD8(DE, 'h', nullptr, 0); break;
    case 0x26: LD8(HL, 'h', nullptr, 0); break;
    case 0x36: LD8(HL, '-', nullptr, 0); break;
    case 0x0E: LD8(BC, 'l', nullptr, 0); break;
    case 0x1E: LD8(DE, 'l', nullptr, 0); break;
    case 0x2E: LD8(HL, 'l', nullptr, 0); break;
    case 0x3E: LD8(AF, 'h', nullptr, 0); break;


    case 0x40: LD8(BC, 'h', &BC, 'h'); break;
    case 0x41: LD8(BC, 'h', &BC, 'l'); break;
    case 0x42: LD8(BC, 'h', &DE, 'h'); break;
    case 0x43: LD8(BC, 'h', &DE, 'l'); break;
    case 0x44: LD8(BC, 'h', &HL, 'h'); break;
    case 0x45: LD8(BC, 'h', &HL, 'l'); break;
    case 0x46: LD8(BC, 'h', &HL, '-'); break;
    case 0x47: LD8(BC, 'h', &AF, 'h'); break;

    case 0x48: LD8(BC, 'l', &DE, 'h'); break;
    case 0x49: LD8(BC, 'l', &BC, 'l'); break;
    case 0x4a: LD8(BC, 'l', &DE, 'h'); break;
    case 0x4b: LD8(BC, 'l', &DE, 'l'); break;
    case 0x4c: LD8(BC, 'l', &HL, 'h'); break;
    case 0x4d: LD8(BC, 'l', &HL, 'l'); break;
    case 0x4e: LD8(BC, 'l', &HL, '-'); break;
    case 0x4F: LD8(BC, 'l', &AF, 'h'); break;

    case 0x50: LD8(DE, 'h', &BC, 'h'); break;
    case 0x51: LD8(DE, 'h', &BC, 'l'); break;
    case 0x52: LD8(DE, 'h', &DE, 'h'); break;
    case 0x53: LD8(DE, 'h', &DE, 'l'); break;
    case 0x54: LD8(DE, 'h', &HL, 'h'); break;
    case 0x55: LD8(DE, 'h', &HL, 'l'); break;
    case 0x56: LD8(DE, 'h', &HL, '-'); break;
    case 0x57: LD8(DE, 'h', &AF, 'h'); break;

    case 0x58: LD8(DE, 'l', &BC, 'h'); break;
    case 0x59: LD8(DE, 'l', &BC, 'l'); break;
    case 0x5a: LD8(DE, 'l', &DE, 'h'); break;
    case 0x5b: LD8(DE, 'l', &DE, 'l'); break;
    case 0x5c: LD8(DE, 'l', &HL, 'h'); break;
    case 0x5d: LD8(DE, 'l', &HL, 'l'); break;
    case 0x5e: LD8(DE, 'l', &HL, '-'); break;
    case 0x5f: LD8(DE, 'l', &AF, 'h'); break;

    case 0x60: LD8(HL, 'h', &BC, 'h'); break;
    case 0x61: LD8(HL, 'h', &BC, 'l'); break;
    case 0x62: LD8(HL, 'h', &DE, 'h'); break;
    case 0x63: LD8(HL, 'h', &DE, 'l'); break;
    case 0x64: LD8(HL, 'h', &HL, 'h'); break;
    case 0x65: LD8(HL, 'h', &HL, 'l'); break;
    case 0x66: LD8(HL, 'h', &HL, '-'); break;
    case 0x67: LD8(HL, 'h', &AF, 'h'); break;

    case 0x68: LD8(HL, 'l', &BC, 'h'); break;
    case 0x69: LD8(HL, 'l', &BC, 'l'); break;
    case 0x6a: LD8(HL, 'l', &DE, 'h'); break;
    case 0x6b: LD8(HL, 'l', &DE, 'l'); break;
    case 0x6c: LD8(HL, 'l', &HL, 'h'); break;
    case 0x6d: LD8(HL, 'l', &HL, 'l'); break;
    case 0x6e: LD8(HL, 'l', &HL, '-'); break;
    case 0x6f: LD8(HL, 'l', &AF, 'h'); break;


    case 0x77: LD8(HL, '-', &AF, 'h'); break;
    case 0x78: LD8(AF, 'h', &BC, 'h'); break;
    case 0x79: LD8(AF, 'h', &BC, 'l'); break;
    case 0x7A: LD8(AF, 'h', &DE, 'h'); break;
    case 0x7B: LD8(AF, 'h', &DE, 'l'); break;
    case 0x7C: LD8(AF, 'h', &HL, 'h'); break;
    case 0x7D: LD8(AF, 'h', &HL, 'l'); break;
    case 0x7E: LD8(AF, 'h', &HL, '-'); break;
    case 0x7F: LD8(AF, 'h', &AF, 'h'); break;


    case 0xE2: LDH(BC, 0); break;
    case 0xF2: LDH(0, BC); break;
    case 0xE0: LDH(0xFF, 0); break;
    case 0xF0: LDH(0, 0xFF); break;
    case 0xEA: LDH(0xFFFF, 0); break;
    case 0xFA: LDH(0, 0xFFFF); break;


    case 0x02: LD_MEM(BC, AF); break;
    case 0x12: LD_MEM(DE, AF); break;
    case 0x22: LD_MEM(HL, AF); break;
    case 0x32: LD_MEM(HL, AF); break;
    case 0x1A: LD_MEM(AF, DE); break;
    case 0x2A: LD_MEM(AF, AF); break;
    case 0x3A: LD_MEM(AF, HL); break;


    case 0x01: LD16(BC, nullptr); break;
    case 0x11: LD16(DE, nullptr); break;
    case 0x21: LD16(HL, nullptr); break;
    case 0x31: LD16(stkp, nullptr); break;


    case 0x04: INC8(BC, 'h'); break;
    case 0x0C: INC8(BC, 'l'); break;
    case 0x14: INC8(DE, 'h'); break;
    case 0x1C: INC8(DE, 'l'); break;
    case 0x24: INC8(HL, 'h'); break;
    case 0x2C: INC8(HL, 'l'); break;
    case 0x34: INC8(HL, '-'); break;


    case 0x05: DEC8(BC, 'h'); break;
    case 0x15: DEC8(DE, 'h'); break;
    case 0x25: DEC8(HL, 'h'); break;
    case 0x35: DEC8(HL, '-'); break;
    case 0x0D: DEC8(BC, 'l'); break;
    case 0x1D: DEC8(DE, 'l'); break;
    case 0x2D: DEC8(HL, 'l'); break;
    case 0x3D: DEC8(AF, 'h'); break;


    case 0x03: INC16(BC); break;
    case 0x13: INC16(DE); break;
    case 0x23: INC16(HL); break;
    case 0x33: INC16(stkp); break;

    case 0x80: ADD8(BC, 'h'); break;
    case 0x81: ADD8(BC, 'l'); break;
    case 0x82: ADD8(DE, 'h'); break;
    case 0x83: ADD8(HL, 'l'); break;
    case 0x84: ADD8(HL, '-'); break;
    case 0x85: ADD8(AF, 'h'); break;
   
    case 0xC6: ADD8(BC, 'h'); break;
    

    case 0xF3: DI(); break;
    case 0xFB: EI(); break;

    case 0xFE: CP(0x0000, 0); break;


    case 0x19: ADD16(HL, DE); break;


    case 0xAA: XOR(DE, 'h'); break;
    case 0xAB: XOR(DE, 'l'); break;
    case 0xAF: XOR(AF, 'h'); break;


    }
}

void LR35902::interrupts() {

    //check if interrupts are enabled
    if (IME) {
        
        //check for every interrupt in priority order

        //vblank
        if (((IE & IF) & 1) == 1) {
            
            IME = false;
            set_bit(IF, 1, 0);
            PUSH(pc);
            pc = 0x40;
            lookup();
            return;
        }
        
        //LCD STAT
        if ((((IE & IF) & 1) >> 1) == 1) {
            IME = false;
            set_bit(IF, 1, 0);
            PUSH(pc);
            pc = 0x48;
            lookup();
            return;
        }

        //timer
        if ((((IE & IF) & 1) >> 2) == 1) {
            IME = false;
            set_bit(IF, 1, 0);
            PUSH(pc);
            pc = 0x50;
            lookup();
            return;
        }

        //serial (never rly gonna happen)
        if (((IE & IF) & 1) == 1) {
            IME = false;
            set_bit(IF, 1, 0);
            PUSH(pc);
            pc = 0x58;
            lookup();
            return;
        }

        //joypad
        if ((((IE & IF) & 1) >> 3) == 1) {
            IME = false;
            set_bit(IF, 1, 0);
            PUSH(pc);
            pc = 0x60;
            lookup();
            return;
        }
    }
}

//#define DIV ram[0xFF04];
//#define TIMA ram[0xFF05];
//#define TMA ram[0xFF06];
//#define TAC ram[0xFF07];

void LR35902::handle_timers(int cycles) {
    if (DIV_check != DIV) {
        DIV = 0x00;

    }
}

void LR35902::cycle() {
    
    
    if (ram[0xFF44] == ram[0xFF45]) {  //if LY==LYC
        set_bit(STAT, 2); //stat.2 = true 
    }
    
    opcode = ram[pc];
    lookup();

    //checking if DMA register was written to, and if it was, launching DMA
    if (DMA_check) { 
        DMA();
    }

    //LCD routine
    LCD(cycles);


    handle_timers(cycles);

    interrupts();

    cycles_done += cycles;
    cycles = 0;

}

int LR35902::get_addr(uint8_t len) {
    if (len == 1)
        return 0;
    else if (len == 2)
        return ((int)ram[pc + 1]);
    else if (len == 3) {
        return ((int)ram[pc + 2] << 8 | (int)ram[pc + 1]);
    }
    return -1;
}



void get_reg(uint16_t reg, char lo_hi) {

}

void LR35902::set_reg(uint16_t& reg, char hilo, uint8_t val) {
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

void LR35902::write_mem(uint16_t address, uint8_t value) {

    //if DIV register is written to, then it is reset to 0x00
    if (address == 0xFF04) {
        DIV = 0x00;
        return;
    }
    else if (address == 0xFF46) {
        DMA_check = true;
        ram[0xFF46] = value;
        return;
    }

    ram[address] = value;
}

void LR35902::DI() {
    IME = false;

    cycles = 4;
    pc++;
}

void LR35902::EI() {
    IME = true;

    cycles = 4;
    pc++;
}

void LR35902::JP(FLAG f) {

    if (f == FLAG::NONE) {
        pc = ((int)ram[pc + 2] << 8) | (int)ram[pc + 1];
        cycles = 16;
        return;
    }
    else if (f == FLAG::H) {
        pc = HL;
        cycles = 4;
        return;
    }
    else if (f == FLAG::NZ) {
        if (check_flag(FLAG::Z) == 0) {
            uint16_t addr = ((int)ram[pc + 2] << 8) | (int)ram[pc + 1];
            pc = addr;
            cycles = 16;
            return;
        }
    }
    else if (f == FLAG::Z) {
        if (check_flag(FLAG::Z) == 1) {
            uint16_t addr = ((int)ram[pc + 2] << 8) | (int)ram[pc + 1];
            pc = addr;
            cycles = 16;
            return;
        }
    }
    else if (f == FLAG::NC) {
        if (check_flag(FLAG::C) == 0) {
            uint16_t addr = ((int)ram[pc + 2] << 8) | (int)ram[pc + 1];
            pc = addr;
            cycles = 16;
            return;
        }
    }
    else if (f == FLAG::C) {
        if (check_flag(FLAG::C) == 1) {
            uint16_t addr = ((int)ram[pc + 2] << 8) | (int)ram[pc + 1];
            pc = addr;
            cycles = 16;
            return;
        }
    }
    pc++;
    cycles = 12;
}

void LR35902::JR(FLAG f) {

    auto unsigned_to_signed = [](uint8_t u) -> int8_t {
        if (u <= INT8_MAX)
            return static_cast<int8_t>(u);
        if(u >= INT8_MIN)
            return static_cast<int8_t>(u - INT8_MIN) + INT8_MIN;
        throw u;
    };

    if (f == FLAG::NZ || f == FLAG::NC) {
        bool flag = f == NZ ? check_flag(FLAG::Z) : check_flag(FLAG::C);

        if (flag == false) {
            int8_t s8 = unsigned_to_signed(ram[pc + 1]);
            pc += s8 + 2;
            cycles = 12;
        }
        else {
            pc += 2;
            cycles = 8;
        }
    }
    else if (f == FLAG::NONE) {
        int8_t s8 = unsigned_to_signed(ram[pc + 1]);
        pc += s8 + 2;
        cycles = 12;
    }
    else {
        if (check_flag(f) == 1) {
            int8_t s8 = unsigned_to_signed(ram[pc + 1]);
            pc += s8 +2;
            cycles = 12;
        }
        else {
            pc += 2;
            cycles = 8;
        }
    }
}

void LR35902::HALT() {
    //set halt mode 
    //TBI
}

void LR35902::CALL(FLAG f) {

    if (f == NZ && !check_flag(Z)) {
        uint16_t hl = ((int)ram[pc + 2] << 8) | (int)ram[pc + 1];
        ram[stkp - 1] = (((pc + 3) & 0xFF00) >> 8);
        ram[stkp - 2] = (pc + 3) & 0x00FF;
        stkp -= 2;
        pc = hl;
        cycles = 24;
        return;
    }
    
    if (f == NC && !check_flag(C)) {
        uint16_t hl = ((int)ram[pc + 2] << 8) | (int)ram[pc + 1];
        ram[stkp - 1] = (((pc + 3) & 0xFF00) >> 8);
        ram[stkp - 2] = (pc + 3) & 0x00FF;
        stkp -= 2;
        pc = hl;
        cycles = 24;
        return;
    }

    if ((f == Z || f == C) && check_flag(f)) {
        uint16_t hl = ((int)ram[pc + 2] << 8) | (int)ram[pc + 1];
        ram[stkp - 1] = (((pc + 3) & 0xFF00) >> 8);
        ram[stkp - 2] = (pc + 3) & 0x00FF;
        stkp -= 2;
        pc = hl;
        cycles = 24;
        return;
    }

    if (f == NONE) {
        uint16_t hl = ((int)ram[pc + 2] << 8) | (int)ram[pc + 1];
        ram[stkp - 1] = (((pc + 3) & 0xFF00) >> 8);
        ram[stkp - 2] = (pc + 3) & 0x00FF;
        stkp -= 2;
        pc = hl;
        cycles = 24;
        return;
    }

    pc += 3;
    cycles = 12;
}

void LR35902::RET(FLAG f) {
    if (f == FLAG::NONE) {
        uint16_t newPC = (ram[stkp] | ram[stkp + 1] << 8);
        stkp += 2;
        pc = newPC;
        cycles = 4;
        return;
    }
    else if((f==FLAG::NZ || f==FLAG::NC) && check_flag(f) == false){
        uint16_t newPC = (ram[stkp] | ram[stkp + 1] << 8);
        stkp += 2;
        pc = newPC;
        cycles = 5;
        return;
    }
    else if ((f == FLAG::Z || f == FLAG::C) && check_flag(f) == true) {
        uint16_t newPC = (ram[stkp] | ram[stkp + 1] << 8);
        stkp += 2;
        pc = newPC;
        cycles = 5;
        return;
    }

    pc++;
    cycles = 2;
}

void LR35902::RETI() {
    pc = (ram[stkp] | ram[stkp + 1] << 8);
    stkp += 2;
    cycles = 16;
    IME = true;
}

//POSSIBLE PROBLEMS WHEN LOADING zeros into registers, such like  dst | 0x0000
//TROUBLE LOADING ADDRESSES
//OPIWFGNAWIGFWAOPAW
// 4x, 5x, 6x, 7x and apparently 0,1,2,3x instructions
void LR35902::LD8(uint16_t& dst, char hilo, uint16_t* src, char hilo_src) {
    if (dst == HL && hilo == '-') {
        uint8_t val = 0x00;
        if (hilo_src == 'l')
            val = (*src & 0x00FF);
        else if (hilo_src == 'h')
            val = (*src & 0xFF00) >> 8;
        write_mem(HL, val);
        pc++;
        cycles = 8;
        return;
    }
    if (src == nullptr) {
        set_reg(dst, hilo, ram[pc + 1]);
        pc += 2;
        cycles = 4;
        return;
    }

    //default:
    uint8_t val = 0x00;
    if (hilo_src == 'l')
        val = (*src & 0x00FF);
    else if (hilo_src == 'h')
        val = (*src & 0xFF00) >> 8; 
    set_reg(dst, hilo, val);
    pc++;
    cycles = 4;
}

void LR35902::LD16(uint16_t& reg, uint16_t* src) {
    if (src == nullptr) {
        uint16_t addr = (ram[pc + 1] | ram[pc + 2] << 8);
        reg = addr;
        pc += 3;
        cycles = 12;
        return;
    }
    else if (reg == 0xFEA1) {
        uint16_t addr = (ram[pc + 1] << 8 | ram[pc + 2]);
        write_mem(addr, stkp & 0xFF00);
        write_mem(addr + 1, stkp )

        ram[addr] = stkp & 0xFF00;
        ram[addr + 1] = stkp & 0xFF00;
        pc += 3;
        cycles = 20;
        return;
    }
    else if (reg == HL && src == &stkp) {
        uint8_t sgn = ram[pc + 1];
        reg = *src + sgn;
        pc += 2;
        cycles = 12;
    }
    else {
        reg = *src;
        pc++;
        cycles = 8;
    }
}

//TO REFACTOR
// Ex and Fx instructions
// in (C), A   or in every single if the amount of bytes pc is increased by is probably wrong in the opcode table
void LR35902::LDH(uint16_t reg, uint16_t src) {
    address = show_hex(pc);
    if (reg == 0xFFFF) {
        ram[(ram[pc + 1] | ram[pc + 2] << 8)] = (AF & 0xFF00) >> 8;
        pc += 3;
        cycles = 16;
    }
    else if (src == 0xFFFF) {
        set_reg(AF, 'h', ram[(ram[pc + 1] | ram[pc + 2] << 8)]);
        pc += 3;
        cycles = 16;
    }
    else if (reg == 0xFF) {
        cout << "ff00 + " + show_hex(ram[pc + 1]) << endl;
        ram[0xFF00 + ram[pc + 1]] = (AF & 0xFF00) >> 8;
        pc += 2;
        cycles = 12;
    }
    else if (src == 0xFF) {
        //cout << "ff00 + " + show_hex(ram[pc + 1]) << endl;
       // cout << show_hex(ram[0xff00+ram[pc + 1]]) << endl;
        //cout << endl << "LDH ADDR: " << show_hex(ram[0xffff]) << endl;
        //cout << "before: " << show_hex(AF) << endl;
        //set_reg(AF, 'h', ram[0xFF00 + ram[pc + 1]]);
        //cout << "after: " << show_hex(AF) << endl;

        pc += 2;
        cycles = 12;
    }
    else if (reg == BC) {
        ram[0xFF00 + (BC & 0x00FF)] = (AF & 0xFF00) >> 8;
        pc += 1;
        cycles = 8;
    }
    else if (src == BC) {
        set_reg(AF, 'h', ram[0xFF00 + (BC & 0x00FF)]);
        pc += 2;
        cycles = 8;
    }

}

//TO REFACTOR
void LR35902::LD_MEM(uint16_t& reg, uint16_t src) {
    if (src == AF) {
        if (opcode == 0x22)
            ram[reg++] = (AF & 0xFF00) >> 8;
        else if (opcode == 0x32) {
            ram[reg--] = (AF & 0xFF00) >> 8;
        }
        else {
            ram[reg] = (AF & 0xFF00) >> 8;
        }

        pc++;
        cycles = 8;
    }
    else if (reg == AF) {

        set_reg(AF, 'h', ram[src]);
        if (opcode == 0x2A)
            HL++;
        else if (opcode == 0x3A)
            HL--;
        pc++;
        cycles = 8;
    }


}

void LR35902::INC16(uint16_t& reg) {
    reg++;
    cycles = 8;
    pc++;
}

void LR35902::DEC16(uint16_t& reg) {
    reg--;
    cycles = 8;
    pc++;
}

//NOT SURE IF HALFCARRY FLAG IS SET PROPERLY
void LR35902::INC8(uint16_t& reg, char hilo) {
    if (hilo == '-') {
        set_flag(FLAG::N, 0);
        uint16_t halfcarry_check;

        halfcarry_check = ram[HL] & 0b0001'0000;
        ram[HL] += 1;
        if (halfcarry_check != (ram[HL] & 0b0001'0000))
            set_flag(FLAG::H);
        else
            set_flag(FLAG::H, 0);

        if (ram[HL] == 0)
            set_flag(FLAG::Z);
        else
            set_flag(FLAG::Z, 0);
        cycles = 12;
        return;
    }


    set_flag(FLAG::N, 0);

    uint16_t halfcarry_check;
    uint8_t R=0;
    if (hilo == 'l') {
        R = reg & 0x00FF;
    }
    else if (hilo == 'h') {
        R = (reg & 0xFF00) >> 8;
    }
    
    set_reg(reg, hilo, R+1);

    if (R + 1 == 0)
        set_flag(FLAG::Z);
    else
        set_flag(FLAG::Z, 0);




    cycles = 4;
    pc++;
}

void LR35902::DEC8(uint16_t& reg, char hilo) {

    if (hilo == 0) {
        ram[HL]--;
        set_flag(FLAG::N);

        if (ram[HL] == 0)
            set_flag(FLAG::Z);
        else
            set_flag(FLAG::Z, 0);


        //XD?
        if ((ram[HL] & 0x10) == 0x10)
            set_flag(FLAG::H);
        else
            set_flag(FLAG::H, 0);
        pc++;
        cycles = 12;
        return;
    }


    if (hilo == 'h')
        set_reg(reg, hilo, ((reg & 0xFF00) >> 8) - 1);
    else if (hilo == 'l')
        set_reg(reg, hilo, (reg & 0x00FF) - 1);

    set_flag(FLAG::N);

    if (hilo == 'h') {
        
        if (((reg & 0xFF00)>>8) == 0)
            set_flag(FLAG::Z);
        else
            set_flag(FLAG::Z, 0);
        
        if ((reg & (1 << 12)) >> 12 == 1)
            set_flag(FLAG::H);
        else
            set_flag(FLAG::H, 0);

    }
    else if (hilo == 'l') {

        if ((reg & 0x00ff) == 0) {
            set_flag(FLAG::Z);
        }
        else
            set_flag(FLAG::Z, 0);

        if ((reg & (1 << 4)) >> 4 == 1)
            set_flag(FLAG::H);
        else
            set_flag(FLAG::H, 0);
    }

    cycles = 1;
    pc++;
}

void LR35902::ADD16(uint16_t& dst, uint16_t src) {

}

void LR35902::ADD8(uint16_t src, char hilo) {
    
    uint8_t A = (AF & 0xFF00) >> 8;

    //checks for half-carry and sets/resets it
    if (((A & 0xF) + (src & 0xF)) == 0x10)
        set_flag(FLAG::H);
    else
        set_flag(FLAG::H, 0);

    //checks if result==0, sets/resets Z flag
    if ((uint8_t)(A + src) == 0)
        set_flag(FLAG::Z, 1);
    else
        set_flag(FLAG::Z, 0);

    //always resets N flag
    set_flag(FLAG::N, 0);
  
    //checks for carry, sets/resets flag
    if ((uint16_t)(A + src) == 0x100)
        set_flag(FLAG::C);
    else
        set_flag(FLAG::C, 0);

    //sets accumulator to result;
    set_reg(AF, 'h', (uint8_t)(A + src));

}

void LR35902::ADC(uint16_t reg, char hilo) {

    if (hilo == '-') {
        uint8_t value = ram[HL] + check_flag(C);
        set_flag(C, 0);
        uint8_t A = AF >> 8;
        if (A + value > 255)
            set_flag(C, 1);

        A += value;

        if (((A & 0xF) + (reg & 0xF)) == 0x10)
            set_flag(FLAG::H);
        else
            set_flag(FLAG::H, 0);

        if (A == 0)
            set_flag(Z, 1);
        else
            set_flag(Z, 0);

        set_flag(N, 0);

        set_reg(AF, 'h', A);

        pc++;
        cycles = 4;
        return;
    }

    uint8_t value = hilo == 'l' ? reg & 0xFF : (reg & 0xFF00) >> 8;

    value += check_flag(C);
    set_flag(C, 0);
    uint8_t A = AF >> 8;
    if (A + value > 255)
        set_flag(C, 1);

    A += value;

    if (((A & 0xF) + (reg & 0xF)) == 0x10)
        set_flag(FLAG::H);
    else
        set_flag(FLAG::H, 0);

    if (A == 0)
        set_flag(Z, 1);
    else
        set_flag(Z, 0);

    set_flag(N, 0);

    set_reg(AF, 'h', A);

    pc++;
    cycles = 4;
    return;
}

//not finished ( (HL) case not handled)
void LR35902::SUB(uint8_t reg) {

    uint8_t A = (AF & 0xFF00) >> 8;

    if (reg == -1) {

    }

    if (reg > A) {
        if (
            ((A & 16) >> 4) == 1 && (((A + reg) & 16) >> 4) == 0
            ||
            ((A & 16) >> 4) == 0 && (((A + reg) & 16) >> 4) == 1
            )
            set_flag(FLAG::H);
        else
            set_flag(FLAG::H, 0);

        A = 256 - ((A - reg) * (-1));

        set_reg(AF, 'h', A);

        set_flag(C, 1);
        set_flag(FLAG::N, 1);

        if (A == 0)
            set_flag(Z, 1);
        else
            set_flag(Z, 0);

        cycles = 4;
        pc++;
        return;
    }

    //checks for half carry
    if (
        ((A & 16) >> 4) == 1 && (((A + reg) & 16) >> 4) == 0 //lhp - A before addition |  rhp - A after addition    shifted from 4th bit 
        || // if the bits are different then there was half carry
        ((A & 16) >> 4) == 0 && (((A + reg) & 16) >> 4) == 1
        )
        set_flag(FLAG::H);
    else
        set_flag(FLAG::H, 0);
        

    set_flag(C, 0);
    set_flag(N, 1);

    A = A - reg;

    if (A == 0)
        set_flag(Z, 1);
    else
        set_flag(Z, 0);


    set_reg(AF, 'h', A);


    cycles += 4;
    pc++;
    return;
}

void LR35902::XOR(uint16_t reg, char hilo) {
    address = "XOR A";
    if (hilo == '-') {
        uint8_t value = ram[HL];
        uint8_t A = (AF & 0xFF00) >> 8;
        A ^= value;
        set_reg(AF, 'h', A);
        if (A == 0)
            set_flag(Z);
        else
            set_flag(Z, 0);

        set_flag(FLAG::C, 0);
        set_flag(FLAG::N, 0);
        set_flag(FLAG::H, 0);

        pc++;
        cycles = 8;
        return;
    }

    uint16_t A = (AF & 0xFF00) >> 8;
    uint16_t R = 0x0000;

    if (hilo == 'h')
        R = (reg & 0xFF00) >> 8;
    else if (hilo == 'l')
        R = (reg & 0x00FF);

    A ^= R;
    set_reg(AF, 'h', A);


    if (A == 0x0000)
        set_flag(FLAG::Z);
    else
        set_flag(FLAG::Z, 0);

    set_flag(FLAG::C, 0);
    set_flag(FLAG::N, 0);
    set_flag(FLAG::H, 0);

    pc++;
    cycles = 4;
    
}

void LR35902::OR(uint16_t reg, uint16_t half) {
    uint16_t A = (AF & 0xFF00) >> 8;
    uint16_t R = (reg & half);
    if (half == 0xFF00)
        R >>= 8;
    A |= R;
    AF = AF & (0x00FF);
    AF = (A << 8) | AF;
    if (AF == 0x0000)
        set_flag(FLAG::Z);
    else
        set_flag(FLAG::Z, 0);

    set_flag(FLAG::C, 0);
    set_flag(FLAG::N, 0);
    set_flag(FLAG::H, 0);

    pc++;
    cycles = 4;
    if (half == 0xFFFF)
        cycles = 8;
}

void LR35902::AND(uint16_t reg, uint16_t half) {
    uint16_t A = (AF & 0xFF00) >> 8;
    uint16_t R = (reg & half);
    if (half == 0xFF00)
        R >>= 8;
    A |= R;
    AF = AF & (0x00FF);
    AF = (A << 8) | AF;
    if (AF == 0x0000)
        set_flag(FLAG::Z);
    else
        set_flag(FLAG::Z, 0);

    set_flag(FLAG::C, 0);
    set_flag(FLAG::H, 1);
    set_flag(FLAG::N, 0);

    pc++;
    cycles = 4;
    if (half == 0xFFFF)
        cycles = 8;
}

void LR35902::PUSH(const uint16_t& reg) {
    stkp--;
    ram[stkp] = (reg & 0xFF00) >> 8;
    stkp--;
    ram[stkp] = (reg & 0x00FF);
    cycles = 16;
    pc++;
}

void LR35902::POP(uint16_t& reg) {

    //its possible that when POPing AF register flags should be set accordingly
    if (reg == AF) {
    
        reg = (ram[stkp] | ram[stkp + 1] << 8);
    
        //??? set flags?
        
        stkp += 2;
        pc++;
        cycles = 12;
        return;
    }

    reg = (ram[stkp] | ram[stkp + 1] << 8);
    stkp += 2;
    pc++;
    cycles = 12;
}

void LR35902::CP(uint16_t reg, char hilo = 0) {
    if (reg == 0x0000) {
        uint8_t d8 = ram[pc + 1];
        uint8_t A = (AF & 0xFF00) >> 8;

        if ((A - d8) == 0)
            set_flag(FLAG::Z);
        else
            set_flag(FLAG::Z, 0);

        set_flag(FLAG::N, 1);
        if ((((A & 0xF) - (d8 & 0xF)) & 0x10) == 0x10)
            set_flag(FLAG::H);
        else
            set_flag(FLAG::H, 0);
        set_flag(FLAG::C, 0);
        pc += 2;
        cycles = 8;
        return;
    }

    uint8_t cp;
    if (hilo == 'l')
        cp = reg & 0xFF;
    else if (hilo == 'h')
        cp = (reg & 0xFF) >> 8;

    if (((AF & 0xFF) >> 8) - cp == 0)
        set_flag(FLAG::Z);
    else
        set_flag(FLAG::Z, 0);

    set_flag(FLAG::N, 1);

    uint8_t A = (AF & 0xFF) >> 8;
    if ((((A & 0xF) - (cp & 0xF)) & 0x10) == 0x10)
        set_flag(FLAG::H);
    else
        set_flag(FLAG::H, 0);
    set_flag(FLAG::C, 0);

    pc++;
    cycles = 4;
}

void LR35902::SCF() {
    set_flag(FLAG::N, 0);
    set_flag(FLAG::H, 0);
    set_flag(FLAG::C, 1);
    cycles = 1;
    pc++;
}


//CB PREFIXED FUNCTIONS START
void LR35902::SLA(uint16_t& reg, uint16_t half) {
    if (reg == HL && half == 0xFFFF) {
        pc++;
        cycles = 16;
        return;
    }
    pc++;
    cycles = 8;
}

void LR35902::RL(uint16_t& reg, char hilo) {
    if (hilo == '-') {

        int bit7 = (ram[HL] & (1 << 7)) >> 7;

        ram[HL] <<= 1;
        ram[HL] |= bit7;

        set_flag(FLAG::C, bit7);
        set_flag(FLAG::N, 0);
        set_flag(FLAG::H, 0);

        if (ram[HL] == 0)
            set_flag(FLAG::Z);
        else
            set_flag(FLAG::Z, 0);

        pc += 2;
        cycles = 8;
        return;
    }

    uint8_t R = 0;
    if (hilo == 'h')
        R = uint8_t((reg & 0xFF00) >> 8);
    else
        R = uint8_t(reg & 0x00FF);


    int bit7 = (R & (1 << 7)) >> 7;

    R <<= 1;
    R |= bit7;

    set_flag(FLAG::C, bit7);
    set_flag(FLAG::N, 0);
    set_flag(FLAG::H, 0);

    if (R == 0)
        set_flag(FLAG::Z);
    else
        set_flag(FLAG::Z, 0);


    set_reg(reg, hilo, R);

    pc += 2;
    cycles = 8;
    return;

}

void LR35902::RLC(uint16_t& reg, char hilo) {

}

void LR35902::RES(uint16_t& reg, char hilo, uint8_t bit) {
    if (hilo == 'l') 
        reg = reg & (0xFFFF ^ (1 << bit));
    else if (hilo == 'h') 
        reg = reg & (0xFFFF ^ (1 << bit + 8));
    else
        ram[reg] = ram[reg] & (0 << bit);
    pc += 2;
    cycles = 8;
}

void LR35902::SET(uint16_t& reg, char hilo, uint8_t bit) {
    if (hilo == 'l')
        reg = reg | (1 << bit);
    else if (hilo == 'h')
        reg = reg | (1 << bit + 8);
    else
        ram[reg] = ram[reg] | (1 << bit);
    pc += 2;
    cycles = 8;
}

void LR35902::BIT(uint8_t bit, uint16_t reg, uint16_t half) {
    uint8_t R;
    uint8_t test = 1 << bit;
    if (half == 0xFF00)
        R = (reg & half) >> 8;
    else if (half == 0x00FF)
        R = (reg & half);
    else if (half == 0x0000) {
        R = ram[reg];
    }
    int result = (R & test) >> bit;
    set_flag(FLAG::Z, !result);
    set_flag(FLAG::N, 0);
    set_flag(FLAG::H);
    pc+=2;
    cycles = 8;
    if (half == 0x0000)
        cycles = 16;
}