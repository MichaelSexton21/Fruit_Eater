/*
 * text.c
 *
 *      Author: Michael Sexton and Jack Bybel
 */

#include <text.h>
//
//  Font data for Microsoft Sans Serif 8pt
//

// Character bitmaps for Microsoft Sans Serif 8pt
uint8_t microsoftSansSerif_8ptBitmaps[] =
{
    // @0 '0' (5 pixels wide)
    0x70, //  ###
    0x88, // #   #
    0x88, // #   #
    0x88, // #   #
    0x88, // #   #
    0x88, // #   #
    0x88, // #   #
    0x88, // #   #
    0x70, //  ###

    // @9 '1' (3 pixels wide)
    0x20, //   #
    0xE0, // ###
    0x20, //   #
    0x20, //   #
    0x20, //   #
    0x20, //   #
    0x20, //   #
    0x20, //   #
    0x20, //   #

    // @18 '2' (5 pixels wide)
    0x70, //  ###
    0x88, // #   #
    0x08, //     #
    0x08, //     #
    0x10, //    #
    0x20, //   #
    0x40, //  #
    0x80, // #
    0xF8, // #####

    // @27 '3' (5 pixels wide)
    0x70, //  ###
    0x88, // #   #
    0x08, //     #
    0x08, //     #
    0x30, //   ##
    0x08, //     #
    0x08, //     #
    0x88, // #   #
    0x70, //  ###

    // @36 '4' (5 pixels wide)
    0x10, //    #
    0x30, //   ##
    0x30, //   ##
    0x50, //  # #
    0x50, //  # #
    0x90, // #  #
    0xF8, // #####
    0x10, //    #
    0x10, //    #

    // @45 '5' (5 pixels wide)
    0xF8, // #####
    0x80, // #
    0x80, // #
    0xF0, // ####
    0x88, // #   #
    0x08, //     #
    0x08, //     #
    0x88, // #   #
    0x70, //  ###

    // @54 '6' (5 pixels wide)
    0x70, //  ###
    0x88, // #   #
    0x80, // #
    0x80, // #
    0xF0, // ####
    0x88, // #   #
    0x88, // #   #
    0x88, // #   #
    0x70, //  ###

    // @63 '7' (5 pixels wide)
    0xF8, // #####
    0x08, //     #
    0x10, //    #
    0x10, //    #
    0x20, //   #
    0x20, //   #
    0x40, //  #
    0x40, //  #
    0x40, //  #

    // @72 '8' (5 pixels wide)
    0x70, //  ###
    0x88, // #   #
    0x88, // #   #
    0x88, // #   #
    0x70, //  ###
    0x88, // #   #
    0x88, // #   #
    0x88, // #   #
    0x70, //  ###

    // @81 '9' (5 pixels wide)
    0x70, //  ###
    0x88, // #   #
    0x88, // #   #
    0x88, // #   #
    0x78, //  ####
    0x08, //     #
    0x08, //     #
    0x88, // #   #
    0x70, //  ###

    // @90 'E' (5 pixels wide)
    0xF8, // #####
    0x80, // #
    0x80, // #
    0x80, // #
    0xF0, // ####
    0x80, // #
    0x80, // #
    0x80, // #
    0xF8, // #####

    // @99 'F' (5 pixels wide)
    0xF8, // #####
    0x80, // #
    0x80, // #
    0x80, // #
    0xF0, // ####
    0x80, // #
    0x80, // #
    0x80, // #
    0x80, // #

    // @108 'P' (6 pixels wide)
    0xF8, // #####
    0x84, // #    #
    0x84, // #    #
    0x84, // #    #
    0xF8, // #####
    0x80, // #
    0x80, // #
    0x80, // #
    0x80, // #

    // @117 'S' (5 pixels wide)
    0x70, //  ###
    0x88, // #   #
    0x80, // #
    0x80, // #
    0x70, //  ###
    0x08, //     #
    0x08, //     #
    0x88, // #   #
    0x70, //  ###

    // @126 'W' (11 pixels wide)
    0x80, 0x20, // #         #
    0x80, 0x20, // #         #
    0x44, 0x40, //  #   #   #
    0x44, 0x40, //  #   #   #
    0x44, 0x40, //  #   #   #
    0x2A, 0x80, //   # # # #
    0x2A, 0x80, //   # # # #
    0x11, 0x00, //    #   #
    0x11, 0x00, //    #   #

    // @144 'a' (5 pixels wide)
    0x00, //
    0x00, //
    0x00, //
    0x70, //  ###
    0x08, //     #
    0x78, //  ####
    0x88, // #   #
    0x88, // #   #
    0x78, //  ####

    // @153 'c' (5 pixels wide)
    0x00, //
    0x00, //
    0x00, //
    0x70, //  ###
    0x88, // #   #
    0x80, // #
    0x80, // #
    0x88, // #   #
    0x70, //  ###

    // @162 'e' (5 pixels wide)
    0x00, //
    0x00, //
    0x00, //
    0x70, //  ###
    0x88, // #   #
    0xF8, // #####
    0x80, // #
    0x88, // #   #
    0x70, //  ###

    // @171 'i' (1 pixels wide)
    0x80, // #
    0x00, //
    0x00, //
    0x80, // #
    0x80, // #
    0x80, // #
    0x80, // #
    0x80, // #
    0x80, // #

    // @180 'l' (1 pixels wide)
    0x80, // #
    0x80, // #
    0x80, // #
    0x80, // #
    0x80, // #
    0x80, // #
    0x80, // #
    0x80, // #
    0x80, // #

    // @189 'm' (7 pixels wide)
    0x00, //
    0x00, //
    0x00, //
    0xEC, // ### ##
    0x92, // #  #  #
    0x92, // #  #  #
    0x92, // #  #  #
    0x92, // #  #  #
    0x92, // #  #  #

    // @198 'o' (5 pixels wide)
    0x00, //
    0x00, //
    0x00, //
    0x70, //  ###
    0x88, // #   #
    0x88, // #   #
    0x88, // #   #
    0x88, // #   #
    0x70, //  ###

    // @207 'r' (2 pixels wide)
    0x00, //
    0x00, //
    0x00, //
    0xC0, // ##
    0x80, // #
    0x80, // #
    0x80, // #
    0x80, // #
    0x80, // #

    // @216 's' (4 pixels wide)
    0x00, //
    0x00, //
    0x00, //
    0x60, //  ##
    0x90, // #  #
    0x40, //  #
    0x20, //   #
    0x90, // #  #
    0x60, //  ##

    // @225 't' (2 pixels wide)
    0x00, //
    0x80, // #
    0x80, // #
    0xC0, // ##
    0x80, // #
    0x80, // #
    0x80, // #
    0x80, // #
    0x40, //  #

    // @234 'u' (5 pixels wide)
    0x00, //
    0x00, //
    0x00, //
    0x88, // #   #
    0x88, // #   #
    0x88, // #   #
    0x88, // #   #
    0x98, // #  ##
    0x68, //  ## #

    // @117 'C' (6 pixels wide)
    0x78, //  ####
    0x84, // #    #
    0x80, // #
    0x80, // #
    0x80, // #
    0x80, // #
    0x80, // #
    0x84, // #    #
    0x78, //  ####

    // @180 'O' (6 pixels wide)
    0x78, //  ####
    0x84, // #    #
    0x84, // #    #
    0x84, // #    #
    0x84, // #    #
    0x84, // #    #
    0x84, // #    #
    0x84, // #    #
    0x78, //  ####

    // @171 'N' (6 pixels wide)
    0x84, // #    #
    0xC4, // ##   #
    0xC4, // ##   #
    0xA4, // # #  #
    0xA4, // # #  #
    0x94, // #  # #
    0x8C, // #   ##
    0x8C, // #   ##
    0x84, // #    #

    // @144 'G' (6 pixels wide)
    0x78, //  ####
    0x84, // #    #
    0x80, // #
    0x80, // #
    0x9C, // #  ###
    0x84, // #    #
    0x84, // #    #
    0x8C, // #   ##
    0x74, //  ### #

    // @198 'R' (6 pixels wide)
    0xF8, // #####
    0x84, // #    #
    0x84, // #    #
    0x84, // #    #
    0xF8, // #####
    0x84, // #    #
    0x84, // #    #
    0x84, // #    #
    0x84, // #    #

    // @108 'A' (7 pixels wide)
    0x10, //    #
    0x10, //    #
    0x28, //   # #
    0x28, //   # #
    0x44, //  #   #
    0x44, //  #   #
    0x7C, //  #####
    0x82, // #     #
    0x82, // #     #

    // @216 'T' (5 pixels wide)
        0xF8, // #####
        0x20, //   #
        0x20, //   #
        0x20, //   #
        0x20, //   #
        0x20, //   #
        0x20, //   #
        0x20, //   #
        0x20, //   #

    // @225 'U' (6 pixels wide)
    0x84, // #    #
    0x84, // #    #
    0x84, // #    #
    0x84, // #    #
    0x84, // #    #
    0x84, // #    #
    0x84, // #    #
    0x84, // #    #
    0x78, //  ####

// @162 'L' (5 pixels wide)
    0x80, // #
    0x80, // #
    0x80, // #
    0x80, // #
    0x80, // #
    0x80, // #
    0x80, // #
    0x80, // #
    0xF8, // #####

    // @153 'I' (1 pixels wide)
    0x80, // #
    0x80, // #
    0x80, // #
    0x80, // #
    0x80, // #
    0x80, // #
    0x80, // #
    0x80, // #
    0x80, // #

    // @252 'Y' (7 pixels wide)
    0x82, // #     #
    0x82, // #     #
    0x44, //  #   #
    0x28, //   # #
    0x10, //    #
    0x10, //    #
    0x10, //    #
    0x10, //    #
    0x10, //    #



};

