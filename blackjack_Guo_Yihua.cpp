#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <algorithm>

/*
In Blackjack, you are trying to build a hand with a higher value than the other player without going over 21.
In the usual case, players get cards from a full deck of cards, aces may count as either 11 or 1, and face cards are worth 10.
But since this is a simplified two-players game, I modified the rules by changing a full deck of cards to number cards only,
from 1 to 11, and ace will only have the value equals 1.
Each player will initialize with two cards randomly chosen from the deck. For each round, players will have the chance to choose,
whether to hit(get another card) or stand(stay with the current hand). The choice round will be alternated between two players.
I design the game to be risky that even a player gets to 21, the player can still choose to hit or stand, so this is completely
up to the player, but each time a warning message will be printed.
After both players have decided to stand, or one of the players gets over 21, the game will end. A result will be printed out.
If two players' hands have the same value, it is a push. If a player gets a hand worth more than 21, it is called a bust. Otherwise,
the game is going to print a congratulations sentence to the winning player.
*/

using namespace std;

//prototypes of three functions
void Image(int n);
int Result(int, int);
int Total(vector <int>);

int main()
{
    //prompt for start of the game and basic instructions
    cout << "*** Welcome to Simplified Two Player Blackjack! ***" << endl;
    cout << "\nIn this game, you will randomly get cards from a deck of 11 cards(Ace to Jack)." << endl;
    cout << "All cards are worth the number they show. Ace=1 and Jack=11." << endl;
    cout << "Try to build a hand with a higher level than the other player without going over 21." << endl;

    //prompt for players to enter their names
    char name1[50];
    cout << "\nPlayer 1, please enter your name: ";
    cin.getline(name1, 50);
    cin.clear(); //clear the input buffer

    char name2[50];
    cout << "\nPlayer 2, please enter your name: ";
    cin.getline(name2, 50);
    cin.clear(); //clear the input buffer
    system("CLS"); //clear the screen

    //each player has a vector that store the player's hand
    vector <int> player1_cards;
    vector <int> player2_cards;

    //the game exits when function Result is called and game result is displayed
    while(1)
    {
        //while I shuffle the cards, I also need to tell the player that the cards are shuffled
        cout << "Shuffling... ..." << endl;

        //deck is a vector that contains 11 elements
        vector <int> deck;
        for (int i=0; i<11; i++)
            deck.push_back(i+1);

        srand(time(NULL)); //set the time to NULL
        std::random_shuffle(deck.begin(), deck.end()); //shuffle the deck

        //get both players the first two cards
        player1_cards.push_back(deck[0]);
        player2_cards.push_back(deck[1]);
        player1_cards.push_back(deck[2]);
        player2_cards.push_back(deck[3]);

        //player's choice will be recorded as char
        char player1_choice;
        char player2_choice;
        //player_hit is 1 if the player chooses hit, and 0 if the player stands
        int player1_hit = 1;
        int player2_hit = 1;
        //call the function total for the first two cards and store the return totals to an integer
        int player1_total = Total(player1_cards);
        int player2_total = Total(player2_cards);
        //the string button serves as a button to switch player
        string button;
        //counter counts the next card in the deck
        int counter = 0;

        //display the first two cards and the total of first two cards for player one
        cout << "\n" << name1 << ", your first two cards are: " << endl;
        Image(player1_cards[0]);
        Image(player1_cards[1]);
        cout << "\n" << name1 << ", your current total is " << player1_total << endl;

        //prompt for player one to switch to player two
        cout << "\nHit Enter to switch player. " << endl;
        getline(cin, button);
        system("CLS"); //clear the screen so that current player will not read previous player's cards

        //display the first two cards and the total of first two cards for player two
        cout << "\n" << name2 << ", your first two cards are: " << endl;
        Image(player2_cards[0]);
        Image(player2_cards[1]);
        cout << "\n" << name2 << ", your current total is " << player2_total << endl;
        //prompt for player two to switch to player one
        cout << "\nHit Enter to switch player. " << endl;
        getline(cin, button);
        system("CLS"); //clear the screen so that current player will not read previous player's cards


        //this loop breaks when both players stand or at least one of they gets over 21
        do
        {
            //after switch to player one, display the current total and prompt for hit or stand
            cout << "\n" << name1 << ", your current total is " << player1_total << endl;
            cout << "Hit(h) or Stand(s): " << endl;
            cout << "You may hit as many times as you like, but if you go over 21 you lose." << endl;
            cin >> player1_choice;

            //Input Validation
            while (player1_choice!='h' && player1_choice!='s' )
            {
                cout << "Wrong input! Hit(h) or Stand(s): ";
                cin >> player1_choice;
                cin.clear();
                while(cin.get()!='\n'){} //clear input buffer
            }

            //get a new card from the deck, if player one choose to hit
            if(player1_choice  == 'h'){
                player1_cards.push_back(deck[counter+4]);
                //display the card
                cout << "\n" << name1 << ", your new card is: " << endl;
                Image(deck[counter+4]);
                counter++; //counter moves to a next card
            }
            else
                player1_hit = 0; //counter does not change if player one chooses to stand


			//call the function Total() and update player one's total
			cout << endl;
			player1_total = Total(player1_cards);
            //display the current total for player one and switch to player two
			cout << "Your total now is " << player1_total << endl;
            cout << "\nHit Enter to switch player. " << endl;
            getline(cin, button);
            cin.clear();
            while(cin.get()!='\n'){} //clear input buffer
            system("CLS"); //clear the screen for player switch

            ////after switch to player two, display the current total and prompt for hit or stand
            cout << "\n" << name2 << ", Your current total is " << player2_total << endl;
            cout << "Hit(h) or Stand(s): " << endl;
            cout << "You may hit as many times as you like, but if you go over 21 you lose." << endl;
            cin >> player2_choice;

            //Input Validation
            while (player2_choice!='h' && player2_choice!='s' )
            {
                cout << "Wrong input! Hit(h) or Stand(s): ";
                cin >> player2_choice;
                cin.clear();
                while(cin.get()!='\n'){} //clear input buffer
            }

            //get a new card from the deck, if player one choose to hit
            if(player2_choice == 'h'){
            player2_cards.push_back(deck[counter+4]);
            //display the new cards
            cout << "\n" << name2 << ", your new card is: " << endl;
            Image(deck[counter+4]);
            counter++; //counter moves to a next card
            }
            else
                player2_hit = 0; //counter does not change if player two choose stand

            //call the function Total() and update player two's total
            cout << endl;
            player2_total = Total(player2_cards);
            //display the current total of player two and switch back to player one
            cout << "\n" << name2 << ", your total now is " << player2_total << endl;
            cout << "\nHit Enter to switch player. " << endl;
            getline(cin, button);
            cin.clear();
            while(cin.get()!='\n'){} //clear input buffer
            system("CLS"); //clear the screen

        } while ((player1_hit || player2_hit) && (player1_total < 22 && player2_total < 22)); //end of loop

        //call the function Result() and it will print out the winner and return an integer(1=player one wins, 2=player two wins)
        int winner;
        cout << endl;
        cout << endl;
        cout << endl;
        winner = Result(player1_total, player2_total);

        //exit the loop when a result is reached and print out congratulations message
        if (winner == 1)
        {
            cout << "\n**** Player One Wins!!! ****" << endl;
            cout << "Congratulations to " << name1 << " !!" << endl;
            break;
        } else if(winner == 2)
        {
            cout << "\n**** Player Two Wins!!! ****" << endl;
            cout << "Congratulations to " << name2 << " !!" << endl;
            break;
        }
        cout << endl;
        cout << endl;
        cout << endl;
        break;
    }
    return EXIT_SUCCESS;
}

