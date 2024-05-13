#ifndef EQUAKE_H
#define EQUAKE_H

#define MAX_DAYS 31
#define MAX_COLS 10

typedef struct equake_data {
    int year;
    int month;
    int day;
    char *timeOfQuake;
    float latitude;
    float longitude;
    float magnitude;
    float depth;
    char *location;
    struct equake_data *next;
} equake_data_t;

typedef struct region_header {
    char *region_name;
    struct equake_data *data;
    struct region_header *next;
} region_header_t;


/*Arguments: filename, numberOfRegions
	Function takes filename (input argument), total number of regions found  (output argument) 
	File supplied contains names of actual data files containing quake records one for each region
	Open input file specified (data.txt for example) 
		Each line in data.txt is a filename to be opened - create a linked list of region headers
			Each data file (like NorthEast.txt) contains quake records one per link
			Best to use fscanf to read items in each record and create a data node in that region's linked list 
			Repeat for every line in region input/data file until EOF
		Repeat for every data file 
	Keep track of how many regions exist and return it via output argument
  Function value return is the header to the region headers, which will lead us to the entire set of data
*/
region_header_t *readData(char *, int *);



/*Arguments: header pointer to region headers, filename
	Function takes header pointing to the region headers (input argument), filename for creating output file (input argument)
	Start with the first region (via region header) and navigate through the region's (data) linked list 
		Keep track of all the statistics needed for the region
		Write the summary of statistics onto the output file
	Repeat for every region
	Close output file
  Function value return 0 if output file open/write fails or 1 if file open/write is successful
*/
int printSummary(region_header_t *, char *);


/*Arguments: header pointer to region headers, 2-D Array of integers
	Function takes header pointing to the region headers (input argument), 2-D array of integers filled in for daily totals (input/output argument)
	Start with the first region (via region header) and navigate through the region's (data) linked list 
		Pick up the day of quake occurence and bump up the count for that day in the 2-D array of daily records
		Continue until the end of the linked list of data nodes for that region
	Repeat for every region
*/
void buildDailyTotalsArray(region_header_t *, int [][MAX_DAYS]);


/*Arguments: 2-D Array of integers, number of regions
	Function takes 2-D array of integers filled in for daily totals (input/output argument), 
	header pointing to the region headers (input argument), number of regions/rows in 2-D array (input argument)
	Print 2-D array for daily totals
*/
void printDailyTotals(int [][MAX_DAYS], region_header_t *, int);


/*Arguments: header pointer to region headers, 2-D Array of integers 
	Function takes header pointing to the region headers (input argument), 2-D array of integers filled in for magnitude totals by range
	(input/output argument)
	Start with the first region (via region header) and navigate through the region's (data) linked list 
		Pick up the magnitude of quake, truncate to an integer value and bump up the count for that range
		Continue until the end of the linked list of data nodes for that region
	Repeat for every region
*/
void buildMagnitudeTotalsArray(region_header_t *header, int [][MAX_COLS]);


/*Arguments: 2-D Array of integers, number of regions
	Function takes 2-D array of integers filled in for quake magnitudes (input/output argument), 
	header pointing to the region headers (input argument), number of regions/rows in 2-D array (input argument)
	Print 2-D array for magnitude totals (by range)
*/
void printMagnitudeTotals(int [][MAX_COLS], region_header_t *, int);


/*Arguments: header pointer to region headers, 2-D Array of integers
	Function takes header pointing to the region headers (input argument), 2-D array of integers filled in for depth totals by range 
	(input/output argument)
	(input/output argument)
	Start with the first region (via region header) and navigate through the region's (data) linked list 
		Pick up the depth of quake, truncate to an integer value and bump up the count for that range
		Continue until the end of the linked list of data nodes for that region
	Repeat for every region
*/
void buildDepthTotalsArray(region_header_t *header, int [][MAX_COLS+1]);


/*Arguments: 2-D Array of integers, number of regions
	Function takes 2-D array of integers filled in for quake depths (input/output argument), 
	header pointing to the region headers (input argument), number of regions/rows in 2-D array (input argument)
	Print 2-D array for depth totals (by range)
*/
void printDepthTotals(int [][MAX_COLS+1], region_header_t *, int);


/*Arguments: header pointer to region headers, pointer to 2-D array, pointer to 2-D array, pointer to 2-D array
	Function takes header pointing to the region headers (input/output argument), pointer to daily totals array (input argument),
	pointer to magnitude totals array (input argument), pointer to depth totals array (input argument)
	All dynamic memory allocated must be freed. Care must be taken to free up any other member element in the linked list data structures
	before freeing up each node
*/
void cleanUp(region_header_t *, int *, int *, int *);


#endif