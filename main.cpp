#include "main.h"

int main(void)
{
	SPPoint*** hist;
	SPPoint*** sift; 
	char img_dir_path[1024];
	char img_prefix[1024];
	char img_suffix[1024];
	char input_image[1024];
	int nImg;
	int nBins;
	int nFeaturesToExtract;
	int *nFeatures;
	int i;
	//need to allocate every char arr and build a method which cleans them.
	
	//scanning from user	
	printf("Enter images directory path:\n");
	scanf("%s",&img_dir_path);

	printf("Enter images prefix:\n");
	scanf("%s",&img_prefix);

	printf("Enter number of images:\n");
	scanf("%d",&nImg);
	if ( nImg < 1)
		error_msg_ret("invalid number of images\n",-1);

	
	printf("Enter images suffix:\n");
	scanf("%s",img_suffix);

	printf("Enter number of bins:\n");
	scanf("%s",&nBins);
	if(nBins < 1 || nBins > 255)
		error_msg_ret("invalid nubmer of bins\n",-1);

	pritnf("Enter number of features:\n");
	scanf("%d",&nFeaturesToExtract);
	if( nFeaturesToExtract < 1)
		error_msg_ret("invalid number of features\n",-1);

	if ((nFeatures = (int *)malloc(sizeof(int) * nImg)) == NULL)
	{
		error_msg_ret(N_Feature_Alloc_Error_MSG);
		goto sec1;
	}


	// calculate RGB histogram
	if ((hist = (SPPoint ***)malloc(sizeof(SPPoint **) * nImg)) == NULL)
	{
		error_msg(HIST_Alloc_Error_MSG);
		goto sec2;
	}


	if( (sift = (SPPoint ***)malloc(sizeof(SPPoint **) * nImg)) == NULL)
	{
		error_msg(SIFT_Alloc_Error_MSG)
		goto sec3;
	}
	
	for (i = 0; i < nImg; ++i)
	 {
		sprintf(input_image, "%s%s%d.%s", img_dir_path, img_prefix,i, img_suffix);
		hist[i] = spGetRGBHist(input_image, i, nBins);
		sift[i] = spGetSiftDescriptors(input_image, i, nFeaturesToExtract, nFeatures[i]);
	}




	//free section
	sec4:
	
	sec3:
	
	sec2:
		free(hist);
	sec1:
		free(nFeatures);

	return 0;
}