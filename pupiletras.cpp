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
    for(int i=0,f=n-1;i<f && word[i]!=word[f];i++,f--){
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


int main(){
    const int row = 5;
    const int col = 6;

    char** A = new char* [row];
    for (char i = 0; i < row; i++)
    {
        A[i] = new char[col];
    }
    char valores[row][col] = {
        {'P', 'J', 'P', 'A', 'T', 'O'},
        {'P', 'L', 'O', 'T', 'A', 'P'},
        {'A', 'T', 'T', 'H', 'L', 'O'},
        {'T', 'H', 'A', 'T', 'O', 'L'},
        {'O', 'I', 'P', 'O', 'L', 'M'}};

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            A[i][j] = valores[i][j];
        }
    }

    print(A);

    char s[]="P";
    int n=sizeof(s)-1;

    int res=find(A,s,n);

    std::cout<<"The word "<<s<<" was found "<<res<<" times.";

    for(int i=0;i<5;i++){
        delete[] A[i];
    }
    delete[] A;

    return 0;
}