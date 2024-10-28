#include "StickerSheet.h"
#include "Image.h"


using namespace std;
namespace cs225{
    StickerSheet::StickerSheet(const Image &picture, unsigned max){
        _basePicture = picture;
        _max=max;
        _arrayStickers = new Image*[_max];
        for (unsigned i = 0; i<max; i++) _arrayStickers[i]=nullptr;
        _StickerX = new unsigned[_max];
        _StickerY = new unsigned[_max];
        
    }

    StickerSheet::~StickerSheet(){
        cleanup();
    }

    void StickerSheet::cleanup(){
        for(unsigned int i=0;i<this->_max;i++){
            if(_arrayStickers[i]!=nullptr){
                //delete _arrayStickers[i];
                _arrayStickers[i]=nullptr;
            }
        }
        delete[] _StickerX;
        delete[] _StickerY;
        delete[] _arrayStickers;
        _StickerX=nullptr;
        _StickerY=nullptr;
        _arrayStickers=nullptr;
    }

    StickerSheet::StickerSheet(const StickerSheet &other){
        _basePicture = other._basePicture;
        _max=other._max;
        _arrayStickers = new Image*[_max];
        _StickerX = new unsigned[_max];
        _StickerY = new unsigned[_max];

        for(unsigned i = 0; i<_max; i++){
            _arrayStickers[i] = other._arrayStickers[i];
            _StickerX[i] = other._StickerX[i];
            _StickerY[i] = other._StickerY[i]; 
        }
    }

    const StickerSheet & StickerSheet::operator=(const StickerSheet &other){
        if(this==&other) return *this;

        cleanup();
        _basePicture = other._basePicture;
        _max=other._max;
        _arrayStickers = new Image*[_max];
        _StickerX = new unsigned[_max];
        _StickerY = new unsigned[_max];

        for(unsigned i = 0; i<_max; i++){
            _arrayStickers[i] = other._arrayStickers[i];
            _StickerX[i] = other._StickerX[i];
            _StickerY[i] = other._StickerY[i]; 
        }
        return *this;
    }

    void StickerSheet::changeMaxStickers(unsigned max){
        if(max==_max) return;

        Image** new_arrayStickers= new Image*[max];
        unsigned* new_StickerX = new unsigned[max];
        unsigned* new_StickerY = new unsigned[max];

        for(unsigned i=0; i<max; i++){
            new_StickerX[i] = (i<_max)?_StickerX[i] : 0;
            new_StickerY[i] = (i<_max)?_StickerY[i] : 0;
            new_arrayStickers[i] = (i<_max)? _arrayStickers[i]: nullptr;
        }

        cleanup();

        _max=max;
        _StickerX=new_StickerX;
        _StickerY=new_StickerY;
        _arrayStickers=new_arrayStickers;
    }

    int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y){
        for(unsigned i=0; i<_max; i++){
            if(_arrayStickers[i]==nullptr){
                _arrayStickers[i] = &sticker;
                _StickerX[i]=x;
                _StickerY[i]=y;
                return i;
            }
        }
        return -1;
    }

    bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
        if(index>=_max||_arrayStickers[index]==nullptr) return false;
        _StickerX[index]=x;
        _StickerY[index]=y;
        return true;
    }

    void StickerSheet::removeSticker(unsigned index){
        if(index>=_max||_arrayStickers[index]==nullptr) return;
        //delete _arrayStickers[index];
        _arrayStickers[index]= nullptr;
    }

    Image* StickerSheet::getSticker (unsigned index) const{
        if(index>=_max||_arrayStickers[index]==nullptr) return nullptr;
        return _arrayStickers[index];
    }

    Image StickerSheet::render() const{
        // get the output image size
        unsigned new_w = _basePicture.width();
        unsigned new_h = _basePicture.height();
        unsigned temp_w, temp_h; 
        for(unsigned i=0; i<_max; i++){
            if(!_arrayStickers[i]) continue;
            temp_w=_arrayStickers[i]->width()+_StickerX[i];
            temp_h=_arrayStickers[i]->height()+_StickerY[i];
            new_h = (temp_h>new_h)? temp_h : new_h;
            new_w = (temp_w>new_w)? temp_w : new_w;
        }

        Image outputImage(new_w,new_h);
        // render base image
        Image basePicture=_basePicture;
        for(unsigned int x=0; x<_basePicture.width(); x++){
            for (unsigned int y=0;y<_basePicture.height(); y++){
                HSLAPixel* pixelPtr = outputImage.getPixel(x,y);
                *pixelPtr = *(basePicture.getPixel(x,y));
            }
        }
        // render stickers
        for(unsigned i=0; i<_max; i++){
            if(!_arrayStickers[i]) continue;
            Image* stickerNow=_arrayStickers[i];
            for(unsigned x=0; x<_arrayStickers[i]->width(); x++){
                for(unsigned y=0; y<_arrayStickers[i]->height(); y++){
                    HSLAPixel* pixelPtr=outputImage.getPixel(x+_StickerX[i],y+_StickerY[i]);
                    HSLAPixel* newPixel=stickerNow->getPixel(x,y);
                    if(newPixel->a) *pixelPtr = *newPixel;
                }
            }
        }
        return outputImage;
    }
} // namespace cs225
