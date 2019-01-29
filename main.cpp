#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
int times [1001]={0}; //ftable
vector<long long int> exp;
string dictionary [1001];
long long int sentenceHash[1000];
long long int dictionaryHash[1000];
int modula = 1000000007;


long long int rehash(int hash1, int hash2){
    long long int h2 = sentenceHash[hash2];
    long long int difh = exp[hash2-hash1]*sentenceHash[hash1]%modula;
    long long int result = h2-difh;
    result=result%modula;
    result=result+modula;
    result=result%modula;
    return result;
}

int fun(int sentenceLength, int start, int dicSize) {

    int count = 0;
    if (times[start] == 0) {

        if (start == sentenceLength) {

            times[start] = 1;
            return 1;
        }
        for (int i = 0; i < dicSize; i++) {
            if (start == 0) {

                if ( dictionaryHash[i] == sentenceHash[dictionary[i].length() - 1]) {

                    count =count + fun(sentenceLength, start + dictionary[i].length(), dicSize);
                    count=count%modula;
                }
            } else {

                if ((dictionaryHash[i]%modula) == rehash(start - 1, start + dictionary[i].length() - 1)%modula) {
                    count =count + fun(sentenceLength, start + dictionary[i].length(), dicSize);
                    count=count%modula;
                }
            }
        }
        times[start]=count;
    }else{
        count=times[start];
    }
    return count;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Run the code with the following command: ./project5 [input_file] [output_file]" << endl;
        return 1;
    }

    ifstream infile(argv[1]);
    ofstream outfile;
    outfile.open(argv[2]);

    string line;
    infile >> line;
    vector<char> sentence;      ///sonradan ekledim
    copy(line.begin(), line.end(), back_inserter(sentence));      //sonradan ekledim
    int num;
    infile >> num;

    for (int i = 0; i < num; ++i) {
        infile >> dictionary[i];
    }

    int sentenceLength = line.length();


    exp.push_back(1);
    for(int i=1;i<sentenceLength;i++){

        exp.push_back(exp[i-1]*31%modula);

    }

    sentenceHash[0]=sentence[0];
    for (int i = 1; i < sentenceLength; i++) {
//        sentenceHash[i] = ((line.at(i))+sentenceHash[i-1]*exp[1])%modula;
        sentenceHash[i] = ((sentence[i])+sentenceHash[i-1]*exp[1])%modula;

    }

    for (int i = 0; i < num; i++) {
        int wordLength = dictionary[i].length();
        for (int j = 0; j < wordLength; ++j) {
//            if (j == 0)
//                dictionaryHash[i] = dictionary[i].at(0);
//            else
//                dictionaryHash[i] = (((dictionaryHash[i]) * exp[1]) + dictionary[i].at(j)) % modula;
            if (j > 0)
                dictionaryHash[i] = (((dictionaryHash[i]) * exp[1]) + dictionary[i].at(j)) % modula;
            else
                dictionaryHash[i] = dictionary[i].at(0);

        }

    }

    int result = fun(sentenceLength, 0, num);
    result+=modula;
    result%=modula;
    outfile<<result<<endl;
    outfile.close();
    return 0;
}