#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
//Reference string length
int ReferenceStringLength;
//Array to store reference string
int *ArrayReference;
//Number of time frames per process
int ProcessFrames;
//Entry storing array
int *ArrayEntry;
//page faults counter
int PageFaultsCounter=0;
//Array holding the priority requests
int *ArrayPriorityRequests;
//Array holding the used bits  in the clock policy
int *ArrayClockBits;
//Used for loops as counters
int i=0,j=0,k=0,z=0;
void FIFO()
{
    //Tracing the queues
    int Trace = 0;
    //Queue location index
    int CurrentIndex=0;
    //initialize all array entries by -1
    i=0;
    while(i<=ProcessFrames-1)
    {
        ArrayEntry[i]=-1;
        i++;
    }
    //Start traversing the pages.
    for(int i=0; i<ReferenceStringLength; i++)
    {
        //Check if the needed page is found in the main memory or not
        k=0;
        int PageIndex=0;
        while(k<=ProcessFrames-1)
        {
            if(ArrayEntry[k] != ArrayReference[i])
            {

//Page is not found in the main memory
                PageIndex=-1;
            }
            else
            {
                //Page is found in the main memory
                PageIndex=k;
                break;
            }
            k++;
        }
        //If page is found in the main memory print the entry
        if(PageIndex != -1)
        {
            printf("\n%02d     ",ArrayReference[i]);
            //Display Array entries
            k=0;
            while(k<=ProcessFrames-1)
            {
                if(ArrayEntry[k]!=-1)
                {
                    printf("%02d ",ArrayEntry[k]);
                }
                k++;
            }
        }
        //If the page is not found in the main memory
        else
        {
            //if the ArrayEntry table still have space for more pages
            if(CurrentIndex<ProcessFrames)
            {
                printf("\n%02d     ",ArrayReference[i]);
                //Insert page from hard disk into main memory
                ArrayEntry[CurrentIndex]=ArrayReference[i];
                CurrentIndex++;
            }
            //If main memory is full then we need to use page replacement algorithm to free a space to the needed page
            else
            {
                printf("\n%02d F   ",ArrayReference[i]);
                //Replace the first page in the queue with the current page in string and store it
                ArrayEntry[Trace] = ArrayReference[i];
                Trace=(Trace+1)%ProcessFrames;
                //increment page faults
                PageFaultsCounter++;
            }
            //Display Array entries
            k=0;
            while(k<=ProcessFrames-1)
            {
                if(ArrayEntry[k]!=-1)
                {
                    printf("%02d ",ArrayEntry[k]);
                }
                k++;
            }
        }
    }
    printf("\n-------------------------------------");
    printf("\nNumber of page faults = %d\n",PageFaultsCounter);
}
void LRU()
{
    //Holding frequency
    int HoldingCounter=0;
    //Queue location index
    int CurrentIndex=0;
    //initialize all entries by -1
    i=0;
    while(i<=ProcessFrames-1)
    {
        ArrayEntry[i]=-1;
        i++;
    }
    //initialize page index
    int PageIndex=-1;
    //Start traversing the pages.s
    for(int i=0; i<ReferenceStringLength; i++)
    {

        k=0;
        int PageNumber=0;
        //Check if the needed page is found in the main memory or not
        while(k<=ProcessFrames-1)
        {
            if(ArrayEntry[k] != ArrayReference[i])
            {
//Page is not found in the main memory
                PageNumber=-1;
            }
            else
            {
                //Page is found in the main memory
                PageNumber=k;
                break;
            }
            k++;
        }
        if(PageNumber!= -1)
        {

            printf("\n%02d     ",ArrayReference[i]);
            //Update the index of the page
            PageIndex = PageNumber;
            //Create a map to save page indexes
            ArrayPriorityRequests[PageIndex]=HoldingCounter;
            HoldingCounter++;
            //Display Array entries
            k=0;
            while(k<=ProcessFrames-1)
            {
                if(ArrayEntry[k]!=-1)
                {
                    printf("%02d ",ArrayEntry[k]);
                }
                k++;
            }
        }
        //if the page doesn't exist in memory
        else
        {
            //if the ArrayEntry table still have space for more pages
            if(CurrentIndex<ProcessFrames)
            {
                printf("\n%02d     ",ArrayReference[i]);
                //Insert page into the setss
                ArrayEntry[CurrentIndex]=ArrayReference[i];
                ArrayPriorityRequests[CurrentIndex]=HoldingCounter;
                HoldingCounter++;
                CurrentIndex++;
                //Display Array entries
                k=0;
                while(k<=ProcessFrames-1)
                {
                    if(ArrayEntry[k]!=-1)
                    {
                        printf("%02d ",ArrayEntry[k]);
                    }
                    k++;
                }
            }
            else  //if the ArrayEntry table is full, we will need to replace
            {
                printf("\n%02d F   ",ArrayReference[i]);
                //Index of the lowest recently used page
                int MinimumValueIndex = 0;
                for(j=1; j<CurrentIndex; j++)
                {
                    if(ArrayPriorityRequests[j]<ArrayPriorityRequests[0])
                    {
                        MinimumValueIndex = j;
                    }
                }
                //replace the current page with the lowest recently used page
                int MinimumValue=ArrayPriorityRequests[0];
                z=0;
                while(z<CurrentIndex)
                {
                    if(CurrentIndex<ArrayPriorityRequests[i])
                    {
                        MinimumValue=CurrentIndex;
                    }
                    z++;
                }
                //Update the page index of the current page
                ArrayEntry[MinimumValueIndex]=ArrayReference[i];
                ArrayPriorityRequests[MinimumValueIndex]=HoldingCounter;
                HoldingCounter++;
                PageFaultsCounter++;
                //Display Array entries
                k=0;
                while(k<=ProcessFrames-1)
                {
                    if(ArrayEntry[k]!=-1)
                    {
                        printf("%02d ",ArrayEntry[k]);
                    }
                    k++;
                }
            }
        }
    }
    printf("\n-------------------------------------");
    printf("\nNumber of page faults = %d\n",PageFaultsCounter);

}
void OPTIMAL()
{
    ////RandomSlots array used to store the index of future referenced slots
    int RandomSlots[999],Current_Position,i,CurrentIndex=0;
    i=0;
    //initialize all entries by -1
    while(i<=ProcessFrames-1)
    {
        ArrayEntry[i]=-1;
        i++;
    }
    //Check if the page needed located in the main memory or not
    for(i=0; i<ReferenceStringLength; i++)
    {
        int z=0;
        int PageNumber=0;
        //Check if the needed page is found in the main memory or not
        while(z<=ProcessFrames-1)
        {
            if(ArrayEntry[z] != ArrayReference[i])
            {
//Page is not found in the main memory
                PageNumber=-1;
            }
            else
            {
                //Page is found in the main memory
                PageNumber=z;
                break;
            }
            z++;
        }
        //Page is found in the main memory
        if(PageNumber!=-1)
        {
            printf("\n%02d     ",ArrayReference[i]);;
            k=0;
            //Display Array entries
            while(k<=ProcessFrames-1)
            {
                if(ArrayEntry[k]!=-1)
                {
                    printf("%02d ",ArrayEntry[k]);
                }
                k++;
            }
        }
        //If the page is not found in the main memory
        else
        {
            //if the ArrayEntry table still have space for pages
            if(CurrentIndex<ProcessFrames)
            {
                printf("\n%02d     ",ArrayReference[i]);
                ArrayEntry[CurrentIndex]=ArrayReference[i];
                CurrentIndex++;
                //Display Array entries
                k=0;
                while(k<=ProcessFrames-1)
                {
                    if(ArrayEntry[k]!=-1)
                    {
                        printf("%02d ",ArrayEntry[k]);
                    }
                    k++;
                }
            }
            else
            {
                printf("\n%02d F   ",ArrayReference[i]);
                for(j=0; j<ProcessFrames; j++)
                {
                    Current_Position=ArrayEntry[j];
                    bool Found=false;
                    //this loop is for scanning the rest of the ArrayReference string to check for later references to remove them as an estimation for which page will take the longest time to reach so we can remove it by predicting it
                    for(k=i; k<ReferenceStringLength; k++)
                    {
                        if(Current_Position==ArrayReference[k])
                        {
                            RandomSlots[j]=k;
                            Found=true;
                            break;
                        }
                        else
                        {
                            Found=false;
                        }
                    }
                    if(Found==false)
                    {
                        // Assigning highest value
                        RandomSlots[j]=INT_MAX;
                    }
                }
                // Assigning Lowest value
                int Minimum=INT_MIN;
                for(j=0; j<ProcessFrames; j++)
                {
                    if(RandomSlots[j]>Minimum)
                    {
                        Minimum=RandomSlots[j];
                        k=j;
                    }
                }
                ArrayEntry[k]=ArrayReference[i];
                PageFaultsCounter++;
                //Display Array entries
                k=0;
                while(k<=ProcessFrames-1)
                {
                    if(ArrayEntry[k]!=-1)
                    {
                        printf("%02d ",ArrayEntry[k]);
                    }
                    k++;
                }
            }
        }
    }
    printf("\n-------------------------------------");
    printf("\nNumber of page faults = %d\n",PageFaultsCounter);
}
void CLOCK()
{
    //Tracing the queue
    int Trace = 0;
    //Queue location indsex
    int CurrentIndex=0;
    //initialize all entries by -1
    i=0;
    while(i<=ProcessFrames-1)
    {
        ArrayEntry[i]=-1;
        i++;
    }
    //Start traversing the pages.
    for(int i=0; i<ReferenceStringLength; i++)
    {
        //Check if the page is in the frames and if not found return one , if found return page index
        k=0;
        int PageNumber=0;
        while(k<=ProcessFrames-1)
        {
            if(ArrayEntry[k] != ArrayReference[i])
            {

                PageNumber=-1;
            }
            else
            {
                //Return page index if the page is found
                PageNumber=k;
                break;
            }
            k++;
        }
        //Check if the page is in the frames and if not found return one , if found return page index
        j=0;
        PageNumber=0;
        while(j<=ProcessFrames-1)
        {
            if(ArrayEntry[j] != ArrayReference[i])
            {

                PageNumber=-1;
            }
            else
            {
                //Return page index if the page is found
                PageNumber=j;
                break;
            }
            j++;
        }
        if(PageNumber!= -1)
        {
            printf("\n%02d     ",ArrayReference[i]);
            int PageIndex = PageNumber;
            ArrayClockBits[PageIndex]=1;
            //Display Array entries
            k=0;
            while(k<=ProcessFrames-1)
            {
                if(ArrayEntry[k]!=-1)
                {
                    printf("%02d ",ArrayEntry[k]);
                }
                k++;
            }
        }
        //if the page doesn't exist in memory
        else
        {
            //if the ArrayEntry table still have space for pages
            if(CurrentIndex<ProcessFrames)
            {
                printf("\n%02d     ",ArrayReference[i]);
                ArrayEntry[CurrentIndex]=ArrayReference[i];
                //Assign use bit as 0,candidate for replacement
                ArrayClockBits[CurrentIndex]=1;
                CurrentIndex++;
                //Display Array entries
                k=0;
                while(k<=ProcessFrames-1)
                {
                    if(ArrayEntry[k]!=-1)
                    {
                        printf("%02d ",ArrayEntry[k]);
                    }
                    k++;
                }
            }
            else  //if the ArrayEntry table is full, we will need to replace
            {
                printf("\n%02d F   ",ArrayReference[i]);
                //Mark all the bits by false till we find the one which was already false
                while(ArrayClockBits[Trace]!=0)
                {
                    //Mark the current bit as zero bit
                    ArrayClockBits[Trace]=0;
                    Trace=(Trace+1)%ProcessFrames;
                }
                //This page will be the most suitable page for replacements
                //replace the first ArrayEntry with 0 use bit
                ArrayEntry[Trace] = ArrayReference[i];
                //set the use bit of the newly added page to 1
                ArrayClockBits[Trace]=1;
                Trace=(Trace+1)%ProcessFrames;
                PageFaultsCounter++;
                //Display Array entries
                k=0;
                while(k<=ProcessFrames-1)
                {
                    if(ArrayEntry[k]!=-1)
                    {
                        printf("%02d ",ArrayEntry[k]);
                    }
                    k++;
                }
            }
        }
    }
    printf("\n-------------------------------------");
    printf("\nNumber of page faults = %d\n",PageFaultsCounter);
}
//Printing the header statment
void PrintHeader(bool Print, char * policy)
{
    if(Print)
    {
        printf("Replacement Policy = %s\n",policy);
        printf("-------------------------------------\n");
        printf("Page   Content of Frames\n");
        printf("----   -----------------");
    }
}
//Check if the policy is one of the main four
bool validPolicy(char * policy)
{
    bool validation=false;
    if(strcmp("LRU",policy)==0 || strcmp("FIFO",policy)==0 || strcmp("OPTIMAL",policy)==0 || strcmp("CLOCK",policy)==0)
    {
        validation= true;
    }
    else
    {
        validation= false;
    }
    return(validation);
}
int main()
{
    int ResultType;
    scanf("%d",&ProcessFrames);
    ArrayEntry = (int*)malloc(sizeof(int)*ProcessFrames);
    char *usedPolicy = (char*)malloc(sizeof(char)*10);
    scanf("%s",usedPolicy);
    ArrayReference = (int*)malloc(sizeof(int)*999);
    while(scanf("%d",&ArrayReference[i]))
    {
        if(ArrayReference[i]==-1)
        {
            break;
        }
        i++;
    }
    //Reference string array
    ReferenceStringLength=i;
    //Print the header part
    PrintHeader(true, usedPolicy);
    //Check if the policy needed is one of our four polices
    if(!validPolicy(usedPolicy))
    {
        //Policy is not one of our four polices we will scan again
        while(!validPolicy(usedPolicy))
        {
            printf("\n");
            scanf("%s",usedPolicy);
        }
    }
    else
    {
        if(strcmp("FIFO",usedPolicy)==0)
        {
            FIFO();
        }
        else if(strcmp("LRU",usedPolicy)==0)
        {
            ArrayPriorityRequests=(int*)malloc(sizeof(int)*ProcessFrames);
            LRU();
            free(ArrayPriorityRequests);
        }
        else if(strcmp("OPTIMAL",usedPolicy)==0)
        {
            OPTIMAL();
        }
        else if(strcmp("CLOCK",usedPolicy)==0)
        {
            ArrayClockBits=(int*)malloc(sizeof(int)*ProcessFrames);
            CLOCK();
            free(ArrayClockBits);
        }
    }
    free(usedPolicy);
    free(ArrayEntry);
    free(ArrayReference);
    return 0;
}