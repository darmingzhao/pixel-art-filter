#include "twoDtree.h"
#include "util/RGBAPixel.h"
#include "util/PNG.h"

using namespace util;
using namespace std;

/* 
 * Demonstration of project functionality.
 * Reads Point data from external files.
 * Produces PNG images of the point sets.
 * Add more images with various prune paramters
 * as necessary.
 */
int main() {

	//read in images
	PNG origImg1;
	PNG origImg2;
	PNG origImg3;
	origImg1.readFromFile("images/starry-night.png");
	origImg2.readFromFile("images/mona-lisa.png");
	origImg3.readFromFile("images/hokusai.png");

	//build twoDtrees
	twoDtree t1(origImg1);
	twoDtree t2(origImg2);
	twoDtree t3(origImg3);

	//prune images
	//modify paramters to get different effects
	t1.prune(0.99, 8500);
	t2.prune(0.99, 8500);
	t3.prune(0.95, 8500);

	//render tree
	PNG pic1 = t1.render();
	PNG pic2 = t2.render();
	PNG pic3 = t3.render();

	//write to file
	pic1.writeToFile("images/output-starry-night.png");
	pic2.writeToFile("images/output-mona-lisa.png");
	pic3.writeToFile("images/output-hokusai.png");
	
	return 0;
}