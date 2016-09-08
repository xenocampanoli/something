/* sortints.c
12345678901234567890123456789012345678901234567890123456789012345678901234567890
*/

#include <ctype.h>
#include "../env.h"
#include "itemtype.h"
#include "xcppsorts.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void printUsage() {
	printf("USAGE:  ./sortints [optionswitches]\n");
	printf("\t-c cmp function by number (varies by itemtype; at least {0,1}).\n");
	printf("\t-d Descending sort (default is ascending).\n");
	printf("\t-h Print this usage without error.\n");
	printf("\t-i<inputfilespec> Some file containing a vector of integers.  Defaults to array literal.\n");
	printf("\t-n<number> Same as -i../../trydata/<ItemTypeName>vector<number>.lst\n");
	printf("\t-o<outputfilespec> Output file to write the results to.  Defaults to stdout.\n");
	printf("\t-s<sorttype> (See sort types under uppercase letter switches devoted to default sort types)\n");
	printf("\t-v Verbose output describing activity.\n");
	printf("\t-B BubbleSort (TBD).\n");
	printf("\t-C CycleSort (TBD).\n");
	printf("\t-G GhomeSort (TBD).\n");
	printf("\t-H HeapSort {[%s],%s,%s}\n",WPPCShiftDownHeapSort,WPPCShiftUpHeapSort,CLRSPCHeapSort);
	printf("\t-I InsertionSort (TBD).\n");
	printf("\t-K BlockSort (TBD).\n");
	printf("\t-L LibrarySort (TBD).\n");
	printf("\t-M MergeSort (TBD).\n");
	printf("\t-N IntroSort (TBD).\n");
	printf("\t-O SmoothSort (TBD).\n");
	printf("\t-P CombSort (TBD).\n");
	printf("\t-Q QuickSort (TBD).\n");
	printf("\t-R TournamentSort ().\n");
	printf("\t-S ShellSort (TBD).\n");
	printf("\t-T TimSort (TBD).\n");
	printf("\t-U CubeSort (TBD).\n");
	printf("\t-V OddEvenSort (TBD).\n");
	printf("\t-X ExternalMergeSort (TBD).\n");
}

void handleArgs(int argc, char * const* argv, char *cmpflag, FILE **ifp, FILE **ofp, char *st, bool *v) {

	char c;
	char ifspec[80];
	char ofspec[80];

	*cmpflag = '0';
	*ifp = (FILE *)NULL;
	*ofp = (FILE *)NULL;
	strcpy(st,SortDefault);
	*v = false;

	while ((c = getopt (argc, argv, "B:C:G:H:I:K:L:M:N:O:P:Q:R:S:T:U:V:c:dhi:n:o:s:v")) != -1)
		switch (c) {
			case 'B': /* BubbleSort */
				strcpy(st,"someBubbleSort");
				break;
			case 'C': /* CycleSort */
				strcpy(st,"someCycleSort");
				break;
			case 'G': /* GnomeSort */
				strcpy(st,"someGnomeSort");
				break;
			case 'H': /* HeapSort */
				switch(optarg[0]) {
					case '0': strcpy(st,"wppcShiftDownHeapSort"); break;
					case '1': strcpy(st,"wppcShiftUpHeapSort"); break;
					case '2': strcpy(st,"clrspcHeapSort"); break;
					default:  fprintf(stderr, "Switch -%c takes only arguments: '0', '1', or '2'.\n", optopt);
				}
				break;
			case 'I': /* InsertionSort */
				strcpy(st,"someInsertionSort");
				break;
			case 'K': /* BlockSort */
				strcpy(st,"someBlockSort");
				break;
			case 'L': /* LibrarySort */
				strcpy(st,"someLibrarySort");
				break;
			case 'M': /* MergeSort */
				strcpy(st,"someMergeSort");
				break;
			case 'N': /* IntroSort */
				strcpy(st,"someIntroSort");
				break;
			case 'O': /* SmoothSort */
				strcpy(st,"someSmoothSort");
				break;
			case 'P': /* Comb Sort (Peinar) */
				strcpy(st,"someCombSort");
				break;
			case 'Q': /* QuickSort */
				strcpy(st,"wppcQuickSort");
				break;
			case 'R': /* TournamentSort */
				strcpy(st,"someTournamentSort");
				break;
			case 'S': /* ShellSort */
				strcpy(st,"someShellSort");
				break;
			case 'T': /* TimSort */
				strcpy(st,"someTimSort");
				break;
			case 'U': /* CubeSort */
				strcpy(st,"someCubeSort");
				break;
			case 'V': /* OddEvenSort */
				strcpy(st,"someOddEvenSort");
				break;
			case 'c': /* comparison function, by number.  There should
						be at least two {0,1}, but any itemtype may have
						any in the set {0,1,2,3,4,5,6,7,8,9}. */
				if ( strlen(optarg) != 1 || optarg[0] < '0' || '9' < optarg[0] ) { 
					puts("Comparison function switch argument must be an integer from 0 to 9.");
					printUsage();
					exit(1);
				}
				*cmpflag = optarg[0];
				break;
			case 'd': /* Descending */
				SortAscending = false;
				LessThanValue		= 1;
				GreaterThanValue	= -1;
				break;
			case 'h': /* Help */
				printUsage();
				exit(0);
			case 'i': /* input filespec */
				sprintf(ifspec,"%s/%s",RelSpecTryData,optarg);
				/* Later add rw et al in external sort case */
				*ifp = fopen(ifspec,"r");
				break;
			case 'n': /* named input file by sorttype and switch argument. Free form. */
				sprintf(ifspec,"%s/%svector%s.lst",RelSpecTryData,ItemTypeName,optarg);
				/* Later prevent use in external sort case. */
				*ifp = fopen(ifspec,"r");
				break;
			case 'o': /* output filespec; goes to LocalOutData directory */
				sprintf(ofspec,"%s/%s",LocalOutData,optarg);
				*ofp = fopen(ofspec,"w");
				break;
			case 's': /* sort type */
				strcpy(st,optarg);
				break;
			case 'v': /* turn on verbose mode */
				*v = true;
				break;
			case '?': /* handles undefined switch combinations */
				fprintf(stderr,"argument:  %s\n",optarg);
				if ( isprint(optopt) )
					fprintf(stderr,"Bad switch value `-%c'.\n", optopt);
				else
					fprintf(stderr,"Bad switch `\\x%x'.\n", optopt);
				printUsage();
				exit(1);
			default: /* This will handle something defined in the
						getopt command, but not in the switch.  There should not
						be any such thing.
					  */
				puts("Programmer Error!");
				printUsage();
				exit(1);
		}
}

