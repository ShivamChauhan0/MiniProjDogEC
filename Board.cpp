#include "Board.hpp"
#include <iostream>
using namespace std;
/* Shivam Chauhan Extra Credit 
In this class I made monsters and shamans as improvements in the game. They are idnciated by the 'M' and 'S' in the board. The user has the option to fight or interact the monster and shaman, respectively. The user has a 50% chance of winning the interaction, regardless of the mode. Depending on the mode, there are more/less shamans/monsters. I also improved the interface slightly by adding emojis in all of the prompts in the game, such as up arrows, muscles for strength, bricks for walls, and an ogre for the monster. */

Board::Board(char diff, bool d){
  level = diff;
  debug = d;
  wallStrength = 6;
  InitAll();
}

Board::Board(bool d){
  level = 'e';
  debug = d;
  wallStrength = 6;
  InitAll();
}

Board::Board(char diff, string name, bool d) {
  level = diff;
  debug = d;
  mydog.name = name; 
  wallStrength = 6;
  InitAll();
}

void Board::InitAll() {

  bool keepPlaying = true;
  while (keepPlaying) {
    cout << "What level of difficulty do you want (e, m, or h)? 🎮" << endl;
    char c;
    cin >> c;
    level = c;
    startx = rand()% size;
    starty = 0;
    endx = rand() % size;
    endy = size-1; 
    mydog.x = startx;
    mydog.y = starty;
    boardConfig(); 
    addFood();
    addTraps();
    addMonster();
    addShaman(); 
    printBoard();
    playGame();
    cout << "Play again? 🎲 " << endl;
    string s = "no";
    cin>>s;
    if (s == "yes" || s == "Yes" || s == "Y" || s == "y") {
      keepPlaying = true;
      mydog.reset();
      }
    else {
      cout <<"Thanks for playing! 🖱️" << endl;
      keepPlaying = false;
      }
    }

}

void Board::playGame() {
  bool play = true;
  while (play) {
    cout << "Move (u, d, l, r) (⬆️, ⬇️, ⬅️, ➡️) "<<endl;
    cout << mydog.name << "'s Strength (💪):" << mydog.strength << endl;
    char c;
    cin >> c;
    play = moveDog(c);
    printBoard();
    }
}

void Board::addFood() {
/* (5 pts) code for the addFood method goes here
*/
  int amtfood = 0;
  if(level == 'e') {
    amtfood = size;  
    } 
  else if(level == 'm') {
    amtfood = size - 2; 
    } 
  else if(level == 'h') {
    amtfood = size - 4;
  }
  int foodplaced = 0;
  int x, y;
  while(foodplaced < amtfood) {
    x = (rand() % (size-2)) + 1;
    y = (rand() % (size-2)) + 1;
    if(board[x][y] == ' ') {
      board[x][y] = 'F';
      foodplaced++; 
    }
  }
  
}
void Board::addTraps() {
/* (5 pts) code for the addTraps method goes here
*/
  int amttraps = 0;
  if(level == 'e') {
    amttraps = 6;  
    } 
  else if(level == 'm') {
    amttraps = 8; 
    } 
  else if(level == 'h') {
    amttraps = 10;
  }
  int trapsplaced = 0;
  while(trapsplaced < amttraps) {
    int x = (rand() % (size-2)) + 1;
    int y = (rand() % (size-2)) + 1;
    if(board[x][y] == ' ') {
      board[x][y] = 'T';
      trapsplaced++; 
    }
  }
  
}

void Board::addMonster() {
  int amtmonsters = 0; 
  if(level == 'e') {
    amtmonsters = 3;  
    } 
  else if(level == 'm') {
    amtmonsters = 5; 
    } 
  else if(level == 'h') {
    amtmonsters = 7;
  }
  int monstersplaced = 0;
  while(monstersplaced < amtmonsters) {
    int x = (rand() % (size-2)) + 1;
    int y = (rand() % (size-2)) + 1;
    if(board[x][y] == ' ') {
      board[x][y] = 'M';
      monstersplaced++; 
    }
    }
  }

