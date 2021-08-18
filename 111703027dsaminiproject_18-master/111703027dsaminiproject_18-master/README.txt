TITLE OF PROJECT:- SORT command
NAME :- KSHITIJ S KAKADE
MIS :- 111703027
DESCRIPTION :- 1)I have implemented my own sort command which works on non binary files in a similar fashion as linux/unix sort. I have splitted big size files into small files each having a maximum of 10000 lines. Then i have used quicksort algorithm to sort each individual files as per the mode entered by the user. 
2)I have named the sorted files from file0.txt to filen.txt where n is the number of files formed. Then i have used merging technique on two files by taking one line from each file and comparing them and passing the appropriate line to third file and taking line from file whose line was passed to third file and comparing it with the line left behind and repeating the process untill both files are merged into third file.
3) I have created two temporary files called odd.txt and even.txt. Initially i merged file0.txt and file1.txt in odd.txt and henceforth if i in filei.txt was even i merged filei.txt and odd.txt in even.txt and if i is odd i merged filei.txt and even.txt in odd.txt. Finally i merged even.txt and odd.txt in another file named sorted.txt.
4) All the comparator functions and the mergesort implementing funcitons have been designed to be reusable. 
