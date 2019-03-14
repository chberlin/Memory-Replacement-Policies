# Memory-Replacement-Policies
Description: Implements and tests memory replacement polcies for effectivenss including Least Recently Used(LRU), First-In-First-Out(FIFO), Random, Clock, and Optimal.

Tests replacement policies with 100 unique pages, 10,000 page accesses and varying size of a memory-like cache. Example holding 5, 10, 15..100 pages.

### Class Structure
**PageGenerate:** 
Creates vectors of different makeup to represent disk
   - No-Locality: Values are random between a given range. Default to provide 10,000 elements with values 0-99
  - 8020: 20% of elements make up 80% of the vector. Values are shuffled.
  - looping: Assumes values are sequential before repeating. eg. [0,1,2,3,4,0,1,2,3,4,0,1,2,3,4]
  
**RepPolicies:**
Provides methods to implement replacement policy algorithims when memory is full and get a cache-miss
(memory is repersented as a c++ std linked list)
- Optimal: Not-predictive. Removes page from memory that will appear furthest away into the future
- FIFO: Removes victim page that came in first
- RAND: Removes victim at random
- Clock: Searches through memory for page with use bit of 0 for victim. 
- Least Recently Used: Removes page from memory that will appeared furthest away into the past

**prog3:**
- Runner program.
- Makes an instance of PageGenerate to generate various vector types
- Makes instance of RepPolicies
- Creates three CSV files
  - No-Locality.csv
  - 8020.csv
  - loop.csv
- Each CSV file contains hit rate data on each algorithim with memory size between 0 to 100 in intervals of 5
- CSV data can be graphed using


# Run Instructions
To compile
`make`

To run and Generate CSV files
`./prog3`

To graph output
`make graph`

Removes .o, executable, csv, and png files
`make clean`
