#include <bits/stdc++.h>

using namespace std;

class SingleHash
{
    int buckets;
    std::vector<long long> *table;

public:
    explicit SingleHash(int v)
    {
        buckets = v;
        table = new vector<long long>[buckets];
    }

    void insertItem(long long key)
    {
        int index = hashFunction(key);
        table[index].push_back(key);
    }

    void deleteItem(long long key)
    {
        int index = hashFunction(key);

        std::vector<long long>::iterator i;
        for (i = table[index].begin(); i != table[index].end(); i++)
        {
            if (*i == key)
                break;
        }

        if (i != table[index].end())
        {
            table[index].erase(i);
        }
    }

    int hashFunction(long long x)
    {
        return x % (long long)buckets;
    }

    void displayHash()
    {
        for (int i = 0; i < buckets; i++)
        {
            cout << i;
            for (auto x : table[i])
                cout << " --> " << x;
            cout << endl;
        }
    }

    void displaySizes()
    {
        for (int i = 0; i < buckets; i++)
        {
            cout << i << "-->" << table[i].size() << '\n';
        }
    }

    void findNumber(long long key)
    {
        int index = hashFunction(key);
        int k = 0;
        std::vector<long long>::iterator i;
        for (i = table[index].begin(); i != table[index].end(); i++)
        {
            k++;
            if (*i == key)
                break;
        }

        if (i != table[index].end())
        {
            cout << "Found the number " << key << " in list " << index << " at index " << k << '\n';
        }
        else
        {
            cout << "Not Found" << '\n';
        }
    }

    long long getNumber(int index, int lst)
    {
        auto i = table[lst].begin();
        advance(i, index - 1);
        return *i;
    }
};

int main()
{
    SingleHash H(37);

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(1.0, 1000000000.0);

    std::cout << "Hashing With Chaining!!" << std::endl;

    int size = 100;
    long long find;
    auto start1 = std::chrono::high_resolution_clock::now();

    cout << "Allocating Items" << endl;
    for (auto i = 0; i < size; i++)
    {
        auto temp = (long long)(dist(mt));
        if (i == 25)
            find = temp;
        H.insertItem(temp);
    }
    cout << "Items Allocated" << endl;
    auto stop1 = std::chrono::high_resolution_clock::now();

    auto duration1 = std::chrono::duration_cast<std::chrono::seconds>(stop1 - start1);
    cout << "Item Allocation Duration: " << duration1.count() << " seconds" << endl;

    H.displaySizes();

    auto start2 = std::chrono::high_resolution_clock::now();
    H.findNumber(find);
    auto stop2 = std::chrono::high_resolution_clock::now();

    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);
    cout << "Single Hash Function completed searching in " << duration2.count() << " microseconds" << endl;

    H.deleteItem(find);

    H.findNumber(find);

    H.displayHash();

    return 0;
}