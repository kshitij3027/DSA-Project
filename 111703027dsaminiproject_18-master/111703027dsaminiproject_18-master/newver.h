#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
void sortsinglefile(FILE *fps, long long no, char mode);
int splitfile(FILE *fp);
void sortallfiles(long long count, char mode);
void sortlines(char *lines[], int linecount, char mode);
void writefile(char *lines[], long long no, int linecount);
int readfile(FILE *fps, char *lines[]);
void swap(char *v[], int i, int j);
void quicksort(char *v[], int left, int right, char mode);
int partition (char *v[], int low, int high, char mode);
void mergeallfiles(long long count, char mode);
void mergesorttwofiles(FILE *bfp1, int file1, long long file2, char mode);
void copyfile(FILE *target, FILE *source);
int mystrcmp(char *str1, char *str2, char mode);
void mergedtwwosortedfiles(FILE *fp1, FILE *fp2);
int removeleadingblankspacesandcompare(char *str1, char *str2);
int ignorenonprintingandcompare(char *str1, char *str2);
