//
// Created by Kumar Chakravarthy on 18-May-23.
//

// TIL : return type of function used in for_each MUST be void

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>


// Simple Algorithm
void simpleAlgorithm(int n) {
    int steps = 0;
    while(n != 1) {
        if(n < 1) {
            std::cout << "Invalid number encountered" << std::endl;
            return;
        }
        n = (n % 2 == 0) ? n / 2 : 3 * n + 1;
        steps++;
    }

    std::cout << "Number of steps: " << steps << std::endl;
}


// One Edit Away
// "e" & "" = false
bool oneEditAway(const std::string& s1, const std::string& s2) {
    int ptr_1 = 0, ptr_2 = 0, diff = 0;
    while(ptr_1 < s1.length() && ptr_2 < s2.length()) {
        if(diff > 1)
            return false;
        if(s1[ptr_1] == s2[ptr_2]) {
            ptr_1++;
            ptr_2++;
        } else {
            // move ptr_1 or ptr_2 or both ptr one step
            if((ptr_1 + 1 < s1.length()) && (s1[ptr_1 + 1] == s2[ptr_2]))
                ptr_1++;
            else if((ptr_2 + 1 < s2.length()) && (s1[ptr_1] == s2[ptr_2 + 1]))
                ptr_2++;
            else {
                ptr_1++;
                ptr_2++;
            }
            diff++;
        }
    }

    if(ptr_1 == s1.length()) {
        diff += s2.length() - ptr_2;
    }
    if(ptr_2 == s2.length()) {
        diff += s1.length() - ptr_1;
    }

    return (diff > 1) ? false : ((diff == 0) ? false : true);
}


int main() {

    // Simple Algorithm
    if(false) {
        std::vector<int> test_num {12, 20, 97, 256, 6171, 2000000001};
        for_each(test_num.begin(), test_num.end(), simpleAlgorithm);
    }

    // One Edit Away
    if(false) {
        std::vector<std::pair<std::string, std::string>> test_input {
                {"abcd", "abc"},
                {"abde", "aebd"},
                {"abcd", "abfcd"},
                {"geeks", "geek"},
                {"geeks", "geeks"},
                {"geaks", "geeks"},
                {"peaks", "geeks"}
        };
        for(const auto& ele : test_input)
            std::cout << oneEditAway(ele.first, ele.second) <<std::endl;
    }

}
