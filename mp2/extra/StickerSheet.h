#include <iostream>
#include <string>
#include <algorithm>
#include "Image.h"

namespace cs225
{
    class StickerSheet
    {
    public:
        StickerSheet(const Image &picture, unsigned max);
        ~StickerSheet();
        void cleanup();
        StickerSheet(const StickerSheet &other);
        const StickerSheet & operator=(const StickerSheet &other);
        void changeMaxStickers(unsigned max);
        int addSticker(Image &sticker, unsigned x, unsigned y);
        bool translate(unsigned index, unsigned x, unsigned y);
        void removeSticker (unsigned index);
        Image* getSticker (unsigned index) const;
        Image render () const;
    private:
        unsigned* _StickerX;
        unsigned* _StickerY;
        Image _basePicture;
        Image** _arrayStickers;
        unsigned _max;
    };
    
} // namespace cs225
