#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <cmath>

#include "cs225/PNG.h"
#include "maptiles.h"
#include "mosaiccanvas.h"
#include "sourceimage.h"
#include "util/util.h"

using namespace std;
using namespace util;
using namespace cs225;

void makePhotoMosaic(const string& inFile, const string& tileDir, int numTiles,
                     int pixelsPerTile, const string& outFile);
map<Point<3>,string> getTiles(string tileDir);
bool hasImageExtension(const string& fileName);
Point<3> getAverageColor(PNG& png);
namespace opts
{
    bool help = false;
}

int main(int argc, const char** argv)
{
    string inFile = "";
    string tileDir = "mp5_pngs/";
    string numTilesStr = "100";
    string pixelsPerTileStr = "50";
    string outFile = "mosaic.png";

    OptionsParser optsparse;
    optsparse.addArg(inFile);
    optsparse.addArg(tileDir);
    optsparse.addArg(numTilesStr);
    optsparse.addArg(pixelsPerTileStr);
    optsparse.addArg(outFile);
    optsparse.addOption("help", opts::help);
    optsparse.addOption("h", opts::help);
    optsparse.parse(argc, argv);

    if (opts::help) {
        cout << "Usage: " << argv[0]
             << " background_image.png tile_directory/ [number of tiles] "
                "[pixels per tile] [output_image.png]"
             << endl;
        return 0;
    }

    if (inFile == "") {
        cout << "Usage: " << argv[0]
             << " background_image.png tile_directory/ [number of tiles] "
                "[pixels per tile] [output_image.png]"
             << endl;
        return 1;
    }

    makePhotoMosaic(inFile, tileDir, lexical_cast<int>(numTilesStr),
                    lexical_cast<int>(pixelsPerTileStr), outFile);

    return 0;
}

void makePhotoMosaic(const string& inFile, const string& tileDir, int numTiles,
                     int pixelsPerTile, const string& outFile)
{
    PNG inImage;
    inImage.readFromFile(inFile);
    SourceImage source(inImage, numTiles);
    map<Point<3>,string> tiles = getTiles(tileDir);

    if (tiles.empty()) {
        cerr << "ERROR: No tile images found in " << tileDir << endl;
        exit(2);
    }

    MosaicCanvas::enableOutput = true;
    MosaicCanvas* mosaic = mapTiles(source, tiles);
    cerr << endl;

    if (mosaic == NULL) {
        cerr << "ERROR: Mosaic generation failed" << endl;
        exit(3);
    }

    PNG result = mosaic->drawMosaic(pixelsPerTile);
    cerr << "Saving Output Image... ";
    result.writeToFile(outFile);
    cerr << "Done" << endl;
    delete mosaic;
}

map<Point<3>,string> getTiles(string tileDir)
{
#if 1
    if (tileDir[tileDir.length() - 1] != '/')
        tileDir += '/';

    vector<string> allFiles = get_files_in_dir(tileDir);
    sort(allFiles.begin(), allFiles.end());
    // rename the files
    vector<string> imageFiles;
    imageFiles.reserve(allFiles.size());
    for (size_t i = 0; i < allFiles.size(); i++)
        if (hasImageExtension(allFiles[i]))
            imageFiles.push_back(allFiles[i]);

    //vector<TileImage> images;
    //set<HSLAPixel> avgColors;
    // update: 
    map<Point<3>,string> tileFiles;
    for (size_t i = 0; i < imageFiles.size(); i++) {
        cerr << "\rLoading Tile Images... ("
             << (i + 1) << "/" << imageFiles.size()
             << ")" << string(20, ' ') << "\r";
        cerr.flush();
        
        PNG png;
        png.readFromFile(imageFiles.at(i));
        Point<3> curr=getAverageColor(png);
        if (tileFiles.find(curr)==tileFiles.end()) {
            tileFiles[curr]=imageFiles.at(i);
        }
    }
    cerr << "\rLoading Tile Images... ("
         << imageFiles.size() << "/" << imageFiles.size()
         << ")";
    cerr << "... " << tileFiles.size() << " unique images loaded" << endl;
    cerr.flush();
    
    return tileFiles;
#else
    PNG temp;
    vector<TileImage> tiles;
    *temp(0, 0) = RGBAPixel(0,   0,   0);   tiles.push_back(TileImage(temp));
    *temp(0, 0) = RGBAPixel(0,   0,   127); tiles.push_back(TileImage(temp));
    *temp(0, 0) = RGBAPixel(0,   0,   255); tiles.push_back(TileImage(temp));
    *temp(0, 0) = RGBAPixel(0,   127, 0);   tiles.push_back(TileImage(temp));
    *temp(0, 0) = RGBAPixel(0,   255, 0);   tiles.push_back(TileImage(temp));
    *temp(0, 0) = RGBAPixel(127, 0,   0);   tiles.push_back(TileImage(temp));
    *temp(0, 0) = RGBAPixel(255, 0,   0);   tiles.push_back(TileImage(temp));
    *temp(0, 0) = RGBAPixel(0,   127, 127); tiles.push_back(TileImage(temp));
    *temp(0, 0) = RGBAPixel(0,   255, 255); tiles.push_back(TileImage(temp));
    *temp(0, 0) = RGBAPixel(127, 0,   127); tiles.push_back(TileImage(temp));
    *temp(0, 0) = RGBAPixel(255, 0,   255); tiles.push_back(TileImage(temp));
    *temp(0, 0) = RGBAPixel(127, 127, 0);   tiles.push_back(TileImage(temp));
    *temp(0, 0) = RGBAPixel(255, 255, 0);   tiles.push_back(TileImage(temp));
    return tiles;
#endif
}

bool hasImageExtension(const string& fileName)
{
    size_t dotpos = fileName.find_last_of(".");
    if (dotpos == string::npos)
        return false;
    string ext = toLower(fileName.substr(dotpos + 1));
    return (ext == "bmp" || ext == "png" || ext == "jpg" || ext == "gif"
            || ext == "tiff");
}

Point<3> getAverageColor(PNG& png){
    double h_sin = 0, h_cos = 0, s = 0, l = 0;

    for (unsigned y = 0; y < png.height(); y++) {
        for (unsigned x = 0; x < png.width(); x++) {
            HSLAPixel & pixel = png.getPixel(x, y);
            double h_rad = pixel.h * M_PI / 180;
            h_sin += sin( h_rad );
            h_cos += cos( h_rad );
            s += pixel.s;
            l += pixel.l;
        }
    }

    unsigned numPixels = png.width() * png.height();

    Point<3> color;
    color[0] = atan2(h_sin, h_cos) * 180 / M_PI;
    if (color[0] < 0) {
        color[0] += 360;
    }
    color[0]=color[0]/360;
    color[1] = s / numPixels;
    color[2] = l / numPixels;
    return color;
}