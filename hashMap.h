#include <unordered_map>
#include <iostream>
using namespace std;


class hashMap{
private:
    unordered_map<string, int>dogMap;
public:
    hashMap()= default;


    void insert(const string &name){
        if (dogMap.find(name) == dogMap.end()){
            dogMap.insert(make_pair(name, 1));
        }
        else{
            dogMap[name]++; ///chaining when a name is repeated
        }
    }
    int get_count(string name){
        if (dogMap.find(name) == dogMap.end()){
            return 0;
        }
        else{
            return dogMap.find(name)->second;
        }
    }
    int ranking(string name){
        int compare = get_count(name);
        int rank = 1;
        for (auto dogs : dogMap){
            if (dogs.second > compare){
                rank++; //rank calculated as 1 + # of names more popular
            }
        }
        return rank;
    }
};