void Board::addShaman() {
  int amtshamans = 0; 
  if(level == 'e') {
    amtshamans = 7;  
    } 
  else if(level == 'm') {
    amtshamans = 5; 
    } 
  else if(level == 'h') {
    amtshamans = 3;
  }
  int shamansplaced = 0;
  while(shamansplaced < amtshamans) {
    int x = (rand() % (size-2)) + 1;
    int y = (rand() % (size-2)) + 1;
    if(board[x][y] == ' ') {
      board[x][y] = 'S';
      shamansplaced++; 
    }
    }
  }

void Board::boardConfig() {
/* (8 pts) code for the boardConfig method goes here 
*/
  for(int i = 0; i < size; i++) {
    for(int j = 0; j < size; j++) {
      board[i][j] = ' ';
      }
    }
  for(int i =0; i < size; i++) {
    board[0][i] = '-';
    board[i][0] = '|';
    board[19][i] = '-';
    board[i][19] = '|';
    board[0][19] = '|'; /* creates borders */
    }
  int maxwalls = 0; /* depends on what difficulty */ 
  if(level == 'e') {
    maxwalls = 20;
    } 
  else if(level == 'm') {
    maxwalls = 50;
    } 
  else if(level == 'h') {
    maxwalls = 75;
    }
  int walls = 0;
  int kindofwall = 0;
  while(walls < maxwalls) {
    for(int i =1; i<20; i = i+2) {
      for(int j =1; j<20; j = j+2) {
        kindofwall = rand()%2; /* decides if vertical or horizontal */
        if(kindofwall == 0) {
          if(j>=19) {
            j--;
            }
          if(i>=19) {
            i--;
            }
          board[i][j] = '|'; /* itertes backwards and adds walls */
          walls++;
          } 
        else if(kindofwall == 1) {
          if(j>=19) {
            j--;
            }
          if(i>=19) {
            i--;
            }
          board[i][j] = '-'; /* itertes backwards and adds walls */
          walls++; 
          }
        }
      }
    }
  board[startx][starty] = 'D'; /* dog position */
  board[endx][endy] = ' ';
  mydog.x = startx;
  mydog.y = starty;
}


