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

    // counts letters and stores it in the letters vector (which letter and its frequency)
    countletters(input, letters);

    // sorts the letters based on letter frequency
    std::sort(letters.begin(), letters.end(), [](letter first, letter second) {return first.frequency > second.frequency;});

    for(size_t i = 0; i < letters.size(); i++)
    {
        std::cout << "Character: " << letters[i].character << " Frequency: " << letters[i].frequency << "\n";
    }
    return 0;
    
}


// function definitions
void countletters(std::string input, std::vector<letter> &letters)
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