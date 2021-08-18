#define MAX 100000
#define MAX1 100000
#include "sort.h"

int splitfile(FILE *fp) {
	int count = 1, i = 10000, j = 0;
	FILE *fps;	
	char ch = '\0';
	while(1) {
		i = 10000;
		int is_done = 0;
		char name[1000000] = { 0 };
		sprintf(name, "file%d.txt", j);
		fps = fopen( name, "w");
		while(i--) {
			is_done = 0;
		 	while(1) {
		 		if(!fread(&ch, 1, 1, fp)) {
		 			is_done = 1;
		 			break;
		 		}
		 		if(ch == '\n')
		 			break;
		 		fwrite(&ch, 1, 1, fps);
		 	}
		 	fwrite("\n", 1, 1, fps);
		 	if(is_done == 1)
		 		break;
		 }
		 if(is_done == 1)
		 	break;
		 if(fread(&ch, 1, 1, fp)) {
		 	j++;
		 } else {
		 	break;
		 }
		 count++;
		 fclose(fps);
	}
	return count;
}

void sortallfiles(long long count, char mode) {
	int i = 0, j = 0;
	for(i = 0; i < count; i++) {
		FILE *fps;
		char name[1000000] = { 0 };
		sprintf(name, "file%d.txt", i);
		fps = fopen( name, "r");
		sortsinglefile(fps, i, mode);
		
	}	
}

void sortsinglefile(FILE *fps, long long no, char mode) {
	char *lines[MAX];
	int linecount = 0;
	linecount = readfile(fps, lines);
	sortlines(lines, linecount, mode);
	writefile(lines, no, linecount);
	
}

void sortlines(char *lines[], int linecount, char mode) {
	quicksort(lines, 0, linecount - 1, mode);
	int i = 0;	
}

void writefile(char *lines[], long long no, int linecount) {
	int i = 0;
	char name[1000000] = { 0 };
	sprintf(name, "file%lld.txt", no);
	FILE *fps = fopen( name, "w");
	for(i = 0; i < linecount; i++)
		fputs(lines[i], fps);
	fclose(fps);
	printf("%d\t", linecount);
	for(i = 0; i < 10000; i++)
		free(lines[i]);
	printf("SORTED file %lld.txt\n", no);	
}

int readfile(FILE *fps, char *lines[]) {
	int linecount = 0, i;
	for(i = 0; i < 10000; i++)
		lines[i] = (char *)malloc(sizeof(char) * 500);
	i = 0;	
	while(fgets(lines[i], 500, fps)) {
		linecount++;
		i++;
	}
	fclose(fps);
	printf("%d\t", linecount);	
	return linecount;	 	
}
void quicksort(char *v[], int left, int right, char mode) {
	int pi, low = left, high = right;
	if (low < high)
	{
	        pi = partition(v, low, high, mode);

	        quicksort(v, low, pi - 1, mode);  // Before pi
	        quicksort(v, pi + 1, high, mode); // After pi
	}
}
void swap(char *v[], int i, int j) {
	char *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}
int partition (char *v[], int low, int high, char mode) {
	char *pivot = v[high];
	int i, j;  
	i = (low - 1);  // Index of smaller element
	for (j = low; j <= high- 1; j++) {
		if (mystrcmp(v[j], pivot, mode) < 0) {
			i++;    // increment index of smaller element
			swap(v, i, j);
		}
	}
	swap(v, i + 1, high);
	return (i + 1);
}

int mystrcmp(char *str1, char *str2, char mode) {
	if(mode == 'b') {
		return removeleadingblankspacesandcompare(str1, str2);
	}			//remove blankspaces and compare
	} else if(mode == 'i') {
		return ignorenonprintingandcompare(str1, str2);//ignore case and compare
	}
	else if(mode == 'r') {
		return strcmp(str2, str1);
	}  
	return strcmp(str1, str2);		
}

