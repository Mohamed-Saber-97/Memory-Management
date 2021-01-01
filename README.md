# Memory Management


## Page Replacement Algorithms in Operating Systems


+ **Introduction:**


  + In operating systems that use paging for memory management, page replacement algorithm are needed to decide which page needed to be replaced when new page comes in. Whenever a new page is referred and not present in memory, page fault occurs and Operating System replaces one of the existing pages with newly needed page. Different page replacement algorithms suggest different ways to decide which page to replace. The target for all algorithms is to reduce number of page faults. Let capacity be the number of pages that memory can hold.  Let set be the current set of pages in memory.
  
  
+ **Algorithms:**  


  + First In First Out (FIFO)    
  
  
    + This is the simplest page replacement algorithm. In this algorithm, the operating system keeps track of all pages in the memory in a queue, the oldest page is in the front of the queue. When a page needs to be replaced page in the front of the queue is selected for removal.
    
    
  + Least Recently Used (LRU)
  
  
    + In Least Recently Used (LRU) algorithm is a Greedy algorithm where the page to be replaced is least recently used. The idea is based on locality of reference
    
    
  + Optimal
  
  
    + In this algorithm, pages are replaced which would not be used for the longest duration of time in the future. If referred page is already present, increment hit count. If not present, find if a page that is never referenced in future. If such a page exists, replace this page with new page. If no such page exists, find a page that is referenced farthest in future. Replace this page with new page.


  + Clock
     
     + Create an array frames to track the pages currently in memory and another Boolean array second_chance to track whether that page has been accessed since it’s last replacement (that is if it deserves a second chance or not) and a variable pointer to track the target for replacement. Start traversing the array arr. If the page already exists, simply set its corresponding element in second_chance to true and return. If the page doesn’t exist, check whether the space pointed to by pointer is empty (indicating cache isn’t full yet) – if so, we will put the element there and return, else we’ll traverse the array arr one by one (cyclically using the value of pointer), marking all corresponding second_chance elements as false, till we find a one that’s already false. That is the most suitable page for replacement, so we do so and return. Finally, we report the page fault count.