void Board::printBoard() {
/* (8 pts) code for the printBoard method goes here
*/
  for(int i = 0; i < size; i++) {
    for(int j = 0; j < size; j++) {
      cout << board[i][j]; /* prints blank board to start */
      cout << ' ';
    }
    cout << endl;
  }
}
bool Board::moveDog(char c) {
/* (12 pts) code for the moveDog method goes here
*/
  if(c == 'r') { /* for moving right */
    if(mydog.y < 19) {
      board[mydog.x][mydog.y] = ' ';
      if(board[mydog.x][mydog.y+1] == 'F'){
        mydog.changeStrength(rand()%15+2); /* if food adds more strength and moves in y */
        mydog.printDog();
      }
      if(board[mydog.x][mydog.y+1] == 'T'){
        mydog.changeStrength(-(rand()%15+2)); /* if trap removes somestrength and moves in y */
        mydog.printDog();
      }
      if(board[mydog.x][mydog.y+1] == 'M'){
         if(mydog.strength > 4) {
          cout << "Oh no you encountered a monster! 👹 Do you want to fight it? (For 4 strength) 💪 (y/n)" << endl;
          char z;
          cin >> z;
          if(z == 'y') { /* option to fight monster */
            mydog.changeStrength(-4); 
            int randomnumber = rand()%2;
            if(randomnumber == 0) {
              cout << "You won the fight 🏆, move ahead and again 10 strength! 💪" << endl; 
              mydog.printDog(); 
              if(mydog.x == endx && mydog.y == endy){ /* if at end ends game */
                mydog.won();
                return false;
                }
               mydog.changeStrength(10);
              }
              if(randomnumber == 1) {
                cout << "Oh no you lost the fight 😵, you lose 5 strength! 💪" << endl; 
               mydog.printDog();
              if(mydog.x == endx && mydog.y == endy){ /* if at end ends game */
                mydog.won();
                return false;
                }
                 mydog.changeStrength(-5);
              }
            }
          if(z == 'n') {
            board[mydog.x][mydog.y] = 'D';    /* does not fight monster */
          }
        }
        mydog.printDog();
      }
       if(board[mydog.x][mydog.y+1] == 'S'){
         if(mydog.strength > 4) {
          cout << "Looks like you encountered a shaman, do you want to talk to him? 🦋 (For 4 strength) (y/n) 💪" << endl;
          char a;
          cin >> a;
          if(a == 'y') { /* option to encounter shaman */
            mydog.changeStrength(-4); 
            int randomnumber2 = rand()%2;
            if(randomnumber2 == 0) {
              cout << "The shaman deems you as a good dog! 🐶 Gain 8 strength! 💪" << endl; 
              mydog.printDog(); 
              if(mydog.x == endx && mydog.y == endy){ /* if at end ends game */
                mydog.won();
                return false;
                }
               mydog.changeStrength(8);
              }
              if(randomnumber2 == 1) {
                cout << "The shaman deems you as a bad dog! 🌭 Loss 3 strength 💪" << endl; 
               mydog.printDog();
              if(mydog.x == endx && mydog.y == endy){ /* if at end ends game */
                mydog.won();
                return false;
                }
                 mydog.changeStrength(-3);
              }
            }
          if(a == 'n') {
            board[mydog.x][mydog.y] = 'D';    /* does not fight shaman */
          }
        }
        mydog.printDog();
      }
      if((board[mydog.x][mydog.y+1] == '|' || board[mydog.x][mydog.y+1] == '-') && mydog.y < 18) { /* checks if wall is up ahead */
        if(mydog.strength > 6) {
          cout << "Do you want to break the wall 🧱 (For 6 strength) (y/n) 💪" << endl;
          char input;
          cin >> input;
          if(input == 'y') { /* option to break open wall */
            mydog.y = mydog.y+1;
            board[mydog.x][mydog.y] = 'D';
            if(mydog.x == endx && mydog.y == endy){ /* if at end ends game */
              mydog.won();
              return false;
            }
            mydog.changeStrength(-6);
          }
          if(input == 'n') {
            board[mydog.x][mydog.y] = 'D';    /* does not break wall */
          }
        }else{
          board[mydog.x][mydog.y] = 'D';
          cout << "You don't have enough strength to move. 💪" << endl; 
        }
      }else if((board[mydog.x][mydog.y+1] != '|')) {  /* basic movement if not wall */
        mydog.y = mydog.y + 1;
        board[mydog.x][mydog.y] = 'D';
        if(mydog.x == endx && mydog.y == endy) {
          mydog.won();
          return false;
        }
        mydog.changeStrength(-2);  /* loses strength per move  */
        if(mydog.strength <= 0) {
          board[mydog.x][mydog.y] = 'X';  /* dog dies */
          return false;
        } 
      }else {
        board[mydog.x][mydog.y] = 'D';
      }
    }
  return true; 
  }

  if(c == 'l') { /* for moving left */
    if(mydog.y > 1) {
      board[mydog.x][mydog.y] = ' ';
      if(board[mydog.x][mydog.y-1] == 'F'){
        mydog.changeStrength(rand()%15+2); /* messed up */ 
        mydog.printDog();
      }
      if(board[mydog.x][mydog.y-1] == 'T'){
        mydog.changeStrength(-(rand()%15+2));
        mydog.printDog();
      }
         if(board[mydog.x][mydog.y-1] == 'M'){
         if(mydog.strength > 4) {
          cout << "Oh no you encountered a monster! 👹 Do you want to fight it? (For 4 strength) 💪 (y/n)" << endl;
          char z;
          cin >> z;
          if(z == 'y') { /* option to fight monster */
            mydog.changeStrength(-4); 
            int randomnumber = rand()%2;
            if(randomnumber == 0) {
              cout << "You won the fight 🏆, move ahead and again 10 strength! 💪" << endl; 
               mydog.printDog();
              if(mydog.x == endx && mydog.y == endy){ /* if at end ends game */
                mydog.won();
                return false;
                }
               mydog.changeStrength(10);
              }
              if(randomnumber == 1) {
                cout << "Oh no you lost the fight 😵, you lose 5 strength! 💪" << endl; 
               mydog.printDog();
              if(mydog.x == endx && mydog.y == endy){ /* if at end ends game */
                mydog.won();
                return false;
                }
                 mydog.changeStrength(-5);
              }
            }
          if(z == 'n') {
            board[mydog.x][mydog.y] = 'D';    /* does not fight monster */
          }
        }
        mydog.printDog();
      }
       if(board[mydog.x][mydog.y-1] == 'S'){
         if(mydog.strength > 4) {
          cout << "Looks like you encountered a shaman 🦋, do you want to talk to him? (For 4 strength) 💪 (y/n)" << endl;
          char a;
          cin >> a;
          if(a == 'y') { /* option to encounter shaman */
            mydog.changeStrength(-4); 
            int randomnumber2 = rand()%2;
            if(randomnumber2 == 0) {
              cout << "The shaman deems you as a good dog! 🐶 Gain 8 strength! 💪" << endl; 
              mydog.printDog(); 
              if(mydog.x == endx && mydog.y == endy){ /* if at end ends game */
                mydog.won();
                return false;
                }
               mydog.changeStrength(8);
              }
              if(randomnumber2 == 1) {
                cout << "The shaman deems you as a bad dog! 🌭 Loss 3 strength 💪" << endl; 
               mydog.printDog();
              if(mydog.x == endx && mydog.y == endy){ /* if at end ends game */
                mydog.won();
                return false;
                }
                 mydog.changeStrength(-3);
              }
            }
          if(a == 'n') {
            board[mydog.x][mydog.y] = 'D';    /* does not fight shaman */
          }
        }
        mydog.printDog();
      }
      if((board[mydog.x][mydog.y-1] == '|' || board[mydog.x][mydog.y-1] == '-') && mydog.y > 0) {
        if(mydog.strength > 6) {
          cout << "Do you want to break the wall 🧱 (For 6 strength) 💪 (y/n)" << endl;
          char input;
          cin >> input;
          if(input == 'y') {
            mydog.y = mydog.y-1;
            board[mydog.x][mydog.y] = 'D';
            if(mydog.x == endx && mydog.y == endy){
              mydog.won();
              return false;
            }
            mydog.changeStrength(-6);
          }
          if(input == 'n') {
            board[mydog.x][mydog.y] = 'D'; 
          }
        }else{
          board[mydog.x][mydog.y] = 'D';
          cout << "You don't have enough strength to move. 💪" << endl;
        }
      }else if((board[mydog.x][mydog.y-1] != '|')) {
        mydog.y = mydog.y - 1;
        board[mydog.x][mydog.y] = 'D';
        if(mydog.x == endx && mydog.y == endy) {
          mydog.won();
          return false;
        }
        mydog.changeStrength(-2);
        if(mydog.strength <= 0) {
          board[mydog.x][mydog.y] = 'X';
          return false;
        } 
      }
    }
  return true; 
  }

  if(c == 'u') { /* for moving up */
    if(mydog.x > 1) {
      board[mydog.x][mydog.y] = ' ';
      if(board[mydog.x-1][mydog.y] == 'F'){
        mydog.changeStrength(rand()%15+2);
        mydog.printDog();
      }
      if(board[mydog.x-1][mydog.y] == 'T'){
        mydog.changeStrength(-(rand()%15+2));
        mydog.printDog();
      }
         if(board[mydog.x-1][mydog.y] == 'M'){
         if(mydog.strength > 4) {
          cout << "Oh no you encountered a monster! 👹 Do you want to fight it? (For 4 strength) 💪 (y/n)" << endl;
          char z;
          cin >> z;
          if(z == 'y') { /* option to fight monster */
            mydog.changeStrength(-4); 
            int randomnumber = rand()%2;
            if(randomnumber == 0) {
              cout << "You won the fight 🏆, move ahead and again 10 strength! 💪" << endl; 
               mydog.printDog();
              if(mydog.x == endx && mydog.y == endy){ /* if at end ends game */
                mydog.won();
                return false;
                }
               mydog.changeStrength(10);
              }
              if(randomnumber == 1) {
                cout << "Oh no you lost the fight 😵, you lose 5 strength! 💪" << endl; 
               mydog.printDog();
              if(mydog.x == endx && mydog.y == endy){ /* if at end ends game */
                mydog.won();
                return false;
                }
                 mydog.changeStrength(-6);
              }
            }
          if(z == 'n') {
            board[mydog.x][mydog.y] = 'D';    /* does not fight monster */
          }
        }
        mydog.printDog();
      }
       if(board[mydog.x-1][mydog.y] == 'S'){
         if(mydog.strength > 4) {
          cout << "Looks like you encountered a shamann 🦋 do you want to talk to him? (For 4 strength) 💪 (y/n)" << endl;
          char a;
          cin >> a;
          if(a == 'y') { /* option to encounter shaman */
            mydog.changeStrength(-4); 
            int randomnumber2 = rand()%2;
            if(randomnumber2 == 0) {
              cout << "The shaman deems you as a good dog! 🐶 Gain 8 strength! 💪" << endl; 
              mydog.printDog(); 
              if(mydog.x == endx && mydog.y == endy){ /* if at end ends game */
                mydog.won();
                return false;
                }
               mydog.changeStrength(8);
              }
              if(randomnumber2 == 1) {
                cout << "The shaman deems you as a bad dog! 🌭Loss 3 strength 💪" << endl; 
               mydog.printDog();
              if(mydog.x == endx && mydog.y == endy){ /* if at end ends game */
                mydog.won();
                return false;
                }
                 mydog.changeStrength(-3);
              }
            }
          if(a == 'n') {
            board[mydog.x][mydog.y] = 'D';    /* does not fight shaman */
          }
        }
        mydog.printDog();
      }
      if((board[mydog.x-1][mydog.y] == '|' || board[mydog.x-1][mydog.y] == '-') && mydog.x > 0) {
        if(mydog.strength > 6) {
          cout << "Do you want to break the wall 🧱 (For 6 strength) 💪 (y/n)" << endl;
          char input;
          cin >> input;
          if(input == 'y') {
            mydog.x = mydog.x-1;
            board[mydog.x][mydog.y] = 'D';
            if(mydog.x == endx && mydog.y == endy){
              mydog.won();
              return false;
            }
            mydog.changeStrength(-6);
          }
          if(input == 'n') {
            board[mydog.x][mydog.y] = 'D'; 
          }
        }else{
          board[mydog.x][mydog.y] = 'D';
          cout << "You don't have enough strength to move. 💪" << endl;
        }
      }else if((board[mydog.x-1][mydog.y] != '-')) {
        mydog.x = mydog.x-1;
        board[mydog.x][mydog.y] = 'D';
        if(mydog.x == endx && mydog.y == endy) {
          mydog.won();
          return false;
        }
        mydog.changeStrength(-2);
        if(mydog.strength <= 0) {
          board[mydog.x][mydog.y] = 'X';
          return false;
        } 
      }
    }
  return true; 
  }

  if(c == 'd') { /* for moving down */
    if(mydog.x < 19) {
      board[mydog.x][mydog.y] = ' ';
      if(board[mydog.x+1][mydog.y] == 'F'){
        mydog.changeStrength(rand()%15+2);
        mydog.printDog();
      }
      if(board[mydog.x+1][mydog.y] == 'T'){
        mydog.changeStrength(-(rand()%15+2));
        mydog.printDog();
      }
      if(board[mydog.x+1][mydog.y] == 'M'){
         if(mydog.strength > 4) {
          cout << "Oh no you encountered a monster! 👹 Do you want to fight it? (For 4 strength)  💪(y/n)" << endl;
          char z;
          cin >> z;
          if(z == 'y') { /* option to fight monster */
            mydog.changeStrength(-4); 
            int randomnumber = rand()%2;
            if(randomnumber == 0) {
              cout << "You won the fight, 🏆 move ahead and again 10 strength! 💪 " << endl; 
               mydog.printDog(); 
              if(mydog.x == endx && mydog.y == endy){ /* if at end ends game */
                mydog.won();
                return false;
                }
               mydog.changeStrength(10);
              }
              if(randomnumber == 1) {
                cout << "Oh no you lost the fight, 😵 you lose 5 strength! 💪 " << endl; 
               mydog.printDog();
              if(mydog.x == endx && mydog.y == endy){ /* if at end ends game */
                mydog.won();
                return false;
                }
                 mydog.changeStrength(-5);
              }
            }
          if(z == 'n') {
            board[mydog.x][mydog.y] = 'D';    /* does not fight monster */
          }
        }
        mydog.printDog();
      }
       if(board[mydog.x+1][mydog.y] == 'S'){
         if(mydog.strength > 4) {
          cout << "Looks like you encountered a shaman, 🦋 do you want to talk to him? (For 4 strength)  💪(y/n)" << endl;
          char a;
          cin >> a;
          if(a == 'y') { /* option to encounter shaman */
            mydog.changeStrength(-4); 
            int randomnumber2 = rand()%2;
            if(randomnumber2 == 0) {
              cout << "The shaman deems you as a good dog! 🐶 Gain 8 strength! 💪" << endl; 
              mydog.printDog(); 
              if(mydog.x == endx && mydog.y == endy){ /* if at end ends game */
                mydog.won();
                return false;
                }
               mydog.changeStrength(8);
              }
              if(randomnumber2 == 1) {
                cout << "The shaman deems you as a bad dog! 🌭 Loss 3 strength 💪 " << endl; 
               mydog.printDog();
              if(mydog.x == endx && mydog.y == endy){ /* if at end ends game */
                mydog.won();
                return false;
                }
                 mydog.changeStrength(-3);
              }
            }
          if(a == 'n') {
            board[mydog.x][mydog.y] = 'D';    /* does not fight shaman */
          }
        }
        mydog.printDog();
      }
      if((board[mydog.x+1][mydog.y] == '|' || board[mydog.x+1][mydog.y] == '-') && mydog.x < 18) {
        if(mydog.strength > 6) {
          cout << "Do you want to break the wall 🧱 (For 6 strength) 💪 y/n)" << endl;
          char input;
          cin >> input;
          if(input == 'y') {
            mydog.x = mydog.x+1;
            board[mydog.x][mydog.y] = 'D';
            if(mydog.x == endx && mydog.y == endy){
              mydog.won();
              return false;
            }
            mydog.changeStrength(-6);
          }
          if(input == 'n') {
            board[mydog.x][mydog.y] = 'D'; 
          }
        }else{
          board[mydog.x][mydog.y] = 'D';
          cout << "You don't have enough strength to move. 💪"<<endl;
        }
      }else if((board[mydog.x+1][mydog.y] != '-')) {
        mydog.x = mydog.x+1;
        board[mydog.x][mydog.y] = 'D';
        if(mydog.x == endx && mydog.y == endy) {
          mydog.won();
          return false;
        }
        mydog.changeStrength(-2);
        if(mydog.strength <= 0) {
          board[mydog.x][mydog.y] = 'X';
          return false;
        } 
      }
    }
  return true; 
  }
 }
      
    
    

