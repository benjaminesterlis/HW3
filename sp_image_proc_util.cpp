#include "sp_image_proc_util.h"
#include <opencv2/core.hpp>// Mat
#include <opencv2/imgcodecs.hpp>//imread
#include <opencv2/highgui.hpp> //imshow, drawKeypoints, waitKey
#include <opencv2/xfeatures2d.hpp>//SiftDescriptorExtractor
#include <opencv2/features2d.hpp>
#include <opencv2/imgproc.hpp>//calcHist
#include <vector>
#include <cstdio>
#include <iostream>

using namespace cv;

SPPoint** spGetRGBHist(const char* str,int imageIndex, int nBins){
	
	if ( str == NULL || nBins <= 0)
		return NULL;

	if (SPPoint** Histogram = (SPPoint**)malloac(sizeof(SPPoint*)*nBins)) == NULL )
		return NULL;

	Mat src;

	//Load image
	if(src = imread(str,VC_LOAD_IMAGE_COLOR)).empty()
		return NULL

	/// Separate the image in 3 places ( B, G and R )
	std::vector<Mat> bgr_planes;
	split(src, bgr_planes);

	// Set the ranges ( for B,G,R) )
	float range[] = { 0, nBins };
	const float* histRange = { range };
}

double spRGBHistL2Distance(SPPoint** rgbHistA, SPPoint** rgbHistB);

SPPoint** spGetSiftDescriptors(const char* str, int imageIndex, int nFeaturesToExtract, int *nFeatures);

int* spBestSIFTL2SquaredDistance(int kClosest, SPPoint* queryFeature,
		SPPoint*** databaseFeatures, int numberOfImages,
		int* nFeaturesPerImage);