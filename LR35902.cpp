#include "LR35902.h"

void Processor::initialization() {
    const int offset_y = 300;
    const int offset_x = 400;

    for (int y = 0; y < 144; y++) {
        for (int x = 0; x < 160; x++) {
            display[y][x] = olc::Pixel(255, 255, 255, 255);
        }
    }

    set_reg(AF, 'h', 0x11);
    set_reg(AF, 'l', 0x80);
    set_reg(BC, 'h', 0x00);
    set_reg(BC, 'l', 0x00);
    set_reg(DE, 'h', 0xFF);
    set_reg(DE, 'l', 0x56);
    set_reg(HL, 'h', 0x00);
    set_reg(HL, 'l', 0x0D);
    

    pc = 0x100; //start of the game rom

    SP = 0xFFFE; //top of the stack

    JOYP = 0xCF;
    DIV = 0xAB;
    TIMA = 0x00;
    TMA = 0x00;
    TAC = 0xF8;
    IF = 0xE1;
    IE = 0x00;
    LCDC = 0x91;
    STAT = 0x81;



    //nintendo logo

    {
        ram[0x8010] = 0xF0;
        ram[0x8011] = 0x00;
        ram[0x8012] = 0xF0;
        ram[0x8013] = 0x00;
        ram[0x8014] = 0xFC;
        ram[0x8015] = 0x00;
        ram[0x8016] = 0xFC;
        ram[0x8017] = 0x00;
        ram[0x8018] = 0xFC;
        ram[0x8019] = 0x00;
        ram[0x801a] = 0xFC;
        ram[0x801b] = 0x00;
        ram[0x801c] = 0xF3;
        ram[0x801d] = 0x00;
        ram[0x801e] = 0xF3;
        ram[0x801f] = 0x00;
        ram[0x8020] = 0x3C;
        ram[0x8021] = 0x00;
        ram[0x8022] = 0x3C;
        ram[0x8023] = 0x00;
        ram[0x8024] = 0x3C;
        ram[0x8025] = 0x00;
        ram[0x8026] = 0x3C;
        ram[0x8027] = 0x00;
        ram[0x8028] = 0x3C;
        ram[0x8029] = 0x00;
        ram[0x802a] = 0x3C;
        ram[0x802b] = 0x00;
        ram[0x802c] = 0x3C;
        ram[0x802d] = 0x00;
        ram[0x802e] = 0x3C;
        ram[0x802f] = 0x00;
        ram[0x8030] = 0xF0;
        ram[0x8031] = 0x00;
        ram[0x8032] = 0xF0;
        ram[0x8033] = 0x00;
        ram[0x8034] = 0xF0;
        ram[0x8035] = 0x00;
        ram[0x8036] = 0xF0;
        ram[0x8037] = 0x00;
        ram[0x8038] = 0x00;
        ram[0x8039] = 0x00;
        ram[0x803a] = 0x00;
        ram[0x803b] = 0x00;
        ram[0x803c] = 0xF3;
        ram[0x803d] = 0x00;
        ram[0x803e] = 0xF3;
        ram[0x803f] = 0x00;
        ram[0x8040] = 0x00;
        ram[0x8041] = 0x00;
        ram[0x8042] = 0x00;
        ram[0x8043] = 0x00;
        ram[0x8044] = 0x00;
        ram[0x8045] = 0x00;
        ram[0x8046] = 0x00;
        ram[0x8047] = 0x00;
        ram[0x8048] = 0x00;
        ram[0x8049] = 0x00;
        ram[0x804a] = 0x00;
        ram[0x804b] = 0x00;
        ram[0x804c] = 0xCF;
        ram[0x804d] = 0x00;
        ram[0x804e] = 0xCF;
        ram[0x804f] = 0x00;
        ram[0x8050] = 0x00;
        ram[0x8051] = 0x00;
        ram[0x8052] = 0x00;
        ram[0x8053] = 0x00;
        ram[0x8054] = 0x0F;
        ram[0x8055] = 0x00;
        ram[0x8056] = 0x0F;
        ram[0x8057] = 0x00;
        ram[0x8058] = 0x3F;
        ram[0x8059] = 0x00;
        ram[0x805a] = 0x3F;
        ram[0x805b] = 0x00;
        ram[0x805c] = 0x0F;
        ram[0x805d] = 0x00;
        ram[0x805e] = 0x0F;
        ram[0x805f] = 0x00;
        ram[0x8060] = 0x00;
        ram[0x8061] = 0x00;
        ram[0x8062] = 0x00;
        ram[0x8063] = 0x00;
        ram[0x8064] = 0x00;
        ram[0x8065] = 0x00;
        ram[0x8066] = 0x00;
        ram[0x8067] = 0x00;
        ram[0x8068] = 0xC0;
        ram[0x8069] = 0x00;
        ram[0x806a] = 0xC0;
        ram[0x806b] = 0x00;
        ram[0x806c] = 0x0F;
        ram[0x806d] = 0x00;
        ram[0x806e] = 0x0F;
        ram[0x806f] = 0x00;
        ram[0x8070] = 0x00;
        ram[0x8071] = 0x00;
        ram[0x8072] = 0x00;
        ram[0x8073] = 0x00;
        ram[0x8074] = 0x00;
        ram[0x8075] = 0x00;
        ram[0x8076] = 0x00;
        ram[0x8077] = 0x00;
        ram[0x8078] = 0x00;
        ram[0x8079] = 0x00;
        ram[0x807a] = 0x00;
        ram[0x807b] = 0x00;
        ram[0x807c] = 0xF0;
        ram[0x807d] = 0x00;
        ram[0x807e] = 0xF0;
        ram[0x807f] = 0x00;
        ram[0x8080] = 0x00;
        ram[0x8081] = 0x00;
        ram[0x8082] = 0x00;
        ram[0x8083] = 0x00;
        ram[0x8084] = 0x00;
        ram[0x8085] = 0x00;
        ram[0x8086] = 0x00;
        ram[0x8087] = 0x00;
        ram[0x8088] = 0x00;
        ram[0x8089] = 0x00;
        ram[0x808a] = 0x00;
        ram[0x808b] = 0x00;
        ram[0x808c] = 0xF3;
        ram[0x808d] = 0x00;
        ram[0x808e] = 0xF3;
        ram[0x808f] = 0x00;
        ram[0x8090] = 0x00;
        ram[0x8091] = 0x00;
        ram[0x8092] = 0x00;
        ram[0x8093] = 0x00;
        ram[0x8094] = 0x00;
        ram[0x8095] = 0x00;
        ram[0x8096] = 0x00;
        ram[0x8097] = 0x00;
        ram[0x8098] = 0x00;
        ram[0x8099] = 0x00;
        ram[0x809a] = 0x00;
        ram[0x809b] = 0x00;
        ram[0x809c] = 0xC0;
        ram[0x809d] = 0x00;
        ram[0x809e] = 0xC0;
        ram[0x809f] = 0x00;
        ram[0x80a0] = 0x03;
        ram[0x80a1] = 0x00;
        ram[0x80a2] = 0x03;
        ram[0x80a3] = 0x00;
        ram[0x80a4] = 0x03;
        ram[0x80a5] = 0x00;
        ram[0x80a6] = 0x03;
        ram[0x80a7] = 0x00;
        ram[0x80a8] = 0x03;
        ram[0x80a9] = 0x00;
        ram[0x80aa] = 0x03;
        ram[0x80ab] = 0x00;
        ram[0x80ac] = 0xFF;
        ram[0x80ad] = 0x00;
        ram[0x80ae] = 0xFF;
        ram[0x80af] = 0x00;
        ram[0x80b0] = 0xC0;
        ram[0x80b1] = 0x00;
        ram[0x80b2] = 0xC0;
        ram[0x80b3] = 0x00;
        ram[0x80b4] = 0xC0;
        ram[0x80b5] = 0x00;
        ram[0x80b6] = 0xC0;
        ram[0x80b7] = 0x00;
        ram[0x80b8] = 0xC0;
        ram[0x80b9] = 0x00;
        ram[0x80ba] = 0xC0;
        ram[0x80bb] = 0x00;
        ram[0x80bc] = 0xC3;
        ram[0x80bd] = 0x00;
        ram[0x80be] = 0xC3;
        ram[0x80bf] = 0x00;
        ram[0x80c0] = 0x00;
        ram[0x80c1] = 0x00;
        ram[0x80c2] = 0x00;
        ram[0x80c3] = 0x00;
        ram[0x80c4] = 0x00;
        ram[0x80c5] = 0x00;
        ram[0x80c6] = 0x00;
        ram[0x80c7] = 0x00;
        ram[0x80c8] = 0x00;
        ram[0x80c9] = 0x00;
        ram[0x80ca] = 0x00;
        ram[0x80cb] = 0x00;
        ram[0x80cc] = 0xFC;
        ram[0x80cd] = 0x00;
        ram[0x80ce] = 0xFC;
        ram[0x80cf] = 0x00;
        ram[0x80d0] = 0xF3;
        ram[0x80d1] = 0x00;
        ram[0x80d2] = 0xF3;
        ram[0x80d3] = 0x00;
        ram[0x80d4] = 0xF0;
        ram[0x80d5] = 0x00;
        ram[0x80d6] = 0xF0;
        ram[0x80d7] = 0x00;
        ram[0x80d8] = 0xF0;
        ram[0x80d9] = 0x00;
        ram[0x80da] = 0xF0;
        ram[0x80db] = 0x00;
        ram[0x80dc] = 0xF0;
        ram[0x80dd] = 0x00;
        ram[0x80de] = 0xF0;
        ram[0x80df] = 0x00;
        ram[0x80e0] = 0x3C;
        ram[0x80e1] = 0x00;
        ram[0x80e2] = 0x3C;
        ram[0x80e3] = 0x00;
        ram[0x80e4] = 0xFC;
        ram[0x80e5] = 0x00;
        ram[0x80e6] = 0xFC;
        ram[0x80e7] = 0x00;
        ram[0x80e8] = 0xFC;
        ram[0x80e9] = 0x00;
        ram[0x80ea] = 0xFC;
        ram[0x80eb] = 0x00;
        ram[0x80ec] = 0x3C;
        ram[0x80ed] = 0x00;
        ram[0x80ee] = 0x3C;
        ram[0x80ef] = 0x00;
        ram[0x80f0] = 0xF3;
        ram[0x80f1] = 0x00;
        ram[0x80f2] = 0xF3;
        ram[0x80f3] = 0x00;
        ram[0x80f4] = 0xF3;
        ram[0x80f5] = 0x00;
        ram[0x80f6] = 0xF3;
        ram[0x80f7] = 0x00;
        ram[0x80f8] = 0xF3;
        ram[0x80f9] = 0x00;
        ram[0x80fa] = 0xF3;
        ram[0x80fb] = 0x00;
        ram[0x80fc] = 0xF3;
        ram[0x80fd] = 0x00;
        ram[0x80fe] = 0xF3;
        ram[0x80ff] = 0x00;
        ram[0x8100] = 0xF3;
        ram[0x8101] = 0x00;
        ram[0x8102] = 0xF3;
        ram[0x8103] = 0x00;
        ram[0x8104] = 0xC3;
        ram[0x8105] = 0x00;
        ram[0x8106] = 0xC3;
        ram[0x8107] = 0x00;
        ram[0x8108] = 0xC3;
        ram[0x8109] = 0x00;
        ram[0x810a] = 0xC3;
        ram[0x810b] = 0x00;
        ram[0x810c] = 0xC3;
        ram[0x810d] = 0x00;
        ram[0x810e] = 0xC3;
        ram[0x810f] = 0x00;
        ram[0x8110] = 0xCF;
        ram[0x8111] = 0x00;
        ram[0x8112] = 0xCF;
        ram[0x8113] = 0x00;
        ram[0x8114] = 0xCF;
        ram[0x8115] = 0x00;
        ram[0x8116] = 0xCF;
        ram[0x8117] = 0x00;
        ram[0x8118] = 0xCF;
        ram[0x8119] = 0x00;
        ram[0x811a] = 0xCF;
        ram[0x811b] = 0x00;
        ram[0x811c] = 0xCF;
        ram[0x811d] = 0x00;
        ram[0x811e] = 0xCF;
        ram[0x811f] = 0x00;
        ram[0x8120] = 0x3C;
        ram[0x8121] = 0x00;
        ram[0x8122] = 0x3C;
        ram[0x8123] = 0x00;
        ram[0x8124] = 0x3F;
        ram[0x8125] = 0x00;
        ram[0x8126] = 0x3F;
        ram[0x8127] = 0x00;
        ram[0x8128] = 0x3C;
        ram[0x8129] = 0x00;
        ram[0x812a] = 0x3C;
        ram[0x812b] = 0x00;
        ram[0x812c] = 0x0F;
        ram[0x812d] = 0x00;
        ram[0x812e] = 0x0F;
        ram[0x812f] = 0x00;
        ram[0x8130] = 0x3C;
        ram[0x8131] = 0x00;
        ram[0x8132] = 0x3C;
        ram[0x8133] = 0x00;
        ram[0x8134] = 0xFC;
        ram[0x8135] = 0x00;
        ram[0x8136] = 0xFC;
        ram[0x8137] = 0x00;
        ram[0x8138] = 0x00;
        ram[0x8139] = 0x00;
        ram[0x813a] = 0x00;
        ram[0x813b] = 0x00;
        ram[0x813c] = 0xFC;
        ram[0x813d] = 0x00;
        ram[0x813e] = 0xFC;
        ram[0x813f] = 0x00;
        ram[0x8140] = 0xFC;
        ram[0x8141] = 0x00;
        ram[0x8142] = 0xFC;
        ram[0x8143] = 0x00;
        ram[0x8144] = 0xF0;
        ram[0x8145] = 0x00;
        ram[0x8146] = 0xF0;
        ram[0x8147] = 0x00;
        ram[0x8148] = 0xF0;
        ram[0x8149] = 0x00;
        ram[0x814a] = 0xF0;
        ram[0x814b] = 0x00;
        ram[0x814c] = 0xF0;
        ram[0x814d] = 0x00;
        ram[0x814e] = 0xF0;
        ram[0x814f] = 0x00;
        ram[0x8150] = 0xF3;
        ram[0x8151] = 0x00;
        ram[0x8152] = 0xF3;
        ram[0x8153] = 0x00;
        ram[0x8154] = 0xF3;
        ram[0x8155] = 0x00;
        ram[0x8156] = 0xF3;
        ram[0x8157] = 0x00;
        ram[0x8158] = 0xF3;
        ram[0x8159] = 0x00;
        ram[0x815a] = 0xF3;
        ram[0x815b] = 0x00;
        ram[0x815c] = 0xF0;
        ram[0x815d] = 0x00;
        ram[0x815e] = 0xF0;
        ram[0x815f] = 0x00;
        ram[0x8160] = 0xC3;
        ram[0x8161] = 0x00;
        ram[0x8162] = 0xC3;
        ram[0x8163] = 0x00;
        ram[0x8164] = 0xC3;
        ram[0x8165] = 0x00;
        ram[0x8166] = 0xC3;
        ram[0x8167] = 0x00;
        ram[0x8168] = 0xC3;
        ram[0x8169] = 0x00;
        ram[0x816a] = 0xC3;
        ram[0x816b] = 0x00;
        ram[0x816c] = 0xFF;
        ram[0x816d] = 0x00;
        ram[0x816e] = 0xFF;
        ram[0x816f] = 0x00;
        ram[0x8170] = 0xCF;
        ram[0x8171] = 0x00;
        ram[0x8172] = 0xCF;
        ram[0x8173] = 0x00;
        ram[0x8174] = 0xCF;
        ram[0x8175] = 0x00;
        ram[0x8176] = 0xCF;
        ram[0x8177] = 0x00;
        ram[0x8178] = 0xCF;
        ram[0x8179] = 0x00;
        ram[0x817a] = 0xCF;
        ram[0x817b] = 0x00;
        ram[0x817c] = 0xC3;
        ram[0x817d] = 0x00;
        ram[0x817e] = 0xC3;
        ram[0x817f] = 0x00;
        ram[0x8180] = 0x0F;
        ram[0x8181] = 0x00;
        ram[0x8182] = 0x0F;
        ram[0x8183] = 0x00;
        ram[0x8184] = 0x0F;
        ram[0x8185] = 0x00;
        ram[0x8186] = 0x0F;
        ram[0x8187] = 0x00;
        ram[0x8188] = 0x0F;
        ram[0x8189] = 0x00;
        ram[0x818a] = 0x0F;
        ram[0x818b] = 0x00;
        ram[0x818c] = 0xFC;
        ram[0x818d] = 0x00;
        ram[0x818e] = 0xFC;
        ram[0x818f] = 0x00;
        ram[0x8190] = 0x3C;
        ram[0x8191] = 0x00;
        ram[0x8192] = 0x42;
        ram[0x8193] = 0x00;
        ram[0x8194] = 0xB9;
        ram[0x8195] = 0x00;
        ram[0x8196] = 0xA5;
        ram[0x8197] = 0x00;
        ram[0x8198] = 0xB9;
        ram[0x8199] = 0x00;
        ram[0x819a] = 0xA5;
        ram[0x819b] = 0x00;
        ram[0x819c] = 0x42;
        ram[0x819d] = 0x00;
        ram[0x819e] = 0x3C;
        ram[0x819f] = 0x00;
    }
}


