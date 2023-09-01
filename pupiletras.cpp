#include <iostream>

void print(char** A) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
            std::cout << A[i][j]<<" ";
            if (j == 5) {
                std::cout << std::endl;
            }
        }
    }
}

bool palindromo(char* word,int n){
    for(int i=0,f=n-1;i<=f && word[i]!=word[f];i++,f--){
        return 0;
    }
    return 1;
}

bool findV1(char**A, int i, int j, char* word, int n){
    if (5-n-i<0 || A[i][j]!=word[0])
        return 0;
    else{
        for(int c=1;c<n;c++){
            if (A[i+c][j]!=word[c])
                return 0;
        }
    }
    return 1;
}

bool findV2(char**A, int i, int j, char* word, int n){
    if (i < n-1 || A[i][j]!=word[0])
        return 0;
    else{
        for(int c=1;c<n;c++){
            if (A[i-c][j]!=word[c])
                return 0;
        }
    }
    return 1;
}

bool findH1(char**A, int i, int j, char* word, int n){
    if (6-n-j<0 || A[i][j]!=word[0])
        return 0;
    else{
        for(int c=1;c<n;c++){
            if (A[i][j+c]!=word[c])
                return 0;
        }
    }
    return 1;
}

bool findH2(char**A, int i, int j, char* word, int n){
    if (j < n-1 || A[i][j]!=word[0])
        return 0;
    else{
        for(int c=1;c<n;c++){
            if (A[i][j-c]!=word[c])
                return 0;
        }
    }
    return 1;
}

int find(char**A,char* word,int n){
    int res=0;

    for (int i=0;i<5;i++){
        for (int j=0;j<6;j++){
            res+=findV1(A,i,j,word,n);
            res+=findV2(A,i,j,word,n);
            res+=findH1(A,i,j,word,n);
            res+=findH2(A,i,j,word,n);
        }
    }
    if (palindromo(word,n)){
        if (n==1)
            return res/4;
        else
            return res/2;
    }
    return res;
}


int main()
{
    char** A = new char* [5];
    for (int i = 0; i < 5; i++) {
        A[i] = new char[6];
    }
    **A = 'P';
    *(*A + 1) = 'J';
    *(*A + 2) = 'P';
    *(*A + 3) = 'A';
    *(*A + 4) = 'T';
    *(*A + 5) = 'O';

    **(A + 1) = 'P';
    *(*(A + 1) + 1) = 'L';
    *(*(A + 1) + 2) = 'O';
    *(*(A + 1) + 3) = 'L';
    *(*(A + 1) + 4) = 'A';
    *(*(A + 1) + 5) = 'P';

    **(A + 2) = 'A';
    *(*(A + 2) + 1) = 'T';
    *(*(A + 2) + 2) = 'T';
    *(*(A + 2) + 3) = 'H';
    *(*(A + 2) + 4) = 'L';
    *(*(A + 2) + 5) = 'O';

    **(A + 3) = 'T';
    *(*(A + 3) + 1) = 'H';
    *(*(A + 3) + 2) = 'A';
    *(*(A + 3) + 3) = 'T';
    *(*(A + 3) + 4) = 'O';
    *(*(A + 3) + 5) = 'J';

    **(A + 4) = 'O';
    *(*(A + 4) + 1) = 'I';
    *(*(A + 4) + 2) = 'P';
    *(*(A + 4) + 3) = 'O';
    *(*(A + 4) + 4) = 'L';
    *(*(A + 4) + 5) = 'M';



    print(A);

    char s[]="PATO";
    int n=sizeof(s)-1;

    int res=find(A,s,n);

    std::cout<<"The word "<<s<<" was found "<<res<<" times.";

    for(int i=0;i<5;i++){
        delete[] A[i];
    }
    delete[] A;

    return 0;
}