/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
#include "sourceimage.h"
#include "kdtree.h"

using namespace std;

Point<3> convertToLAB(HSLAPixel pixel) {
    Point<3> result(pixel.h/360, pixel.s, pixel.l);
    return result;
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    if(theTiles.size()==0||theSource.getRows()==0||theSource.getColumns()==0) return NULL;
    MosaicCanvas* newMosaicCanvas = new MosaicCanvas(theSource.getRows(),theSource.getColumns());
    vector<Point<3>> pixels(theTiles.size());
    map<Point<3>,int> tile_avg_map;
    for(size_t i=0;i<theTiles.size();i++){
        pixels[i]=convertToLAB(theTiles[i].getAverageColor());
        tile_avg_map[pixels[i]]=i;
    }
    KDTree<3> tree(pixels);
    //tree.printTree();
    for(int row=0;row<theSource.getRows();row++){
        for(int column=0;column<theSource.getColumns();column++){
            TileImage* match=get_match_at_idx(tree,tile_avg_map,theTiles,theSource,row,column);
            newMosaicCanvas->setTile(row,column,match);
        }
    }
    return newMosaicCanvas;
}

TileImage* get_match_at_idx(const KDTree<3>& tree,
                                  map<Point<3>, int> tile_avg_map,
                                  vector<TileImage>& theTiles,
                                  const SourceImage& theSource, int row,
                                  int col)
{
    // Create a tile which accurately represents the source region we'll be
    // using
    HSLAPixel avg = theSource.getRegionColor(row, col);
    Point<3> avgPoint = convertToLAB(avg);
    Point<3> nearestPoint = tree.findNearestNeighbor(avgPoint);

    // Check to ensure the point exists in the map
    map< Point<3>, int >::iterator it = tile_avg_map.find(nearestPoint);
    //cout<<avgPoint<<"/"<<nearestPoint<<endl;
    if (it == tile_avg_map.end())
        cerr << "Didn't find " << avgPoint << " / " << nearestPoint << endl;

    // Find the index
    int index = tile_avg_map[nearestPoint];
    return &theTiles[index];

}
