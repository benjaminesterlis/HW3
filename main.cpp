#include "main.h"


#define CANT_ALLOC "allocation failure"
#define EXIT "Exiting...\n"
#define SHARP "#"
#define LOCAL "Nearest images using local descriptors:\n"
#define GLOBAL "Nearest images using global descriptors:\n"
#define ENTER_IMAGE "Enter a query image or # to terminate:\n"
#define N_FEATURE_FAILURE "invalid number of features\n"
#define ENTER_N_FEATURE "Enter number of features:\n"
#define N_BINS_FAILURE "invalid nubmer of bins\n"
#define ENTER_N_BINS "Enter number of bins:\n"
#define ENTER_IMG_SUFFIX "Enter images suffix:\n"
#define N_IMG_FAILURE "invalid number of images\n"
#define ENTER_N_IMG "Enter number of images:\n"
#define ENTER_IMG_PREFIX "Enter images prefix:\n"
#define ENTER_DIR_PATH "Enter images directory path:\n"
#define CURRENT_IMAGE "Enter a query image or # to termiante:\n"
#define STRING "%s" //overkill

#define error_msg_ret(msg,ret)							\
 	do {												\
 		printf("An error occurred - %s\n",(msg));		\
 		return (ret);									\
 	} while (0)	

int main(void)
{
	int err_flag = 0;
	SPBPQueue *kClosest;
	SPBPQueue *best_queue;
	SPPoint*** hist;
	SPPoint*** sift; 
	SPPoint **query_hist;
	SPPoint **query_sift;
	int min_index;
	char img_dir_path[1024];
	char img_prefix[1024];
	char img_suffix[1024];
	char input_image[1024];
	char current_image[1024];
	SP_BPQUEUE_MSG SPBQueue_MGS;
	int nImg;
	int nBins;
	int nFeaturesToExtract;
	int *nFeatures;
	int nFeaturesQ;
	int i,j;
	double l;
	int *Img_Indexes;
	int *current_feature_best_k;
	int k = 5; /***** how many indexes to save,deafult is 5 *****/

	//scanning from user	
	printf(ENTER_DIR_PATH);
	scanf(STRING,img_dir_path);

	printf(ENTER_IMG_PREFIX);
	scanf(STRING,img_prefix);

	printf(ENTER_N_IMG);
	scanf("%d",&nImg);
	if ( nImg < 1)
		error_msg_ret(N_IMG_FAILURE,-1);

	
	printf(ENTER_IMG_SUFFIX);
	scanf(STRING,img_suffix);

	printf(ENTER_N_BINS);
	scanf("%d",&nBins);
	if(nBins < 1 || nBins > 255)
		error_msg_ret(N_BINS_FAILURE,-1);

	printf(ENTER_N_FEATURE);
	scanf("%d",&nFeaturesToExtract);
	if( nFeaturesToExtract < 1)
		error_msg_ret(N_FEATURE_FAILURE,-1);

	if ((nFeatures = (int *)malloc(sizeof(int) * nImg+1)) == NULL){
		err_flag = 1;
		goto exit;
	}


	// calculate RGB histogram
	if ((hist = (SPPoint ***)malloc(sizeof(SPPoint **) * nImg)) == NULL){
		err_flag = 1;
		goto sec3;
	}

	if( (sift = (SPPoint ***)malloc(sizeof(SPPoint **) * nImg)) == NULL){
		err_flag = 1;
		goto sec2;
	}

	for (i = 0; i < nImg; ++i){
		sprintf(input_image, "%s%s%d%s", img_dir_path, img_prefix,i, img_suffix);
		hist[i] = spGetRGBHist(input_image, i, nBins);
		sift[i] = spGetSiftDescriptors(input_image, i, nFeaturesToExtract, &nFeatures[i]);
	}

	printf(CURRENT_IMAGE);
	scanf(STRING, current_image);
	
	if ((kClosest = spBPQueueCreate(k)) == NULL){
		err_flag = 1;
		goto sec3;
	}

	while(strcmp(current_image,SHARP) != 0){
		//calc for global descriptor
		query_hist = spGetRGBHist(current_image,nImg,nBins);

		for( i = 0; i < nImg; i++){
			l = spRGBHistL2Distance(query_hist,hist[i]);
			SPBQueue_MGS = spBPQueueEnqueue(kClosest,i, l);
			if (SP_BPQUEUE_SUCCESS != SPBQueue_MGS &&  SP_BPQUEUE_FULL != SPBQueue_MGS){
				err_flag = 1;
				goto sec4;
			}
		}

		// print for globar descriptor
		printf(GLOBAL);
		for (i = 0; i < k-1; ++i){
			min_index = spBPQueueMinValueIndex(kClosest);
			if(min_index == -1){
				err_flag = 1;
				goto sec4;
			}
			printf("%d, ", min_index);
			if(spBPQueueDequeue(kClosest) != SP_BPQUEUE_SUCCESS){
				err_flag = 1;
				goto sec4;
			} 
		}

		min_index = spBPQueueMinValueIndex(kClosest);
		if(min_index == -1){
			err_flag = 1;
			goto sec4;
		}

		printf("%d\n",min_index);
		if(spBPQueueDequeue(kClosest) != SP_BPQUEUE_SUCCESS){
			err_flag = 1;
			goto sec4;
		} 
		//for local descriptor
		query_sift = spGetSiftDescriptors(current_image, nImg,
												nFeaturesToExtract, &nFeaturesQ);

		//malloc for array of Img_indexes
		if ((Img_Indexes = (int*)calloc( nImg, sizeof(int))) == NULL){
			err_flag = 1;
			goto sec5;
		}

		//to get the best k indexes
		for(i = 0; i < nFeaturesQ; ++i){
			current_feature_best_k = spBestSIFTL2SquaredDistance(k,query_sift[i],
												sift, nImg, nFeatures); 
			for (j = 0; j < k; j++)
			{
				Img_Indexes[current_feature_best_k[j]]++;
			}
		}
		free(current_feature_best_k);
		if ((best_queue = spBPQueueCreate(k)) == NULL){
			err_flag = 1;
			goto sec6;
		}
		for(i = 0; i <nImg ; ++i){
			 SPBQueue_MGS = spBPQueueEnqueue(best_queue,i,k*nFeaturesQ - Img_Indexes[i]);
			 if (SP_BPQUEUE_SUCCESS != SPBQueue_MGS &&  SP_BPQUEUE_FULL != SPBQueue_MGS){
				err_flag = 1;
				goto sec7;
			}
		}

		//print local		
		printf(LOCAL);
		for (i = 0; i < k-1; ++i){
			min_index = spBPQueueMinValueIndex(best_queue);
			if(min_index == -1){
				err_flag = 1;
				goto sec7;
			}
			printf("%d, ",min_index);
			if(spBPQueueDequeue(best_queue) != SP_BPQUEUE_SUCCESS){
				err_flag = 1;
				goto sec7;
			} 
		}

		min_index = spBPQueueMinValueIndex(best_queue);
		if(min_index == -1){
			err_flag = 1;
			goto sec7;
		}
		printf("%d\n",min_index);
		if(spBPQueueDequeue(best_queue) != SP_BPQUEUE_SUCCESS){
			err_flag = 1;
			goto sec7;
		} 

		printf(CURRENT_IMAGE);
		scanf(STRING, current_image);
	}

	//free section
	sec7:
		spBPQueueDestroy(best_queue);
	sec6:
		free(Img_Indexes);
	sec5:
		free(query_sift);
	sec4:
		free(query_hist);
		spBPQueueDestroy(kClosest);
	sec3:
		for (i = nImg-1; i >= 0; --i)
			free(sift[i]);
		free(sift);//free all that inside
	sec2:
		for (i = nImg-1; i >= 0; --i)
			free(hist[i]);
		free(hist);//free all that inside
		free(nFeatures);
	exit:
	
	printf(EXIT);
	if (err_flag){
		error_msg_ret(CANT_ALLOC,-1);
		return -1;
	}
	return 0;
}