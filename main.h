#include "sp_image_proc_util.h"
#include "main_aux.h"
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
 		printf("An error occurred - %s",msg);			\
 		return (ret);									\
 	} while (0)	
#define error_msg(msg)									\
 	do {												\
 		printf("An error occurred - %s",msg);			\									\
 	} while (0)	

#define CANT_ALLOC "allocation failure"
#define EXIT "Exiting...\n"
#define SHARP "#"
#define GLOBAL "Nearest images using global descriptors:\n"