void Processor::load_boot_routine() {
    FILE* f;
    errno_t err = fopen_s(&f, "dmg_boot.gb", "rb");

    uint8_t boot_rom[256];

    size_t size_read = fread(boot_rom, 1, 256, f);
    if (size_read == 0) {
        cout << "error loading boot routine\n";
        exit(-1);
    }
    //cout << "Loaded boot rom of size: " << size_read << endl;

    //for (int i = 0; i < size_read; i++) {
    //    ram[i] = boot_rom[i];
    //}
    //current_bank = -1; //bootrom


    fclose(f);
}

void Processor::load_rom(const char* filename) {
    FILE* f;
    errno_t err = fopen_s(&f, filename, "rb");
    size_t size_read = fread(rom_memory, 1, ROM_MAX, f);
    if (size_read != 0) {
        cout << "Loaded ROM of size: " << size_read << endl;
    }

    //load first bank of the ROM into RAM
    for (int i = 0; i < 0x8000; i++) {
        if (i == size_read) break;
        ram[i] = rom_memory[i];
    }

    current_bank = 1;

    fclose(f);

}

void Processor::manage_banking() {
    uint8_t cartridge_type = rom_memory[0x148];

    if (current_bank == -1) { //switch from boot rom
        for (int i = 0; i < 256; i++) {
            ram[i] = rom_memory[i];
        }
        return;
    }

    if (cartridge_type == 0x00) {
        no_mbc = true;
    }
    else if (cartridge_type == 0x01) {
        mbc1 = true;
    }
    else if (cartridge_type == 0x02) {
        mbc2 = true;
    }
}

void Processor::launch_DMA(uint8_t data) {
    uint16_t address = data * 100;
    for (int i = 0; i < 0xA0; i++)
        write_mem(0xFE00 + i, ram[address + i]);
}

void Processor::timers() {

    DIV += op_cycles;
    if (div_counter >= 255) {
        div_counter = 0;
        DIV++;
    }

    if (get_bit(TAC, 2)) {

        timer_counter -= op_cycles;

        if (timer_counter <= 0) {

            uint8_t frequency = TAC & 3;
            if (frequency == 0)
                timer_counter = 1024;
            else if (frequency == 1)
                timer_counter = 16;
            else if (frequency == 2)
                timer_counter = 64;
            else if (frequency == 3)
                timer_counter = 256;

            if (TIMA == 255) {
                TIMA = TMA;
                set_interrupt(INT::TIMER);
            }
            else {
                TIMA++;
            }

        }
    }
}

