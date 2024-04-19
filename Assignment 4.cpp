#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>


// LRU page replacement algorithm using stack implementation
int LRU(const std::vector<int>& pages, int num_frames) {
    std::unordered_map<int, int> page_table; // map for storing page numbers & corresponding indices in frame
    std::stack<int> frames; // stack to hold frames
    int page_faults = 0; // initialize and declare page fault value
    int step = 1; // step counter for print

    for (int page : pages) { // iterate through each page
        if (page_table.find(page) != page_table.end()) { // find current page in table
            std::stack<int> tempStack; // if page exists in the frames, push to the top of stack
            while (!frames.empty() && frames.top() != page) { // pop elements from stack until target page found
                tempStack.push(frames.top());
                frames.pop();
            }
            if (!frames.empty())
                frames.pop(); // remove page from stack
            while (!tempStack.empty()) {
                frames.push(tempStack.top()); //restore stack by putting remaining pages back on top
                tempStack.pop();
            }
        }
        else {
            page_faults++; // if page not present in frame, increment page fault
            if (frames.size() == num_frames) {
                // If frames are full, pop the least recently used page
                page_table.erase(frames.top());
                frames.pop();
            }
        }

        frames.push(page); // push the current page onto the stack (most recently used)
        page_table[page] = 1; // update page_table with current page & index in frames

        // print results
        std::cout << "Step " << step++ << ": Page fault (" << page << ") - Page Table: {";
        for (auto iter = page_table.begin(); iter != page_table.end(); ++iter) {
            std::cout << iter->first << ", ";
        }
        std::cout << "}, Frames: [";
        std::vector<int> temp_frame_vector; // temp vector for storing frames to print in order
        while (!frames.empty()) { // pop elements in stack, push into vector
            temp_frame_vector.push_back(frames.top());
            frames.pop();
        }
        // print frames in order
        for (auto iter = temp_frame_vector.rbegin(); iter != temp_frame_vector.rend(); ++iter) {
            std::cout << *iter << ", ";
            frames.push(*iter); // restore stack
        }
        std::cout << "], Faults: " << page_faults << std::endl;
    }
    return page_faults; // total number of page faults
}

// Optimal page replacement algorithm
int Optimal(const std::vector<int>& pages, int num_frames) {
    std::unordered_map<int, int> page_table; // map for storing page numbers & corresponding indices in frame
    std::vector<int> frames; // stack to hold frames
    int page_faults = 0; // initialize and declare page fault value
    int step = 1; // step counter for print

    for (int i = 0; i < pages.size(); ++i) { // iterate through each page
        int page = pages[i]; // initialize page with the current page number

        if (page_table.find(page) != page_table.end()) { // search for current page in page table
            continue;
        }
        else { // if page not present in frame, increment page fault
            page_faults++;
            if (frames.size() == num_frames) { // check frame space
                int farthest = i; // initialize variable for tracking the farthest page
                int frame_removal; // initialize variable for frame removal
                for (int frame : frames) { // iterate through frames to search for page not being used for longest time
                    int j; // initialize variable to iterate through remaining frames
                    for (j = i; j < pages.size(); ++j) { // iterate through page to find next occorrence of current page
                        if (pages[j] == frame) { // if found and page is farther in future, update farthest and frame_removal
                            if (j > farthest) {
                                farthest = j;
                                frame_removal = frame;
                            }
                            break;
                        }
                    }
                    if (j == pages.size()) { // if not found, set it for removal
                        frame_removal = frame;
                        break;
                    }
                } // remove frame, replace from frames vector & page table
                auto iter = std::find(frames.begin(), frames.end(), frame_removal);
                frames.erase(iter);
                page_table.erase(frame_removal);
            }
        }

        frames.push_back(page); // push current page into frames vector
        page_table[page] = 1; // update page table with current page

        // print results 
        std::cout << "Step " << step++ << ": Page fault (" << page << ") - Page Table: {";
        for (auto entry : page_table) {
            std::cout << entry.first << ", ";
        }
        std::cout << "}, Frames: [";
        for (int frame : frames) {
            std::cout << frame << ", ";
        }
        std::cout << "], Faults: " << page_faults << std::endl;
    }

    return page_faults; // total number of page faults
}

// FIFO page replacement algorithm using a queue
int FIFO(const std::vector<int>& pages, int num_frames) { 
    std::queue<int> frames; // queue for frames
    std::unordered_map<int, bool> page_status; // map for pages present in frame
    int page_faults = 0; // initialize and declare page fault value
    int step = 1; // step counter for print

    for (int page : pages) { // iterate through pages
        if (page_status.find(page) != page_status.end()) { // search for page
            continue; // if current page found in frame, continue
        }
        else {
            page_faults++; // if page not in frame, increment page fault
            if (frames.size() == num_frames) { // if frame space is full, remove oldest page
                int oldest = frames.front(); // oldest is at the front of queue
                frames.pop(); // remove oldest from the queue
                page_status.erase(oldest); // remove oldest from the map
            }
        }
        // for page faults
        frames.push(page); // push page into frames queue
        page_status[page] = true; // update map, current page is in frames

        // print results
        std::cout << "Step " << step++ << ": Page fault (" << page << ") - Frames: [";

        std::queue<int> temp = frames;
        while (!temp.empty()) {
            std::cout << temp.front() << ", ";
            temp.pop();
        }
        std::cout << "], Faults: " << page_faults << std::endl;
    }

    return page_faults; // total number of page faults
}

int main() {
    std::vector<int> pages = { 1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5 }; // page references
    int num_frames = 4; // number of frames available

    std::cout << "LRU Algorithm:" << std::endl;
    int lru_faults = LRU(pages, num_frames); // call LRU algorithm function
    std::cout << "Total Page Faults: " << lru_faults << std::endl << std::endl;

    std::cout << "Optimal Algorithm:" << std::endl;
    int opt_faults = Optimal(pages, num_frames); // call Optimal algorithm function
    std::cout << "Total Page Faults: " << opt_faults << std::endl << std::endl;

    std::cout << "FIFO Algorithm:" << std::endl;
    int fifo_faults = FIFO(pages, num_frames); // call FIFO algorithm function
    std::cout << "Total Page Faults: " << fifo_faults << std::endl;

    return 0;
}
