# Memory-Replacement-Policies
Description: Implements and tests memory replacement polcies for effectivenss including Least Recently Used(LRU), First-In-First-Out(FIFO), Random, Clock, and Optimal.

Tests replacement policies with 100 unique pages, 10,000 page accesses and varying size of a memory-like cache. Example holding 5, 10, 15..100 pages.

### Class Structure
**PageGenerate:** 
Creates vectors of different makeup to represent disk
   - No-Locality: Values are read-in from either stdin or file using prog1generator.c
      - Values are random between a given range. Assumes to provide 10,000 elements with values 0-99
  - 8020: 20% of elements make up 80% of the vector. Values are shuffled.
  - looping: Assumes values are sequential before repeating. eg. [0,1,2,3,4,0,1,2,3,4,0,1,2,3,4]
  
**RepPolicies:**
Provides methods to implement replacement policy algorithims when memory is full and get a cache-miss
(memory is repersented as a c++ std linked list)
- Optimal: Not-predictive. Removes page from memory that is furthest away
- FIFO: Removes victim page that came in first
- RAND: Removes victim at random
- Clock: Not yet implemented
- Least Recently Used: Not yet implemented

**prog3:**
- Runner program.
- Makes an instance of PageGenerate to generate various vector types
- Makes various instances of RepPolicies to generate different sized memories and runs polices off vectors