void Processor::joypad() {

}

 void Processor::lookup()  {

    switch (opcode) {

    //8-bit Load instructions
    case 0x02: LD8(BC, '2', &AF, -1); break;
    case 0x12: LD8(DE, '2', &AF, -1); break;
    case 0x22: LD8(HL, '2', &AF, -1); HL++; break;
    case 0x32: LD8(HL, '2', &AF, -1); HL--; break;

    case 0x0A: LD8(AF, 'A', &BC, '-'); break;
    case 0x1A: LD8(AF, 'A', &DE, '-'); break;
    case 0x2A: LD8(AF, 'A', &HL, '-'); HL++; break;
    case 0x3A: LD8(AF, 'A', &HL, '-'); HL--; break;

    case 0x06: LD8(BC, 'h', nullptr, '6'); break;
    case 0x16: LD8(DE, 'h', nullptr, '6'); break;
    case 0x26: LD8(HL, 'h', nullptr, '6'); break;
    case 0x36: LD8(HL, '-', nullptr, '6'); break;

    case 0x0E: LD8(BC, 'l', nullptr, 'E'); break;
    case 0x1E: LD8(DE, 'l', nullptr, 'E'); break;
    case 0x2E: LD8(HL, 'l', nullptr, 'E'); break;
    case 0x3E: LD8(AF, 'h', nullptr, 'E'); break;

    case 0x40: LD8(BC, 'h', &BC, 'h'); break;
    case 0x41: LD8(BC, 'h', &BC, 'l'); break;
    case 0x42: LD8(BC, 'h', &DE, 'h'); break;
    case 0x43: LD8(BC, 'h', &DE, 'l'); break;
    case 0x44: LD8(BC, 'h', &HL, 'h'); break;
    case 0x45: LD8(BC, 'h', &HL, 'l'); break;
    case 0x46: LD8(BC, 'h', &HL, '-'); break;
    case 0x47: LD8(BC, 'h', &AF, 'h'); break;

    case 0x48: LD8(BC, 'l', &BC, 'h'); break;
    case 0x49: LD8(BC, 'l', &BC, 'l'); break;
    case 0x4A: LD8(BC, 'l', &DE, 'h'); break;
    case 0x4B: LD8(BC, 'l', &DE, 'l'); break;
    case 0x4C: LD8(BC, 'l', &HL, 'h'); break;
    case 0x4D: LD8(BC, 'l', &HL, 'l'); break;
    case 0x4E: LD8(BC, 'l', &HL, '-'); break;
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
    case 0x5A: LD8(DE, 'l', &DE, 'h'); break;
    case 0x5B: LD8(DE, 'l', &DE, 'l'); break;
    case 0x5C: LD8(DE, 'l', &HL, 'h'); break;
    case 0x5D: LD8(DE, 'l', &HL, 'l'); break;
    case 0x5E: LD8(DE, 'l', &HL, '-'); break;
    case 0x5F: LD8(DE, 'l', &AF, 'h'); break;

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
    case 0x6A: LD8(HL, 'l', &DE, 'h'); break;
    case 0x6B: LD8(HL, 'l', &DE, 'l'); break;
    case 0x6C: LD8(HL, 'l', &HL, 'h'); break;
    case 0x6D: LD8(HL, 'l', &HL, 'l'); break;
    case 0x6E: LD8(HL, 'l', &HL, '-'); break;
    case 0x6F: LD8(HL, 'l', &AF, 'h'); break;

    case 0x70: LD8(HL, '-', &BC, 'h'); break;
    case 0x71: LD8(HL, '-', &BC, 'l'); break;
    case 0x72: LD8(HL, '-', &DE, 'h'); break;
    case 0x73: LD8(HL, '-', &DE, 'l'); break;
    case 0x74: LD8(HL, '-', &HL, 'h'); break;
    case 0x75: LD8(HL, '-', &HL, 'l'); break;
    case 0x77: LD8(HL, '-', &AF, 'h'); break;

    case 0x78: LD8(AF, 'h', &BC, 'h'); break;
    case 0x79: LD8(AF, 'h', &BC, 'l'); break;
    case 0x7A: LD8(AF, 'h', &DE, 'h'); break;
    case 0x7B: LD8(AF, 'h', &DE, 'l'); break;
    case 0x7C: LD8(AF, 'h', &HL, 'h'); break;
    case 0x7D: LD8(AF, 'h', &HL, 'l'); break;
    case 0x7E: LD8(AF, 'h', &HL, '-'); break;
    case 0x7F: LD8(AF, 'h', &AF, 'h'); break;

    case 0xE0: LD8(AF, 'E', &AF, 'h'); break;
    case 0xF0: LD8(AF, 'F', &AF, 'h'); break;
    case 0xE2: LD8(AF, 0, nullptr, 0); break;
    case 0xF2: LD8(AF, 0, nullptr, 0); break;
    case 0xEA: LD8(AF, 0, &AF, 'E'); break;
    case 0xFA: LD8(AF, 0, &AF, 'F'); break;

    //16-bit Load instructions
    case 0x01: LD16(&BC, nullptr); break;
    case 0x11: LD16(&DE, nullptr); break;
    case 0x21: LD16(&HL, nullptr); break;
    case 0x31: LD16(&SP, nullptr); break;

    case 0x08: LD16(nullptr, &SP); break;
    case 0xF8: LD16(&HL, &SP);     break;
    case 0xF9: LD16(&SP, &HL);     break;


    //8-bit ADD instructions
    case 0x80: ADD8(&BC, 'h'); break;
    case 0x81: ADD8(&BC, 'l'); break;
    case 0x82: ADD8(&DE, 'h'); break;
    case 0x83: ADD8(&DE, 'l'); break;
    case 0x84: ADD8(&HL, 'h'); break;
    case 0x85: ADD8(&HL, 'l'); break;
    case 0x86: ADD8(&HL, '-'); break;
    case 0x87: ADD8(&AF, 'h'); break;
    case 0xC6: ADD8(nullptr, 0); break;

    //8-bit ADC instructions
    case 0x88: ADC8(&BC, 'h'); break;
    case 0x89: ADC8(&BC, 'l'); break;
    case 0x8A: ADC8(&DE, 'h'); break;
    case 0x8B: ADC8(&DE, 'l'); break;
    case 0x8C: ADC8(&HL, 'h'); break;
    case 0x8D: ADC8(&HL, 'l'); break;
    case 0x8E: ADC8(&HL, '-'); break;
    case 0x8F: ADC8(&AF, 'h'); break;
    case 0xCE: ADC8(nullptr, 0); break;

    //8-bit SUB instructions
    case 0x90: SUB8(&BC, 'h'); break;
    case 0x91: SUB8(&BC, 'l'); break;
    case 0x92: SUB8(&DE, 'h'); break;
    case 0x93: SUB8(&DE, 'l'); break;
    case 0x94: SUB8(&HL, 'h'); break;
    case 0x95: SUB8(&HL, 'l'); break;
    case 0x96: SUB8(&HL, '-'); break;
    case 0x97: SUB8(&AF, 'h'); break;
    case 0xD6: SUB8(nullptr, 0); break;

    //8-bit SBC instructions
    case 0x98: SBC8(&BC, 'h'); break;
    case 0x99: SBC8(&BC, 'l'); break;
    case 0x9A: SBC8(&DE, 'h'); break;
    case 0x9B: SBC8(&DE, 'l'); break;
    case 0x9C: SBC8(&HL, 'h'); break;
    case 0x9D: SBC8(&HL, 'l'); break;
    case 0x9E: SBC8(&HL, '-'); break;
    case 0x9F: SBC8(&AF, 'h'); break;
    case 0xDE: SBC8(nullptr, 0); break;


    //8-bit increment and decrement instructions

    case 0x04: INC8(BC, 'h'); break;
    case 0x14: INC8(DE, 'h'); break;
    case 0x24: INC8(HL, 'h'); break;
    case 0x34: INC8(HL, '-'); break;

    case 0x0C: INC8(BC, 'l'); break;
    case 0x1C: INC8(DE, 'l'); break;
    case 0x2C: INC8(HL, 'l'); break;
    case 0x3C: INC8(AF, 'h'); break;

    case 0x05: DEC8(BC, 'h'); break;
    case 0x15: DEC8(DE, 'h'); break;
    case 0x25: DEC8(HL, 'h'); break;
    case 0x35: DEC8(HL, '-'); break;

    case 0x0D: DEC8(BC, 'l'); break;
    case 0x1D: DEC8(DE, 'l'); break;
    case 0x2D: DEC8(HL, 'l'); break;
    case 0x3D: DEC8(AF, 'h'); break;

    //16-bt increment and decrement instructions

    case 0x03: INC16(BC); break;
    case 0x13: INC16(DE); break;
    case 0x23: INC16(HL); break;
    case 0x33: INC16(SP); break;

    case 0x0B: DEC16(BC); break;
    case 0x1B: DEC16(DE); break;
    case 0x2B: DEC16(HL); break;
    case 0x3B: DEC16(SP); break;


    //16-bit add instructions


    //bitwise operations

    case 0xA0: AND(&BC, 'h'); break;
    case 0xA1: AND(&BC, 'l'); break;
    case 0xA2: AND(&DE, 'h'); break;
    case 0xA3: AND(&DE, 'l'); break;
    case 0xA4: AND(&HL, 'h'); break;
    case 0xA5: AND(&HL, 'l'); break;
    case 0xA6: AND(&HL, '-'); break;
    case 0xA7: AND(&AF, 'h'); break;
    case 0xE6: AND(nullptr, 0); break;

    case 0xA8: XOR(&BC, 'h'); break;
    case 0xA9: XOR(&BC, 'l'); break;
    case 0xAA: XOR(&DE, 'h'); break;
    case 0xAB: XOR(&DE, 'l'); break;
    case 0xAC: XOR(&HL, 'h'); break;
    case 0xAD: XOR(&HL, 'l'); break;
    case 0xAE: XOR(&HL, '-'); break;
    case 0xAF: XOR(&AF, 'h'); break;
    case 0xEE: XOR(nullptr, 0); break;

    case 0xB0: OR(&BC, 'h'); break;
    case 0xB1: OR(&BC, 'l'); break;
    case 0xB2: OR(&DE, 'h'); break;
    case 0xB3: OR(&DE, 'l'); break;
    case 0xB4: OR(&HL, 'h'); break;
    case 0xB5: OR(&HL, 'l'); break;
    case 0xB6: OR(&HL, '-'); break;
    case 0xB7: OR(&AF, 'h'); break;
    case 0xF6: OR(nullptr, 0); break;

    case 0xB8: CP(&BC, 'h'); break;
    case 0xB9: CP(&BC, 'l'); break;
    case 0xBA: CP(&DE, 'h'); break;
    case 0xBB: CP(&DE, 'l'); break;
    case 0xBC: CP(&HL, 'h'); break;
    case 0xBD: CP(&HL, 'l'); break;
    case 0xBE: CP(&HL, '-'); break;
    case 0xBF: CP(&AF, 'h'); break;
    case 0xFE: CP(nullptr, 0); break;

    case 0x07: RLCA(); break;
    case 0x17: RLA();  break;
        
    case 0x0F: RRCA(); break;
    case 0x1F: RRA();  break;

    //calls, jumps and returns
    case 0x20: JR(NZ); break;
    case 0x30: JR(NC); break;
    case 0x28: JR(Z);  break;
    case 0x38: JR(C);  break;
    case 0x18: JR(NONE); break;

    case 0xC2: JP(NZ); break;
    case 0xD2: JP(NC); break;
    case 0xCA: JP(Z);  break;
    case 0xDA: JP(C);  break;
    case 0xC3: JP(NONE); break;

    case 0xC4: CALL(NZ); break;
    case 0xD4: CALL(NC); break;
    case 0xCC: CALL(Z);  break;
    case 0xDC: CALL(C);  break;
    case 0xCD: CALL(NONE); break;

    case 0xD9: RETI();  break;
    case 0xC0: RET(NZ); break;
    case 0xD0: RET(NC); break;
    case 0xC8: RET(Z);  break;
    case 0xD8: RET(C);  break;
    case 0xC9: RET(NONE); break;

    //push and pop
    case 0xC1: POP(BC); break;
    case 0xD1: POP(DE); break;
    case 0xE1: POP(HL); break;
    case 0xF1: POP(AF); break;

    case 0xC5: PUSH(BC); break;
    case 0xD5: PUSH(DE); break;
    case 0xE5: PUSH(HL); break;
    case 0xF5: PUSH(AF); break;

    //miscellaneous instructions
    case 0x00: NOP(); break;
    case 0x10: STOP(); break;
    case 0xF3: DI(); break;
    case 0xFB: EI(); break;
    case 0x37: SCF(); break;
    case 0x3F: CCF(); break;
    case 0x2F: CPL(); break;

    //extended instructions
    case 0xCB: {
        opcode = ram[pc + 1];

        switch (opcode) {

        case 0x00: RLC(BC, 'h'); break;
        case 0x01: RLC(BC, 'l'); break;
        case 0x02: RLC(DE, 'h'); break;
        case 0x03: RLC(DE, 'l'); break;
        case 0x04: RLC(HL, 'h'); break;
        case 0x05: RLC(HL, 'l'); break;
        case 0x06: RLC(HL, '-'); break;
        case 0x07: RLC(AF, 'h'); break;

        case 0x08: RRC(BC, 'h'); break;
        case 0x09: RRC(BC, 'l'); break;
        case 0x0A: RRC(DE, 'h'); break;
        case 0x0B: RRC(DE, 'l'); break;
        case 0x0C: RRC(HL, 'h'); break;
        case 0x0D: RRC(HL, 'l'); break;
        case 0x0E: RRC(HL, '-'); break;
        case 0x0F: RRC(AF, 'h'); break;

        case 0x10: RL(BC, 'h'); break;
        case 0x11: RL(BC, 'l'); break;
        case 0x12: RL(DE, 'h'); break;
        case 0x13: RL(DE, 'l'); break;
        case 0x14: RL(HL, 'h'); break;
        case 0x15: RL(HL, 'l'); break;
        case 0x16: RL(HL, '-'); break;
        case 0x17: RL(AF, 'h'); break;

        case 0x18: RR(BC, 'h'); break;
        case 0x19: RR(BC, 'l'); break;
        case 0x1A: RR(DE, 'h'); break;
        case 0x1B: RR(DE, 'l'); break;
        case 0x1C: RR(HL, 'h'); break;
        case 0x1D: RR(HL, 'l'); break;
        case 0x1E: RR(HL, '-'); break;
        case 0x1F: RR(AF, 'h'); break;

        case 0x20: SLA(BC, 'h'); break;
        case 0x21: SLA(BC, 'l'); break;
        case 0x22: SLA(DE, 'h'); break;
        case 0x23: SLA(DE, 'l'); break;
        case 0x24: SLA(HL, 'h'); break;
        case 0x25: SLA(HL, 'l'); break;
        case 0x26: SLA(HL, '-'); break;
        case 0x27: SLA(AF, 'h'); break;

        case 0x28: SRA(BC, 'h'); break;
        case 0x29: SRA(BC, 'l'); break;
        case 0x2A: SRA(DE, 'h'); break;
        case 0x2B: SRA(DE, 'l'); break;
        case 0x2C: SRA(HL, 'h'); break;
        case 0x2D: SRA(HL, 'l'); break;
        case 0x2E: SRA(HL, '-'); break;
        case 0x2F: SRA(AF, 'h'); break;

        case 0x38: SRL(BC, 'h'); break;
        case 0x39: SRL(BC, 'l'); break;
        case 0x3A: SRL(DE, 'h'); break;
        case 0x3B: SRL(DE, 'l'); break;
        case 0x3C: SRL(HL, 'h'); break;
        case 0x3D: SRL(HL, 'l'); break;
        case 0x3E: SRL(HL, '-'); break;
        case 0x3F: SRL(AF, 'h'); break;

        case 0x30: SWAP(&BC, 'h'); break;
        case 0x31: SWAP(&BC, 'l'); break;
        case 0x32: SWAP(&DE, 'h'); break;
        case 0x33: SWAP(&DE, 'l'); break;
        case 0x34: SWAP(&HL, 'h'); break;
        case 0x35: SWAP(&HL, 'l'); break;
        case 0x36: SWAP(&HL, '-'); break;
        case 0x37: SWAP(&AF, 'h'); break;

        case 0x40: BIT(&BC, 'h', 0); break;
        case 0x41: BIT(&BC, 'l', 0); break;
        case 0x42: BIT(&DE, 'h', 0); break;
        case 0x43: BIT(&DE, 'l', 0); break;
        case 0x44: BIT(&HL, 'h', 0); break;
        case 0x45: BIT(&HL, 'l', 0); break;
        case 0x46: BIT(&HL, '-', 0); break;
        case 0x47: BIT(&AF, 'h', 0); break;

        case 0x48: BIT(&BC, 'h', 1); break;
        case 0x49: BIT(&BC, 'l', 1); break;
        case 0x4A: BIT(&DE, 'h', 1); break;
        case 0x4B: BIT(&DE, 'l', 1); break;
        case 0x4C: BIT(&HL, 'h', 1); break;
        case 0x4D: BIT(&HL, 'l', 1); break;
        case 0x4E: BIT(&HL, '-', 1); break;
        case 0x4F: BIT(&AF, 'h', 1); break;

        case 0x50: BIT(&BC, 'h', 2); break;
        case 0x51: BIT(&BC, 'l', 2); break;
        case 0x52: BIT(&DE, 'h', 2); break;
        case 0x53: BIT(&DE, 'l', 2); break;
        case 0x54: BIT(&HL, 'h', 2); break;
        case 0x55: BIT(&HL, 'l', 2); break;
        case 0x56: BIT(&HL, '-', 2); break;
        case 0x57: BIT(&AF, 'h', 2); break;

        case 0x58: BIT(&BC, 'h', 3); break;
        case 0x59: BIT(&BC, 'l', 3); break;
        case 0x5A: BIT(&DE, 'h', 3); break;
        case 0x5B: BIT(&DE, 'l', 3); break;
        case 0x5C: BIT(&HL, 'h', 3); break;
        case 0x5D: BIT(&HL, 'l', 3); break;
        case 0x5E: BIT(&HL, '-', 3); break;
        case 0x5F: BIT(&AF, 'h', 3); break;

        case 0x60: BIT(&BC, 'h', 4); break;
        case 0x61: BIT(&BC, 'l', 4); break;
        case 0x62: BIT(&DE, 'h', 4); break;
        case 0x63: BIT(&DE, 'l', 4); break;
        case 0x64: BIT(&HL, 'h', 4); break;
        case 0x65: BIT(&HL, 'l', 4); break;
        case 0x66: BIT(&HL, '-', 4); break;
        case 0x67: BIT(&AF, 'h', 4); break;

        case 0x68: BIT(&BC, 'h', 5); break;
        case 0x69: BIT(&BC, 'l', 5); break;
        case 0x6A: BIT(&DE, 'h', 5); break;
        case 0x6B: BIT(&DE, 'l', 5); break;
        case 0x6C: BIT(&HL, 'h', 5); break;
        case 0x6D: BIT(&HL, 'l', 5); break;
        case 0x6E: BIT(&HL, '-', 5); break;
        case 0x6F: BIT(&AF, 'h', 5); break;

        case 0x70: BIT(&BC, 'h', 6); break;
        case 0x71: BIT(&BC, 'l', 6); break;
        case 0x72: BIT(&DE, 'h', 6); break;
        case 0x73: BIT(&DE, 'l', 6); break;
        case 0x74: BIT(&HL, 'h', 6); break;
        case 0x75: BIT(&HL, 'l', 6); break;
        case 0x76: BIT(&HL, '-', 6); break;
        case 0x77: BIT(&AF, 'h', 6); break;

        case 0x78: BIT(&BC, 'h', 7); break;
        case 0x79: BIT(&BC, 'l', 7); break;
        case 0x7A: BIT(&DE, 'h', 7); break;
        case 0x7B: BIT(&DE, 'l', 7); break;
        case 0x7C: BIT(&HL, 'h', 7); break;
        case 0x7D: BIT(&HL, 'l', 7); break;
        case 0x7E: BIT(&HL, '-', 7); break;
        case 0x7F: BIT(&AF, 'h', 7); break;

        ///////////////////////////////////

        case 0x80: RES(&BC, 'h', 0); break;
        case 0x81: RES(&BC, 'l', 0); break;
        case 0x82: RES(&DE, 'h', 0); break;
        case 0x83: RES(&DE, 'l', 0); break;
        case 0x84: RES(&HL, 'h', 0); break;
        case 0x85: RES(&HL, 'l', 0); break;
        case 0x86: RES(&HL, '-', 0); break;
        case 0x87: RES(&AF, 'h', 0); break;

        case 0x88: RES(&BC, 'h', 1); break;
        case 0x89: RES(&BC, 'l', 1); break;
        case 0x8A: RES(&DE, 'h', 1); break;
        case 0x8B: RES(&DE, 'l', 1); break;
        case 0x8C: RES(&HL, 'h', 1); break;
        case 0x8D: RES(&HL, 'l', 1); break;
        case 0x8E: RES(&HL, '-', 1); break;
        case 0x8F: RES(&AF, 'h', 1); break;

        case 0x90: RES(&BC, 'h', 2); break;
        case 0x91: RES(&BC, 'l', 2); break;
        case 0x92: RES(&DE, 'h', 2); break;
        case 0x93: RES(&DE, 'l', 2); break;
        case 0x94: RES(&HL, 'h', 2); break;
        case 0x95: RES(&HL, 'l', 2); break;
        case 0x96: RES(&HL, '-', 2); break;
        case 0x97: RES(&AF, 'h', 2); break;

        case 0x98: RES(&BC, 'h', 3); break;
        case 0x99: RES(&BC, 'l', 3); break;
        case 0x9A: RES(&DE, 'h', 3); break;
        case 0x9B: RES(&DE, 'l', 3); break;
        case 0x9C: RES(&HL, 'h', 3); break;
        case 0x9D: RES(&HL, 'l', 3); break;
        case 0x9E: RES(&HL, '-', 3); break;
        case 0x9F: RES(&AF, 'h', 3); break;

        case 0xA0: RES(&BC, 'h', 4); break;
        case 0xA1: RES(&BC, 'l', 4); break;
        case 0xA2: RES(&DE, 'h', 4); break;
        case 0xA3: RES(&DE, 'l', 4); break;
        case 0xA4: RES(&HL, 'h', 4); break;
        case 0xA5: RES(&HL, 'l', 4); break;
        case 0xA6: RES(&HL, '-', 4); break;
        case 0xA7: RES(&AF, 'h', 4); break;

        case 0xA8: RES(&BC, 'h', 5); break;
        case 0xA9: RES(&BC, 'l', 5); break;
        case 0xAA: RES(&DE, 'h', 5); break;
        case 0xAB: RES(&DE, 'l', 5); break;
        case 0xAC: RES(&HL, 'h', 5); break;
        case 0xAD: RES(&HL, 'l', 5); break;
        case 0xAE: RES(&HL, '-', 5); break;
        case 0xAF: RES(&AF, 'h', 5); break;

        case 0xB0: RES(&BC, 'h', 6); break;
        case 0xB1: RES(&BC, 'l', 6); break;
        case 0xB2: RES(&DE, 'h', 6); break;
        case 0xB3: RES(&DE, 'l', 6); break;
        case 0xB4: RES(&HL, 'h', 6); break;
        case 0xB5: RES(&HL, 'l', 6); break;
        case 0xB6: RES(&HL, '-', 6); break;
        case 0xB7: RES(&AF, 'h', 6); break;

        case 0xB8: RES(&BC, 'h', 7); break;
        case 0xB9: RES(&BC, 'l', 7); break;
        case 0xBA: RES(&DE, 'h', 7); break;
        case 0xBB: RES(&DE, 'l', 7); break;
        case 0xBC: RES(&HL, 'h', 7); break;
        case 0xBD: RES(&HL, 'l', 7); break;
        case 0xBE: RES(&HL, '-', 7); break;
        case 0xBF: RES(&AF, 'h', 7); break;

        case 0xC0: SET(&BC, 'h', 0); break;
        case 0xC1: SET(&BC, 'l', 0); break;
        case 0xC2: SET(&DE, 'h', 0); break;
        case 0xC3: SET(&DE, 'l', 0); break;
        case 0xC4: SET(&HL, 'h', 0); break;
        case 0xC5: SET(&HL, 'l', 0); break;
        case 0xC6: SET(&HL, '-', 0); break;
        case 0xC7: SET(&AF, 'h', 0); break;

        case 0xC8: SET(&BC, 'h', 1); break;
        case 0xC9: SET(&BC, 'l', 1); break;
        case 0xCA: SET(&DE, 'h', 1); break;
        case 0xCB: SET(&DE, 'l', 1); break;
        case 0xCC: SET(&HL, 'h', 1); break;
        case 0xCD: SET(&HL, 'l', 1); break;
        case 0xCE: SET(&HL, '-', 1); break;
        case 0xCF: SET(&AF, 'h', 1); break;

        case 0xD0: SET(&BC, 'h', 2); break;
        case 0xD1: SET(&BC, 'l', 2); break;
        case 0xD2: SET(&DE, 'h', 2); break;
        case 0xD3: SET(&DE, 'l', 2); break;
        case 0xD4: SET(&HL, 'h', 2); break;
        case 0xD5: SET(&HL, 'l', 2); break;
        case 0xD6: SET(&HL, '-', 2); break;
        case 0xD7: SET(&AF, 'h', 2); break;

        case 0xD8: SET(&BC, 'h', 3); break;
        case 0xD9: SET(&BC, 'l', 3); break;
        case 0xDA: SET(&DE, 'h', 3); break;
        case 0xDB: SET(&DE, 'l', 3); break;
        case 0xDC: SET(&HL, 'h', 3); break;
        case 0xDD: SET(&HL, 'l', 3); break;
        case 0xDE: SET(&HL, '-', 3); break;
        case 0xDF: SET(&AF, 'h', 3); break;

        case 0xE0: SET(&BC, 'h', 4); break;
        case 0xE1: SET(&BC, 'l', 4); break;
        case 0xE2: SET(&DE, 'h', 4); break;
        case 0xE3: SET(&DE, 'l', 4); break;
        case 0xE4: SET(&HL, 'h', 4); break;
        case 0xE5: SET(&HL, 'l', 4); break;
        case 0xE6: SET(&HL, '-', 4); break;
        case 0xE7: SET(&AF, 'h', 4); break;

        case 0xE8: SET(&BC, 'h', 5); break;
        case 0xE9: SET(&BC, 'l', 5); break;
        case 0xEA: SET(&DE, 'h', 5); break;
        case 0xEB: SET(&DE, 'l', 5); break;
        case 0xEC: SET(&HL, 'h', 5); break;
        case 0xED: SET(&HL, 'l', 5); break;
        case 0xEE: SET(&HL, '-', 5); break;
        case 0xEF: SET(&AF, 'h', 5); break;

        case 0xF0: SET(&BC, 'h', 6); break;
        case 0xF1: SET(&BC, 'l', 6); break;
        case 0xF2: SET(&DE, 'h', 6); break;
        case 0xF3: SET(&DE, 'l', 6); break;
        case 0xF4: SET(&HL, 'h', 6); break;
        case 0xF5: SET(&HL, 'l', 6); break;
        case 0xF6: SET(&HL, '-', 6); break;
        case 0xF7: SET(&AF, 'h', 6); break;

        case 0xF8: RES(&BC, 'h', 7); break;
        case 0xF9: RES(&BC, 'l', 7); break;
        case 0xFA: RES(&DE, 'h', 7); break;
        case 0xFB: RES(&DE, 'l', 7); break;
        case 0xFC: RES(&HL, 'h', 7); break;
        case 0xFD: RES(&HL, 'l', 7); break;
        case 0xFE: RES(&HL, '-', 7); break;
        case 0xFF: RES(&AF, 'h', 7); break;

        }
    }
    }
}

