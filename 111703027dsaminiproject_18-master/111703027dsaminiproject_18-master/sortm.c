#define MAX 100000
#define MAX1 100000
#include "sort.h"
/* splitting big file into smaller files each of max 10000 lines and returning no of files formed*/
int splitfile(FILE *fp) {
	int count = 0, i = 0, j = 0;
	FILE *fps;	
	char ch = '\0', *line = (char *)malloc(1000);
	while(!feof(fp)) {
		char name[1000000] = { 0 };
		sprintf(name, "file%d.txt", j);
		fps = fopen( name, "w");
		for(i = 0; i < 10000; i++){
		 	if(fgets(line, 1000, fp))
		 		fputs(line, fps);
		 	else
		 		break;
		 }
		 if(!feof(fp)) { 
		 	j++;		
			count++;
			
		 }
		 fclose(fps);
	}
	return count;
}
/*passing each file to be sorted to sortsinglefile function one by one*/
void sortallfiles(long long count, char mode, int key) {
	int i = 0, j = 0;
	FILE *fps;
	if(count == 0) {
		fps = fopen("file0.txt", "r");
		sortsinglefile(fps, i, mode, key);
	}	
	for(i = 0; i < count; i++) {
		char name[1000000] = { 0 };
		sprintf(name, "file%d.txt", i);
		fps = fopen( name, "r");
		sortsinglefile(fps, i, mode, key);
		
	}	
}

void sortsinglefile(FILE *fps, long long no, char mode, int key) {
	char *lines[MAX];
	int linecount = 0;
	linecount = readfile(fps, lines);
	sortlines(lines, linecount, mode, key);
	writefile(lines, no, linecount, mode);
}

void sortlines(char *lines[], int linecount, char mode, int key) {
	quicksort(lines, 0, linecount - 1, mode, key);
	int i = 0;	
}
/*writing sorted buffer to file*/
void writefile(char *lines[], long long no, int linecount, char mode) {
	int i = 0, j = 0, k = 0;
	char name[1000000] = { 0 };
	sprintf(name, "file%lld.txt", no);
	FILE *fps = fopen( name, "w");			
	for(i = 0; i < linecount; i++)
		fputs(lines[i], fps);
	fclose(fps);
	if (mode == 'u') {
		fps = fopen( name, "r");
		removeduplicatefromfile(fps, no);
	}	
		printf("%d\t", linecount);
		for(i = 0; i < 10000; i++)
			free(lines[i]);
	printf("SORTED file %lld.txt\n", no);		
}
/* reading contents of each file line by line and storing them in buffer*/
int readfile(FILE *fps, char *lines[]) {
	int linecount = 0, i;
	for(i = 0; i < 10000; i++)
		lines[i] = (char *)malloc(sizeof(char) * 1000);
	i = 0;	
	while(fgets(lines[i], 1000, fps)) {
		linecount++;
		i++;
	}
	fclose(fps);
	printf("%d\t", linecount);	
	return linecount;	 	
}

void quicksort(char *v[], int left, int right, char mode, int key) {
	int pi, low = left, high = right;
	if (low < high)
	{
	        pi = partition(v, low, high, mode, key);

	        quicksort(v, low, pi - 1, mode, key);  
	        quicksort(v, pi + 1, high, mode, key);
	}
}

int partition (char *v[], int low, int high, char mode, int key) {
	char *pivot = v[high];
	int i, j;  
	i = (low - 1); 
	for (j = low; j <= high- 1; j++) {
		if (mystrcmp(v[j], pivot, mode, key) < 0) {
			i++;   
			swap(v, i, j);
		}
	}
	swap(v, i + 1, high);
	return (i + 1);
}

void swap(char *v[], int i, int j) {
	char *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}
