//! Unit Tests for MPAGSCipher Cipher Class(es)
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "CipherType.hpp"
#include "CipherFactory.hpp"
#include "CaesarCipher.hpp"
#include "PlayfairCipher.hpp"
#include "VigenereCipher.hpp"

bool testCipher( const std::unique_ptr<Cipher>& cipher, const CipherMode mode,const std::string& inputText, const std::string& outputText)
{
    if(cipher->applyCipher(inputText, mode)==outputText)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool testCollection(const std::unique_ptr<Cipher>& cipher, const CipherMode mode, const CipherType type)
{
  if(mode==CipherMode::Encrypt)
  {
    switch(type)
    {
        case(CipherType::Caesar):
            return testCipher(cipher, CipherMode::Encrypt, "HELLOWORLD", "ROVVYGYBVN");
        case(CipherType::Playfair):
            return testCipher(cipher, CipherMode::Encrypt, "BOBISSOMESORTOFJUNIORCOMPLEXXENOPHONEONEZEROTHING", "FHIQXLTLKLTLSUFNPQPKETFENIOLVSWLTFIAFTLAKOWATEQOKPPA");
        case(CipherType::Vigenere):
            return testCipher(cipher, CipherMode::Encrypt, "WORLD", "DSCWR");
    };
    return false;
  }
  else if(mode==CipherMode::Decrypt)
  {
    switch(type)
    {
        case(CipherType::Caesar):
            return testCipher(cipher, CipherMode::Encrypt, "HELLOWORLD", "ROVVYGYBVN");
        case(CipherType::Playfair):
            return testCipher(cipher, CipherMode::Encrypt, "BOBISSOMESORTOFJUNIORCOMPLEXXENOPHONEONEZEROTHING", "FHIQXLTLKLTLSUFNPQPKETFENIOLVSWLTFIAFTLAKOWATEQOKPPA");
        case(CipherType::Vigenere):
            return testCipher(cipher, CipherMode::Encrypt, "WORLD", "DSCWR");
    };
    return false;
  }
  else
  {
    return false;
  }
  
}

std::vector<std::unique_ptr<Cipher>> ciphers;
std::vector<CipherType> types{CipherType::Caesar,CipherType::Playfair,CipherType::Vigenere};

TEST_CASE("Ciphers encrypt correctly", "[encrypt]")
{
  ciphers.push_back(cipherFactory(CipherType::Caesar, "10"));
  ciphers.push_back(cipherFactory(CipherType::Playfair, "hello"));
  ciphers.push_back(cipherFactory(CipherType::Vigenere, "hello"));
  for(size_t i{0};i<ciphers.size();++i)
  {
    REQUIRE(testCollection(ciphers.at(i), CipherMode::Encrypt, types.at(i)));
  }
}

TEST_CASE("Ciphers decrypt correctly", "[decrypt]") // Don't need to add the ciphers to the collection here since they're added in the previous test.
{
  for(size_t i{0};i<ciphers.size();++i)
  {
    REQUIRE(testCollection(ciphers.at(i), CipherMode::Decrypt, types.at(i)));
  }
}