void Processor::cycle() {

    while (scanline_cycles < FRAME_CYCLES) {
        opcode = ram[pc];
        lookup();
        scanline_cycles += op_cycles;
        passed_cycles += op_cycles;
        graphics();
        interrupts();
        timers();
    }

    scanline_cycles = 0;
    render_scanline();
}

void Processor::set_interrupt(int n) {
    set_bit(IF, n);
}

void Processor::interrupts() {

    auto push_pc = [&]() {
        write_mem(SP, pc >> 8);
        SP++;
        write_mem(SP, (pc & 0x00FF));
        SP++;
    };


    if (IME) {

        if (IF) {

            //v-blank interrupt
            if (get_bit(IF, 0) && get_bit(IE, 0)) {
                IME = false;
                set_bit(IF, 0, 0);
                push_pc();
                pc = 0x40;
            }

            //LCD interrupt
            else if (get_bit(IF, 1) && get_bit(IE, 1)) {
                IME = false;
                set_bit(IF, 1, 0);
                push_pc();
                pc = 0x48;
            }

            //Timer interrupt
            else if (get_bit(IF, 2) && get_bit(IE, 2)) {
                IME = false;
                set_bit(IF, 2, 0);
                push_pc();
                pc = 0x50;
            }

            //Joypad interrupt
            else if (get_bit(IF, 4) && get_bit(IE, 4)) {
                IME = false;
                set_bit(IF, 4, 0);
                push_pc();
                pc = 0x60;
            }

            //serial interrupt is missing, but it's probably optional

        }
    }
}

