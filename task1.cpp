/*
Solving this task I was trying to implement production style approach, not just "code the implementation". 
Using iterators, dynamic container 
*/

#include<stdio.h>
#include<string.h>
#include<vector>
#include <iostream>
#include <sstream>


char *intToAscii(char *src, uint32_t srcLen){
    // Converts array of ascii codes represneed as integers to a char based array
    char *asString = src;
    auto i = 0;
    while (src[i] == 0){
        asString++;        //skipping unused zero elements if a result length the same as the longest var length
        i++;
    }
    while (i < srcLen){
        src[i++] += '0';
    }
    return asString;
}


int main(int argc, char** argv){
    std::string casesNum;
    getline(std::cin, casesNum);
    int casesNumInt = std::stoi(casesNum);
    
    auto caseCounter = 1;
    while(caseCounter <= casesNumInt){
        std::string rawSummands;
        std::vector<std::string> summands;
        
        getline(std::cin, rawSummands);
        std::stringstream ss(rawSummands);
        
        //Parsing summands
        for (std::string token; getline(ss, token, ' '); summands.push_back(token));
        
        //Result container init
        auto bigger_element = max_element(summands.begin(), summands.end(), [] (std::string const lhs, std::string const rhs) {
            return lhs.size() < rhs.size();});
        uint32_t resultMaxLength = (*bigger_element).size() + 1;
        char result[resultMaxLength];
        memset(result, 0, sizeof(result));
        
        

        std::string::const_reverse_iterator summandA = summands[0].crbegin();
        std::string::const_reverse_iterator summandB = summands[1].crbegin();
        auto resCnt = resultMaxLength - 1; //leaving last byte as null terminated for further converting to string

        for (auto i = std::make_pair(summandA, summandB);
        i.first != summands[0].crend() && i.second != summands[1].crend();
        i.first++, i.second++, resCnt--)
        {
            uint8_t sum = *i.first + *i.second - 2*('0'); //converting both numbers to int and calculating sum
            if (sum > 9){
                result[resCnt] += (sum % 10);
                result[resCnt - 1] +=  1;
            }
            else result[resCnt] = sum;
        }
        char *formattedResult = intToAscii(result, resultMaxLength);
        printf("Case %d:\n", caseCounter);
        printf("%s + %s = %s\n", summands[0].c_str(), summands[1].c_str(), formattedResult);
        caseCounter++;
    }
}