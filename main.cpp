#include "main.h"
#include "sp_image_proc_util.h"
#include "main_aux.h"

#define report_error(str)								\
 	do { 												\
 		printf("Error: %s, line %d\n",(str), __LINE__); \
 		return -1; 										\
 	} while(0)

int main(void)
{
	int nImg;
	int nBins;
	int nFeatures;
	char dir_path[100];
	char img_pre[100];
	char img_suff[10];
	char input_img[212];
	int i;
	
	// if ( (dir_path = malloc(MAX_PATH*sizeof(char))) == NULL ) //we used MAX_PATH path's size is unknown
	// 	report_error("can't allocate memory for the path");

	printf("Enter images directory path:\n");
	scanf("%s",&dir_path);

	printf("Enter images prefix:\n");
	scanf("%s",&img_pre);

	printf("Enter number of images:\n")
	scanf("%d",&nImg);
	if (nImg < 1){
		printf("An error occurred - invalid number of images\n");
		return -1;
	}

	printf("Enter images suffix:\n");
	scanf("%s",&img_suff);

	printf("Enter number of bins:\n");
	scanf("%d",&nBins);

	if (nBins < 1){
		printf("An error occurred - invalid number of bins\n");
		return -1;
	}
	
	printf("Enter number of features:\n");
	scanf("%d",&nFeatures);
	if ( nFeatures < 1)
	{
		printf("An error occurred - invalid number of features\n");
		return -1;
	}

	for (i = 0; i < nImg; ++i)
	{
		sprintf(input_img, "%s.%s", img_pre, img_suff);

	}

	return 0;
}