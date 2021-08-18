#include<stdio.h>
#include "sort.h"
int main(int argc, char *argv[]) {
	FILE *fp = fopen(argv[1], "r+"), *fp1;
	long long count = 0;
	char name[100000];
	int key = atoi(argv[3]);
	char mode = argv[2][0];
	printf("%d\n", key);
	printf("%c\n", mode);
	if(argv[1] == NULL && mode == 'm') {
		printf("Enter names of files to be merged\n");
		if(!scanf("%s", name)) {
			fprintf(stderr, "enter at least one file");
		}
		scanf("%s", name);
		fp = fopen(name, "r+");			
		while((scanf("%s", name)) != -1) {
			fp1 = fopen(name, "r");
			mergedtwwosortedfiles(fp, fp1);			
		}
		printf("SORTED file in sorted.txt\n");
	}		
	if(!fp) 
	   fprintf(stderr, "file not present in memory");
	else if (mode == '\0')
		fprintf(stderr, "usage: filename mode value");
	//else if(atoi(argv[3]) == '\0')
		//value = 0;	
	else {
		count = splitfile(fp);
		printf("%lld\n", count);
		sortallfiles(count, mode, key);
		mergeallfiles(count, mode, key);
		printf("SORTED file in sorted.txt\n");
		//mergesort();
	}
	return 0;
}		
		     		
	       
	     