// Character descriptors for Microsoft Sans Serif 8pt
// { [Char width in bits], [Offset into microsoftSansSerif_8ptCharBitmaps in bytes] }
FONT_CHAR_INFO microsoftSansSerif_8ptDescriptors[] =
{
    {5, 0},         // 0
    {3, 9},         // 1
    {5, 18},        // 2
    {5, 27},        // 3
    {5, 36},        // 4
    {5, 45},        // 5
    {5, 54},        // 6
    {5, 63},        // 7
    {5, 72},        // 8
    {5, 81},        // 9
    {0, 0},         // :
    {0, 0},         // ;
    {0, 0},         // <
    {0, 0},         // =
    {0, 0},         // >
    {0, 0},         // ?
    {0, 0},         // @
    {7, 288},         // A
    {0, 0},         // B
    {6, 243},         // C
    {0, 0},         // D
    {5, 90},        // E
    {5, 99},        // F
    {6, 270},         // G
    {0, 0},         // H
    {1, 324},         // I
    {0, 0},         // J
    {0, 0},         // K
    {5, 315},         // L
    {0, 0},         // M
    {6, 261},         // N
    {6, 252},         // O
    {6, 108},       // P
    {0, 0},         // Q
    {6, 279},         // R
    {5, 117},       // S
    {5, 297},         // T
    {6, 306},         // U
    {0, 0},         // V
    {11, 126},      // W
    {0, 0},         // X
    {7, 333},         // Y
    {0, 0},         // Z
    {0, 0},         // [
    {0, 0},         //
    {0, 0},         // ]
    {0, 0},         // ^
    {0, 0},         // _
    {0, 0},         // `
    {5, 144},       // a
    {0, 0},         // b
    {5, 153},       // c
    {0, 0},         // d
    {5, 162},       // e
    {0, 0},         // f
    {0, 0},         // g
    {0, 0},         // h
    {1, 171},       // i
    {0, 0},         // j
    {0, 0},         // k
    {1, 180},       // l
    {7, 189},       // m
    {0, 0},         // n
    {5, 198},       // o
    {0, 0},         // p
    {0, 0},         // q
    {2, 207},       // r
    {4, 216},       // s
    {2, 225},       // t
    {5, 234},       // u
};

// Font information for Microsoft Sans Serif 8pt
FONT_INFO microsoftSansSerif_8ptFontInfo =
{
    2, //  Character height
    '0', //  Start character
    'u', //  End character
    2, //  Width, in pixels, of space character
    microsoftSansSerif_8ptDescriptors, //  Character descriptor array
    microsoftSansSerif_8ptBitmaps, //  Character bitmap array
};

