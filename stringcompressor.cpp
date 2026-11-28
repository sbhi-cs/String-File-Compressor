#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

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
void gettreevalues(treenode* currnode, std::string &bitvalue, std::unordered_map<char, std::string> &codes);
std::string encode(std::string input, std::unordered_map<char, std::string> codes);


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
    } // IMPORTANT: REMEMBER TO FREE MEMORY LATER/AT THE END OF CODE (done)

    treenode* rootnode;

    bool treemade = false;
    if(treenodestorage.size() < 2)
    {
        if(treenodestorage.size() <= 0)
        {
            std::cout << "Not enough values to make the tree\n"; // when no values just do this
            return 0; // maybe add a different return value for this input error? maybe 2
        }
        treemade = true;
        // if theres just one or no values to make the tree with set treemade to true
    }

    while(!treemade) // while tree isn't fully made yet
    {
        bool onenodeleft = false;

        treenode* merge1 = nullptr;
        treenode* merge2 = nullptr; // creates 2 treenodes which will be the 2 lowest valued ones in the array to merge
        
        merge1 = findsmallesttreenode(treenodestorage, merge1, merge2); // will never return as nullptr since there will always be one non-merged node always
        merge2 = findsmallesttreenode(treenodestorage, merge1, merge2);

        if(merge1 != nullptr && merge2 != nullptr) // checks if any of the merges are null, so it won't merge if thats the case
        { 
            // merge time!! this is the merge function
            
            treenode* temp = new treenode; // create a new treenode off the heap
            temp->character = '\0'; // sets its char to null since it doesnt have one so null terminator is best option i think
            temp->childleft = merge1;
            temp->childright = merge2; // set its 2 children (pointers) as merge1 and merge2
            temp->value = merge1->value + merge2->value; // combine the values of merge1 and 2 for the merge nodes value
            treenodestorage.push_back(temp); // append the merged node to the vector

            merge1->ismerged = true;
            merge2->ismerged = true; 
            // set the merge1 and 2 to ismerged \
            (since they point to the values in the vector treenodestorage, it changes those values which is what we want)
        }

        int notmergedcount = 0; // initializes variable for search
        for(size_t i = 0; i < treenodestorage.size(); i++) // checks if theres only one node left that hasnt been merged yet
        {
            if(!treenodestorage[i]->ismerged)
            {
                notmergedcount++; // increments notmergedcount for every node that isn't merged
            }
            if(notmergedcount >= 2)
            {
                break; // if over 2 things have been merged break out of loop
            }
        }
        if(notmergedcount == 1) // if notmergedcount is exactly one
        {
            onenodeleft = true;
            for(size_t i = 0; i < treenodestorage.size(); i++)
            {
                if(!treenodestorage[i]->ismerged) // theres definetly a better way to write this search..
                {
                    rootnode = treenodestorage[i]; // turn that one into the root node
                    break;
                }
            }
        }
        if(onenodeleft)
        {
            std::cout << "Tree Formed\n"; // only when theres one unmerged node left (root) the tree is formed
            treemade = true;
            break;
        }
    }
    // FIX EDGE CASE WHERE THERE IS ONLY ONE CHARACTER INPUT BECAUSE NOTHING HAPPENS IN THAT SCENARIO AND TREE IS NEVER MADE

    std::string bitvalue; // string that will hold the bit code of a node when going down the tree
    std::unordered_map<char, std::string> codes; // hashmap that saves the char (as a key) and the code (string)
    std::unordered_map<std::string, char> decodes; // opposite hashmap for decoding rather than encoding
    // string might change to packed bits later
    // hashmap is also whats used to encode afterwards and print

    
    gettreevalues(rootnode, bitvalue, codes);

    std::string encodedstring = encode(input, codes); // this guy will hold the encoded string, which we get from encode function

    std::cout << encodedstring << "\n"; // print encoded

    // build decode function
    // abstract later
    for(auto item : codes) // loops through every key/val in codes, item stored the current key/val pair its looping over
    {
        decodes.insert({item.second, item.first}); 
        // insert it opposite to codes, string first (key) then char(val)
        // item.first and item.second just mean the key and value of codes respectively
    }

    std::string decodebuffer;
    std::string decodedstring;
    for(size_t i = 0; i < encodedstring.size(); i++)
    {
        decodebuffer.push_back(encodedstring[i]);
        if(decodes.contains(decodebuffer))
        {
            decodedstring.push_back(decodes[decodebuffer]);
            decodebuffer.clear();
        }
    }
    std::cout << decodedstring << "\n";




    // MEMORY FREEING
    for(size_t i = 0; i < treenodestorage.size(); i++)
    {
        delete treenodestorage[i];
    }
    treenodestorage.clear();
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

void gettreevalues(treenode* currnode, std::string &bitvalue, std::unordered_map<char, std::string> &codes)
{
    // this function will recursively search through the tree to generate the huffman code

    if(currnode->character == '\0') // null terminator means it has children, which means it will recurse
    {
        if(currnode->childleft != nullptr) // check if left child isnt null
        {
            bitvalue.append("1"); // append 1 on the string bitvalue code (1 is left)
            gettreevalues(currnode->childleft, bitvalue, codes); // recurse on left node
            bitvalue.pop_back(); // after returned, remove last letter from string bitvalue code
        }
        if(currnode->childright != nullptr) // now check if right child isnt null
        {
            bitvalue.append("0"); // append 0 on the string bitvalue code (0 is right)
            gettreevalues(currnode->childright, bitvalue, codes); // recurse on right node
            bitvalue.pop_back(); // after returned, remove last letter from string bitvalue code
        }
    }
    else // in case of a leaf node (since no null terminator as char)
    {
        // add current character (curr->character) and code (bitvalue string) to hashmap
        codes.insert({currnode->character, bitvalue});
        return; // return to previous function since recursion
    } // the leaf node basically acts as a base case
}

std::string encode(std::string input, std::unordered_map<char, std::string> codes)
{
    std::string encoded;

    for(size_t i = 0; i < input.size(); i++)
    {
        if(codes.contains(input[i]))
        {
           encoded.append(codes[input[i]]); 
        }
    }
    return encoded;
}
