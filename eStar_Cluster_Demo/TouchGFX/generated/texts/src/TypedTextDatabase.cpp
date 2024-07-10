/* DO NOT EDIT THIS FILE */
/* This file is autogenerated by the text-database code generator */

#include <touchgfx/TypedText.hpp>
#include <fonts/GeneratedFont.hpp>
#include <texts/TypedTextDatabase.hpp>

extern touchgfx::GeneratedVectorFont& getFont_vector_Technology_Bold_96();
extern touchgfx::GeneratedFont& getFont_Technology_Bold_17_4bpp();
extern touchgfx::GeneratedVectorFont& getFont_vector_Technology_Bold_36();
extern touchgfx::GeneratedVectorFont& getFont_vector_Technology_Bold_24();
extern touchgfx::GeneratedFont& getFont_Technology_Bold_16_4bpp();
extern touchgfx::GeneratedFont& getFont_Technology_Bold_20_4bpp();
extern touchgfx::GeneratedFont& getFont_Technology_Bold_24_4bpp();
extern touchgfx::GeneratedFont& getFont_Technology_Bold_22_4bpp();

const touchgfx::Font* touchgfx_fonts[] = {
    &(getFont_vector_Technology_Bold_96()),
    &(getFont_Technology_Bold_17_4bpp()),
    &(getFont_vector_Technology_Bold_36()),
    &(getFont_vector_Technology_Bold_24()),
    &(getFont_Technology_Bold_16_4bpp()),
    &(getFont_Technology_Bold_20_4bpp()),
    &(getFont_Technology_Bold_24_4bpp()),
    &(getFont_Technology_Bold_22_4bpp())
};

extern const touchgfx::TypedText::TypedTextData typedText_database_DEFAULT[];
extern const touchgfx::TypedText::TypedTextData* const typedTextDatabaseArray[];

TEXT_LOCATION_FLASH_PRAGMA
const touchgfx::TypedText::TypedTextData typedText_database_DEFAULT[] TEXT_LOCATION_FLASH_ATTRIBUTE = {
    { 4, touchgfx::LEFT, touchgfx::TEXT_DIRECTION_LTR },
    { 4, touchgfx::LEFT, touchgfx::TEXT_DIRECTION_LTR },
    { 7, touchgfx::LEFT, touchgfx::TEXT_DIRECTION_LTR },
    { 7, touchgfx::LEFT, touchgfx::TEXT_DIRECTION_LTR },
    { 7, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 5, touchgfx::LEFT, touchgfx::TEXT_DIRECTION_LTR },
    { 5, touchgfx::RIGHT, touchgfx::TEXT_DIRECTION_LTR },
    { 0, touchgfx::LEFT, touchgfx::TEXT_DIRECTION_LTR },
    { 1, touchgfx::LEFT, touchgfx::TEXT_DIRECTION_LTR },
    { 1, touchgfx::LEFT, touchgfx::TEXT_DIRECTION_LTR },
    { 3, touchgfx::LEFT, touchgfx::TEXT_DIRECTION_LTR },
    { 3, touchgfx::RIGHT, touchgfx::TEXT_DIRECTION_LTR },
    { 1, touchgfx::LEFT, touchgfx::TEXT_DIRECTION_LTR },
    { 1, touchgfx::LEFT, touchgfx::TEXT_DIRECTION_LTR },
    { 2, touchgfx::LEFT, touchgfx::TEXT_DIRECTION_LTR },
    { 2, touchgfx::RIGHT, touchgfx::TEXT_DIRECTION_LTR },
    { 1, touchgfx::LEFT, touchgfx::TEXT_DIRECTION_LTR },
    { 1, touchgfx::LEFT, touchgfx::TEXT_DIRECTION_LTR },
    { 0, touchgfx::LEFT, touchgfx::TEXT_DIRECTION_LTR },
    { 0, touchgfx::RIGHT, touchgfx::TEXT_DIRECTION_LTR }
};

TEXT_LOCATION_FLASH_PRAGMA
const touchgfx::TypedText::TypedTextData* const typedTextDatabaseArray[] TEXT_LOCATION_FLASH_ATTRIBUTE = {
    typedText_database_DEFAULT
};

namespace TypedTextDatabase
{
const touchgfx::TypedText::TypedTextData* getInstance(touchgfx::LanguageId id)
{
    return typedTextDatabaseArray[id];
}

uint16_t getInstanceSize()
{
    return sizeof(typedText_database_DEFAULT) / sizeof(touchgfx::TypedText::TypedTextData);
}

const touchgfx::Font** getFonts()
{
    return touchgfx_fonts;
}

const touchgfx::Font* setFont(touchgfx::FontId fontId, const touchgfx::Font* font)
{
    const touchgfx::Font* old = touchgfx_fonts[fontId];
    touchgfx_fonts[fontId] = font;
    return old;
}

void resetFont(touchgfx::FontId fontId)
{
    switch (fontId)
    {
    case 0:
        touchgfx_fonts[0] = &(getFont_vector_Technology_Bold_96());
        break;
    case 1:
        touchgfx_fonts[1] = &(getFont_Technology_Bold_17_4bpp());
        break;
    case 2:
        touchgfx_fonts[2] = &(getFont_vector_Technology_Bold_36());
        break;
    case 3:
        touchgfx_fonts[3] = &(getFont_vector_Technology_Bold_24());
        break;
    case 4:
        touchgfx_fonts[4] = &(getFont_Technology_Bold_16_4bpp());
        break;
    case 5:
        touchgfx_fonts[5] = &(getFont_Technology_Bold_20_4bpp());
        break;
    case 6:
        touchgfx_fonts[6] = &(getFont_Technology_Bold_24_4bpp());
        break;
    case 7:
        touchgfx_fonts[7] = &(getFont_Technology_Bold_22_4bpp());
        break;
    }
}
} // namespace TypedTextDatabase
