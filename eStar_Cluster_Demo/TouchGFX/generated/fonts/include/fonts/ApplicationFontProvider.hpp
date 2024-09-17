/* DO NOT EDIT THIS FILE */
/* This file is autogenerated by the text-database code generator */

#ifndef TOUCHGFX_APPLICATIONFONTPROVIDER_HPP
#define TOUCHGFX_APPLICATIONFONTPROVIDER_HPP

#include <touchgfx/FontManager.hpp>

namespace touchgfx
{
class FlashDataReader;
}

struct Typography
{
    static const touchgfx::FontId SPEED = 0;
    static const touchgfx::FontId KMPH = 1;
    static const touchgfx::FontId ODO = 2;
    static const touchgfx::FontId DRIVERINFO = 3;
    static const touchgfx::FontId AM_PM = 4;
    static const touchgfx::FontId CLOCK_HR = 5;
    static const touchgfx::FontId CLOCK_MIN = 6;
    static const touchgfx::FontId SEMICOLON = 7;
    static const touchgfx::FontId DRIVRINFO_DATA = 8;
    static const touchgfx::FontId DRIVERINFOMENU = 9;
    static const touchgfx::FontId CLOCK = 10;
    static const touchgfx::FontId ODO_UNITS = 11;
};

struct TypographyFontIndex
{
    static const touchgfx::FontId SPEED = 0;          // Vector_arial_80
    static const touchgfx::FontId KMPH = 1;           // arial_13_4bpp
    static const touchgfx::FontId ODO = 2;            // Vector_arial_36
    static const touchgfx::FontId DRIVERINFO = 3;     // Vector_arial_24
    static const touchgfx::FontId AM_PM = 4;          // arial_12_4bpp
    static const touchgfx::FontId CLOCK_HR = 5;       // arial_18_4bpp
    static const touchgfx::FontId CLOCK_MIN = 5;      // arial_18_4bpp
    static const touchgfx::FontId SEMICOLON = 6;      // Technology_Bold_24_4bpp
    static const touchgfx::FontId DRIVRINFO_DATA = 7; // Technology_Bold_17_4bpp
    static const touchgfx::FontId DRIVERINFOMENU = 8; // arial_17_4bpp
    static const touchgfx::FontId CLOCK = 5;          // arial_18_4bpp
    static const touchgfx::FontId ODO_UNITS = 9;      // arial_14_4bpp
    static const uint16_t NUMBER_OF_FONTS = 10;
};

class ApplicationFontProvider : public touchgfx::FontProvider
{
public:
    virtual touchgfx::Font* getFont(touchgfx::FontId typography);

    static void setFlashReader(touchgfx::FlashDataReader* /*flashReader*/)
    {
    }

    static touchgfx::FlashDataReader* getFlashReader()
    {
        return 0;
    }
};

#endif // TOUCHGFX_APPLICATIONFONTPROVIDER_HPP