//this function takes a vector of cards and returns the total scores of the hand
int Total(vector <int> cards)
{
    int sum = 0;
    for(int i=0; i<cards.size();i++)
        sum+=cards[i];
    return sum;
}

//this function takes two scores and returns the winner
int Result(int score1, int score2)
{
    int win;

    if(score1 == score2) //if two players' hands have the same value, it is a push.
        cout << "\n**** Push. **** " << endl << "\nYour totals equal." << endl;
    else if(score1 > 21 && score2 > 21) // If both of the players end up having hands worth more than 21, either of them gets a bust.
        cout << "\n**** Bust. **** " << endl << "\nBoth of you get over 21." << endl;
    else if (score1 <= 21 && score2 <= 21 && score1>score2) //case of player one wins
        win = 1;
    else if (score1 <= 21 && score2 <= 21 && score1<score2) //case of player two wins
        win = 2;
    else if(score1 > 21 && score2 <= 21) //case of player two wins and player one bust
        win = 2;
    else if(score1 <= 21 && score2 > 21) //case of player one wins and player two bust
        win = 1;

    return win;
}

//self-designed number cards (are they pretty :))
void Image(int n)
{
    switch (n)
    {
    case 1:
        cout << "----------------" << endl;
        cout << "|              |" << endl;
        cout << "|              |" << endl;
        cout << "|      /\\      |" << endl;
        cout << "|     /  \\     |" << endl;
        cout << "|    /____\\    |" << endl;
        cout << "|   /      \\   |" << endl;
        cout << "|  /        \\  |" << endl;
        cout << "|              |" << endl;
        cout << "|              |" << endl;
        cout << "----------------" << endl;
        break;
    case 2:
        cout << "----------------" << endl;
        cout << "|              |" << endl;
        cout << "|     ____     |" << endl;
        cout << "|    /    \\    |" << endl;
        cout << "|          |   |" << endl;
        cout << "|         /    |" << endl;
        cout << "|       /      |" << endl;
        cout << "|     /        |" << endl;
        cout << "|   /______    |" << endl;
        cout << "|              |" << endl;
        cout << "----------------" << endl;
        break;
    case 3:
        cout << "----------------" << endl;
        cout << "|              |" << endl;
        cout << "|     ____     |" << endl;
        cout << "|    /    \\    |" << endl;
        cout << "|          |   |" << endl;
        cout << "|     ____/    |" << endl;
        cout << "|         \\    |" << endl;
        cout << "|          |   |" << endl;
        cout << "|    \\____/    |" << endl;
        cout << "|              |" << endl;
        cout << "----------------" << endl;
        break;
    case 4:
        cout << "----------------" << endl;
        cout << "|              |" << endl;
        cout << "|      / |     |" << endl;
        cout << "|     /  |     |" << endl;
        cout << "|    /   |     |" << endl;
        cout << "|   /____|__   |" << endl;
        cout << "|        |     |" << endl;
        cout << "|        |     |" << endl;
        cout << "|        |     |" << endl;
        cout << "|              |" << endl;
        cout << "----------------" << endl;
        break;
    case 5:
        cout << "----------------" << endl;
        cout << "|              |" << endl;
        cout << "|    ______    |" << endl;
        cout << "|    |         |" << endl;
        cout << "|    |____     |" << endl;
        cout << "|         \\    |" << endl;
        cout << "|          |   |" << endl;
        cout << "|    \\____/    |" << endl;
        cout << "|              |" << endl;
        cout << "|              |" << endl;
        cout << "----------------" << endl;
        break;
    case 6:
        cout << "----------------" << endl;
        cout << "|              |" << endl;
        cout << "|       /      |" << endl;
        cout << "|      /       |" << endl;
        cout << "|     /___     |" << endl;
        cout << "|    /    \\    |" << endl;
        cout << "|   |      |   |" << endl;
        cout << "|    \\____/    |" << endl;
        cout << "|              |" << endl;
        cout << "|              |" << endl;
        cout << "----------------" << endl;
        break;
    case 7:
        cout << "----------------" << endl;
        cout << "|              |" << endl;
        cout << "|   ________   |" << endl;
        cout << "|          /   |" << endl;
        cout << "|         /    |" << endl;
        cout << "|        /     |" << endl;
        cout << "|       /      |" << endl;
        cout << "|      /       |" << endl;
        cout << "|     /        |" << endl;
        cout << "|              |" << endl;
        cout << "----------------" << endl;
        break;
    case 8:
        cout << "----------------" << endl;
        cout << "|              |" << endl;
        cout << "|     ____     |" << endl;
        cout << "|    /    \\    |" << endl;
        cout << "|   |      |   |" << endl;
        cout << "|    \\____/    |" << endl;
        cout << "|    /    \\    |" << endl;
        cout << "|   |      |   |" << endl;
        cout << "|    \\____/    |" << endl;
        cout << "|              |" << endl;
        cout << "----------------" << endl;
        break;
    case 9:
        cout << "----------------" << endl;
        cout << "|              |" << endl;
        cout << "|     ____     |" << endl;
        cout << "|    /    \\    |" << endl;
        cout << "|   |      |   |" << endl;
        cout << "|    \\____/    |" << endl;
        cout << "|        /     |" << endl;
        cout << "|       /      |" << endl;
        cout << "|      /       |" << endl;
        cout << "|              |" << endl;
        cout << "----------------" << endl;
        break;
    case 10:
        cout << "----------------" << endl;
        cout << "|              |" << endl;
        cout << "|   _    ___   |" << endl;
        cout << "|  /|   /   \\  |" << endl;
        cout << "|   |  /     \\ |" << endl;
        cout << "|   |  |     | |" << endl;
        cout << "|   |  |     | |" << endl;
        cout << "|   |  \\     / |" << endl;
        cout << "|  _|_  \\___/  |" << endl;
        cout << "|              |" << endl;
        cout << "----------------" << endl;
        break;
    case 11:
        cout << "----------------" << endl;
        cout << "|              |" << endl;
        cout << "|   ________   |" << endl;
        cout << "|        |     |" << endl;
        cout << "|        |     |" << endl;
        cout << "|        |     |" << endl;
        cout << "|        |     |" << endl;
        cout << "|       /      |" << endl;
        cout << "|   \\__/       |" << endl;
        cout << "|              |" << endl;
        cout << "----------------" << endl;
        break;
    }

}
