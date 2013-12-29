#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include <bitset>
using namespace std;

class Test {
private:
    static const long long MAXRES = 1000000007;
    static int round(double d)
    {
        return ceil(d) - d < d - floor(d) ? ceil(d) : floor(d);
    }
    static long long sequenceSum(int minVal, int maxVal)
    {
        if(minVal > maxVal)return 0;
        return (minVal + maxVal)*(maxVal - minVal + 1LL)/2;
    }
 
    //compute Least Common Multiple of a,b
    static long long lcm(long long a, long long b)
    {
       long long tmp, aCopy = a, bCopy = b;
        while(b != 0)
        {
            tmp = b;
            b = a % b;
            a = tmp;
        }
        //a is gcd(a,b)
        return aCopy / a * bCopy;
    }
    //compute sum(R) and sizeof(R)
    static void computeR()
    {
        bitset<32> bitMin(minp),bitMax(maxp);
        int i = 31;
        for(; i >= 0; i--)//find the first bit '1' in minp
            if(bitMin[i] == true)break;
        int minpBitNum = i + 1;
        //containMax indicates whether element max(a,b) is in set R
        bool containMax = false;
        for(int k = 0; k < minpBitNum; k++)
            if(bitMax[k] == true)containMax = true;
        for(; i >= 0 && bitMax[i] == false; i--)
            bitMax[i] = bitMax[i]^bitMin[i];
        for(; i >= 0; i--)
            bitMax[i] = true;
        int maxR = bitMax.to_ulong();//max element in set R
        sumR = 0;//sum of elements in R
        sizeR = maxR + 1;//the number of element in R
        sumR = sequenceSum(1, maxR);
        if(!containMax)
        {
            sumR  = (sumR - maxp) % MAXRES;
            if(sumR < 0)sumR += MAXRES;
            sizeR--;
        }
        if(minp == 1)
        {
            sumR--;
            sizeR--;
        }
    }
    static bool computeLRecur(int index, vector<int> &vec, long long lcmVec)
    {
        if(index == minp + 1)
        {
            int vecSize = vec.size();
            if(vecSize == 0)return true;
            int op = vecSize%2 == 0 ? -1 : 1;
            int seqStart = 0;
            for(int i = 0; i < vecSize; i++)
                seqStart = max(seqStart, mulStartVal[vec[i]]);
            seqStart = ceil( seqStart * 1.0 / lcmVec );
            int seqEnd = vec[0] * maxp / lcmVec;
            if(seqStart <= seqEnd)
            {
                sumL = (sumL + op * lcmVec *sequenceSum(seqStart, seqEnd))
                    % MAXRES ;
                sizeL += op * (seqEnd - seqStart + 1);
                return true;
            }
            else
                return false;
        }
        if(computeLRecur(index + 1, vec, lcmVec))
        {
            vec.push_back(index);
            computeLRecur(index + 1, vec, lcm(lcmVec, index));
            vec.pop_back();
            return true;
        }
        else return false;
    }
    //compute sum(L) and sizeof(L)
    static void computeL()
    {
        //min prime factor of [0,1,2...30]
        int minPriFac[] = {0, 1,2,3,2,5,2,7,2,3,2, 11,2,13,2,3,2,17,2,19,2
                            ,3,2,23,2,5,2,3,2,29,2};
        sumL = 0;
        sizeL = 0;
        mulStartVal.clear();
        mulStartVal.push_back(0);
        mulStartVal.push_back(1);
        for(int i = 2; i <= minp; i++)
            mulStartVal.push_back(max(maxp / minPriFac[i] + 1, i) * i);
        vector<int> vec;
        computeLRecur(1, vec, 1);
    }
public:
    static int minp, maxp;//minp = min(a,b),maxp = max(a,b)
    //sumR = sum of elelment in set R
    //sumL = sum of elelment in set L
    //sizeR = number of element in set R
    //sizeL = number of element in set L
    static long long sumR, sizeR, sizeL, sumL;
    static vector<int> mulStartVal;
 
    static int run (int   a,int   b)
    {
        //--------compute the digit number of b
        int bDigitNum = 0;
        for(int bcopy = b, factor = 10; bcopy != 0;)
        {
            bcopy = bcopy / factor;
            bDigitNum++;
        }
        minp = a > b ? b : a;
        maxp = a > b ? a : b;
 
        //--------comput sum(R) and sizeof(R)
        computeR();
 
        //--------comput sum(L) and sizeof(L)
        computeL();
 
        //compute final result, result = sumL*factor*sizeR + sumR*sizeL
        long long factor = round(pow(10.0, bDigitNum + 1));
        long long res = sumL * factor % MAXRES;
        res = res * sizeR % MAXRES;
        res = (res + (sizeL * sumR)) % MAXRES;
        return res;
    }
};
int Test::minp;
int Test::maxp;
long long Test::sumL;
long long Test::sizeL;
long long Test::sizeR;
long long Test::sumR;
vector<int> Test::mulStartVal;
//------------------------------------------
int main(int argc, char *argv[])
{
    int a = 2, b = 4;
    if(argc > 2) {
      a = atoi(argv[1]);
      b = atoi(argv[2]);
    }
    cout<<Test::run(a,b)<<endl;
    return 0;
}
