#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// struct definitions
struct letter
{
    char character;
    int frequency;
};

struct treenode
{
    char character; // leave empty if its a merged node instead of a value node for a char
    int value; // this is frequency but if its a merged node then its just the value
    bool ismerged = false; // to see if we can merge/operate on this specific treenode or if its alr been merged
    treenode *childright = NULL;
    treenode *childleft = NULL; // both children for binary tree
};

// function prototypes
void countletters(std::string input, std::vector<letter> &letters);
treenode* findsmallesttreenode(std::vector<treenode*> treenodestorage, treenode* merge1, treenode* merge2);


int main(void)
{
    // variable definitions
    std::string input; // this guy holds the input
    std::vector<letter> letters; // this guy holds all the letters + their frequency

    // takes input and stores it in the input string
    std::cout << "Give me a word, sentence, or piece of text: ";
    std::getline(std::cin, input);

    // PART 1: Letter Frequency Calculation
    // counts letters and stores it in the letters vector (which letter and its frequency)
    countletters(input, letters);

    // sorts the letters based on letter frequency from least to most frequent
    std::sort(letters.begin(), letters.end(), [](letter first, letter second) {return first.frequency < second.frequency;});

    // PART 2: Creation of Huffman Tree


    // HARDCODED TEST - delete before ship

    // treenode leaf1;\
    leaf1.character = letters[0].character;\
    leaf1.value = letters[0].frequency; // 2 pointers alr set to nullptr point to nothing since they are leafs\
    leaf1.ismerged = true;\
    treenode leaf2;\
    leaf2.character = letters[1].character;\
    leaf2.value = letters[1].frequency;\
    leaf2.ismerged = true;\

    // treenode merge1; // no character since merged value, but will have child values\
    merge1.childleft = &leaf1;\
    merge1.childright = &leaf2;\
    merge1.value = merge1.childleft->value + merge1.childright->value;\
    
    // std::cout << "Least common char: " << leaf1.character << " appears " << leaf1.value << " times\n";\
    std::cout << "Second least common char: " << leaf2.character << " appears " << leaf2.value << " times\n";\
    std::cout << "First merged node value: " << merge1.value << "\n";\

    // END OF HARDCODED TEST
    // DELETE WHEN NOT NEEDED WHICH IS AFTER DEBUGGING BEFORE SHIP


    std::vector<treenode*> treenodestorage; // this guy stores all the tree nodes so they can exist and be referenced properly
    
    for(size_t i = 0; i < letters.size(); i++)
    {
        treenode* temp = new treenode;
        temp->character = letters[i].character;
        temp->value = letters[i].frequency;
        temp->ismerged = false;
        temp->childright = nullptr;
        temp->childleft = nullptr;
        // this takes some memory from the heap for temp so we can store in the vector

        treenodestorage.push_back(temp);
    } // IMPORTANT: REMEMBER TO FREE MEMORY LATER/AT THE END OF CODE

    bool treemade = false;
    if(treenodestorage.size() < 2)
    {
        treemade = true;
        // if theres just one or no values to make the tree with set treemade to true
    }

    while(!treemade) // while tree isn't fully made yet
    {
        treenode* merge1 = nullptr;
        treenode* merge2 = nullptr; // creates 2 treenodes which will be the 2 lowest valued ones in the array to merge
        
        merge1 = findsmallesttreenode(treenodestorage, merge1, merge2);
        merge2 = findsmallesttreenode(treenodestorage, merge1, merge2);

        std::cout << "smallest val letter " << merge1->character << " " << merge1->value << "\n";
        std::cout << "next small val letter " << merge2->character << " " << merge2->value << "\n";
        break;
    }

    // MEMORY FREEING
    for(size_t i = 0; i < treenodestorage.size(); i++)
    {
        delete treenodestorage[i];
    }
    treenodestorage.clear();
    
    // don't forget to devlog!!
}


// function definitions
void countletters(std::string input, std::vector<letter> &letters) // this function counts each character and their frequency
{
    // function variable definitions
    std::size_t length = input.length(); // this guy holds the length of the inputted string
    bool found = false; // this guy holds a checker if the current letter is already in the vector

    for(std::size_t i = 0; i < length; i++)
    {
        found = false; // reset found to false
        
        if(i == 0)
        {
            letters.push_back({input[i], 1}); // appends a value to vector: {character, frequency}
        } 
        // checks if the vector is empty and if so puts in the current letter input
        // also sets frequency to 1 since its the first time that letter is in, so frequency is always 1

        else
        {
            for(std::size_t j = 0; j < letters.size(); j++) // loops through all characters in letters vector
            {
                if(input[i] == letters[j].character) // checks if current char in input already is stored in the letters vector
                {
                    letters[j].frequency++; // increment the vector letter frequency by 1
                    found = true; // set found to true (useful for a conditionnal later)
                    break; // break out of the loop
                }
            }
            if(found) // if character was alr in vector
            {
                found = false;
                continue;
            } // go to next loop iteration
            letters.push_back({input[i], 1});
            // append the current character to the vector
            // again, frequency of 1
            // characters only reach this far if they aren't yet in the vector
            // the if(found) filters them out
        }
    }
    return;
}

treenode* findsmallesttreenode(std::vector<treenode*> treenodestorage, treenode* merge1, treenode* merge2)
{
    treenode* smallest = nullptr; // for the for loop to check which val is the smallest

    for(size_t i = 0; i < treenodestorage.size(); i++) // iterates between each treenode in treenodestorage to find smallest value one
    {
        if(smallest == nullptr) // on the case that smallest hasnt been given a val to compare against yet
        {
            if(!treenodestorage[i]->ismerged) // if the current vector treenode isn't merged yet
            {
                if(treenodestorage[i] != merge1 && treenodestorage[i] != merge2) // if the current vector treenode isnt merge1 or merge2
                {
                    smallest = treenodestorage[i]; // set smallest as current treenode in the vector
                } // i might have to clean this up i hate more than 2 nested if statements
            }
            else
            {
                continue; // if the treenode isn't merged (or isnt merge1 or merge2)
            }
        }
        else // if smallest actually has a value (isn't a nullptr) which means we can compare it to check if anything is smaller
        {
            if(treenodestorage[i]->value < smallest->value && !treenodestorage[i]->ismerged && treenodestorage[i] != merge1 && treenodestorage[i] != merge2)
            // quick breakdown: current treenodestorage value must be less than the current smallest value, cant be merged, or equal to any of the current merged
            {
                smallest = treenodestorage[i];
            }
        }
    }
    return smallest;
}