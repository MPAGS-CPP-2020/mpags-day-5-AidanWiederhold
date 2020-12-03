#ifndef CIPHER_HPP
#define CIPHER_HPP

#include "CipherMode.hpp"

/**
 * \file Cipher.hpp
 * \brief Contains the declaration of the Cipher class
 */

/**
 * \class Cipher
 * \brief Encrypt or decrypt text using the chosen cipher
 */
class Cipher
{
    public:
        Cipher() = default;
        Cipher(const Cipher& rhs) = default;
        Cipher(Cipher&& rhs) = default;
        Cipher& operator=(const Cipher& rhs) = default;
        Cipher& operator=(Cipher&& rhs) = default;
        virtual ~Cipher() = default;

        /**
         * Apply the cipher to the provided text
         *
         * \param inputText the text to encrypt or decrypt
         * \param cipherMode whether to encrypt or decrypt the input text
         * \return the result of applying the cipher to the input text
         */
        virtual std::string applyCipher(const std::string& inputText, const CipherMode cipherMode) const=0;
};

#endif // CIPHER_HPP