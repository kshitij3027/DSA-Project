#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
void sortsinglefile(FILE *fps, long long no, char mode, int key);
int splitfile(FILE *fp);
void sortallfiles(long long count, char mode, int key);
void sortlines(char *lines[], int linecount, char mode, int key);
void writefile(char *lines[], long long no, int linecount, char mode);
int readfile(FILE *fps, char *lines[]);
void swap(char *v[], int i, int j);
void quicksort(char *v[], int left, int right, char mode, int key);
int partition (char *v[], int low, int high, char mode, int key);
void mergeallfiles(long long count, char mode, int key);
void mergesorttwofiles(FILE *bfp1, int file1, long long file2, char mode, int key);
void copyfile(FILE *target, FILE *source);
int mystrcmp(char *str1, char *str2, char mode, int key);
void mergedtwwosortedfiles(FILE *fp1, FILE *fp2, FILE *fp3);
int removeleadingblankspacesandcompare(char *str1, char *str2);
int ignorenonprintingandcompare(char *str1, char *str2);
int numericsort(char *str1, char *str2);
int sortviakey(char *str1, char *str2, int key);
int sortindictionaryorder(char *str1, char *str2);
void removeduplicateandcopyfile( FILE *fp1, FILE *fp2);
void removeduplicatefromfile( FILE *fp, long long no);
int sortedstringcompare(char *str1, char *str2);
