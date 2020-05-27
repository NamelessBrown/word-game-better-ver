// word game better ver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <random>
#include <algorithm>
#include <assert.h>

bool IsWord(const std::vector<std::string>& words, const std::string& word);
std::vector<int> FillLetters(const std::string& word);
int Score(const std::string& word1, const std::string& word2);

int main()
{
	std::vector<std::string> words;
	std::ifstream wordFile("20k  most used words.txt");

	for (std::string line; std::getline(wordFile, line);)
	{
		if (line.empty())
		{
			continue;
		}

		words.emplace_back(line);
	}

	wordFile.close();

	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> distribution(0, words.size() - 1);
	std::string answer = words[distribution(rng)];
	std::string guess;

	while (true)
	{
		std::cout << "Guess the word: ";
		std::getline(std::cin, guess);

		if (!IsWord(words, guess))
		{
			std::cout << guess << " is not a word...\n";
			continue;
		}

		if (guess == "hint")
		{
			std::cout << "the answer is: " << answer << '\n';
			continue;
		}

		const int score = Score(answer, guess);

		if (score == answer.size() * 2)
		{
			std::cout << "You win...\n";
			break;
		}
		else
		{
			std::cout << "Not the word, but the points are: " << score << " get to " << answer.size() * 2 << "! \n";
			continue;
		}

	}


}

bool IsWord(const std::vector<std::string>& words, const std::string& word)
{
	for (const auto& w : words)
	{
		if (w == word)
		{
			return true;
		}
	}

	return false;
}

std::vector<int> FillLetters(const std::string& word)
{
	std::vector<int> letters(26, 0);

	for (char c : word)
	{
		assert(!(c < 'a' || c > 'z')); /* Make sure that the character is a letter */
		letters[c - 'a']++;
	}

	return letters;

}

int Score(const std::string& word1, const std::string& word2)
{
	const auto wordLetters1 = FillLetters(word1);
	const auto wordLetters2 = FillLetters(word2);

	int score = 0;
	for (unsigned i = 0; i < 26; i++)
	{
		score += std::min(wordLetters1[i], wordLetters2[i]);
	}

	for (unsigned i = 0; i < word1.size() && i < word2.size(); i++)
	{
		if (word1[i] == word2[i])
		{
			score++;
		}
	}

	return score;
}