void Processor::render_scanline() {

    if (get_bit(LCDC, 0))
        render_tiles();

    if (get_bit(LCDC, 1))
        render_sprites();
}

void Processor::render_tiles() {

    bool unsigned_addressing = true;

    uint8_t SCX = ram[0xFF42];
    uint8_t SCY = ram[0xFF43];
    uint8_t WX = ram[0xFF4A];
    uint8_t WY = ram[0xFF4B] - 7;

    bool window_on = false;

    //window enabled?
    if (get_bit(LCDC, 5)) {

        if (WY <= ram[0xFF44]) { //if LY is within boundries of our window we have to render it 
            window_on = true;
        }
    }

    uint16_t tile_region;

    //tile region
    if (get_bit(LCDC, 4)) { //tile region = 0x8000, unsigned addressing
        tile_region = 0x8000;
    }
    else {
        tile_region = 0x8800;
        unsigned_addressing = false;
    }

    uint16_t background_region;

    //background region
    if (window_on) {

        if (get_bit(LCDC, 6))
            background_region = 0x9C00;
        else
            background_region = 0x9800;
    }
    else {

        if (get_bit(LCDC, 3))
            background_region = 0x9C00;
        else
            background_region = 0x9800;
    }

    uint8_t y_pos;

    if (window_on)
        y_pos = ram[0xFF44] - WY;
    else
        y_pos = SCY + ram[0xFF44];

    uint16_t tile_row = (((uint8_t)(y_pos / 8)) * 32);

    for (int pixel = 0; pixel < 160; pixel++) {
        uint8_t x_pos = pixel + SCX;

        if (window_on == false) {
            if (pixel >= WX) {
                x_pos = pixel - WX;
            }
        }

        uint16_t tile_column = x_pos / 8;

        int16_t tile_num;

        uint16_t tile_address = background_region + tile_row + tile_column;

        if (unsigned_addressing)
            tile_num = (uint8_t)ram[tile_address];
        else
            tile_num = (int8_t)ram[tile_address];

        uint16_t tile_location = tile_region;

        if (unsigned_addressing)
            tile_location += tile_num * 16;
        else
            tile_location += ((tile_num + 128) * 16);

        uint8_t line = y_pos % 8;
        line *= 2;
        uint8_t data1 = ram[tile_location + line];
        uint8_t data2 = ram[tile_location + line + 1];

        int color_bit = x_pos % 8;
        color_bit -= 7;
        color_bit *= -1;

        int color = get_bit(data2, color_bit);
        color <<= 1;
        color |= get_bit(data1, color_bit);

        int ly = ram[0xFF44];

        if (ly < 0 || ly > 143 || pixel < 0 || pixel > 159)
            continue;


        int colornum = color;
        if (colornum == 10) {
            display[ly][pixel].r = 00;
            display[ly][pixel].g = 00;
            display[ly][pixel].b = 00;
        }
        else if (colornum == 11) {
            display[ly][pixel].r = 224;
            display[ly][pixel].g = 248;
            display[ly][pixel].b = 208;
        }
        else if (colornum == 01) {
            display[ly][pixel].r = 52;
            display[ly][pixel].g = 104;
            display[ly][pixel].b = 86;
        }
        else if (colornum == 00) {
            display[ly][pixel].r = 136;
            display[ly][pixel].g = 192;
            display[ly][pixel].b = 112;
        }
    }

}

void Processor::render_sprites() {

    bool double_sprite = get_bit(LCDC, 2);

    for (int sprite = 0; sprite < 40; sprite++) {

        uint8_t index = sprite * 4;
        uint8_t sprite_x = ram[0xFE00 + index] - 16;
        uint8_t sprite_y = ram[0xFE00 + index + 1] - 8;
        uint8_t tile_index = ram[0xFE00 + index + 2];
        uint8_t attribs = ram[0xFE00 + index + 3];

        bool flipped_x = get_bit(attribs, 5);
        bool flipped_y = get_bit(attribs, 6);

        int ly = ram[0xFF44];

        int height = double_sprite ? 16 : 8;

        if ((ly >= sprite_y) && (ly < (sprite_y + height))) {
            int line = ly - sprite_y;

            if (flipped_y) {
                line -= height;
                line *= -1;
            }

            line *= 2;

            uint16_t tile_address = (0x8000 + (tile_index * 16)) + line;
            uint8_t data1 = ram[tile_address];
            uint8_t data2 = ram[tile_address + 1];

            for (int pixel = 7; pixel >= 0; pixel--) {

                int colorbit = pixel;

                if (flipped_x) {
                    colorbit -= 7;
                    colorbit *= -1;
                }

                int colornum = get_bit(data2, colorbit);
                colornum <<= 1;
                colornum |= get_bit(data1, colorbit);

                int xPix = 0 - pixel;
                xPix += 7;
                int pixel_x = sprite_x + xPix;

                if (colornum == 10) {
                    display[ly][pixel_x].r = 136;
                    display[ly][pixel_x].g = 192;
                    display[ly][pixel_x].b = 112;
                }
                else if (colornum == 11) {
                    display[ly][pixel_x].r = 224;
                    display[ly][pixel_x].g = 248;
                    display[ly][pixel_x].b = 208;
                }
                else if (colornum == 01) {
                    display[ly][pixel_x].r = 52;
                    display[ly][pixel_x].g = 104;
                    display[ly][pixel_x].b = 86;
                }
                else if (colornum == 00) {
                    display[ly][pixel_x].r = 00;
                    display[ly][pixel_x].g = 00;
                    display[ly][pixel_x].b = 00;
                }

                
            }
        }
    }
}

void Processor::graphics() {

    LCD();

    if (get_bit(LCDC, 7))
        scanline -= op_cycles;
    else
        return;

    if (scanline <= 0) {
        ram[0xFF44]++;
        uint8_t ly = ram[0xFF44];

        scanline = 456;

        if (ly == 144)
            set_interrupt(INT::VBLANK);
        else if (ly > 153)
            ram[0xFF44] = 0;
        else if (ly < 144) {
            //DRawscanline
        }
    }
}

void Processor::LCD() {

    uint8_t stat = STAT;

    if (get_bit(LCDC, 7) == 0) { //lcd disabled
        scanline = 456;
        ram[0xFF44] = 0;
        stat &= 252;
        set_bit(stat, 0);
        STAT = stat;
        return;
    }

    uint8_t current_ly = ram[0xFF44];
    uint8_t current_mode = (stat & 3);

    uint8_t mode = 0;
    bool request_int = false;

    if (current_ly >= 144) { //v-blank
        mode = 1;
        set_bit(stat, 0);
        set_bit(stat, 1, 0);
        request_int = get_bit(stat, 4);
    }
    else {

        int mode2 = 456 - 80;
        int mode3 = mode2 - 172;

        if (scanline >= mode2) {
            mode = 2;
            set_bit(stat, 1);
            set_bit(stat, 0, 0);
            request_int = get_bit(stat, 5);
        }
        else if (scanline >= mode3) {
            mode = 3;
            set_bit(stat, 1);
            set_bit(stat, 0);
        }
        else { //mode 0
            mode = 0;
            set_bit(stat, 1, 0);
            set_bit(stat, 0, 0);
            request_int = get_bit(stat, 3);
        }
    }

    if (request_int && (mode != current_mode)) {
        set_interrupt(INT::LCDSTAT);
    }


    if (ram[0xFF44] == ram[0xFF45]) {
        set_bit(stat, 2);
        if (get_bit(stat, 6))
            set_interrupt(INT::LCDSTAT);
    }
    else {
        set_bit(stat, 2, 0);
    }
    STAT = stat;
}

void Processor::write_mem(uint16_t address, uint8_t value) {
    if (address < 0x8000) {
        //restricted
    }
    else if ((address >= 0xE000) && (address < 0xFE00)) {
        rom_memory[address] = value;
        write_mem(address - 0x2000, value);
    }
    else if (address >= 0xFEA0 && address < 0xFEFF) {
        //restricted
    }
    else if (address == 0xFF46) {
        launch_DMA(value);
    }
    else if (address == 0xFF04) {
        ram[0xFF04] = 0; //writing to DIV always sets it to 0
    }
    else if (address == 0xFF44) {
        ram[address] = 0; //writing to LY always sets it to 0
    }
    else if (address == 0xFF50) { //turn off the boot rom and swap for the actual game rom
        manage_banking();
    }
    else {
        ram[address] = value;
    }
}

