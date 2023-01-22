#include "MyDisplay.h"

void MyDisplay::begin() {
    _ht.begin();
    _ht.sendCommand(HT1621::RC256K);
    _ht.sendCommand(HT1621::BIAS_THIRD_4_COM);
    _ht.sendCommand(HT1621::SYS_EN);
    _ht.sendCommand(HT1621::LCD_ON);
}

void MyDisplay::clear() {
    for (uint8_t i = 0; i < _ht.MAX_ADDR; i++)
        _ht.write(i, 0);

    memset(_buffer, 0, sizeof(_buffer));
}

// pos is calculated from left to right
void MyDisplay::write(uint8_t pos, uint8_t symbol) {
    _buffer[pos] = symbol;
    uint16_t data = _convert(symbol);

    // each address points 4 bits
    // so each char position takes 4*4 bits
    uint8_t address = _ht.MAX_ADDR - 4 * (pos+1);
    _ht.write(address, data, 16);
}

uint8_t MyDisplay::read(uint8_t pos) {
    return _buffer[pos];
}

uint16_t MyDisplay::_convert(uint8_t symbol) {
    return Ascii[symbol];
}

// https://en.wikipedia.org/wiki/Fourteen-segment_display
// Follow 14 segment format.
// Segment bits in my specific display, where each position has 16 segments (14 of which are used to
// display alphanumeric characters and some symbols). This leaves 2 segments that are for the period,
// colon, and other symbols.

// Special Seg1 = 0000 0000 0000 0001 = 1     - Folder Icon, Colon, LOOP, PGM, RND, 1TR, 1ALBUM, DAB
// Segment F    = 0000 0000 0000 0010 = 2
// Segment E    = 0000 0000 0000 0100 = 4
// Special Seg2 = 0000 0000 0000 1000 = 8     - Note Icon, Period, MONO, RDS, SLEEP, ()PLAY, Triangle, USB
// Segment A    = 0000 0000 0001 0000 = 16
// Segment H    = 0000 0000 0010 0000 = 32
// Segment G1   = 0000 0000 0100 0000 = 64
// Segment K    = 0000 0000 1000 0000 = 128
// Segment J    = 0000 0001 0000 0000 = 256
// Segment I    = 0000 0010 0000 0000 = 512
// Segment L    = 0000 0100 0000 0000 = 1024
// Segment D    = 0000 1000 0000 0000 = 2048
// Segment B    = 0001 0000 0000 0000 = 4096
// Segment G2   = 0010 0000 0000 0000 = 8192
// Segment C    = 0100 0000 0000 0000 = 16384
// Segment M    = 1000 0000 0000 0000 = 32768

// A digit/letter can be encoded in 16-bits in 2 bytes.
#define S_S1 1
#define S_S2 8
#define S_A 16
#define S_B 4096
#define S_C 16384
#define S_D 2048
#define S_E 4
#define S_F 2
#define S_G1 64
#define S_G2 8192
#define S_H 32
#define S_I 512
#define S_J 256
#define S_K 128
#define S_L 1024
#define S_M 32768

// 14 segment glyphs
// digits
//      G_x  S_A   S_B   S_C   S_D   S_E   S_F   S_G1   S_G2   S_H   S_I   S_J   S_K   S_L    S_M
#define G_0 (S_A + S_B + S_C + S_D + S_E + S_F +  0   +  0   +   0  +  0  + S_J + S_K +  0  +  0 ) // 48
#define G_1 ( 0  + S_B + S_C +  0  +  0  +  0  +  0   +  0   +   0  +  0  + S_J +  0  +  0  +  0 ) // 49
#define G_2 (S_A + S_B +  0  + S_D + S_E +  0  + S_G1 + S_G2 +   0  +  0  +  0  +  0  +  0  +  0 ) // 50
#define G_3 (S_A + S_B + S_C + S_D +  0  +  0  +  0   + S_G2 +   0  +  0  +  0  +  0  +  0  +  0 ) // 51
#define G_4 ( 0  + S_B + S_C +  0  +  0  + S_F + S_G1 + S_G2 +   0  +  0  +  0  +  0  +  0  +  0 ) // 52
#define G_5 (S_A +  0  + 0   + S_D +  0  + S_F + S_G1 +  0   +   0  +  0  +  0  +  0  +  0  + S_M) // 53
#define G_6 (S_A +  0  + S_C + S_D + S_E + S_F + S_G1 + S_G2 +   0  +  0  +  0  +  0  +  0  +  0 ) // 54
#define G_7 (S_A +  0  +  0  +  0  +  0  +  0  +  0   +  0   +   0  +  0  + S_J +  0  + S_L +  0 ) // 55
#define G_8 (S_A + S_B + S_C + S_D + S_E + S_F + S_G1 + S_G2 +   0  +  0  +  0  +  0  +  0  +  0 ) // 56
#define G_9 (S_A + S_B + S_C +  0  +  0  + S_F + S_G1 + S_G2 +   0  +  0  +  0  +  0  +  0  +  0 ) // 57