/*returning value to partition function as per operations on string and comparisons*/
int mystrcmp(char *str1, char *str2, char mode, int key) {
	if(mode == 'b') 
		return removeleadingblankspacesandcompare(str1, str2);		
	else if(mode == 'i')
		return ignorenonprintingandcompare(str1, str2);
	else if(mode == 'r')
		return strcmp(str2, str1);
	else if(mode == 'n')
		return numericsort(str1, str2);
	else if(mode == 'k') 
		return sortviakey(str1, str2, key);
	else if(mode == 'd') {
		return sortindictionaryorder(str1, str2);	
	}
	else			  
		return strcmp(str1, str2);		
}

void mergeallfiles(long long count, char mode, int key) {
	FILE *bfp1, *bfp2;
	char name[1000000] = { 0 };
	long long i = 0;
	FILE *fpf = fopen("sorted.txt", "w");
	if(count == 0) {
		bfp1 = fopen("file0.txt", "r");
		copyfile(fpf, bfp1);
		fclose(bfp1);
		fclose(fpf);
		remove("file0.txt");
	}
	else {	
		bfp1 = fopen("odd.txt", "w+");
		mergesorttwofiles(bfp1, 0, 1, mode, key);
		fclose(bfp1);
		for(i = 2; i < count; i++) {
			if(i % 2 == 0) {
				bfp2 = fopen("even.txt", "w+");
				mergesorttwofiles(bfp2, -3, i, mode, key);
				fclose(bfp2);
			}	
			else {
				bfp1 = fopen("odd.txt", "w+");
				mergesorttwofiles(bfp1, -1, i, mode, key);
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
}	
/*merging two files by comparing one string of each file at a time*/
void mergesorttwofiles(FILE *bfp, int file1, long long file2, char mode, int key) {
	char *line1, *line2;
	FILE *fp1, *fp2;
	line1 = (char *)malloc(sizeof(char) * 1000);
	line2 = (char *)malloc(sizeof(char) * 1000);
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
	fgets(line1, 1000, fp1);
	fgets(line2, 1000, fp2);
	while(1) {
			if(feof(fp1)) {
				while(!feof(fp2)) {
					fgets(line2, 1000, fp2);
					fputs(line2, bfp);
				}
				break;
			}		
			if(feof(fp2)) {
				while(!feof(fp1)) {
					fgets(line1, 1000, fp1);
					fputs(line1, bfp);
				}
				break;
			}
			if(mystrcmp(line1, line2, mode, key) < 0) {
				fputs(line1, bfp);
				fgets(line1, 1000, fp1);
			}
			else if(mystrcmp(line1, line2, mode, key) > 0) {
				fputs(line2, bfp);
				fgets(line2, 1000, fp2);
			}
			else {
				if(mode == 'u') {
					fputs(line1, bfp);
					fgets(line1, 1000, fp1);
					fgets(line2, 1000, fp2);
				}
				else {	
					fputs(line1, bfp);
					fputs(line2, bfp);
					fgets(line1, 1000, fp1);
					fgets(line2, 1000, fp2);
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

void mergedtwwosortedfiles(FILE *fp1, FILE *fp2, FILE *fp3) {
	char *line1, *line2;
	line1 = (char *)malloc(sizeof(char) * 1000);
	line2 = (char *)malloc(sizeof(char) * 1000);
	fgets(line1, 1000, fp1);
	fgets(line2, 1000, fp2);						
	while(1) {
		if(feof(fp1)) {
			while(!feof(fp2)) {
				fgets(line2, 1000, fp2);
				fputs(line2, fp3);
			}
			break;
		}		
		if(feof(fp2)) {
			while(!feof(fp1)) {
				fgets(line1, 1000, fp1);
				fputs(line1, fp3);
			}
			break;
		}
		if(strcmp(line1, line2) < 0) {
			fputs(line1, fp3);
			fgets(line1, 1000, fp1);
		}
		else if(strcmp(line1, line2) > 0) {
			fputs(line2, fp3);
			fgets(line2, 1000, fp2);
		}
		else {
			fputs(line1, fp3);
			fputs(line2, fp3);
			fgets(line1, 1000, fp1);
			fgets(line2, 1000, fp2);
		}
	}
}

void copyfile(FILE *target, FILE *source) {
	char *line = (char *)malloc(sizeof(char) * 1000);
	while(fgets(line, 1000, source))
		fputs(line, target);
}

/* mystrcmp comparator functions*/
int sortindictionaryorder(char *str1, char *str2) {
	int i = 0, j = 0, result;
	char c1, c2;
	while(str1[i] && str2[j]) {
		if(str1[i] >= 'a' && str1[i] <= 'z' || str1[i] == ' ' || str1[i] >= 'A' && str1[i] <= 'Z' || str1[i] >= '1' && 			str1[i] <= '9') {
			c1 = str1[i];
			i++;
		}
		if(str2[j] >= 'a' && str2[j] <= 'z' || str2[j] == ' ' || str2[j] >= 'A' && str2[j] <= 'Z' || str2[j] >= '1' && 			str2[j] <= '9') {
			c2 = str2[j];
			j++;
		}
		if(i == j) {
			result = c1 - c2;
			if(result < 0) {
				return -2;
			}
			else if(result > 0){
				return 2;
			}
		}	
		else {
			if(i > j) {
				if(c1 == c2) {
					result = c1 - c2;
					if(result < 0) {
						return -2;
					}
					else if(result > 0){
						return 2;
					}
					else {
						j++;
					}
				}
				else {			
				while(1) {
					if(str2[j] >= 'a' && str2[j] <= 'z' || str2[j] == ' ' || str2[j] >= 'A' && str2[j] <= 'Z' 						|| str2[j] >= '1' && str2[j] <= '9') {
						c2 = str2[j];
						break;
					}
					j++;
				}
				result = c1 - c2;
				if(result < 0) {
					return -2;
				}
				else if(result > 0){
					return 2;
				}
				else {
					j++;
				}	
			}
			}
			else if (j > i) {
				if(c1 == c2) {
					result = c1 - c2;
					if(result < 0) {
						return -2;
					}
					else if(result > 0){
						return 2;
					}
					else {
						j++;
					}
				}
				else {
				while(1) {
					if(str1[i] >= 'a' && str1[i] <= 'z' || str1[i] == ' ' || str1[i] >= 'A' && str1[i] <= 'Z' 						|| str1[i] >= '1' && str1[i] <= '9') {
						c1 = str1[i];
						break;
					}
					i++;
				}
				result = c1 - c2;
				if(result < 0) {
					return -2;
				}
				else if(result > 0){
					return 2;
				}
				else {
					i++;
				}	
			}
			}
			else {
				i++;
				j++;
			}
		}
		
	}
	if(str1[i] == '\0') {
		return -2;
	}
	else if(str2[j] == '\0') {
		return 2;
	}	
}

int removeleadingblankspacesandcompare(char *str1, char *str2) {
	int i = 0, result, index_p = 0, index_q = 0;
	char *p, *q, *ptemp, *qtemp;
	p = (char *)malloc(1000);
	q = (char *)malloc(1000);
	ptemp = p;
	qtemp = q;
	strcpy(p, str1);
	strcpy(q, str2);
	while(*p == ' ' || *p == '\t') {
		p++;
	}
	while(*q == ' ' || *q == '\t') {
		q++;
	}
	result = strcmp(p, q);
	free(ptemp);
	free(qtemp);
	return result;					 	
}

int ignorenonprintingandcompare(char *str1, char *str2) {
	int i, result;
	char *p, *q;
	p = (char *)malloc(1000);
	q = (char *)malloc(1000);
	strcpy(p, str1);
	strcpy(q, str2);
	int count1 = 0, count2 = 0;
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

int sortviakey(char *str1, char *str2, int key) {
	char *p = (char *)malloc(1000), *token, *q = (char *)malloc(1000);
	int count = 0, i = 0, j = 0, k = key, result, store;
	while(str1[i] != '\0') {
		while(str1[i] != ',') {
			if(str1[i] == '\0')
				break;
			i++;
		}	
		count++;
		i++;
	}
	if(key >= count) {
		i = 0;
		store = count - 1;
		while(store--) {
			j = 0;
			while(str1[i] != ',') {
				p[j] = str1[i];
				i++;
				j++;
			}
		}
		j = 0;
		while(str1[i] != '\0') {
			p[j] = str1[i];
			i++;
			j++;
		}			
		i = 0;
		store = count - 1;
		while(store--) {
			j = 0;
			while(str2[i] != ',') {
				q[j] = str2[i];
				i++;
				j++;
			}
		}
		j = 0;
		while(str2[i] != '\0') {
			q[j] = str2[i];
			i++;
			j++;
		}
	}
	else {
		i = 0;
		while(k--) {
			j = 0;
			while(str1[i] != ',') {
				p[j] = str1[i];			
				i++;
				j++;
			}
			p[j] = '\0';
			i++;
		}
		i = 0;
		while(key--) {
			j = 0;
			while(str2[i] != ',') {
				q[j] = str2[i];			
				i++;
				j++;
			}
			q[j] = '\0';
			i++;
		}
	}
	result = strcmp(p, q);
	free(p);
	free(q);			
	return result;		
}

int numericsort(char *str1, char *str2) {
	int i = 0, num1 = 0, num2 = 0, flag;
	for(i = 0; str1[i] && str2[i]; i++) {
		if( str1[0] <= '0' && str1[0] >= '9' &&  str2[0] <= '0' && str2[0] >= '9')
			flag = 0;
		else
			flag = 1;
	}
	if(flag == 1) 
		return strcmp(str1, str2);
	else {				
		if(str1[0] >= '0' && str1[0] <= '9' && str2[0] <= '0' && str2[0] >= '9')
			return -2;
		if( str1[0] <= '0' && str1[0] >= '9' && str2[0] >= '0' && str2[0] <= '9')
			return 2;
		if( str1[0] <= '0' && str1[0] >= '9' &&  str2[0] <= '0' && str2[0] >= '9')
			return strcmp(str1, str2);;		
		if(str1[0] >= '0' && str1[0] <= '9' && str2[0] >= '0' && str2[0] <= '9') {
			while(str1[i] >= '0' && str1[i] <= '9') { 
				num1 = num1 * 10 + (str1[i] - '0');
				i++;
			}
			i = 0;	 
			while(str2[i] >= '0' && str2[i] <= '9') { 
				num2 = num2 * 10 + (str2[i] - '0');
				i++;
			}	 		
		}
	}
	if(num1 != 0 || num2 != 0) {
		if(num1 < num2)
			return -2;
		else if(num1 > num2)
			return 2;
		else 
			return strcmp(str1, str2);
	}
	else 
		return strcmp(str1, str2);
							
}	
void removeduplicatefromfile( FILE *fp, long long no) {
	char *p, *q;
	char name[1000000] = { 0 };
	FILE *fp1 = fopen("copy.txt", "w");
	int result;
	copyfile(fp1, fp);
	fclose(fp1);
	fclose(fp);
	fp1 = fopen("copy.txt", "r");
	sprintf(name, "file%lld.txt", no);
	fp = fopen( name, "w");	
	p = (char *)malloc(1000);
	q = (char *)malloc(1000);
	fgets(p, 1000, fp1);
	fgets(q, 1000, fp1);
	while(!feof(fp1)) {
		result = sortedstringcompare(p, q);
		if(result == 0) {
			while(!result) {
				fgets(q, 1000, fp1);
				result = sortedstringcompare(p, q);
			}		
			fputs(p, fp);
			strcpy(p,q);
			fgets(q, 1000, fp1);
		}
		else {
			fputs(p, fp);
			strcpy(p,q);
			fgets(q, 1000, fp1);			
		}		
	}
	fclose(fp1);
	fclose(fp);
	remove("copy.txt");
}
int sortedstringcompare(char *str1, char *str2) {
	int i = 0, j = 0, flag;
	while(str1[i] && str2[j]) {
		if(str1[i] == str2[j]) {
			i++;
			j++;
			flag = 1;
		}
		else {
			flag = 0;
			break;
		}
	}
	if(flag == 1)
		return 0;
	else 
		return 1;
}	




	
				
		
		
		

	
		
		
	
			
