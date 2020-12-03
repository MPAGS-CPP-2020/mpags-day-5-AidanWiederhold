// Standard library includes
#include <iostream>
#include <string>
#include <algorithm>

// Our project headers
#include "Alphabet.hpp"
#include "VigenereCipher.hpp"

VigenereCipher::VigenereCipher(const std::string& key)
{
    // Set the given key
    setKey(key);
}

void VigenereCipher::setKey(const std::string& key)
{
    // Store the key
    key_=key;

    // Make sure the key is uppercase (copy from PlayfairCipher)
    std::transform( std::begin(key_), std::end(key_), std::begin(key_), ::toupper );

    // Remove non-alphabet characters (copy from PlayfairCipher)
    key_.erase( std::remove_if( std::begin(key_), std::end(key_), [](char c){ return !std::isalpha(c); } ), std::end(key_) );

    // Check if the key is empty and replace with default if so
    if(key_=="")
    {
        key_="key";
        std::cout << "No key was provided to the Vigenere cipher, using \"key\" as a default key" << std::endl;
    }

    // loop over the key
    for(const auto& inChar: key_)
    {
        // Find the letter position in the alphabet
        for ( Alphabet::AlphabetSize i{0}; i < Alphabet::size; ++i )
        {
            if(inChar==Alphabet::alphabet[i])
            {
                if(charLookup_.count(inChar)==0) // don't add the same letter to the map, probably doesn't make much difference but is more efficient I guess
                {
                    // Create a CaesarCipher using this position as a key
                    CaesarCipher cipher{i};

                    // Insert a std::pair of the letter and CaesarCipher into the lookup
                    charLookup_.insert(std::make_pair(inChar, cipher));
                    break;
                }
            }
        }
    }
}

std::string VigenereCipher::applyCipher(const std::string& inputText, const CipherMode cipherMode) const
{
    std::string outputText{""};
    char caesarChar{'x'};
    std::string inChar{""};
    // For each letter in input:
    for(size_t i{0}; i<inputText.length(); ++i) // Easier to just loop over the input like this for finding corresponding letter in key
    {
        // Find the corresponding letter in the key, repeating/truncating as required
        inChar = inputText.at(i);
        caesarChar = key_.at(i%key_.length());

        // Find the CaesarCipher from the lookup
        // Run the (de)cryption
        // Add the result to the output
        outputText += (charLookup_.at(caesarChar)).applyCipher(inChar, cipherMode);
    }
    return outputText;
}