void mergeallfiles(long long count, char mode) {
	FILE *bfp1, *bfp2;
	char name[1000000] = { 0 };
	//char name[1] ={0};
	long long i = 0;
	//sprintf(name, "file%d.txt", -3);
	FILE *fpf = fopen("sorted.txt", "w");
	bfp1 = fopen("odd.txt", "w+");
	/*sprintf(name, "file%d.txt", -1);
	FILE *bfp2 = fopen(name, "w+");
	printf("pt3\n");*/
	mergesorttwofiles(bfp1, 0, 1, mode);
	fclose(bfp1);
	//sprintf(name, "file%d.txt", 1);
	//fclose()
	for(i = 2; i < count; i++) {
		if(i % 2 == 0) {
			//sprintf(name, "file%d.txt", -1);
			bfp2 = fopen("even.txt", "w+");
			mergesorttwofiles(bfp2, -3, i, mode);
			fclose(bfp2);
		}	
		else {
			//sprintf(name, "file%d.txt", -3);
			bfp1 = fopen("odd.txt", "w+");
			mergesorttwofiles(bfp1, -1, i, mode);
			fclose(bfp1);
		}	
	}
	if(count % 2 == 0) {
		bfp1 = fopen("odd.txt", "r");
		copyfile(fpf, bfp1);
		fclose(fpf);
		fclose(bfp1);
	}
	else {
		bfp2 = fopen("even.txt", "r");
		copyfile(fpf, bfp2);
		fclose(fpf);
		fclose(bfp2);
	}
	for(i = 0; i < count; i++) {
		sprintf(name, "file%lld.txt", i);
		remove(name);
	}
	remove("odd.txt");
	remove("even.txt");	
				
}
int removeleadingblankspacesandcompare(char *str1, char *str2) {
	int i, result, index = 0;
	char *p, *q;
	p = (char *)malloc(500);
	q = (char *)malloc(500);
	strcpy(p, str1);
	strcpy(q, str2);
	while(p[i] == ' ' || p[i] == '\t')
		index++;
	if(index != 0) {
		i = 0;
		while(p[i + index] != NULL) {
			p[i] = p[i + index];
			i++;
		}
		p[i] = '\0';
	}
	index = 0;
	while(q[i] == ' ' || q[i] == '\t')
		index++;
	if(index != 0) {
		i = 0;
		while(q[i + index] != NULL) {
			q[i] = q[i + index];
			i++;
		}
		q[i] = '\0';
	}
	result = strcmp(p, q);
	free(p);
	free(q);
	return result;					 	
}
int ignorenonprintingandcompare(char *str1, char *str2) {
	int i, result;
	char *p, *q;
	p = (char *)malloc(500);
	q = (char *)malloc(500);
	strcpy(p, str1);
	strcpy(q, str2);
	int count1 = 0, count2 = 0, i = 0;
	for(i = 0; p[i]; i++) {
		if(isprint(p[i]))
			p[count1++] = p[i];
	}
	p[count1] = '\0';	
	for(i = 0; q[i]; i++) {
		if(isprint(q[i]))
			q[count2++] = q[i];
	}
	q[count2] = '\0';
	result = strcmp(p, q);
	free(p);
	free(q);
	return result;
}	
void mergesorttwofiles(FILE *bfp, int file1, long long file2, char mode) {
	char *line1, *line2;
	FILE *fp1, *fp2;
	line1 = (char *)malloc(sizeof(char) * 500);
	line2 = (char *)malloc(sizeof(char) * 500);
	char name[1000000] = { 0 };
	if(file1 == 0) {
		sprintf(name, "file%d.txt", file1);
		fp1 = fopen( name, "r");
	}
	if(file1 == -3) {
		fp1 = fopen( "odd.txt", "r");
	}
	if(file1 == -1) {
		fp1 = fopen( "even.txt", "r");			
	}
	sprintf(name, "file%lld.txt", file2);
	fp2 = fopen( name, "r");
	fgets(line1, 500, fp1);
	fgets(line2, 500, fp2);
	if(mode == 'r') {
		while(1) {
			if(feof(fp1)) {
				while(!feof(fp2)) {
					fgets(line2, 500, fp2);
					fputs(line2, bfp);
				}
				break;
			}		
			if(feof(fp2)) {
				while(!feof(fp1)) {
					fgets(line1, 500, fp1);
					fputs(line1, bfp);
				}
				break;
			}
			if(strcmp(line1, line2) > 0) {
				fputs(line1, bfp);
				fgets(line1, 500, fp1);
			}
			else if(strcmp(line1, line2) < 0) {
				fputs(line2, bfp);
				fgets(line2, 500, fp2);
			}
			else {
				fputs(line1, bfp);
				fputs(line2, bfp);
				fgets(line1, 500, fp1);
				fgets(line2, 500, fp2);
			}
		}
	}
	else if(mode == 'b') {
		while(1) {
			if(feof(fp1)) {
				while(!feof(fp2)) {
					fgets(line2, 500, fp2);
					fputs(line2, bfp);
				}
				break;
			}		
			if(feof(fp2)) {
				while(!feof(fp1)) {
					fgets(line1, 500, fp1);
					fputs(line1, bfp);
				}
				break;
			}
			if(removeblankspacesandcompare(line1, line2) < 0) {
				fputs(line1, bfp);
				fgets(line1, 500, fp1);
			}
			else if(removeblankspacesandcompare(line1, line2) > 0) {
				fputs(line2, bfp);
				fgets(line2, 500, fp2);
			}
			else {
				fputs(line1, bfp);
				fputs(line2, bfp);
				fgets(line1, 500, fp1);
				fgets(line2, 500, fp2);
			}
		}
	}
	else if(mode == 'i') {
		while(1) {
			if(feof(fp1)) {
				while(!feof(fp2)) {
					fgets(line2, 500, fp2);
					fputs(line2, bfp);
				}
				break;
			}		
			if(feof(fp2)) {
				while(!feof(fp1)) {
					fgets(line1, 500, fp1);
					fputs(line1, bfp);
				}
				break;
			}
			if(ignorenonprintingandcompare(line1, line2) < 0) {
				fputs(line1, bfp);
				fgets(line1, 500, fp1);
			}
			else if(ignorenonprintingandcompare(line1, line2) > 0) {
				fputs(line2, bfp);
				fgets(line2, 500, fp2);
			}
			else {
				fputs(line1, bfp);
				fputs(line2, bfp);
				fgets(line1, 500, fp1);
				fgets(line2, 500, fp2);
			}
		}
	}				
	else {
		while(1) {
			if(feof(fp1)) {
				while(!feof(fp2)) {
					fgets(line2, 500, fp2);
					fputs(line2, bfp);
				}
				break;
			}		
			if(feof(fp2)) {
				while(!feof(fp1)) {
					fgets(line1, 500, fp1);
					fputs(line1, bfp);
				}
				break;
			}
			if(strcmp(line1, line2) < 0) {
				fputs(line1, bfp);
				fgets(line1, 500, fp1);
			}
			else if(strcmp(line1, line2) > 0) {
				fputs(line2, bfp);
				fgets(line2, 500, fp2);
			}
			else {
				fputs(line1, bfp);
				fputs(line2, bfp);
				fgets(line1, 500, fp1);
				fgets(line2, 500, fp2);
			}
		}
	}
	if(file1 == 0)
		printf("MERGED files file%d.txt and file%lld.txt in odd.txt\n", file1, file2);
	if(file1 == -1)
		printf("MERGED files even.txt and file%lld.txt in odd.txt\n", file2);
	if(file1 == -3)
		printf("MERGED files odd.txt and file%lld.txt in even.txt\n", file2);
}

