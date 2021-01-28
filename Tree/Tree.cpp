#include <iostream>
#include <vector>

class Root
{
public:
	const char* key;
	std::vector<Root*> items;
public:
	Root(const char* name)
	{
		key = name;
	}
};
// https://www.youtube.com/watch?v=vIAQuDkhXpQ feint snake eyes
// Root: like a folder
//	key: folder name
//	items: items in folder
class Tree
{
	Root* root;
public:
	Tree(const char* rootKey)
	{
		root = new Root(rootKey);
	}
	bool add(const char* path)
	{
		Root* cur = root;
		std::vector<const char*> keys = pathToKeyList(path);
		const char* target = keys[keys.size() - 1];
		if (strcmp(root->key, keys[0]) != 0) return false;
		for (int i = 1; i < keys.size() - 1; i++)
		{
			Root* next = rootWithKey(cur, keys[i]);
			if (next) cur = next;
			else return false;
		}
		Root* temp = new Root(target);
		cur->items.push_back(temp);
		return true;
	}
private:
	// "c/path/to/dir" => {"c", "path", "to", "dir"}
	std::vector<const char*> pathToKeyList(const char* path)
	{
		std::vector<const char*> keys;
		int last_delim = 0;
		bool at_last_char = false;
		for (int i = 0; i < strlen(path); i++)
		{
			at_last_char = i == strlen(path) - 1;

			if (path[i] == '/' || i == strlen(path) - 1)
			{
				int size = i - last_delim + sizeof(char) + at_last_char;
				char* key = new char[size];
				for (int j = 0; j < size; j++)
				{
					key[j] = path[last_delim + j];
				}
				key[size - 1] = 0;

				keys.push_back(key);
				last_delim = i + 1; // one above last delim
			}
		}
		return keys;
	}
	Root* rootWithKey(Root* root, const char* key)
	{
		for (Root* root : root->items)
		{
			if (strcmp(root->key, key) == 0) return root;
		}
		return nullptr;
	}
};

int main()
{
	Tree* tree = new Tree("c");

	return 0;
}