// special
//      G_x             S_A   S_B   S_C   S_D   S_E   S_F   S_G1   S_G2   S_H   S_I   S_J   S_K   S_L   S_M
#define G_space          0                                                                                   // 32
#define G_plus         ( 0  +  0  +  0  +  0  +  0  +  0  + S_G1 + S_G2 +  0  + S_I +  0  +  0  + S_L +  0 ) // 43
#define G_minus        ( 0  +  0  +  0  +  0  +  0  +  0  + S_G1 + S_G2 +  0  +  0  +  0  +  0  +  0  +  0 ) // 45
#define G_period         S_S2                                                                                // 46
#define G_fwd_slash    ( 0  +  0  +  0  +  0  +  0  +  0  +  0   +  0   +  0  +  0  + S_J + S_K +  0  +  0 ) // 47
#define G_colon          S_S1                                                                                // 58
#define G_less_than    ( 0  +  0  +  0  +  0  +  0  +  0  +  0   +  0   +  0  +  0  + S_J +  0  +  0  + S_M) // 60
#define G_equal        ( 0  +  0  +  0  + S_D +  0  +  0  + S_G1 + S_G2 +  0  +  0  +  0  +  0  +  0  +  0 ) // 61
#define G_greater_than ( 0  +  0  +  0  +  0  +  0  +  0  +  0   +  0   + S_H +  0  +  0  + S_K +  0  +  0 ) // 62
#define G_back_slash   ( 0  +  0  +  0  +  0  +  0  +  0  +  0   +  0   + S_H +  0  +  0  +  0  +  0  + S_M) // 92
#define G_underscore   ( 0  +  0  +  0  + S_D +  0  +  0  +  0   +  0   +  0  +  0  +  0  +  0  +  0  +  0 ) // 95
#define G_vertical     ( 0  +  0  +  0  +  0  +  0  +  0  +  0   +  0   +  0  + S_I +  0  +  0  + S_L +  0 ) // 124

