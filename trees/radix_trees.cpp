#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

class RadixTreeNode
{
public:
    unordered_map<char, RadixTreeNode *> children;
    string value;
    bool isEndOfWord;

    RadixTreeNode() : isEndOfWord(false) {}
};

class RadixTree
{
private:
    RadixTreeNode *root;

    void insert(RadixTreeNode *node, const string &key, const string &value, int depth)
    {
        if (depth == key.size())
        {
            node->isEndOfWord = true;
            node->value = value;
            return;
        }

        char currentChar = key[depth];
        if (node->children.find(currentChar) == node->children.end())
        {
            node->children[currentChar] = new RadixTreeNode();
        }

        insert(node->children[currentChar], key, value, depth + 1);
    }

    bool search(RadixTreeNode *node, const std::string &key, int depth) const
    {
        if (depth == key.size())
        {
            return node->isEndOfWord;
        }

        char currentChar = key[depth];
        if (node->children.find(currentChar) == node->children.end())
        {
            return false;
        }

        return search(node->children[currentChar], key, depth + 1);
    }

    void printTree(RadixTreeNode *node, const std::string &prefix) const
    {
        if (node->isEndOfWord)
        {
            cout << prefix << " : " << node->value << endl;
        }

        for (const auto &child : node->children)
        {
            printTree(child.second, prefix + child.first);
        }
    }

public:
    RadixTree() : root(new RadixTreeNode()) {}

    void insert(const string &key, const string &value)
    {
        insert(root, key, value, 0);
    }

    bool search(const string &key) const
    {
        return search(root, key, 0);
    }

    void printTree() const
    {
        printTree(root, "");
    }
};

int main()
{
    RadixTree tree;

    tree.insert("apple", "A fruit");
    tree.insert("app", "Short for application");
    tree.insert("ape", "A primate");
    tree.insert("bat", "A flying mammal");
    tree.insert("bath", "A washing activity");
    tree.insert("batman", "A superhero");

    cout << "Radix Tree Contents:\n";
    tree.printTree();

    std::string searchWord = "batman";
    if (tree.search(searchWord))
    {
        cout << "\n'" << searchWord << "' found in the tree.\n";
    }
    else
    {
        cout << "\n'" << searchWord << "' not found in the tree.\n";
    }

    return 0;
}
