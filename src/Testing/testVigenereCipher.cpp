//! Unit Tests for MPAGSCipher CaesarCipher Class
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "VigenereCipher.hpp"

TEST_CASE("Vigenere encryption", "[vigenere]") {
  VigenereCipher vc{"hello"};
  REQUIRE( vc.applyCipher("WORLD", CipherMode::Encrypt) == "DSCWR");
}

TEST_CASE("Vigenere decryption", "[vigenere]") {
  VigenereCipher vc{"hello"};
  REQUIRE( vc.applyCipher("DSCWR", CipherMode::Decrypt) == "WORLD");
}