uint8_t Processor::read_mem(uint16_t address) {

    if (address < 0x8000) { //read from ROM bank
        return rom_memory[address];
    }
    else {  //read from ram
        return ram[address];
    }
}

void Processor::set_reg(uint16_t& reg, char hilo, uint8_t value) {

    if (hilo == 'l') {
        reg &= 0xFF00;
        reg |= value;
    }
    else if (hilo == 'h') {
        reg &= 0x00FF;
        reg |= (uint16_t)(value << 8);
    }
}

int Processor::get_flag(FLAG f) {

    //Handling negated flags
    if (f == NZ || f == NC) 
        return ((AF >> f+4) & 1) ? 0 : 1;

    return ((AF >> (f)) & 1);
}

void Processor::set_flag(FLAG f, int value) {
    uint8_t n = (1 << f);
    uint8_t F = (AF & 0x00FF);

    if (value == 0) {
        n = ~n;
        F &= n;
    }
    else
        F |= n;

    set_reg(AF, 'l', F);
}

int Processor::get_bit(uint8_t obj, int nbit) {
    return ((obj >> nbit) & 1);
}

int Processor::get_bit(uint16_t obj, int nbit) {
    return ((obj >> nbit) & 1);
}

void Processor::set_bit(uint8_t& obj, int nbit, int val) {
    if (val == 1)
        obj |= 1ul << nbit;
    else
        obj &= ~(1ul << nbit);
}

int8_t Processor::unsigned_to_signed(uint8_t u) {
    if (u <= INT8_MAX)
        return static_cast<int8_t>(u);
    else if (u >= INT8_MIN)
        return static_cast<int8_t> (u - INT8_MIN) + INT8_MIN;
    throw u;
}

std::string Processor::get_hex(int n) {
    std::string result = "";
    const char* digits = "0123456789ABCDEF";
    while (n > 0) {
        result = digits[n % 16] + result;
        n /= 16;
    }
    result = "0x" + result;
    return result;
}


//miscellaneous instructions

void Processor::NOP() {
    pc += 1;
    op_cycles = 4;
}

void Processor::STOP() {
    pc += 2;
    op_cycles = 4;
}


//this instruction sets IME flag to true, enabling all interrupts
void Processor::EI() {
    IME = true;
    pc++;
    op_cycles = 4;
}

//this instruction sets IME flag to false, disabling all interrupts
void Processor::DI() {
    IME = false;
    pc++;
    op_cycles = 4;
}

//this instruction flips all bits of the accumulator
void Processor::CPL() {

    uint8_t A = (AF >> 8);
    A = ~A;
    set_reg(AF, 'h', A);

    set_flag(H);
    set_flag(N);

    pc++;
    op_cycles = 4;
}

//this instruction sets the carry flag
void Processor::SCF() {

    set_flag(C);
    set_flag(H, 0);
    set_flag(N, 0);

    pc++;
    op_cycles = 4;
}

//this instruction flips the carry flag
void Processor::CCF() {

    bool cy = get_flag(C);

    set_flag(C, !cy);
    set_flag(H, 0);
    set_flag(N, 0);

    pc++;
    op_cycles = 4;
}


// LD implementations


//this instruction loads 8-bit data into half of 16-bit register pair or into ram
//this instruction is written out of convetion kept in this project because writing it following convetion is annoying beyond my patience
/*
void Processor::LD8(uint16_t& dst, char hilo, uint16_t* src, char srchilo) {
    


    
    if (opcode == 0xE2) { //0xE2
        uint8_t C = (BC >> 8);
        uint16_t address = 0xFF00 | C;
        uint8_t A = (AF >> 8);
        write_mem(address, A);
        pc++;
        op_cycles = 8;
    }
    else if (opcode == 0xF2) { //0xF2
        uint8_t C = (BC >> 8);
        uint16_t address = 0xFF00 | C;
        set_reg(AF, 'h', ram[C]);
        pc++;
        op_cycles = 8;
    }
    else if (hilo == srchilo && &dst == &AF) { //case 0xXA

        if(src != nullptr)
        set_reg(AF, 'h', ram[*src]);
        pc += 1;
        op_cycles = 8;
        return;
    }
    else if (hilo == 'E') { //0xE0
        uint8_t a8 = ram[pc + 1];
        uint16_t address = 0xFF00;
        address |= a8;
        uint8_t A = (AF >> 8);
        write_mem(address, A);

        pc += 2;
        op_cycles = 12;
    }
    else if (hilo == 'F') { //0xF0
        uint8_t a8 = ram[pc + 1];
        uint16_t address = 0xFF00;
        address |= a8;
        set_reg(AF, 'h', ram[address]);
        pc += 2;
        op_cycles = 12;
    }
    else if (srchilo == 'E') { //0xEA
        uint16_t a16 = 0x0000;
        a16 = ram[pc + 2] << 8;
        a16 |= (ram[pc + 1]);

        cout << "a16: " << get_hex(a16) << endl;

        uint8_t A = (AF >> 8);
        write_mem(a16, A);
        pc += 3;
        op_cycles = 16;
    }
    else if (srchilo == 'F') { //0xFA
        uint16_t a16 = 0x0000;
        a16 = ram[pc + 2] << 8;
        a16 |= ram[pc + 1];
        set_reg(AF, 'h', ram[a16]);
        pc += 3;
        op_cycles = 16;
    }
    else if (srchilo == -1) { //case 0xX2

        uint8_t A = (AF >> 8);
        write_mem(dst, A);
        pc += 1;
        op_cycles = 8;
        return;
    }
    else if (src == nullptr) { //0xX6 and 0xXE
        
        if (hilo == '-') {
            write_mem(HL, ram[pc + 1]);
            pc += 2;
            op_cycles = 12;
            return;
        }
        set_reg(dst, hilo, ram[pc + 1]);
        pc += 2;
        op_cycles = 8;
    }
    else { //default cases
        if (src == &HL && srchilo == '-') {
            set_reg(dst, hilo, ram[HL]);
            pc += 2;
            op_cycles = 8;
            return;
        }
        else if (dst == HL && hilo == '-') {
            uint8_t R = (srchilo == 'h') ? ((*src) >> 8) : ((*src) & 0x00FF);
            write_mem(HL, R);
            pc += 1;
            op_cycles = 8;
            return;
        }
      
        uint8_t R = (srchilo == 'h') ? ((*src) >> 8) : ((*src) & 0x00FF);
        set_reg(dst, hilo, R);
        pc += 1;
        op_cycles = 4;
    }
}
*/


void Processor::LD8(uint16_t &dst, char hilo, uint16_t* src, char srchilo) {

    //
    if (opcode == 0xE0) {
        uint8_t a8 = ram[pc + 1];
        uint16_t address = 0xFF00 | a8;

        write_mem(address, (AF >> 8));

        pc += 2;
        op_cycles = 12;
    }
    else if (opcode == 0xF0) {
        uint8_t a8 = ram[pc + 1];
        uint16_t address = 0xFF00 | a8;

        set_reg(AF, 'h', ram[address]);

        pc += 2;
        op_cycles = 12;
    }
    else if (opcode == 0xE2) {
        uint8_t C = (BC >> 8);
        uint16_t address = 0xFF00 | C;

        write_mem(address, (AF >> 8));
        
        pc += 1;
        op_cycles = 8;
    }
    else if (opcode == 0xF2) {
        uint8_t C = (BC >> 8);
        uint16_t address = 0xFF00 | C;

        set_reg(AF, 'h', ram[address]);

        pc += 1;
        op_cycles = 8;
    }
    else if (opcode == 0xEA) {
        uint16_t a16 = 0x0000;
        a16 = ram[pc + 2] << 8;
        a16 |= (ram[pc + 1]);
        uint8_t A = (AF >> 8);
        write_mem(a16, A);
        pc += 3;
        op_cycles = 16;
    }
    else if (opcode == 0xFA) {
        uint16_t a16 = 0x0000;
        a16 = ram[pc + 2] << 8;
        a16 |= ram[pc + 1];
        set_reg(AF, 'h', ram[a16]);
        pc += 3;
        op_cycles = 16;
    }
    else if (hilo == '2') { // x2
        write_mem(dst, (AF >> 8));
        pc += 1;
        op_cycles = 8;
    }
    else if (srchilo == '6') { // x6

        if (opcode == 0x36) {
            write_mem(HL, ram[pc + 1]);
            pc += 2;
            op_cycles = 12;
            return;
        }

        set_reg(dst, hilo, ram[pc + 1]);

        pc += 2;
        op_cycles = 8;
    }
    else if (hilo == 'A') { // xA
        set_reg(AF, 'h', ram[*src]);
        pc += 1;
        op_cycles = 4;
    }
    else if (srchilo == 'E') { // xE
        set_reg(dst, hilo, ram[pc + 1]);
        pc += 2;
        op_cycles = 8;
    }
    else { //default cases

        if (dst == HL && hilo == '-') {
            uint8_t val = (srchilo == 'h') ? ((*src) >> 8) : (*src & 0x00FF);
            write_mem(HL, val);
            pc += 1;
            op_cycles = 8;
            return;
        }

        if (src == &HL && srchilo == '-') {
            set_reg(dst, hilo, ram[HL]);
            pc += 1;
            op_cycles = 4;
            return;
        }

        uint8_t val = (srchilo == 'h') ? ((*src) >> 8) : (*src & 0x00FF);

        set_reg(dst, hilo, val);

        pc += 1;
        op_cycles = 4;
    }
}

void Processor::LD16(uint16_t* reg, uint16_t* src) {

    if (reg != nullptr && src == nullptr) { //0xX1 case
        uint16_t d16 = (ram[pc + 1] | ram[pc + 2] << 8);
        *reg = (ram[pc + 1] | (ram[pc + 2] << 8));
        pc += 3;
        op_cycles = 12;
    }
    else if (reg == nullptr && src == &SP) { //0x08 case

        uint16_t address = (ram[pc + 1] | (ram[pc + 12] << 8));
        write_mem(address, (uint8_t)(SP & 0x00FF));
        write_mem(address + 1, (uint8_t)(SP >> 8));

        pc += 3;
        op_cycles = 20;
    }
    else if (reg == &HL && src == &SP) { //0xF8
        int8_t s8 = unsigned_to_signed(ram[pc + 1]);

        int H_test1 = (SP >> 8) & 1;

        if (SP + s8 > UINT16_MAX)
            set_flag(C);
        else
            set_flag(C, 0);

        HL = SP + s8;

        int H_test2 = (HL >> 8) & 1;

        if (H_test2 != H_test1)
            set_flag(H);
        else
            set_flag(H, 0);

        set_flag(Z, 0);
        set_flag(N, 0);

        pc += 2;
        op_cycles = 12;
    }
    else if (reg == &SP && src == &HL) { //0xF9 case
        SP = HL;
        pc += 1;
        op_cycles = 8;
    }
}

//ARITHMETIC OPERATIONS

//INC and DEC implementations

//this instruction increments 16-bit register pairs
void Processor::INC16(uint16_t& reg) {
    reg++;
    pc++;
    op_cycles = 8;
}

//this instruction increments 8-bit registers
void Processor::INC8(uint16_t &reg, char hilo) {

    op_cycles = 4;

    uint8_t reg8;

    if (hilo == '-' && &reg == &HL) {
        reg8 = ram[HL];
        op_cycles = 12;
    }
    else
        reg8 = (hilo == 'h') ? (reg >> 8) : (reg & 0x00FF);

    uint8_t H_test1 = (reg8 >> 4) & 1;

    reg8 += 1;

    uint8_t H_test2 = (reg8 >> 4) & 1;

    if (H_test1 != H_test2)
        set_flag(H);
    else
        set_flag(H, 0);

    if (reg8 == 0)
        set_flag(Z);
    else
        set_flag(Z, 0);

    set_flag(N, 0);

    set_reg(reg, hilo, reg8);

    pc += 1;
}

