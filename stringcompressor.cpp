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
    // gonna rq hardcode one from the tree with 2 least frequent characters then merge them

    treenode leaf1;
    leaf1.character = letters[0].character;
    leaf1.value = letters[0].frequency; // 2 pointers alr set to nullptr point to nothing since they are leafs
    leaf1.ismerged = true;
    treenode leaf2;
    leaf2.character = letters[1].character;
    leaf2.value = letters[1].frequency;
    leaf2.ismerged = true;

    treenode merge1; // no character since merged value, but will have child values
    merge1.childleft = &leaf1;
    merge1.childright = &leaf2;
    merge1.value = merge1.childleft->value + merge1.childright->value;
    
    //std::cout << "Least common char: " << leaf1.character << " appears " << leaf1.value << " times\n";
    //std::cout << "Second least common char: " << leaf2.character << " appears " << leaf2.value << " times\n";
    //std::cout << "First merged node value: " << merge1.value << "\n";
    // end of hardcoded test
    // DELETE WHEN NOT NEEDED WHICH IS AFTER DEBUGGING BEFORE SHIP


    std::vector<treenode*> treenodestorage; // this guy stores all the tree nodes so they can exist and be referenced properly
    
    for(size_t i = 0; i < letters.size(); i++)
    {
        treenode *temp = new treenode;
        temp->character = letters[i].character;
        temp->value = letters[i].frequency;
        temp->ismerged = false;
        temp->childright = nullptr;
        temp->childleft = nullptr;
        // this takes some memory from the heap for temp so we can store in the vector

        treenodestorage.push_back(temp);
    } // IMPORTANT: REMEMBER TO FREE MEMORY LATER/AT THE END OF CODE

    for(size_t i = 0; i < letters.size(); i++)
    {
        std::cout << "Character: " << treenodestorage[i]->character << " Value: " << treenodestorage[i]->value << "\n";
    } 

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