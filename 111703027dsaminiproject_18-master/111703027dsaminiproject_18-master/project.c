#include<stdio.h>
#include "sort.h"
int main(int argc, char *argv[]) {
	FILE *fp, *fp1, *fp2, *fpo, *fpe, *fpf;
	long long count = 0;
	int key;
	char name[100000];
	char mode = argv[1][0];
	if(mode == 'b' || mode == 'd' || mode == 'k' || mode == 'm' || mode == 'n' || mode == 'i' || mode == 'r' || mode == 'u' 	|| mode == 't') {
		if(mode == 'k')
			key= atoi(argv[3]);
		else
			key = 0;	
		if(mode == 'm') {
			fpf = fopen("sorted.txt", "w");
			fp1 = fopen(argv[2], "r");
			if(!fp1) {
				fprintf(stderr, "file not present or incorrect file name\n");
				exit(1);
			}
			if(!argv[3]) {
				copyfile(fpf, fp1);
				printf("SORTED file in sorted.txt\n");
				fclose(fpf);
				fclose(fp1);
			}
			else {
				fp2 = fopen(argv[3], "r");
				if(!fp2) {
					fprintf(stderr, "file not present or incorrect file name\n");
					exit(1);
				}
				fpo = fopen("odd.txt", "w");
				mergedtwwosortedfiles(fp1, fp2, fpo);
				fclose(fp1);
				fclose(fp2);
				fclose(fpo);
				count = 4;	
				while(argv[count]) {
					if(count % 2 == 0) {
						fpe = fopen("even.txt", "w");
						fpo = fopen("odd.txt", "r");
						fp1 = fopen(argv[count], "r");
						if(!fp1) {
							fprintf(stderr, "file not present or incorrect file name\n");
							exit(1);
						}	
						mergedtwwosortedfiles(fp1, fpo, fpe);
						fclose(fpo);
						fclose(fpe);
						fclose(fp1);
					}
					else {
						fpe = fopen("even.txt", "r");
						fpo = fopen("odd.txt", "w");
						fp1 = fopen(argv[count], "r");
						if(!fp1) {
							fprintf(stderr, "file not present or incorrect file name\n");
							exit(1);
						}	 	
						mergedtwwosortedfiles(fp1, fpe, fpo);
						fclose(fpo);
						fclose(fpe);
						fclose(fp1);	
					}
					count++;
				}
				if(count % 2 == 0) {
					fpo = fopen("odd.txt", "r");
					copyfile(fpf, fpo);
					fclose(fpo);
					fclose(fpf);
				}
				else {	
					fpe = fopen("even.txt", "r");
					copyfile(fpf, fpe);
					fclose(fpe);
					fclose(fpf);	
				}	
				printf("SORTED file in sorted.txt\n");
				remove("odd.txt");
				remove("even.txt");
			}
		}
		else {	
			fp = fopen(argv[2], "r+");
			if(!fp) {
				fprintf(stderr, "file not present in current folder or in memory\n"); 			
				exit(1);
			}
			count = splitfile(fp);
			sortallfiles(count, mode, key);
			mergeallfiles(count, mode, key);
			fclose(fp);
			printf("SORTED file in sorted.txt\n");
			return 0;
		}	
	}
	else {
		fprintf(stderr, "enter a valid sorting mode\n");
		exit(1);
	}
	return 0;
}						
	       
	     
