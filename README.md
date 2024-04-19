# CS540-Programming-Assignment-4-Page-Replacement-Algorithms

Implementing LRU, Optimal, and FIFO algorithms for page replacements with C++ on Visual Studio.

- For the LRU (Least Recently Used) algorithm, it will replace the least recently used page with a new page. It uses a stack to keep track of ordering. After iterating through pages, they are pushed to the top of the stack. When a page is replaced, the LRU page located at the bottom is removed.
- For Optimal algorithm, it will replace the page that isn't used for the longest time. 
- For FIFO (first in first out) algorithm, a new page will replace the oldest page. It uses a queue to keep track of ordering. For page replacement, the oldest page (located in the front of queue) is removed.

- In this program, you will only need to run it.

- The main function declares and initializes sample page references. The algorithm will use 4 frames, holding 1 page at a time. It will then call each algorithm and print their results containing steps, page faults, page table, frames, faults, and total page faults.

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
OPENING THE PROGRAM:

Open the Visual Studio Solution file --> Assignment 4.sln --> on the top left, press view "solution explorer" --> double click "Assignment 4" --> go to the drop down arrow on source files --> double click "Assignment 4.cpp"
At the top in the middle, select --> Local Windows Debugger (to run the code)

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

