#ifndef _STATS_H
#define _STATS_H

#include "util/PNG.h"
#include "util/RGBAPixel.h"
#include <utility>
#include <vector>

using namespace std;
using namespace util;

class stats {
private:
	vector< vector< long >> sumRed;
	vector< vector< long >> sumGreen;
	vector< vector< long >> sumBlue;
	vector< vector< long >> sumsqRed;
	vector< vector< long >> sumsqGreen;
	vector< vector< long >> sumsqBlue;

	/* 
 	 * Returns the sums of all pixel values across the given color channel.
 	 * This function is used to compute the score of a rectangle.
 	 * @param channel is one of r, g, or b
 	 * @param ul is (x,y) of the upper left corner of the rectangle 
 	 * @param lr is (x,y) of the lower right corner of the rectangle
 	 * @return sum of all pixel values across the channel paramter
 	 */
	long getSum(char channel, pair<int,int> ul, pair<int,int> lr);

	/* 
	 * Returns the sums of squares of all pixel values across the given color channel.
	 * This function is used to compute the score of a rectangle.
	 * @param channel is one of r, g, or b
	 * @param ul is (x,y) of the upper left corner of the rectangle 
	 * @param lr is (x,y) of the lower right corner of the rectangle
	 * @return sum of squares of all pixel values across channel parameter
	 */
	long getSumSq(char channel, pair<int,int> ul, pair<int,int> lr);

public:
	/*
 	 * Constructor: 
 	 * Initalize the private vectors so that, for each color, entry
 	 * (x,y) is the cumulative sum of the color values from the (0,0)
 	 * to (x,y). Similarly, the sumSq vectors are the cumulative sum
 	 * of squares from origin (0,0) to (x,y).
	 * @param &im is reference to PNG image
	 */
	stats(PNG & im); 

	/*
	 * Given a rectangle, compute its sum of squared deviations from
	 * mean, over all color channels. This will be used to make splits
	 * when building trees.
	 * @param ul is (x,y) of the upper left corner of the rectangle
	 * @param lr is (x,y) of the upper right corner of the rectangle
	 * @return sum of squared deviations
	 */
	long getScore(pair<int,int> ul, pair<int,int> lr);

	/*
	 * Given a rectangle, return the average color value over the
	 * rectangle as a pixel. Each color component of the pixel is the
	 * average value of that component over the rectangle.
	 * @param ul is (x,y) of the upper left corner of the rectangle
	 * @param lr is (x,y) of the upper right corner of the rectangle
	 * @return RBGAPixel with average r, g, b color values
	 */
	RGBAPixel getAvg(pair<int,int> ul, pair<int,int> lr);

	/*
	 * Given a rectangle, return the number of pixels in the rectangle.
	 * @param ul is (x,y) of the upper left corner of the rectangle
	 * @param lr is (x,y) of the upper right corner of the rectangle
	 * @return number of pixels in rectangle
	 */
	long rectArea(pair<int,int> ul, pair<int,int> lr);
};

#endif