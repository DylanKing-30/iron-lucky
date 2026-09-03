/*
* File:     main.cpp
* Author:   Dylan King
* Date:     9/03/2026
*
* Description:  A text-based strategy game.
*/

#include <iostream>
#include <string>
#include <random>

using namespace std;

int main() {

    cout << "Strategy game online.\n";

    //  declare variables
    string kingdom_name;
    string user_name;

    int food = 105;
    int gold = 100;
    int stone = 100;
    int wood = 100;
    int soldiers = 1;
    int day = 1;

    bool game_running = true;
    bool farm_available = false;
    bool training_grounds_available = false;
    bool mine_available = false;
    bool loghouse_available = false;

    //  prompt user for their player name
    cout << "Your majesty, what shall you be known as: ";
    getline(cin, user_name);

    //  prompt user for name of their kingdom
    cout << "My liege, what shall your kingdom be called: ";
    getline(cin, kingdom_name);

    // output: Long live user_name of kingdom_name
    cout << "\n\nLong live " << user_name << " of " << kingdom_name << "!";

    //  gameplay loop
    while (game_running) {

        //change stats from buildings
        if (farm_available) {
            food += 5;
        }
        if (training_grounds_available) {
            soldiers += 5;
        }
        if (mine_available) {
            stone += 5;
        }
        if (loghouse_available) {
            wood += 5;
        }

        //  change food stat based on soldier population
        food = food - (soldiers * 5);

        //  display stats of the kingdom
        cout << "\nDay " << day << endl;
        cout << "   Food: " << food << endl;
        cout << "   Gold: " << gold << endl;
        cout << "   Stone: " << stone << endl;
        cout << "   Wood: " << wood << endl;
        cout << "   Soldiers: " << soldiers << endl;

        //  display choices
        cout << "\nEnter the number of the choice you make.";
        cout << "\n\n1. Hire soldiers\n";
        cout << "2. Go to Builder\n";
        cout << "3. Raid nearby villages\n";

        int choice;
        cin >> choice;

        //  if player selects hire soldiers
        int buy_soldiers;

        if (choice == 1) {
            bool buying_soldiers = true; //     sets up loop

            while (buying_soldiers) {
                cout << "How many soldiers would you like to buy? (50g each) \n";
                cin >> buy_soldiers;

                if (gold < (buy_soldiers * 50)) {
                    cout << "Insufficient funds. Please reselect.\n"; //    resets loop
                }
                
                else {
                    gold = gold - (buy_soldiers * 50);
                    soldiers = buy_soldiers + soldiers;
                    day += 1;
                    cout << "\n\nYou have bought " << buy_soldiers << " soldier(s) and spent " << buy_soldiers * 50 << " gold.\n\n";

                    buying_soldiers = false; //     end loop
                }
            }
        }

        int building;
        if (choice == 2) {
            bool in_shop = true; //     sets up loop

            while (in_shop) {
                cout << "Everything costs 50 stone and 50 wood.\nWould you like to buy...\n     1.  farm\n      2.  training grounds\n      3.  mine\n      4.  log house\n     5.  Exit (You are too poor!)\n\n";
                cin >> building;
                if (building == 1 && wood >= 50 && stone >= 50 && farm_available == false) {
                    wood = wood - 50;
                    stone = stone - 50;
                    farm_available = true;
                    cout << "\n\nYou have built a farm!\n\n";
                    day += 1;
                    in_shop = false;
                }
                else if (building == 2 && wood >= 50 && stone >= 50 && training_grounds_available == false) {
                    wood = wood - 50;
                    stone = stone - 50;
                    training_grounds_available = true;
                    cout << "\n\nYou have built a training grounds!\n\n";
                    day += 1;
                    in_shop = false;
                }
                else if (building == 3 && wood >= 50 && stone >= 50 && mine_available == false) {
                    wood = wood - 50;
                    stone = stone - 50;
                    mine_available = true;
                    cout << "\n\nYou have built a mine!\n\n";
                    day += 1;
                    in_shop = false;
                }
                else if (building == 4 && wood >= 50 && stone >= 50 && loghouse_available == false) {
                    wood = wood - 50;
                    stone = stone - 50;
                    loghouse_available = true;
                    cout << "\n\nYou have built a log house!\n\n";
                    day += 1;
                    in_shop = false;
                }
                else if (building == 5) {
                    cout << "\n\nThe Builder laughed at you and wasted your day :(\n\n";
                    day += 1;
                    in_shop = false;
                }
                else {
                    cout << "Insufficient resources, incorrect selection, or you already have this building. Please reselect.\n\n";
                }

            }
        }

        if (choice == 3) {
            bool in_raid = true; //     sets up loop
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<int> distrib(1, 20);
            
            int fate = distrib(gen);

            cout << "May fate be with you.";

            if (fate == 20) {
                stone += (soldiers * 5);
                wood += (soldiers * 5);
                gold += (soldiers * 10);
                cout << "\nLady Luck was on your side!!\nYou decimated a rival kingdom and stole all of their goods!\n";
                cout << "\n You had zero casualties!";
                cout << "\n You gained " << soldiers * 5 << " stone.";
                cout << "\n You gained " << soldiers * 5 << " wood.";
                cout << "\n You gained " << soldiers * 10 << " gold.\n\n";
            }
            else if (fate > 15) {
                int casualties = soldiers * 0.2;
                cout << "\nYou conquered the nearby villages and took their goods!\n";
                if (soldiers > 5) {
                    soldiers -= casualties;
                     cout << "\nYou had " << casualties << " casualties.";
                }
                else {
                    cout << "\nYour small band had no casualties.";
                }
                stone += (soldiers * 2);
                wood += (soldiers * 2);
                gold += (soldiers * 5);
                cout << "\n You gained " << soldiers * 2 << " stone.";
                cout << "\n You gained " << soldiers * 2 << " wood.";
                cout << "\n You gained " << soldiers * 5 << " gold.\n\n";
            }
            else if (fate > 10) {
                int casualties = soldiers * 0.4;
                cout << "\nYou conquered the nearby villages and took their goods, but it was costly.\n";
                if (soldiers > 5) {
                    soldiers -= casualties;
                     cout << "\nYou had " << casualties << " casualties.";
                }
                else {
                    cout << "\nYour small band had no casualties.";
                }
                stone += (soldiers * 2);
                wood += (soldiers * 2);
                gold += (soldiers * 4);
                cout << "\n You gained " << soldiers * 2 << " stone.";
                cout << "\n You gained " << soldiers * 2 << " wood.";
                cout << "\n You gained " << soldiers * 4 << " gold.\n\n";
            }
            else if (fate > 5) {
                int casualties = soldiers * 0.6;
                cout << "\nYou stole loot from the local tribes, but were driven away by a rival kingdom.\n";
                if (soldiers > 5) {
                    soldiers -= casualties;
                     cout << "\nYou had " << casualties << " casualties.";
                }
                else {
                    cout << "\nYour small band had no casualties.";
                }
                stone += (soldiers * 1);
                wood += (soldiers * 1);
                gold += (soldiers * 3);
                cout << "\n You gained " << soldiers * 2 << " stone.";
                cout << "\n You gained " << soldiers * 2 << " wood.";
                cout << "\n You gained " << soldiers * 5 << " gold.\n\n";
            }
            else if (fate > 1) {
                int casualties = soldiers * 0.8;
                cout << "\nYour raid failed miserably.\n";
                if (soldiers > 5) {
                    soldiers -= casualties;
                     cout << "\nYou had " << casualties << " casualties.";
                }
                else {
                    cout << "\nYour small band had no casualties.";
                }
                stone += (soldiers * 1);
                wood += (soldiers * 1);
                gold += (soldiers * 1);
                cout << "\n You gained " << soldiers * 2 << " stone.";
                cout << "\n You gained " << soldiers * 2 << " wood.";
                cout << "\n You gained " << soldiers * 5 << " gold.\n\n";
            }
            else {
                cout << "\nYou were ambushed by a rival army. You swear you saw a demon on that battlefield.";
                soldiers = 1;
                cout << "\nYou are now all alone\n\n\n";
            }
            day += 1;
            bool in_raid = false;
        }
        if (choice == 4) {
            game_running = false;
        }
    }
    return 0;
}

