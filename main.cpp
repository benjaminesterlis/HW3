#include "main.h"

int main(void)
{
	int err_flag = 0;
	SPBQueue *kCloses;
	SPPoint*** hist;
	SPPoint*** sift; 
	char img_dir_path[1024];
	char img_prefix[1024];
	char img_suffix[1024];
	char input_image[1024];
	char *current_image[1024];
	char *SPBQueue_MGS[1024];
	int nImg;
	int nBins;
	int nFeaturesToExtract;
	int *nFeatures;
	int i;
	int *indexes;
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

	if ((nFeatures = (int *)malloc(sizeof(int) * nImg+1)) == NULL)
	{
		err_flag = 1;
		goto exit;
	}


	// calculate RGB histogram
	if ((hist = (SPPoint ***)malloc(sizeof(SPPoint **) * nImg)) == NULL)
	{
		err_flag = 1;
		goto sec3;
	}


	if( (sift = (SPPoint ***)malloc(sizeof(SPPoint **) * nImg)) == NULL)
	{
		err_flag = 1;
		goto sec2;
	}

	for (i = 0; i < nImg; ++i)
	{
		sprintf(input_image, "%s%s%d.%s", img_dir_path, img_prefix,i, img_suffix);
		hist[i] = spGetRGBHist(input_image, i, nBins);
		sift[i] = spGetSiftDescriptors(input_image, i, nFeaturesToExtract, nFeatures[i]);
	}

	
	printf("Enter a query image or # to terminate:\n");
	scantf("%s",&current_image);
	

	if ((kCloses = spBPQueueCreate(5)) == NULL)
	{
		err_flag = 1;
		goto sec3;
	}

	while(strcmp(current_image,SHARP) != 0)
	{
		SPPoint **query_hist = spGetRGBHist(current_image,nImg,nBins);
		for( i = 0; i < nImg; i++)
		{
			SPBQueue_MGS = spBPQueueEnqueue(kCloses,i,spRGBHistL2Distance(query_hist,hist[i]));
			if (SP_BPQUEUE_SUCCESS != SPBQueue_MGS)
			{
				err_flag = 1;
				goto sec4;
			}
		}
		printf(GLOBAL);

		for (i = 0; i < kClosest-1; ++i)
		{
			printf("%d, ",(int)spBPQueueMinValue(length_l2));
			spBPQueueDequeue(length_l2);
		}
		printf("%d\n",(int)spBPQueueMinValue(length_l2));
		spBPQueueDequeue(length_l2);

	}


	//free section
	sec4:
		spBPQueueDestroy(kCloses);
	sec3:
		free(sift);
	sec2:
		free(hist);
	sec1:
		free(nFeatures);

	exit:
	
	printf(EXIT);
	if (err_flag)
	{
		error_msg(CANT_ALLOC);
		return -1;
	}
	return 0;
}