void copyfile(FILE *target, FILE *source) {
	char *line = (char *)malloc(sizeof(char) * 500);
	while(fgets(line, 500, source))
		fputs(line, target);
}

void mergedtwwosortedfiles(FILE *fp1, FILE *fp2) {
	char *line1, *line2, name[20];
	sprintf(name, "sort.txt");
	FILE *fpc = fopen(name, "r+");
	line1 = (char *)malloc(sizeof(char) * 500);
	line2 = (char *)malloc(sizeof(char) * 500);
	fgets(line1, 500, fp1);
	fgets(line2, 500, fp2);						
	while(1) {
		if(feof(fp1)) {
			while(!feof(fp2)) {
				fgets(line2, 500, fp2);
				fputs(line2, fpc);
			}
			break;
		}		
		if(feof(fp2)) {
			while(!feof(fp1)) {
				fgets(line1, 500, fp1);
				fputs(line1, fpc);
			}
			break;
		}
		if(strcmp(line1, line2) < 0) {
			fputs(line1, fpc);
			fgets(line1, 500, fp1);
		}
		else if(strcmp(line1, line2) > 0) {
			fputs(line2, fpc);
			fgets(line2, 500, fp2);
		}
		else {
			fputs(line1, fpc);
			fputs(line2, fpc);
			fgets(line1, 500, fp1);
			fgets(line2, 500, fp2);
		}
	}
	copyfile(fp2, fpc):
}	
	