//this instruction decrements 16-bit register pairs
void Processor::DEC16(uint16_t& reg) {
    reg--;
    pc += 1;
    op_cycles = 8;
}

//this instruction decrements 8-bit registers
void Processor::DEC8(uint16_t &reg, char hilo) {

    op_cycles = 4;

    uint8_t reg8;

    if (hilo == '-' && &reg == &HL) {
        reg8 = ram[HL];
        op_cycles = 12;
    }
    else
        reg8 = (hilo == 'h') ? (reg >> 8) : (reg & 0x00FF);

    uint8_t H_test1 = (reg8 >> 4) & 1;

    reg8 -= 1;

    uint8_t H_test2 = (reg8 >> 4) & 1;

    if (H_test1 != H_test2)
        set_flag(H);
    else
        set_flag(H, 0);

    if (reg8 == 0)
        set_flag(Z);
    else
        set_flag(Z, 0);

    set_flag(N);

    set_reg(reg, hilo, reg8);

    pc += 1;
}

//ADDITION AND SUBSTRACTION

//this instruction adds 8-bit data to the accumulator
void Processor::ADD8(uint16_t* reg, char hilo) {

    uint8_t value = 0;
    op_cycles = 4;

    if (hilo == '-') {
        value = ram[HL];
        op_cycles = 8;
    }
    else if (reg == nullptr) {
        value = ram[pc + 1];
        pc += 1;
        op_cycles = 8;
    }
    else {
        value = (hilo == 'h') ? ((*reg) >> 8) : (*reg & 0x00FF);
    }

    //cout << "VALUE: " << value;

    uint8_t A = (AF >> 8);

    set_flag(N, 0);

    if (A + value > 255)
        set_flag(C);
    else
        set_flag(C, 0);

    uint8_t htest = (A & 0xF);
    htest += (value & 0xF);

    if (htest > 0xF)
        set_flag(H);
    else
        set_flag(H, 0);

    A += value;

    if (A == 0)
        set_flag(Z);
    else
        set_flag(Z, 0);

    set_reg(AF, 'h', A);

    pc += 1;
}

//this instruction adds 16-bit data to HL register or to stack pointer without carry
void Processor::ADD16(uint16_t* src) {

    op_cycles = 8;

    if (src == nullptr) { //0xE8 case

        int8_t s8 = unsigned_to_signed(ram[pc + 1]);

        uint16_t value = s8 + SP;

        if (value > INT16_MAX)
            set_flag(C);
        else
            set_flag(C, 0);

        uint16_t H_test1 = (SP >> 8) & 1;

        uint16_t H_test2 = (value >> 8) & 1;

        if (H_test1 != H_test2)
            set_flag(H);
        else
            set_flag(H, 0);

        SP = value;

        set_flag(Z, 0);
        set_flag(N, 0);

        op_cycles = 16;
        pc += 2;
        return;
    }

    //defalut case

    if (HL + (*src) > INT16_MAX)
        set_flag(C);
    else
        set_flag(C, 0);

    uint16_t H_test1 = HL;

    HL = HL + (*src);

    uint16_t H_test2 = (HL >> 8) & 1;

    if (H_test1 != H_test2)
        set_flag(H);
    else
        set_flag(H, 0);

    set_flag(N, 0);

    pc += 1;
}

//this instruction adds 8-bit data to the accumulator considering the carry flag
void Processor::ADC8(uint16_t* reg, char hilo) {

    op_cycles = 4;

    uint8_t value;

    uint8_t A = (AF >> 8);

    if (hilo == '-') { //0x8E case

        value = ram[HL];

        op_cycles = 8;
    }
    else if (reg == nullptr) {

        value = ram[pc + 1];

        pc += 1;
        op_cycles = 8;
    }
    else {
        value = (hilo == 'h') ? ((*reg) >> 8) : (*reg & 0x00FF);
    }

    value += get_flag(C);

    if (A + value > INT8_MAX)
        set_flag(C);
    else
        set_flag(C, 0);


    uint8_t htest = (A & 0xF);
    htest += (value & 0xF);

    if (htest > 0xF)
        set_flag(H);
    else
        set_flag(H, 0);

    A += value;

    if (A == 0)
        set_flag(Z);
    else
        set_flag(Z, 0);

    set_flag(N, 0);

    set_reg(AF, 'h', A);

    pc += 1;
}

//this instruction substracts 8-bit data from the accumulator
void Processor::SUB8(uint16_t* reg, char hilo) {

    uint8_t value = 0;
    op_cycles = 4;

    if (hilo == '-') {
        value = ram[HL];
        op_cycles = 8;
    }
    else if (reg == nullptr) {
        value = ram[pc + 1];
        pc += 1;
        op_cycles = 8;
    }
    else {
        value = (hilo == 'h') ? ((*reg) >> 8) : (*reg & 0x00FF);
    }

    uint8_t A = (AF >> 8);

    if (A - value == 0)
        set_flag(Z);
    else
        set_flag(Z, 0);

    set_flag(N);

    if (A - value < 0) //actually borrow!
        set_flag(C);
    else
        set_flag(C, 0);

    uint8_t H_test1 = (A >> 4) & 1;

    A -= value;

    uint8_t H_test2 = (A >> 4) & 1;

    if (H_test1 != H_test2)
        set_flag(H);
    else
        set_flag(H, 0);

    set_reg(AF, 'h', A);

    pc += 1;
}

//this instruction substracts 8-bit data from the accumulator considering the carry flag
void Processor::SBC8(uint16_t* reg, char hilo) {
    op_cycles = 4;

    uint8_t value;

    uint8_t A = (AF >> 8);

    if (hilo == '-') { //0x8E case

        value = ram[HL];

        op_cycles = 8;
    }
    else if (reg == nullptr) {

        value = ram[pc + 1];

        pc += 1;
        op_cycles = 8;
    }
    else {
        value = (hilo == 'h') ? ((*reg) >> 8) : (*reg & 0x00FF);
    }

    value += get_flag(C);

    if (A - value < 0)
        set_flag(C);
    else
        set_flag(C, 0);

    uint8_t H_test1 = (A >> 4) & 1;

    A -= value;

    uint8_t H_test2 = (A >> 4) & 1;

    if (A == 0)
        set_flag(Z);
    else
        set_flag(Z, 0);

    set_flag(N, 0);

    if (H_test1 != H_test2)
        set_flag(H);
    else
        set_flag(H, 0);

    set_reg(AF, 'h', A);

    pc += 1;
}


//BITWISE OPERATIONS

//this instruction stores result of AND'ing the accumulator with some value
void Processor::AND(uint16_t* reg, char hilo) {

    op_cycles = 4;

    uint8_t value;

    if (hilo == '-') {
        value = ram[HL];
        op_cycles = 8;
    }
    else if (reg == nullptr) {
        value = ram[pc + 1];
        pc += 1;
        op_cycles = 8;
    }
    else {
        value = (hilo == 'h') ? ((*reg) >> 8) : (*reg & 0x00FF);
    }

    uint8_t A = (AF >> 8);

    if ((A & value) == 0)
        set_flag(Z);
    else
        set_flag(Z, 0);

    set_flag(N, 0);
    set_flag(H);
    set_flag(C, 0);

    A &= value;

    set_reg(AF, 'h', A);

    pc += 1;
}

//this instruction stores result of XOR'ing the accumulator with some value
void Processor::XOR(uint16_t* reg, char hilo) {

    op_cycles = 4;

    uint8_t value;

    if (hilo == '-') {
        value = ram[HL];
        op_cycles = 8;
    }
    else if (reg == nullptr) {
        value = ram[pc + 1];
        pc += 1;
        op_cycles = 8;
    }
    else {
        value = (hilo == 'h') ? ((*reg) >> 8) : (*reg & 0x00FF);
    }

    uint8_t A = (AF >> 8);

    if ((A ^ value) == 0)
        set_flag(Z);
    else
        set_flag(Z, 0);

    set_flag(N, 0);
    set_flag(H, 0);
    set_flag(C, 0);

    A ^= value;

    set_reg(AF, 'h', A);

    pc += 1;
}

//this instruction stores result of OR'ing the accumulator with some value
void Processor::OR(uint16_t* reg, char hilo) {

    op_cycles = 4;

    uint8_t value;

    if (hilo == '-') {
        value = ram[HL];
        op_cycles = 8;
    }
    else if (reg == nullptr) {
        value = ram[pc + 1];
        pc += 1;
        op_cycles = 8;
    }
    else {
        value = (hilo == 'h') ? ((*reg) >> 8) : (*reg & 0x00FF);
    }

    uint8_t A = (AF >> 8);

    if ((A | value) == 0)
        set_flag(Z);
    else
        set_flag(Z, 0);

    set_flag(N, 0);
    set_flag(H, 0);
    set_flag(C, 0);

    A |= value;

    set_reg(AF, 'h', A);

    pc += 1;
}

//this instruction compares the accumulator with a value and sets flags if they are equal
void Processor::CP(uint16_t* reg, char hilo) {

    op_cycles = 4;

    uint8_t value;

    if (hilo == '-') {
        value = ram[HL];
        op_cycles = 8;
    }
    else if (reg == nullptr) {
        value = ram[pc + 1];
        pc += 1;
        op_cycles = 8;
    }
    else {
        value = (hilo == 'h') ? ((*reg) >> 8) : ((*reg) & 0x00FF);
    }

    uint8_t A = (AF >> 8);

    if (A - value < 0)
        set_flag(C);
    else
        set_flag(C, 0);

    if (A - value == 0)
        set_flag(Z);
    else
        set_flag(Z, 0);

    set_flag(N);

    uint8_t H_test1 = (A >> 4) & 1;

    A -= value;

    uint8_t H_test2 = (A >> 4) & 1;

    if (H_test1 != H_test2)
        set_flag(H);
    else
        set_flag(H, 0);

    pc += 1;
}


//Stack instructions

//this instruction pushes content of the register onto the stack
void Processor::PUSH(const uint16_t& reg) {

    SP--;
    write_mem(SP, (reg >> 8));
    SP--;
    write_mem(SP, (reg & 0x00FF));

    pc += 1;
    op_cycles = 16;
}

//this instruction pops data from stack and stores it in the register
void Processor::POP(uint16_t& reg) {

    set_reg(reg, 'l', ram[SP]);
    SP++;
    set_reg(reg, 'h', ram[SP]);
    SP++;

    pc += 1;
    op_cycles = 12;
}


//Jumps and Calls

//this instruction starts a subroutine placed under the provided address 
void Processor::CALL(FLAG f) {
    if (f == FLAG::NONE || get_flag(f)) {

        uint16_t address = (ram[pc + 1] | (ram[pc + 2] << 8));

        pc += 3;

        SP--;
        write_mem(SP, (pc >> 8));
        SP--;
        write_mem(SP, (pc & 0x00FF));

        pc = address;

        op_cycles = 24;

    }
    else {
        op_cycles = 12;
        pc += 3;
    }
}

//relative jump instruction
void Processor::JR(FLAG f) {

    if (get_flag(f) == 1 || f == FLAG::NONE) {

        int8_t s8 = unsigned_to_signed(ram[pc + 1]);
        pc += 2;
        pc += s8;

        op_cycles = 12;
    }
    else {
        pc += 2;
        op_cycles = 8;
    }
}

