#include "stats.h"
#include "math.h"

long stats::getSum(char channel, pair<int, int> ul, pair<int, int> lr) {

	/*
	 * There are four cases for the rectangle:
	 * It will either being at the origin, on the x-axis, on the y-axis, or in the xy quadrant.
	 * Depending on these cases we compute the sum based on the channel parameter.
	 */
	if (ul.first == 0) {
		if (ul.second == 0) {
			switch (channel) {
				case 'r': return sumRed[lr.first][lr.second];
				case 'g': return sumGreen[lr.first][lr.second];
				case 'b': return sumBlue[lr.first][lr.second];
				default : std::cout << "getSum: channel is invalid: " << channel << std::endl;
			}
		} else {
			switch (channel) {
				case 'r': return sumRed[lr.first][lr.second] - sumRed[lr.first][ul.second - 1];
				case 'g': return sumGreen[lr.first][lr.second] - sumGreen[lr.first][ul.second - 1];
				case 'b': return sumBlue[lr.first][lr.second] - sumBlue[lr.first][ul.second - 1];
				default : std::cout << "getSum: channel is invalid: " << channel << std::endl;
			}
		}
	} else {
		if (ul.second == 0) {
			switch (channel) {
				case 'r': return sumRed[lr.first][lr.second] - sumRed[ul.first - 1][lr.second];
				case 'g': return sumGreen[lr.first][lr.second] - sumGreen[ul.first - 1][lr.second];
				case 'b': return sumBlue[lr.first][lr.second] - sumBlue[ul.first - 1][lr.second];
				default : std::cout << "getSum: channel is invalid: " << channel << std::endl;
			}
		} else {
			switch (channel) {
				case 'r': return sumRed[lr.first][lr.second] - sumRed[lr.first][ul.second - 1] 
								 - (sumRed[ul.first - 1][lr.second] - sumRed[ul.first - 1][ul.second - 1]);
				case 'g': return sumGreen[lr.first][lr.second] - sumGreen[lr.first][ul.second - 1] 
								 - (sumGreen[ul.first - 1][lr.second] - sumGreen[ul.first - 1][ul.second - 1]);
				case 'b': return sumBlue[lr.first][lr.second] - sumBlue[lr.first][ul.second - 1] 
								 - (sumBlue[ul.first - 1][lr.second] - sumBlue[ul.first - 1][ul.second - 1]);
				default : std::cout << "getSum: channel is invalid: " << channel << std::endl;
			}
		}
	}

	return 0;
}

long stats::getSumSq(char channel, pair<int, int> ul, pair<int, int> lr) {

	/*
	 * There are four cases for the rectangle:
	 * It will either being at the origin, on the x-axis, on the y-axis, or in the xy quadrant.
	 * Depending on these cases we compute the sum squared based on the channel parameter.
	 */
	if (ul.first == 0) {
		if (ul.second == 0) {
			switch (channel) {
				case 'r': return sumsqRed[lr.first][lr.second];
				case 'g': return sumsqGreen[lr.first][lr.second];
				case 'b': return sumsqBlue[lr.first][lr.second];
				default : std::cout << "getSumSq: channel is invalid: " << channel << std::endl;
			}
		} else {
			switch (channel) {
				case 'r': return sumsqRed[lr.first][lr.second] - sumsqRed[lr.first][ul.second - 1];
				case 'g': return sumsqGreen[lr.first][lr.second] - sumsqGreen[lr.first][ul.second - 1];
				case 'b': return sumsqBlue[lr.first][lr.second] - sumsqBlue[lr.first][ul.second - 1];
				default : std::cout << "getSumSq: channel is invalid: " << channel << std::endl;
			}
		}
	} else {
		if (ul.second == 0) {
			switch (channel) {
				case 'r': return sumsqRed[lr.first][lr.second] - sumsqRed[ul.first - 1][lr.second];
				case 'g': return sumsqGreen[lr.first][lr.second] - sumsqGreen[ul.first - 1][lr.second];
				case 'b': return sumsqBlue[lr.first][lr.second] - sumsqBlue[ul.first - 1][lr.second];
				default : std::cout << "getSumSq: channel is invalid: " << channel << std::endl;
			}
		} else {
			switch (channel) {
				case 'r': return sumsqRed[lr.first][lr.second] - sumsqRed[lr.first][ul.second - 1] 
								 - (sumsqRed[ul.first - 1][lr.second] - sumsqRed[ul.first - 1][ul.second - 1]);
				case 'g': return sumsqGreen[lr.first][lr.second] - sumsqGreen[lr.first][ul.second - 1] 
								 - (sumsqGreen[ul.first - 1][lr.second] - sumsqGreen[ul.first - 1][ul.second - 1]);
				case 'b': return sumsqBlue[lr.first][lr.second] - sumsqBlue[lr.first][ul.second - 1] 
								 - (sumsqBlue[ul.first - 1][lr.second] - sumsqBlue[ul.first - 1][ul.second - 1]);
				default : std::cout << "getSumSq: channel is invalid: " << channel << std::endl;
			}
		}
	}

	return 0;
}

