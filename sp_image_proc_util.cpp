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

#define report_error(str)\
 	do { 												\
 		printf("Error: %s, line %d\n",(str), __LINE__); \
 		return NULL;								 	\
 	} while(0)

#define report_error_exit(str) 							\
 	do { 												\
 		printf("Error: %s, line %d\n",(str), __LINE__); \
 		exit(-1); 										\
 	} while(0)

#define report_error_ret(str,ret)						\
 	do { 												\
 		printf("Error: %s, line %d\n",(str), __LINE__); \
 		return (ret); 									\
 	} while(0)

SPPoint** spGetRGBHist(const char* str,int imageIndex, int nBins){

	int i;
	Mat src;
	Mat b_hist, g_hist, r_hist;
	// Set the ranges ( for B,G,R) )
	float range[] = { 0, 256 };
	const float* histRange = { range };
	double* data;
	SPPoint** Histogram;

	if ( str == NULL || nBins <= 0)
		report_error("nBins must be positive integer");

	if ((Histogram = (SPPoint**)malloc(sizeof(SPPoint*)*3)) == NULL )
		report_error("can't allocate memory for Histogram");

	//Load image
	if((src = imread(str,CV_LOAD_IMAGE_COLOR)).empty() )
		report_error("could't load image");

	/// Separate the image in 3 places ( B, G and R )
	std::vector<Mat> bgr_planes;
	split(src, bgr_planes);

	// calc 3 Mat's of B G & R
	calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &nBins, &histRange);
	calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &nBins, &histRange);
	calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &nBins, &histRange);

	if (!(data = (double *)malloc(sizeof(double)*nBins)))
		report_error("can't allocate memory for Histogram data");

	//for red
	for (i = 0; i < r_hist.rows; ++i)
		data[i] = cvRound(r_hist.at<float>(i,0));
	Histogram[0] = spPointCreate(data, r_hist.rows, imageIndex);

	//for green
	for (i = 0; i < g_hist.rows; ++i)
		data[i] = cvRound(g_hist.at<float>(i,0));	
	Histogram[1] = spPointCreate(data, g_hist.rows, imageIndex);

	//for blue
	for (i = 0; i < b_hist.rows; ++i)
		data[i] = cvRound(b_hist.at<float>(i,0));
	Histogram[2] = spPointCreate(data, b_hist.rows, imageIndex);

	free(data);

	return Histogram;
}

double spRGBHistL2Distance(SPPoint** rgbHistA, SPPoint** rgbHistB)
{
	int i;
	double ret = 0;
	if (rgbHistB == NULL || rgbHistA == NULL)
		report_error_ret("rgbHistA or rgbHistB is NULL", -1);
	for( i = 0; i < 3; ++i)
		ret += (1/3)*spPointL2SquaredDistance(rgbHistA[i], rgbHistB[i]);
	return ret;
}

SPPoint** spGetSiftDescriptors(const char* str, int imageIndex, int nFeaturesToExtract, int *nFeatures)
{
	Mat src, ds1;
	std::vector<KeyPoint> kp1;
	int i, j;
	double data[128];
	SPPoint** SIFT;

	if (!str)
		report_error("the path give to the function is NULL");
	if((src = imread(str,CV_LOAD_IMAGE_COLOR)).empty())
		report_error("could't load image");
	if (!nFeatures)
		report_error("Features is NULL pointer");
	if (nFeaturesToExtract <= 0)
		report_error("nFeaturesToExtract isn't positive");

	Ptr<xfeatures2d::SiftDescriptorExtractor> detect =
			xfeatures2d::SIFT::create(nFeaturesToExtract);

	detect->detect(src, kp1, Mat());
	detect->compute(src, kp1, ds1);

	*nFeatures = ds1.rows;

	if ((SIFT = (SPPoint**)malloc(sizeof(SPPoint*)* (*nFeatures))) == NULL )
		report_error("can't allocate memory for SIFT");

	for (i = 0; i < *nFeatures; ++i)
	{
		for (j = 0; j < 128 ; ++j)
			data[j] = cvRound(ds1.at<float>(j,i));
		SIFT[i] = spPointCreate(data,128,imageIndex);
	}
	return SIFT;
}

int* spBestSIFTL2SquaredDistance(int kClosest, SPPoint* queryFeature,
		SPPoint*** databaseFeatures, int numberOfImages,
		int* nFeaturesPerImage)
{







	return &0;
}