//normal jump instruction
void Processor::JP(FLAG f) {

    //handling 0xE9
    if (f == FLAG::NN) {
        pc = HL;
        op_cycles = 4;
    }
    else if (f == FLAG::NONE || get_flag(f)) {

        uint16_t address = (ram[pc + 1] | (ram[pc + 2] << 8));
        pc = address;
        op_cycles = 16;
    }
    else {
        pc += 3;
        op_cycles = 12;
    }

}


//instruction used to return from subroutine
void Processor::RET(FLAG f) {
    if (f == FLAG::NONE) {
        uint16_t address = (ram[SP] | (ram[SP + 1] << 8));
        pc = address;
        SP += 2;
        op_cycles = 16;
    }
    else if (get_flag(f)) {
        uint16_t address = (ram[SP] | (ram[SP + 1] << 8));
        pc = address;
        SP += 2;
        op_cycles = 20;
    }
    else {
        pc += 1;
        opcode = 8;
    }
}

//instruction used to return from subroutine called by an interrupt
void Processor::RETI() {
    uint16_t address = (ram[SP] | (ram[SP + 1] << 8));
    pc = address;
    SP += 2;
    op_cycles = 16;

    //IME is set to it's pre-interrupt state, whatever this means
    IME = 1;
}


//extended xCB instructions

//this instruction sets the nth bit of the register or memory fragment
void Processor::SET(uint16_t* reg, char hilo, int bit) {

    op_cycles = 12;

    int clear = ~(1 << bit);
    int set = (1 << bit);

    uint8_t value;

    if (reg == nullptr) {
        ram[HL] &= clear;
        ram[HL] |= set;

        op_cycles = 16;

        pc += 2;

        return;
    }
    
    value = (hilo == 'h') ? ((*reg) >> 8) : ((*reg) & 0x00FF);
    

    value &= clear;
    value |= set;

    set_reg(*reg, hilo, value);

    pc += 2;
}

void Processor::RES(uint16_t* reg, char hilo, int bit) {

    op_cycles = 12;

    int clear = ~(1 << bit);

    uint8_t value;

    if (reg == nullptr) {
        ram[HL] &= clear;
        op_cycles = 16;
        pc += 2;
        return;
    }
    else {
        value = (hilo == 'h') ? ((*reg) >> 8) : ((*reg) & 0x00FF);
    }

    value &= clear;

    set_reg(*reg, hilo, value);

    pc += 2;
}

//this instruction shifts a register to the left
void Processor::RL(uint16_t& reg, char hilo) {

    if (hilo == '-') {
        int bit7 = (ram[HL] >> 7);
        ram[HL] <<= 1;
        ram[HL] |= get_flag(C);

        if (ram[HL] == 0)
            set_flag(Z);
        else
            set_flag(Z, 0);


        set_flag(N, 0);
        set_flag(H, 0);
        set_flag(C, bit7);


        op_cycles = 16;
        pc += 2;

        return;
    }

    uint8_t R = (hilo == 'h') ? (reg >> 8) : (reg & 0x00FF);

    int bit7 = (R >> 7);
    R <<= 1;
    R |= get_flag(C);

    if (R == 0)
        set_flag(Z);

    set_flag(N, 0);
    set_flag(H, 0);
    set_flag(C, bit7);

    set_reg(reg, hilo, R);

    op_cycles = 8;
    pc += 2;
}

//this instruction shifts a register to the right
void Processor::RR(uint16_t& reg, char hilo) {
    
    if (hilo == '-') {
        int bit0 = ram[HL] & 1;
        int cy = get_flag(C);
        ram[HL] >>= 1;
        set_bit(ram[HL], 7, cy);

        if (ram[HL] == 0)
            set_flag(Z);
        else
            set_flag(Z, 0);

        set_flag(N, 0);
        set_flag(H, 0);
        set_flag(C, bit0);

        op_cycles = 16;
        pc += 2;

        return;
    }

    uint8_t R = (hilo == 'h') ? (reg >> 8) : (reg & 0x00FF);

    int bit0 = R & 1;
    int cy = get_flag(C);
    R >>= 1;
    set_bit(R, 7, cy);

    if (R == 0)
        set_flag(Z);
    else
        set_flag(Z, 0);

    set_flag(N, 0);
    set_flag(H, 0);
    set_flag(C, bit0);

    set_reg(reg, hilo, R);

    op_cycles = 8;
    pc += 2;
    return;
}

//this instruction rotates the contents of the register to the left and places 7th bit in the CY flag
void Processor::RLC(uint16_t &reg, char hilo) {

    if (hilo == '-') {

        int bit7 = (ram[HL] >> 7);

        ram[HL] <<= 1;
        ram[HL] |= bit7;

        if (ram[HL] == 0)
            set_flag(Z);
        else
            set_flag(Z, 0);

        set_flag(C, bit7);
        set_flag(N, 0);
        set_flag(H, 0);


        pc += 2;
        op_cycles = 16;

        return;
    }

    uint8_t R = (hilo == 'h') ? (reg >> 8) : (reg & 0x00FF);

    int bit7 = (R >> 7);

    R <<= 1;
    R |= bit7;

    if (R == 0)
        set_flag(Z);

    set_flag(C, bit7);
    set_flag(N, 0);
    set_flag(H, 0);


    set_reg(reg, hilo, R);

    pc += 2;
    op_cycles = 8;
}

//pls test this
//this instruction rotates the contents of the register to the right and places the first bit in the CY flag
void Processor::RRC(uint16_t& reg, char hilo) {

    if (hilo == '-') {

        int bit0 = (ram[HL] & 1);

        ram[HL] >>= 1;
        ram[HL] |= (bit0 << 7);

        if (ram[HL] == 0)
            set_flag(Z);
        else
            set_flag(Z, 0);

        set_flag(C, bit0);
        set_flag(N, 0);
        set_flag(H, 0);


        pc += 2;
        op_cycles = 16;

        return;
    }

    uint8_t R = (hilo == 'h') ? (reg >> 8) : (reg & 0x00FF);

    int bit0 = (R & 1);

    R >>= 1;
    R |= (bit0 << 7);

    if (R == 0)
        set_flag(Z);

    set_flag(C, bit0);
    set_flag(N, 0);
    set_flag(H, 0);


    set_reg(reg, hilo, R);

    pc += 2;
    op_cycles = 8;
}

//this instruction shifts register to the left, leaving bit 0 reset
void Processor::SLA(uint16_t& reg, char hilo) {

    if (hilo == '-') {
            
        int bit7 = (ram[HL] >> 7);
        ram[HL] <<= 1;
        set_flag(C, bit7);

        op_cycles = 16;
        pc += 2;

        return;
    }

    uint8_t R = (hilo == 'h') ? (reg >> 8) : (reg & 0x00FF);

    int bit7 = R >> 7;

    R <<= 1;

    if (R == 0)
        set_flag(Z);
    else
        set_flag(Z, 0);

    set_flag(N, 0);
    set_flag(H, 0);
    set_flag(C, bit7);

    set_reg(reg, hilo, R);

    op_cycles = 8;
    pc += 2;
}

void Processor::SRA(uint16_t& reg, char hilo) {
    
    if (hilo == '-') {
        
        int bit0 = ram[HL] & 1;
        int bit7 = ram[HL] >> 7;
        ram[HL] >>= 1;
        ram[HL] |= (bit7 << 7);
        set_flag(C, bit0);

        op_cycles = 16;
        pc += 2;
        return;
    }

    uint8_t R = (hilo == 'h') ? (reg >> 8) : (reg & 0x00FF);

    int bit0 = R & 1;
    int bit7 = R >> 7;
    R >>= 1;
    R |= (bit7 << 7);

    if (R == 0)
        set_flag(Z);
    else
        set_flag(Z, 0);

    set_flag(N, 0);
    set_flag(H, 0);
    set_flag(C, bit0);
    set_reg(reg, hilo, R);

    op_cycles = 8;
    pc += 2;

}

void Processor::SRL(uint16_t& reg, char hilo) {

    if (hilo == '-') {

        int bit0 = ram[HL] & 1;
        ram[HL] >>= 1;
        set_flag(C, bit0);

        op_cycles = 16;
        pc += 2;
        return;
    }

    uint8_t R = (hilo == 'h') ? (reg >> 8) : (reg & 0x00FF);

    int bit0 = R & 1;
    R >>= 1;


    if (R == 0)
        set_flag(Z);
    else
        set_flag(Z, 0);

    set_flag(N, 0);
    set_flag(H, 0);

    set_flag(C, bit0);
    set_reg(reg, hilo, R);

    op_cycles = 8;
    pc += 2;
}

//swap lower 4 bits of the register with its higher 4 bits
void Processor::SWAP(uint16_t* reg, char hilo) {

    if (hilo == '-') {
        uint8_t hi = (ram[HL] >> 4);
        ram[HL] <<= 4;
        ram[HL] |= hi;

        if (ram[HL] == 0)
            set_flag(Z);

        set_flag(N, 0);
        set_flag(H, 0);
        set_flag(C, 0);

        pc += 2;
        op_cycles = 16;
        return;
    }

    uint8_t R = (hilo == 'h') ? (*reg >> 8) : (*reg & 0x00FF);

    uint8_t hi = (R >> 4);

    R <<= 4;

    R |= hi;

    if (R == 0)
        set_flag(Z);

    set_flag(N, 0);
    set_flag(H, 0);
    set_flag(C, 0);

    pc += 2;
    op_cycles = 8;
}


//set flag Z to the complement of a bit in a register
void Processor::BIT(uint16_t* reg, char hilo, int bit) {

    if (hilo == '-') {

        bool cpl = !((ram[HL] >> bit) & 1);

        set_flag(Z, cpl);
        set_flag(N, 0);
        set_flag(H);

        pc += 2;
        op_cycles = 12;
        return;
    }

    uint8_t R = (hilo == 'h') ? (*reg >> 8) : (*reg & 0x00FF);

    bool cpl = !((R >> bit) & 1);

    set_flag(Z, cpl);
    set_flag(N, 0);
    set_flag(H);

    pc += 2;
    op_cycles = 8;
}

//this instruction left shifts accumulator, the carry flag is set to acc's 7th bit
void Processor::RLA() {

    uint8_t R = (AF >> 8);

    int bit7 = (R >> 7);
    R <<= 1;
    R |= get_flag(C);

    set_flag(Z, 0);
    set_flag(N, 0);
    set_flag(H, 0);
    set_flag(C, bit7);

    set_reg(AF, 'h', R);

    op_cycles = 4;
    pc += 1;
}

//this instruction left shifts accumulator, the carry flag is set to acc's 7th bit
void Processor::RLCA() {

    uint8_t A = (AF >> 8);

    int bit7 = (A >> 7);

    A <<= 1;
    A |= bit7;

    set_flag(Z, 0);
    set_flag(N, 0);
    set_flag(H, 0);
    set_flag(C, bit7);

    set_reg(AF, 'h', A);

    op_cycles = 4;
    pc++;

}


//shift content of the accumulator to the right through carry flag
void Processor::RRA() {

    uint8_t A = (AF >> 8);

    int bit0 = A & 1;
    int cy = get_flag(C);

    A |= (cy << 7);

    set_flag(C, bit0);
    set_flag(Z, 0);
    set_flag(N, 0);
    set_flag(H, 0);

    set_reg(AF, 'h', A);

    op_cycles = 4;
    pc += 1;
}

void Processor::RRCA() {
    uint8_t A = (AF >> 8);

    int bit0 = A & 1;
    
    A |= (bit0 << 7);

    set_flag(C, bit0);
    set_flag(Z, 0);
    set_flag(N, 0);
    set_flag(H, 0);

    set_reg(AF, 'h', A);

    op_cycles = 4;
    pc += 1;
}