#include "pch.h" 

#include "CLettersGame.h"

CLettersGame::CLettersGame()
  : CGameBase(new LettersGame(gen, vowels, consonants, words))
{
}

std::mt19937 CLettersGame::gen = std::mt19937(std::random_device{}());
std::string CLettersGame::path = "./";
std::vector<char> CLettersGame::vowels = Io::getLetters(path, "vowels.txt");
std::vector<char> CLettersGame::consonants = Io::getLetters(path, "consonants.txt");
std::vector<std::string> CLettersGame::words = Io::getWords(path, "UK_english_truncated.txt");