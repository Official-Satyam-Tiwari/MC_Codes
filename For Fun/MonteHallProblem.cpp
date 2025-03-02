#include <iostream>
#include <TRandom3.h>

using namespace std;

int main(){
    TRandom3 random;
    random.SetSeed(0);
    int n;
    int wins_without_switch = 0;
    int wins_with_switch = 0;

    cout << "Enter the number of events to simulate : ";
    cin >> n;

    for (int i=1;i<=n;++i){
        int car[3];
        int car_index = random.Integer(3); // Which door has the car from 0, 1, 2
        car[car_index] = 1;
        for (int j=0;j<3;++j){
            if(j==car_index) continue;
            car[j] = 0;
        }
        int contestent_chooses = random.Integer(3); // Which door the contestant chooses from 0, 1, 2
        int host_opens;
        for (int j=0;j<3;++j){
            if(j==contestent_chooses) continue;
            if(car[j]==1) continue;
            host_opens = j;
            break;
        }
        //Case 1: Contestant doesn't switches
        if(car[contestent_chooses]==1) wins_without_switch++;

        //Case 2: Contestant switches
        int new_choice;
        for (int j=0;j<3;++j){
            if(j==contestent_chooses) continue;
            if(j==host_opens) continue;
            new_choice = j;
            break;
        }
        if(car[new_choice]==1) wins_with_switch++;
    }
    cout << "Case 1: Contestant doesn't switches" << endl;
    cout << "Wins: " << wins_without_switch << endl;
    cout << "Winning probability: " << (double)wins_without_switch/n << endl;
    
    cout << "Case 2: Contestant switches" << endl;
    cout << "Wins: " << wins_with_switch << endl;
    cout << "Winning probability: " << (double)wins_with_switch/n << endl;
    return 0;
}