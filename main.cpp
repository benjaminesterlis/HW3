#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/xfeatures2d.hpp>//SiftDescriptorExtractor
#include <opencv2/features2d.hpp>
#include <vector>
#include <opencv2/core.hpp>// Mat
#include <opencv2/imgcodecs.hpp>//imread
#include <opencv2/highgui.hpp> //imshow, drawKeypoints, waitKey
#include <cstdio>
#include <iostream>


#define error_msg_ret(msg,ret)							\
 	do {												\
 		printf("An error occurred - %s",msg);									\
 		return (ret);									\
 	} while (0)											\

int main()
{

	char img_dir_path[1024];
	char img_prefix[1024];
	char img_suffix[1024];
	char input_image[1024];
	int nImg;
	int nBins;
	int nFeatures;
	int i;
	
	//need to allocate every char arr and build a method which cleans them.
	
	printf("Enter images directory path:\n");
	scanf("%s",&img_dir_path);

	printf("Enter images prefix:\n");
	scanf("%s",&img_prefix);

	printf("Enter number of images:\n");
	scanf("%d",&nImg);
	if ( nImg < 1)
		error_msg_ret("invalid number of images\n",-1)

	printf("Enter images suffix:\n");
	scanf("%s",img_suffix);

	printf("Enter number of bins:\n");
	scanf("%s",&nBins);
	if(nBins < 1 || nBins > 255)
		error_msg_ret("invalid nubmer of bins\n",-1)

	pritnf("Enter number of features:\n");
	scanf("%d",&nFeatures);
	if( nFeatures < 1)
		error_msg_ret("invalid number of features\n",-1)

	for (i = 0; i < nImg; ++i)
	{
		sprintf(input_img, "%s%d.%s", img_prefix,i, img_suffix);

	}


	return 0;
}