#include <memory>
#include "Cipher.hpp"
#include "CipherType.hpp"
#include "CaesarCipher.hpp"
#include "PlayfairCipher.hpp"
#include "VigenereCipher.hpp"

std::unique_ptr<Cipher> cipherFactory(const CipherType cipherType, const std::string& key)
{
    switch(cipherType)
    {
        case(CipherType::Caesar):
            return std::make_unique<CaesarCipher>(key);
        case(CipherType::Playfair):
            return std::make_unique<PlayfairCipher>(key);
        case(CipherType::Vigenere):
            return std::make_unique<VigenereCipher>(key);
    };
    return std::unique_ptr<Cipher>(); // Default to this but it will never actually be reached.
}