// upper case letters
//      G_x  S_A   S_B   S_C   S_D   S_E   S_F   S_G1   S_G2   S_H   S_I   S_J   S_K   S_L   S_M
#define G_A (S_A + S_B + S_C +  0  + S_E + S_F + S_G1 + S_G2 +  0  +  0  +  0  +  0  +  0  +  0 ) // A - 65
#define G_B (S_A + S_B + S_C + S_D +  0  +  0  +  0   + S_G2 +  0  + S_I +  0  +  0  + S_L +  0 ) // B - 66
#define G_C (S_A +  0  +  0  + S_D + S_E + S_F +  0   +  0   +  0  +  0  +  0  +  0  +  0  +  0 ) // C - 67
#define G_D (S_A + S_B + S_C + S_D +  0  +  0  +  0   +  0   +  0  + S_I +  0  +  0  + S_L +  0 ) // D - 68
#define G_E (S_A +  0  +  0  + S_D + S_E + S_F + S_G1 +  0   +  0  +  0  +  0  +  0  +  0  +  0 ) // E - 69
#define G_F (S_A +  0  +  0  +  0  + S_E + S_F + S_G1 +  0   +  0  +  0  +  0  +  0  +  0  +  0 ) // F - 70
#define G_G (S_A +  0  + S_C + S_D + S_E + S_F +  0   + S_G2 +  0  +  0  +  0  +  0  +  0  +  0 ) // G - 71
#define G_H ( 0  + S_B + S_C +  0  + S_E + S_F + S_G1 + S_G2 +  0  +  0  +  0  +  0  +  0  +  0 ) // H - 72
#define G_I (S_A +  0  +  0  + S_D +  0  +  0  +  0   +  0   +  0  + S_I +  0  +  0  + S_L +  0 ) // I - 73
#define G_J ( 0  + S_B + S_C + S_D + S_E +  0  +  0   +  0   +  0  +  0  +  0  +  0  +  0  +  0 ) // J - 74
#define G_K ( 0  +  0  +  0  +  0  + S_E + S_F + S_G1 +  0   +  0  +  0  + S_J +  0  +  0  + S_M) // K - 75
#define G_L ( 0  +  0  +  0  + S_D + S_E + S_F +  0   +  0   +  0  +  0  +  0  +  0  +  0  +  0 ) // L - 76
#define G_M ( 0  + S_B + S_C +  0  + S_E + S_F +  0   +  0   + S_H +  0  + S_J +  0  +  0  +  0 ) // M - 77
#define G_N ( 0  + S_B + S_C +  0  + S_E + S_F +  0   +  0   + S_H +  0  +  0  +  0  +  0  + S_M) // N - 78
#define G_O (S_A + S_B + S_C + S_D + S_E + S_F +  0   +  0   +  0  +  0  +  0  +  0  +  0  +  0 ) // O - 79
#define G_P (S_A + S_B +  0  +  0  + S_E + S_F + S_G1 + S_G2 +  0  +  0  +  0  +  0  +  0  +  0 ) // P - 80
#define G_Q (S_A + S_B + S_C + S_D + S_E + S_F +  0   +  0   +  0  +  0  +  0  +  0  +  0  + S_M) // Q - 81
#define G_R (S_A + S_B +  0  +  0  + S_E + S_F + S_G1 + S_G2 +  0  +  0  +  0  +  0  +  0  + S_M) // R - 82
#define G_S (S_A +  0  + S_C + S_D +  0  + S_F + S_G1 + S_G2 +  0  +  0  +  0  +  0  +  0  +  0 ) // S - 83
#define G_T (S_A +  0  +  0  +  0  +  0  +  0  +  0   +  0   +  0  + S_I +  0  +  0  + S_L +  0 ) // T - 84
#define G_U ( 0  + S_B + S_C + S_D + S_E + S_F +  0   +  0   +  0  +  0  +  0  +  0  +  0  +  0 ) // U - 85
#define G_V ( 0  +  0  +  0  +  0  + S_E + S_F +  0   +  0   +  0  +  0  + S_J + S_K +  0  +  0 ) // V - 86
#define G_W ( 0  + S_B + S_C +  0  + S_E + S_F +  0   +  0   +  0  +  0  +  0  + S_K +  0  + S_M) // W - 87
#define G_X ( 0  +  0  +  0  +  0  +  0  +  0  +  0   +  0   + S_H +  0  + S_J + S_K +  0  + S_M) // X - 88
#define G_Y ( 0  + S_B + S_C + S_D +  0  + S_F + S_G1 + S_G2 +  0  +  0  +  0  +  0  +  0  +  0 ) // Y - 89
#define G_Z (S_A +  0  +  0  + S_D +  0  +  0  +  0   +  0   +  0  +  0  + S_J + S_K +  0  +  0 ) // Z - 90

// Ascii lookup tabel
// https://upload.wikimedia.org/wikipedia/commons/1/1b/ASCII-Table-wide.svg
const uint16_t MyDisplay::Ascii[128] = {
        0, 0, 0, 0, 0, 0, 0, 0,                                         // 0-7   Don't populate or use.
        0, 0, 0, 0, 0, 0, 0, 0,                                         // 8-15  Don't populate or use.
        0, 0, 0, 0, 0, 0, 0, 0,                                         // 16-23 Don't populate or use.
        0, 0, 0, 0, 0, 0, 0, 0,                                         // 24-31 Don't populate or use.
        G_space, 0, 0, 0, 0, 0, 0, 0,                                   // 32-39
        0, 0, 0, G_plus, 0, G_minus, G_period, G_fwd_slash,             // 40-47
        G_0, G_1, G_2, G_3, G_4, G_5, G_6, G_7,                         // 48-55
        G_8, G_9, G_colon, 0, G_less_than, G_equal, G_greater_than, 0,  // 56-63
        0, G_A, G_B, G_C, G_D, G_E, G_F, G_G,                           // 64-71 upper case letters
        G_H, G_I, G_J, G_K, G_L, G_M, G_N, G_O,                         // 72-79
        G_P, G_Q, G_R, G_S, G_T, G_U, G_V, G_W,                         // 80-87
        G_X, G_Y, G_Z, 0, G_back_slash, 0, 0, G_underscore,             // 88-95
        0, 0, 0, 0, 0, 0, 0, 0,                                         // 96-103 lower case letters
        0, 0, 0, 0, 0, 0, 0, 0,                                         // 104-111
        0, 0, 0, 0, 0, 0, 0, 0,                                         // 112-119
        0, 0, 0, 0, G_vertical, 0, 0, 0                                 // 120-127
};
