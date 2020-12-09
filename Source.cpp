#include <vector>
#include <string>
#include <fstream>
#include <iostream>

//Day6 Part 1
//Each group, which are separated by blank lines in the puzzle input, are given questions which are represented by the letters a-z, count all unique letters
//in each group, then sum these amounts for the answer.

//For this we may need to store the groups in a nested structure, like a vector<vector<string>> so that we can effectively separate each group. As for each 
//groups unique letters, since they are represented by the alphabet, we can use a boolean array of 26, when we find a letter we can flip the numeric
//location and add 1 to our count for that group, this way we can check that location first, if its true continue, if not flip and add, once we are done
//with the group we can add our count to the total and then reset the count and array.

//Part 2
//Now we need to count which questions where everyone in the group answered, for example in a two person group the first person answers ab and the second
//person answered ac, they both answered a so the count is 1. If there is only one person in the group and they answer abc then the count is 3. If a group
//of four people all answer a then the count is just 1.

//For this we can us something like a frequency chart, where we first iterate our strings and increase counts for each letter, once one of these counts 
//reaches the same value as the number of people in the group we can add one to our group count, then add it to the final sum

std::string alpha = { "abcdefghijklmnopqrstuvwxyz" };

std::vector<std::string> getPuzzleInput()
{
	std::vector<std::string> input;

	std::ifstream file;
	std::string line;
	file.open("puzzle-input.txt");
	int count = 0;
	while (std::getline(file, line))
	{
		input.push_back(line);
	}

	return input;
}

std::vector<std::vector<std::string>> splitIntoGroups(std::vector<std::string> input)
{
	std::vector<std::vector<std::string>> result;
	std::vector<std::string> group;

	for (auto s : input)
	{
		if (!s.empty())
		{
			group.push_back(s);
		}
		else
		{
			result.push_back(group);
			group.clear();
		}
	}
	result.push_back(group);

	return result;
}

int findAnswerPart1(std::vector<std::vector<std::string>> groups)
{
	int count = 0;
	int sum = 0;
	

	for (int i = 0; i < groups.size(); i++)
	{
		bool flags[27] = { 0 };

		for (auto s : groups[i])
		{
			for (int j = 0; j < s.length(); j++)
			{
				int index = alpha.find(s[j]);

				if (!flags[index])
				{
					count++;
					flags[index] = true;
				}
			}
		}
		sum += count;
		count = 0;
	}

	return sum;

}

int findAnswerPart2(std::vector<std::vector<std::string>> groups)
{
	int count = 0;
	int sum = 0;

	for (int i = 0; i < groups.size(); i++)
	{
		int frequency[27] = { 0 };

		for (auto s : groups[i])
		{
			for (int j = 0; j < s.length(); j++)
			{
				int index = alpha.find(s[j]);
				frequency[index] = frequency[index] + 1;

				if (frequency[index] == groups[i].size())
				{
					count++;
				}
			}
		}
		sum += count;
		count = 0;
	}

	return sum;
}

int main()
{
	std::vector<std::string> input = getPuzzleInput();

	std::vector<std::vector<std::string>> groups = splitIntoGroups(input);

	/*for (int i = 0; i < groups.size(); i++)
	{
		std::cout << i << ":" << '\n';
		for (auto s : groups[i])
		{
			std::cout << s << '\n';
		}
		std::cout << '\n';
	}*/

	std::cout << findAnswerPart1(groups) << '\n';

	std::cout << findAnswerPart2(groups) << '\n';

	return 0;
}