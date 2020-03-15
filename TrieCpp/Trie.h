#include <memory>
#include <map>
#include <string>

class TrieNode
{
public:
	char letter{};
	bool isWord{};

	std::unique_ptr<std::map<char, std::unique_ptr<TrieNode>>> children{};

	TrieNode() {}
	TrieNode(char c) : letter(c) 
	{
		children = std::make_unique<std::map<char, std::unique_ptr<TrieNode>>>();
	}

};


class Trie
{
	std::unique_ptr<TrieNode> root;

public:
	Trie()
	{
		Clear();
	}

	~Trie()
	{
		Clear();
	}

	void Clear()
	{
		root = std::make_unique<TrieNode>('$');
	}

	void Insert(std::string word)
	{
		auto children = root->children.get();
		for (int pos = 0; pos < word.length(); pos++)
		{
			char current = word[pos];

			auto itr = children->find(current);

			TrieNode* temp = nullptr;

			if (itr != children->end())
			{
				temp = itr->second.get();
			}
			else
			{
				children->insert({ current, std::make_unique<TrieNode>(current) });
				temp = children->find(current)->second.get();
			}

			children = children->find(current)->second->children.get();

			if (pos == word.length() - 1)
			{
				temp->isWord = true;
			}
			
		}
	}

};