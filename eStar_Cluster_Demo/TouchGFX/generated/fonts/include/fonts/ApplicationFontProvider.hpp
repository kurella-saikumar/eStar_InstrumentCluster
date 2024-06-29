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
};

struct TypographyFontIndex
{
    static const touchgfx::FontId SPEED = 0;          // Technology_Bold_96_4bpp
    static const touchgfx::FontId KMPH = 1;           // Technology_Bold_17_4bpp
    static const touchgfx::FontId ODO = 2;            // Technology_Bold_36_4bpp
    static const touchgfx::FontId DRIVERINFO = 3;     // Technology_Bold_24_4bpp
    static const touchgfx::FontId AM_PM = 4;          // Technology_Bold_14_4bpp
    static const touchgfx::FontId CLOCK_HR = 5;       // Technology_Bold_20_4bpp
    static const touchgfx::FontId CLOCK_MIN = 5;      // Technology_Bold_20_4bpp
    static const touchgfx::FontId SEMICOLON = 3;      // Technology_Bold_24_4bpp
    static const touchgfx::FontId DRIVRINFO_DATA = 1; // Technology_Bold_17_4bpp
    static const uint16_t NUMBER_OF_FONTS = 6;
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