stats::stats(PNG &im) {

	//iterate through all pixels in PNG im
	for (unsigned int x = 0; x < im.width(); x++) {
		long sumR = 0;
		long sumB = 0;
		long sumG = 0;
		
		long sumSqR = 0;
		long sumSqB = 0;
		long sumSqG = 0;

		vector<long> columnR;
		vector<long> columnB;
		vector<long> columnG;
		vector<long> columnSqR;
		vector<long> columnSqB;
		vector<long> columnSqG;

		for (unsigned int y = 0; y < im.height(); y++) {
			if (x == 0) {
				//compute sums for first column
				sumR += im.getPixel(0, y)->r;
				sumB += im.getPixel(0, y)->b;
				sumG += im.getPixel(0, y)->g;
				
				sumSqR += pow(im.getPixel(0, y)->r, 2);
				sumSqB += pow(im.getPixel(0, y)->b, 2);
				sumSqG += pow(im.getPixel(0, y)->g, 2);
			} else {
				//compute sums for other columns
				if (y == 0) {
					//compute first sum in column
					sumR = im.getPixel(x, 0)->r + sumRed[x - 1][0];
					sumB = im.getPixel(x, 0)->b + sumBlue[x - 1][0];
					sumG = im.getPixel(x, 0)->g + sumGreen[x - 1][0];
				
					sumSqR = pow(im.getPixel(x, 0)->r, 2) + sumsqRed[x - 1][0];
					sumSqB = pow(im.getPixel(x, 0)->b, 2) + sumsqBlue[x - 1][0];
					sumSqG = pow(im.getPixel(x, 0)->g, 2) + sumsqGreen[x - 1][0];
				} else {
					//compute all other sums in column
					sumR += im.getPixel(x, y)->r + (sumRed[x - 1][y] - sumRed[x - 1][y - 1]);
					sumB += im.getPixel(x, y)->b + (sumBlue[x - 1][y] - sumBlue[x - 1][y - 1]);
					sumG += im.getPixel(x, y)->g + (sumGreen[x - 1][y] - sumGreen[x - 1][y - 1]);
				
					sumSqR += pow(im.getPixel(x, y)->r, 2) + (sumsqRed[x - 1][y] - sumsqRed[x - 1][y - 1]);
					sumSqB += pow(im.getPixel(x, y)->b, 2) + (sumsqBlue[x - 1][y] - sumsqBlue[x - 1][y - 1]);
					sumSqG += pow(im.getPixel(x, y)->g, 2) + (sumsqGreen[x - 1][y] - sumsqGreen[x - 1][y - 1]);
				}
			}

			//push all sums to corresponding spot in rectangle
			columnR.push_back(sumR);
			columnB.push_back(sumB);
			columnG.push_back(sumG);
			columnSqR.push_back(sumSqR);
			columnSqB.push_back(sumSqB);
			columnSqG.push_back(sumSqG);
		}

		//push column to corresponding x value
		sumRed.push_back(columnR);
		sumBlue.push_back(columnB);
		sumGreen.push_back(columnG);
		sumsqRed.push_back(columnSqR);
		sumsqBlue.push_back(columnSqB);
		sumsqGreen.push_back(columnSqG);
	}
}

long stats::getScore(pair<int, int> ul, pair<int, int> lr) {
	
	//compute area of rectangle and score values for each color in the rectangle
	long area = rectArea(ul, lr);
	long sumRed = getSumSq('r', ul, lr) - (pow(getSum('r', ul, lr), 2) / area);
	long sumGreen = getSumSq('g', ul, lr) - (pow(getSum('g', ul, lr), 2) / area);
	long sumBlue = getSumSq('b', ul, lr) - (pow(getSum('b', ul, lr), 2) / area);
	
	//return total
	return sumRed + sumGreen + sumBlue;
}

RGBAPixel stats::getAvg(pair<int, int> ul, pair<int, int> lr) {
	
	//compute area of rectangle and average color values for that rectangle
	long area = rectArea(ul, lr);
	long avgRed = getSum('r', ul ,lr) / area;
	long avgGreen = getSum('g', ul, lr) / area;
	long avgBlue = getSum('b', ul, lr) / area;
	
	//return an RGBAPixel with those average color values
	return RGBAPixel(avgRed, avgGreen, avgBlue);
}

long stats::rectArea(pair<int, int> ul, pair<int, int> lr) {
	
	//compute number of squares in rectangle (taking into account 0 index cases)
	return (lr.first - ul.first + 1) * (lr.second - ul.second + 1);
}