/*
    During working on this task I tried to find out the balance of optimization and maintanability. 
    The final complexity is more optimzied than brute-force, 
    program logic splitted on different modules that could be easily updated independently.
*/

#include<iostream>
#include<cstdio>
#include<queue>
#include<algorithm>
#include <vector>

int binSearch(const long bound, const std::vector<long> &nums){
    // Kind of binary search looking for max number in a container lower than bound

     int mid;
     int left = 0;
     int right = nums.size() - 1;
     while(left < right)
     {
         mid = (left + right) / 2;
         if(nums[mid] < bound)
             left = mid + 1;
         else
             right  =  mid;
     }
     return left - 1;
}

std::vector<long> &getNumbers(std::vector<long> &container, const long maxBound, const uint16_t cnt){
    // Get all numbers from stdin
    
    for (auto i = 0; i < cnt; ++i){
        long buffer;
        scanf("%ld",&buffer);
        if (buffer < maxBound)
            container.push_back(buffer);
    }
    return container;
}

std::vector<long> &addSumCombinations(std::vector<long> &container, const long maxBound){
    // Update container with sum combinations of existing numbers
    
    for(int i=0; i <= container.size() - 1; i++)
        for(int j=i; j <= container.size() - 1; j++)
            if(container[i] + container[j] < maxBound)
                container.push_back(container[i]+container[j]);
    container.push_back(0);
    sort(container.begin(), container.end());
    container.erase(unique(container.begin(), container.end()), container.end());
    
    return container;
}

int main(){
    long maxBound;
    uint16_t integersNum;
    uint16_t caseCounter = 1;

    std::vector<long> num;
    while(scanf("%hu %ld", &integersNum, &maxBound) && (maxBound != 0 && integersNum != 0)){
        num = getNumbers(num, maxBound, integersNum);
        
        num = addSumCombinations(num, maxBound);

        long answer = 0;
        for (int i = 0; i < num.size(); i++){
            long bound = maxBound - num[i]; //decrease num of cases
            int x = binSearch(bound, num);
            if (num[x] < maxBound)
                answer = std::max(answer, num[x] + num[i]); // check that max border bound is bigger than previous
        }
        printf("Case %d: %ld\n\n", caseCounter++, answer);
    }
    return 0;
}