#include<iostream>
#include<vector>
#ifdef _WIN32
    #include <Windows.h>
#else
    #include <unistd.h>
#endif
using namespace std;

void compTurn(){
    cout<<"\033[1;33m _______     ________     __     __\n|   ____|   |   ___  |   |  |   |  |\n|  |        |  |___| |   |  |   |  |\n|  |        |  ______|   |  |   |  |\n|  |____    |  |         |  |___|  |\n|_______|   |__|         |_________|\033[0m\n";

}

void userTurn(){

    cout<<"\033[1;32m___    ___    _________     __     __\n\\  \\  /  /   |   ___   |   |  |   |  |\n \\  \\/  /    |  |   |  |   |  |   |  |\n  \\    /     |  |   |  |   |  |   |  |\n   |  |      |  |___|  |   |  |___|  |\n   |__|      |_________|   |_________|\033[0m\n";
}

//flag  = 0 means user

int logX(int n){
    return (n==1) ? 0 : (logX(n/2) + 1);
}

void currentState(vector<int> vec){
    cout<<" current pile state: ";
    for(auto u : vec) cout<<u<<" ";
}

void printPile(string s){
    cout<<s<<" selected pile number: ";
}

void printNum(string s){
    cout<<s<<" collected: ";
}

struct ANS{
    int first;
    int second;
};

ANS evaluate(vector<int> & vec){
    int n = vec.size();
    int exor = 0;
    int maxm = 0;
    int idx = 0;
    for(int i = 0;i < n;i++){
        exor ^= vec[i];
        if(vec[i] > maxm){
            maxm = vec[i];
            idx = i;
        }
    }
    if(!exor){
        return (ANS){idx+1,(rand()%maxm)+1};
    }
    int i;
    int pos = logX(exor);
    for(i = 0;i < n;i++){
        if(vec[i] & (1 << pos)) break;
    }
    return (ANS){i+1,vec[i] - (exor ^ vec[i])};
}

void game(int flag){
    int pileID,numberOfCoins;
    vector<int>vec = {1,2,3,4,5};
    int count = 15;
    while(count){
        sleep(1);
        cout<<"-------------------------------------\n|  ";
        currentState(vec);
        cout<<"  |\n-------------------------------------\n";

        if(flag){
            compTurn();
            printPile("CPU");
            ANS ans = evaluate(vec);
            sleep(1);
            cout<<ans.first<<"\n";
            printNum("CPU");
            sleep(1);
            cout<<ans.second<<"\n\n";
            vec[ans.first - 1] -= ans.second;
            count -= ans.second;
        }
        else{
            userTurn();
            here:
            printPile("You");
            cin >> pileID;
            if(pileID > 5 || pileID < 1 || vec[pileID-1] == 0){
                cout<<"\033[1;31mWARNING!!! Enter a valid number.\033[0m\n";
                goto here;
            }
            there:
            printNum("You");
            cin >> numberOfCoins;
            if(vec[pileID - 1] < numberOfCoins){
                cout<<"\033[1;31mWARNING!!! Enter a valid number.\033[0m\n";
                goto there;
            }
            vec[pileID - 1] -= numberOfCoins;
            count -= numberOfCoins;
            cout<<"\n";
        }
        flag ^= 1;
    }
    if(flag) cout<<"\033[1;32mCongrats, You won!!!\033[0m\n";
    else cout<<"\033[1;33mComputer won\033[0m\n";
}

void playgame(){
    char choice;
    cout << "Want to go first [y/n]:";
    cin >> choice;
    if(choice != 'y' && choice != 'n' && choice != 'Y' && choice != 'N'){
        cout<<"\033[1;31mWARNING!!! wrong key pressed.\033[0m\n";
        return playgame();
    }
    if(choice == 'y' || choice == 'Y'){
        game(0);
    }
    else game(1);
}

int main(){

    cout<<"################################################################################\n";
    cout<<"#     This is a simple nim game. You are given a number of piles of coins.     #\n";
    cout<<"#   Playing alternatively, You can select a pile and collect non-zero number   #\n";
    cout<<"#  number of coins from it. The player to collect the last coin from the last  #\n";
    cout<<"#  pile wins the game. Initially, the piles have 1, 2, 3, 4, 5 number of coins.#\n";
    cout<<"################################################################################\n\n\n\n";


    while(true){
        cout<<"press 1 to play the game\npress any other key to exit\n";
        int choice;
        cin >> choice;
        switch(choice){
            case 1 : cout << "_____________________________________\n";
                     playgame();
                     break;
            default : cout<<"Good Bye :)\n";
                     return 0;
        }
    }
}