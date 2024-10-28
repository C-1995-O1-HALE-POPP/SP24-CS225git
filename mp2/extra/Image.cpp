#include <iostream>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <math.h>
#include "cs225/PNG.h"
#include "Image.h"

using namespace std;

namespace cs225{
    void Image::lighten(){
        for(unsigned int x=0; x<this->width(); x++){
            for (unsigned int y=0;y<this->height(); y++){
                HSLAPixel* pixptr = this->getPixel(x,y);
                double newl= pixptr->l+.1;
                pixptr->l = (newl>1.0) ? 1.0 : newl;
            }
        }
    }

    void Image::lighten(double amount){
        for(unsigned int x=0; x<this->width(); x++){
            for (unsigned int y=0;y<this->height(); y++){
                HSLAPixel* pixptr = this->getPixel(x,y);
                double newl= pixptr->l+amount;
                pixptr->l = (newl>1.0) ? 1.0 : newl;
            }
        }
    }

    void Image::darken(){
        double amount = .1;
        for(unsigned int x=0; x<this->width(); x++){
            for (unsigned int y=0;y<this->height(); y++){
                HSLAPixel* pixptr = this->getPixel(x,y);
                double newl= pixptr->l-amount;
                pixptr->l = (newl<0) ? 0 : newl;
            }
        }
    }

    void Image::darken(double amount){
        for(unsigned int x=0; x<this->width(); x++){
            for (unsigned int y=0;y<this->height(); y++){
                HSLAPixel* pixptr = this->getPixel(x,y);
                double newl= pixptr->l-amount;
                pixptr->l = (newl<0) ? 0 : newl;
            }
        }
    }

    void Image::saturate(){
        for(unsigned int x=0; x<this->width(); x++){
            for (unsigned int y=0;y<this->height(); y++){
                HSLAPixel* pixptr = this->getPixel(x,y);
                double news= pixptr->s+.1;
                pixptr->s = (news>1.0) ? 1.0 : news;
            }
        }
    }

    void Image::saturate(double amount){
        for(unsigned int x=0; x<this->width(); x++){
            for (unsigned int y=0;y<this->height(); y++){
                HSLAPixel* pixptr = this->getPixel(x,y);
                double news= pixptr->s+amount;
                pixptr->s = (news>1.0) ? 1.0 : news;
            }
        }
    }

    void Image::desaturate(){
        for(unsigned int x=0; x<this->width(); x++){
            for (unsigned int y=0;y<this->height(); y++){
                HSLAPixel* pixptr = this->getPixel(x,y);
                double news= pixptr->s-.1;
                pixptr->s = (news<.0) ? 0 : news;
            }
        }
    }

    void Image::desaturate(double amount){
        for(unsigned int x=0; x<this->width(); x++){
            for (unsigned int y=0;y<this->height(); y++){
                HSLAPixel* pixptr = this->getPixel(x,y);
                double news= pixptr->s-amount;
                pixptr->s = (news<0) ? 0 : news;
            }
        }
    }

    void Image::grayscale(){
        for(unsigned int x=0; x<this->width(); x++){
            for (unsigned int y=0;y<this->height(); y++){
                HSLAPixel* pixptr = this->getPixel(x,y);
                pixptr->s = 0;
            }
        }
    }

    void Image::rotateColor(double degrees){
        for(unsigned int x=0; x<this->width(); x++){
            for (unsigned int y=0;y<this->height(); y++){
                HSLAPixel* pixptr = this->getPixel(x,y);
                pixptr->h += degrees;
                if(pixptr->h>360) pixptr->h-=360;
                if(pixptr->h<0) pixptr->h+=360;
                
            }
        }
    }

    void Image::illinify(){
        double hueIlliOrg=11.0;
        double hueIlliBlue=216.0;
        for(unsigned int x=0; x<this->width(); x++){
            for (unsigned int y=0;y<this->height(); y++){
                HSLAPixel* pixptr = this->getPixel(x,y);
                if(abs(pixptr->h-hueIlliOrg)<abs(pixptr->h-hueIlliBlue)||        // base case
                    abs(pixptr->h-(360+hueIlliOrg))<abs(pixptr->h-hueIlliBlue))   // for situations like h=359
                    pixptr->h = hueIlliOrg;
                else pixptr->h = hueIlliBlue;
            }
        }
    }

    void Image::scale(unsigned w, unsigned h){
        // Factor = old/new, new(X,Y)=old(x,y)*Factor
        // so if Factor < 1, expand; factor>1, shrink
        double FactorX = (double)width()/(double)w;
        double FactorY = (double)height()/(double)h;
        double actualFactor = std::max(FactorX,FactorY); 

        unsigned actualX = (unsigned)(width()/actualFactor);
        unsigned actualY = (unsigned)(height()/actualFactor);

        PNG newImageData(actualX,actualY);
        if(actualFactor){
            for(unsigned int Xnew=0; Xnew<actualX; Xnew++){
                for(unsigned int Ynew=0; Ynew<actualY; Ynew++){
                    HSLAPixel* oldPixel = this->getPixel(
                        (unsigned)(Xnew*actualFactor), (unsigned)(Ynew*actualFactor));
                    HSLAPixel* newPixel=newImageData.getPixel(Xnew,Ynew);
                    *newPixel = *oldPixel;
                }
            }
        }
        
        this->resize(w,h);
        for(unsigned int Xnew=0; Xnew<w; Xnew++){
            for(unsigned int Ynew=0; Ynew<h; Ynew++){
                    HSLAPixel* newPixel=this->getPixel(Xnew,Ynew);
                    if (Xnew<actualX&&Ynew<actualY){
                        HSLAPixel* tempPixel=newImageData.getPixel(Xnew,Ynew);
                        *newPixel = *tempPixel;
                    }else{
                        *newPixel = HSLAPixel();
                    }
                    

            }
        }
    }

    void Image::scale(double factor){
        unsigned int w = factor*this->width();
        unsigned int h = factor*this->height();
        this->scale(w,h);
    }
}