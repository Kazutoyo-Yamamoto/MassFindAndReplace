/////////////////////////////////////////////////////
//	Authors: Kazutoyo Yamamoto
//	Copyright 2019, Kazutoyo Yamamoto
/////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <locale>
#include <clocale>
#include <codecvt>
#include <Windows.h>

//Loads file line by line into a vector of wide strings
bool LoadFile(std::string filename, std::vector<std::wstring>& text)
{
	std::wifstream in(filename.c_str(), std::ios::binary);
	in.imbue(std::locale(in.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
	
	if (!in)
	{
		std::cerr << "Error" << std::endl;
		return false;
	}

	std::wstring str;
	while (std::getline(in, str))
	{
		if (str.size() > 0)
			text.push_back(str);
	}
	in.close();
	return true;
}

//[unused] planned function for comma delimited word list (CVS style spread sheet)
bool LoadItems(std::string filename, std::vector<std::wstring>& items)
{
	std::wifstream in(filename.c_str(), std::ios::binary);
	in.imbue(std::locale(in.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));

	if (!in)
	{
		std::cerr << "Error" << std::endl;
		return false;
	}
	std::wstring str;
	std::getline(in, str);

	std::wstring word;
	for (auto it = str.cbegin(); it != str.cend(); ++it)
	{
		if (*it == ',')
		{
			items.push_back(word);
			word.clear();
		}
		else
		{
			word.push_back(*it);
		}
	}
	in.close();
	return true;
}

int main(int argc, char** argv)
{
	//file to open, vector of strings
	std::vector<std::wstring> m_text;
	//words to find, vector of words
	std::vector<std::wstring> m_finder;
	//words to replace, vector of words
	std::vector<std::wstring> m_replacer;

	setlocale(LC_ALL, "jp_JP.UTF-8");
	
	//debug info
	//std::cout << argv[1] << std::endl;
	//std::cout << argv[2] << std::endl;
	//std::cout << argv[3] << std::endl;

	if (argc == 4)
	{
		LoadFile(argv[1], m_text);
		LoadFile(argv[2], m_finder);
		LoadFile(argv[3], m_replacer);

		//If the number of items to find does not match the
		// number of items to replace with, display an error
		// and exit out of the program
		if (m_finder.size() != m_replacer.size())
		{
			std::cerr << "Finder(" << m_finder.size() << ") Replacer(" << m_replacer.size() << ")" << std::endl;
			return 0;
		}

		int size = m_finder.size();
		//Iterate through the text file looking for words
		for (auto it_text = m_text.begin(); it_text != m_text.end(); ++it_text)
		{
			for (int i = 0; i < size; ++i)
			{
				size_t pos = 0;
				while ((pos = (*it_text).substr(pos).find(m_finder[i])) != std::string::npos)
				{
					wchar_t preChar;
					//If the word is the start of the string, fill in
					// a dummy char to avoid a pointer error
					if (pos == 0)
						preChar = ' ';
					else
						preChar = (*it_text)[pos - 1];


					wchar_t postChar;
					//If the last letter in the word is the end of the
					// string, fill in a dummy char to avoid an error
					if (pos + m_finder[i].size() + 1 > (*it_text).size())
						postChar = 0;
					else
						postChar = (*it_text)[pos + m_finder[i].size() + 1];

					bool test = true;
					//Test to see if the character before and after the word
					// is a non-letter, thus indicating that its a word
					test = !(iswalpha(preChar)) && test;
					test = !(iswalpha(postChar)) && test;

					if (test)
					{
						if (m_finder[i] == m_replacer[i])
						{
							std::cerr << "Replacing word with same word" << std::endl;
							return 0;
						}
						//word found replace it
						(*it_text).erase(pos, m_finder[i].size());
						(*it_text).insert(pos, m_replacer[i]);
					}
					++pos;
				}
			}
		}

		//Create the output file and fill it with the edited text
		std::wofstream output("Output.txt", std::ios::binary);
		output.imbue(std::locale(output.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
		for (auto it_text = m_text.begin(); it_text != m_text.end(); ++it_text)
		{
			output << *it_text;
		}
		output.close();
	}


    return 0;
}
