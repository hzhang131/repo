/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    int image_rows = theSource.getRows();
    int image_cols = theSource.getColumns();
    vector<Point<3>> theTiles_avg_color;
    map<Point<3>, TileImage*> lookup;
    MosaicCanvas* newCanvas = new MosaicCanvas(image_rows, image_cols);
    // construct a KDtree with the TileImage Vector
    // first we need to translate the tileimages into points.
    for (TileImage& tile: theTiles){
      LUVAPixel pixel = tile.getAverageColor();
      Point<3> converted = convertToXYZ(pixel);
      theTiles_avg_color.push_back(converted);
      lookup.insert({converted, (&tile)});
    }
    //Then construct a KDTree using that vector.
    KDTree<3> happytree718(theTiles_avg_color);

    for (int i = 0; i < image_rows; i++){
      for (int j = 0; j < image_cols; j++){
        LUVAPixel pixel = theSource.getRegionColor(i, j);
        Point<3> converted = convertToXYZ(pixel);
        //solve for the result pixel, then we may lookup the actual image based on the 3d point.
        Point<3> result = happytree718.findNearestNeighbor(converted);
        TileImage* new_tile = lookup[result];
        //fillin the MosaicCanvas with the new_tile.
        newCanvas -> setTile(i, j, new_tile);
      }
    }

    return newCanvas;
}
