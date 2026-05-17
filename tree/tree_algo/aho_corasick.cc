/*
    Aho-Corasick builds a trie from all patterns and adds suffix links to efficiently fall back to shorter matching prefixes.
        The go transitions let the automaton process the text character by character without restarting from the root.
    For V trie nodes and alphabet size A = 26, preprocessing takes O(V * A), searching takes O(M), and memory usage is O(V * A).
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int K = 26;

struct Vertex
{
    int next[K];
    bool output = false;
    int p = -1;
    char pch;
    int link = -1;
    int go[K];

    Vertex(int p = -1, char ch = '$') : p(p), pch(ch)
    {
        fill(begin(next), end(next), -1);
        fill(begin(go), end(go), -1);
    }
};

vector<Vertex> trie(1);

void add_string(string const& s)
{
    int v = 0;

    for (char ch : s)
    {
        int c = ch - 'a';

        if (trie[v].next[c] == -1)
        {
            trie[v].next[c] = trie.size();
            trie.emplace_back(v, ch);
        }

        v = trie[v].next[c];
    }

    trie[v].output = true;
}

int go(int v, char ch);

int get_link(int v)
{
    if (trie[v].link == -1)
    {
        if (v == 0 || trie[v].p == 0)
            trie[v].link = 0;
        else
            trie[v].link = go(get_link(trie[v].p), trie[v].pch);
    }

    return trie[v].link;
}

int go(int v, char ch)
{
    int c = ch - 'a';

    if (trie[v].go[c] == -1)
    {
        if (trie[v].next[c] != -1)
            trie[v].go[c] = trie[v].next[c];
        else
            trie[v].go[c] = v == 0 ? 0 : go(get_link(v), ch);
    }

    return trie[v].go[c];
}

bool has_output(int v)
{
    if (trie[v].output)
        return true;

    if (v == 0)
        return false;

    return has_output(get_link(v));
}

int main()
{
    vector<string> patterns = {
        "abcd",
        "bcd",
        "ab",
        "bc"
    };

    for (string s : patterns)
        add_string(s);

    for (int v = 0; v < (int)trie.size(); v++)
        get_link(v);

    for (int v = 0; v < (int)trie.size(); v++)
        for (char ch = 'a'; ch <= 'z'; ch++)
            go(v, ch);

    cout << "Number of nodes: " << trie.size() << "\n\n";

    cout << "Trie structure:\n\n";

    for (int v = 0; v < (int)trie.size(); v++)
    {
        cout << "Node " << v << "\n";
        cout << "Parent: " << trie[v].p << "\n";
        cout << "Character from parent: " << trie[v].pch << "\n";
        cout << "Suffix link: " << trie[v].link << "\n";
        cout << "Is terminal/output node: " << trie[v].output << "\n";

        cout << "Direct trie transitions: ";

        bool any = false;

        for (char ch = 'a'; ch <= 'z'; ch++)
        {
            int c = ch - 'a';

            if (trie[v].next[c] != -1)
            {
                cout << ch << " -> " << trie[v].next[c] << " ";
                any = true;
            }
        }

        if (!any)
            cout << "none";

        cout << "\n\n";
    }

    string text = "xxabcdxxbcdxxab";

    int v = 0;

    cout << "Testing text: " << text << "\n\n";

    for (int i = 0; i < (int)text.size(); i++)
    {
        char ch = text[i];

        v = go(v, ch);

        cout << "After reading '" << ch << "', automaton is in node " << v;

        if (has_output(v))
            cout << "   pattern found";

        cout << "\n";
    }

    return 0;
}