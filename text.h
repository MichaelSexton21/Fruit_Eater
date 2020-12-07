// Font data for Microsoft Sans Serif 8pt


#ifndef TEXT_H_
#define TEXT_H_
#include <main.h>


// This structure describes a single character's display information
typedef struct
{
    uint8_t widthBits;                 // width, in bits (or pixels), of the character
    uint16_t offset;                   // offset of the character's bitmap, in bytes, into the the FONT_INFO's data array

} FONT_CHAR_INFO;

// Describes a single font
typedef struct
{
    uint8_t            height;    // height, in pages (8 pixels), of the font's characters
    uint8_t            startChar;      // the first character in the font (e.g. in charInfo and data)
    uint8_t            endChar;        // the last character in the font
    uint8_t            width;    // number of pixels that a space character takes up
    FONT_CHAR_INFO*   charInfo;       // pointer to array of char information
    uint8_t*           data;           // pointer to generated array of character visual representation

} FONT_INFO;

extern uint8_t microsoftSansSerif_8ptBitmaps[];
extern FONT_INFO microsoftSansSerif_8ptFontInfo;
extern FONT_CHAR_INFO microsoftSansSerif_8ptDescriptors[];
#endif