bool externalSort(char *sortType) {
	if ( strcmp(sortType,DefaultExternalMergeSort) == 0 ) { return true; }
	return false;
}

void manageSort(char cmpFlag, char *sortType, FILE *iFp, bool verbose, FILE *oFp) {

	bool u = true;
	clock_t before, after, delta;
	time_t now;

	ComparisonFnPtr cmp = GetComparisonFunction(cmpFlag);

	int i;
	int itemcount;
	int *itemlist;

	if ( ! externalSort(sortType) ) {
		itemlist = LoadVector(iFp,&itemcount);
	}

	if ( verbose ) {
		time(&now);
		printf("Before time %s", ctime(&now));
		printf("Number of integers in vector:  %d\n",itemcount);
		printf("ItemTypeSize:  %u\n",(unsigned int)ItemTypeSize);
		/* The following a quick sanity check that you have a valid cmp: */
		printf("Comparison Function Argument Pointer:  %p\n",cmp);
		printf("Initial vector:\n");
		for(i=0; i<itemcount; ++i)
			printf("Element %d has value %d.\n",i,itemlist[i]);
	}

	before = clock();

	/* Begin Sort Execution Section: */

	if ( u && strcmp(sortType,NativeQSort) == 0 )			{ u=false; qsort(itemlist,itemcount,ItemTypeSize,cmp); }
	if ( u && strcmp(sortType,CLRSPCHeapSort) == 0 )		{ u=false; clrspcHeapSort(itemlist,itemcount,cmp); }
	if ( u && strcmp(sortType,WPPCShiftDownHeapSort) == 0 )	{ u=false; wppcShiftDownHeapSort(itemlist,itemcount,cmp); }
	if ( u && strcmp(sortType,WPPCShiftUpHeapSort) == 0 )	{ u=false; wppcShiftUpHeapSort(itemlist,itemcount,cmp); }

	/* End Sort Execution Section: */

	after = clock();

	delta = after - before;
	printf ("%d records sorted, %d clock ticks counted, (approximately %f seconds).\n",
		itemcount,(int)delta,((float)delta)/CLOCKS_PER_SEC);

	if ( oFp ) DumpVector(oFp, itemlist, itemcount);
	if ( verbose ) {
		printf("Clock ticks before:  %d\n",(int)before);
		printf("Clock ticks after:  %d\n",(int)after);
		time(&now);
		printf("After time %s", ctime(&now));
		printf("Sorted vector:\n");
		for(i=0; i<itemcount; ++i)
			printf("Element %d has value %d.\n",i,itemlist[i]);
	}
}

int main(int argumentCount, char * const* argumentVector) {
	char cmpflag = 0; /* So Cmp0ItemType is always the default. */
	FILE *inputfp;
	FILE *outputfp;
	char sorttype[32];
	bool verbose;

	handleArgs(argumentCount,argumentVector,&cmpflag,&inputfp,&outputfp,sorttype,&verbose);

	manageSort(cmpflag,sorttype,inputfp,verbose,outputfp);
}

/*
12345678901234567890123456789012345678901234567890123456789012345678901234567890
End of sortints.c */
