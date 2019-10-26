AutoManualBlackjack

Background
TL;DR: Easy Blackjack is the same as normal Blackjack except with both of dealer's cards exposed.

The game of Blackjack is played against a dealer. Your objective is to get more points than the dealer without going over 21. The game begins with you placing a bet (e.g. $1), followed by both you (the player) and the dealer being dealt two random cards from a regular French deck (with jokers removed). Unlike regular Blackjack, in Easy Blackjack, both cards held by you and the dealer are dealt face up, meaning that you know exactly how many points you or the dealer has.

For cards from 2 to 10, their points are exactly their pip values (e.g., 3 of spades is worth 3 points). All face cards (i.e., J, Q, K) are worth 10 points. Aces may be counted as 1 or 11 points, whichever makes your total larger without going over 21. When your hand has an ace that counts as 11 points, the hand is said to be soft, otherwise it is hard. For example, A2 would give you a total of 13 points (i.e. soft 13), and A58 would give you a total of 14 points (i.e. hard 14). In all cases, the suits on the cards (e.g. spade or heart) are ignored.

A starting hand with an ace and a 10-point card is called blackjack. Whoever has this hand wins immediately, or tie if both the player and the dealer has blackjack. If the player has blackjack, the player is paid 3 to 2 (i.e. $1.50 for every $1 bet, and you get your original bet of $1 back). If the dealer has blackjack, the player loses the initial bet only.

If neither player or dealer has blackjack, the game continues with the player now able to take one or more actions:

Hit: a card is added to the player's hand. If the hand's total exceeds 21 (i.e. bust) then the player loses immediately.
Stand: the player chooses to keep his/her hand as is.
Double: the player doubles the bet on the starting hand, and chooses to add exactly one more card to it. Similar to hit, the player loses if the hand busts.
Split: if the player starts with two cards of the same value (e.g., 33 or KQ), he/she may "split" the hand into two hands, doubling the bet, and each hand receiving a second card. Split hands do not qualify for blackjack (i.e. receiving AK after splitting is only 21 points). You may take more actions on each hand, including doubling or resplitting if possible. However, when splitting aces, no more action is allowed. You may resplit up to a total of 4 hands.
Surrender: the player forfeits the hand and receives half of the bet back. You may not surrender after any other action has been taken.
The player will finish all of his/her actions before the game moves to the next stage. If the player still has live hands (i.e. has not busted) after taking his/her actions, the dealer will now take action based on predetermined rules:

If the dealer has 18 or more, his/her hand stands.
If the dealer has 16 or less, he/she will hit.
If the dealer has soft 17 he/she will hit, otherwise he/she will stand on hard 17.
If the dealer busts, all of the player's live hands win even money (e.g. $1 bet receives $1 payout). If the dealer does not bust, then each of the player's hand is compared with the dealer's hand, whichever is higher wins.

For students who already know Blackjack, the rules for this assignment are summarized as follows:

Dealer hits on soft 17.
Dealer does not offer insurance (you don't need to know what this is for the assignment).
Player may double on any two cards.
Player may not resplit aces, and split aces receive one card only.
Player may split up to 4 hands.
Player may surrender only on the initial hand.
Blackjack pays 3 to 2.
Player may only bet exactly $1.
For those unfamiliar, we suggest that you play regular Blackjack a few times to understand how the game works.

Setup
Add the source files for this assignment, available in easybj.tar, to your repository, and run make in the newly created asst1 directory.

Warning, make sure to complete remote repository setup for your group before continuing.

cd ~/ece326
tar -xf /cad2/ece326f/src/easybj.tar
git status # should say that "asst1/" directory is untracked
git add asst1
git commit -m "Initial code for Assignment 1"
git tag Asst1-start
git push
git push --tags
cd asst1
make
The starter code is organized as follows:

main.cpp: contains the main function.
shoe.cpp: contains two subclasses of the Shoe base class. InfiniteShoe has an infinite supply of cards, generated at random. FileShoe reads in a prearranged shoe from a file and deals out the cards in the exact order as entered in the file.
shoe.h: contains definition of the Shoe base class.
config.cpp: you should modify this file to implement command line parsing.
config.h: contains definition of the Config class.
player.cpp: you should modify this file to implement manual and automatic mode of playing Easy Blackjack.
player.h: contains definition of the Player base class.
easybj.cpp: you should modify this file to implement Easy Blackjack logic.
easybj.h: you should modify this file to define the Hand class as well as add member functions/variables to the Blackjack class.
Solution Requirements
Since this assignment will be graded via an automated marker, you need to print outputs in the exact format described here. You may add additional files if needed, but you may not modify the following files: main.cpp, shoe.cpp, shoe.h, config.h, player.h, and Makefile. During marking, we will replace these files with the original, which may cause your submission to fail if you modified the aforementioned files. Double check that you did not modify these files prior to submission. Code which fails to compile will receive zero marks.

Command Line Parsing
To complete this part of the assignment, you will need to make changes to config.cpp. Let's first fire up the help option "-h" and see what options and arguments the program accepts:

usage: ./asst1 [-h] [-f FILE|-i SEED [-r FILE]] [[-s] -a FILE NUM]
Options:
 -h:	Display this message
 -f:	Use file-based shoe
 -i:	Use random-based shoe (default)
 -r:	Record random-based shoe to file
 -a:	Play automatically using strategy chart
 -s:	Silent mode
 FILE:	File name for associated option
 SEED:	random seed
 NUM:	number of hands to be played
Here is a summary of the available options to the program:

-h: displays the usage message you see above
-f: the shoe used for this game will generate cards from a file. The tester uses this to check the output of your program against various test cases.
-i: the shoe used for this game will generate cards from a random-number generator.
-r: allows you to record the cards that are being dealt in the game to a file. You can load the file later using the -f option to play the exact same shoe again.
-a: allows you to play the game automatically using a strategy table. See the Automatic Mode section for a sample of the table. When we test your code, we use one of four tables that you can look at. They are stored under /cad2/ece326f/tester/data/asst1/. In automatic mode, the player will only play NUM number of hands, specified by the command line.
Your program must accept all correct combinations of the options and reject all else. This includes the following restrictions:

Subsequent parsing is ignored as soon as -h is found.
Only one of -f or -i is allowed, not both.
The -r option is only available if -f is not chosen.
The -s option is only available if -a is chosen.
Here are the list of possible error messages you should print during command line parsing:

Error: SEED must be a non-negative integer.
Error: NUM must be a natural number.
Error: must specify number of hands when playing automatically.
Error: silent mode is only available when playing automatically.
Error: recording is only available for random-based shoe.
Error: cannot choose both file and random-based shoe.
./asst1: option requires an argument -- 'f'
./asst1: option requires an argument -- 'i'
./asst1: option requires an argument -- 'r'
./asst1: option requires an argument -- 'a'
The suggested solution is to use getopt from the standard C library. However, you may choose to do your own parsing as long as the output is identical. Note that for getopt, options that require an argument will treat the next token as argument, even if it is actually another option. for example:

./asst1 -f -i
In this case, getopt thinks the file name for file-based shoe is -i, and therefore you will get this error (which is printed as part of the starter code):

Error: cannot instantiate Shoe. (bad file?)
After command line parsing is done, you have not completed either of the playing mode, so the program still won't do much. That's OK. We will work on the core gameplay first, which both modes need.

Gameplay
This part of the assignment will need to be done along with the manual mode in order to test the program. Alternatively, you may create unit tests to ensure all functionality perform as expected. The files you will modify for this part is easybj.cpp and easybj.h. You may add more files (e.g. hand.cpp) if you prefer to have multiple smaller files than one large file.

Before you start, look at how the Blackjack class is used in main.cpp. There are four functions which are required by main.cpp.

Hand * start(): This function starts a game of Easy Blackjack, and returns the first hand that the player can play. The return value may be nullptr if the game ends immediately (i.e. if player and/or dealer has blackjack). The dealer should receive the first 2 cards from the shoe, followed by the player receiving the next 2 cards. Note that this ordering is not the same as in a casino setting, but is done this way to simplify the implementation.
const Hand * dealer_hand(): This function returns the dealer's hand, or nullptr if the game has not started yet.
Hand * next(): This function may only be called after start(), and returns the next hand that the player can play. The return value may be nullptr if no more hands are left to be played. Note that if a hand has 21 points, it stands automatically.
void finish(): This function may only be called after no more hands are left to be played. Its purpose is to allow the dealer to take action(s) and then updates the player's balance based on the outcome of the game. If the player has no live hands (i.e. all his/her hands busted or surrendered), then the dealer will not draw any cards. In all circumstances, you MUST call Player::update_balance exactly once during this function otherwise the number of hands played will be off.
When the player splits, the immediate next card from the shoe will go to the current hand, and the card after that will go to the new hand. For example, if you have 77 and the next two cards in the shoe are KQ, your current hand will become 7K and the new hand will have 7Q.

The current hand (first hand) will be played out while the new hand (second hand) will be added to the end of a queue. If the current hand is split again, the new hand (third hand) will again be placed to the end of the same queue. Same process repeats until the player cannot split anymore. After all actions on the current hand is complete, the next hand to be played will be the second hand (i.e. in the order that they are created).

In addition, the constructor for Blackjack takes two arguments: a Player object, which is the player playing this game, and a Shoe object, which is the shoe for which cards are pulled from to be dealt to both player and dealer. You should look at shoe.h to see how to draw cards from a Shoe object.

The results (net monetary gain/loss) can be calculated as follows. Remember that a player may have multiple hands if he/she splits one or more hands:

The player loses $1 for each bust hand.
If the dealer busts, all of the player's live hands (not bust ones) win.
For each hand that ties against the dealer's hand, the bet pushes (no net gain or loss).
If the player doubled down and wins, he/she wins $2, otherwise he/she loses $2 (except on a tie).
If the player wins normally, he/she wins $1, otherwise he/she loses $1 (except on a tie).
If the player surrenders, he/she loses $0.5 (i.e. gets half of the money back).
If the player wins with blackjack, he/she wins $1.5.
If the dealer has blackjack, the player loses $1.
Summary Output
If silent mode is not turned on, then main will try to print the result of the game. The following is a sample output:

Dealer: 9 T (19)
Hand 1: J A (soft 21)
Hand 2: J 5 9 (bust) DOUBLE
Hand 3: K 9 (19)
Result: -$1.00
Current Balance: -$1.00
From the above, you have enough information to reconstruct the sequence of events.

The player split his first hand, and resplit his second hand (i.e. Hand 2).
For the first hand, the player had 21 and stood automatically (not blackjack since the hand was split).
For the second hand, the player doubled down on hard 15 and busted.
For the third hand, the player stood on hard 19, which tied with the dealer.
In total, the player lost $1. Having played only once, his balance is at -$1.
Now, we detail the output requirement:

Both the player and the dealer's hand will be printed in the same format. For the dealer's hand, it will start with Dealer:, for the player, it will start with Hand N: where N is the hand number (if splitting occurred).
Each card in a hand will be printed by their pip value (and not point value), separated by a single space.
Following the list of cards will be the total point value or special text in parentheses. If the hand busted, the text will be "bust". If the hand is blackjack, the text will be "blackjack". Lastly, if the hand is soft, it will say so, followed by the point value (e.g. "soft 16" for A5).
Last, if the player doubled down or surrendered a hand, it will say DOUBLE or SURRENDER, respectively.
On the next two lines, print the monetary result of the game, followed by the current balance of the player.
main uses the << stream insertion operator to print the output. Therefore, you will need to remember from ECE244 on how to overload the operator.

Manual Mode
In manual mode, the user of your program will play Easy Blackjack on the terminal using keyboard to enter his/her desired actions. For this, you should make a subclass of Player in player.cpp. Below is a sample game of Easy Blackjack played in manual mode:

Dealer: A 4 (soft 15)
Player: 6 4 (10)
Stand (S) Hit (H) Double (D) Surrender (R): p
Stand (S) Hit (H) Double (D) Surrender (R): h
Dealer: A 4 (soft 15)
Player: 6 4 8 (18)
Stand (S) Hit (H): s
Dealer: A 4 T Q (bust)
Hand 1: 6 4 8 (18)
Result: +$1.00
Current Balance: +$1.00
Press Any Key to Continue, (Q to Quit): q
Here, the player first chose split. However, since splitting is not allowed, he/she chose to hit, followed by stand. After the game ended, he/she decided to quit.

The output requirement is as follows:

For every hand to be played, the dealer's hand is first printed, followed by the player's hand.
All possible actions are listed in the exact order shown below:
Stand (S)
Hit (H)
Double (D)
Split (P)
Surrender (R)
For the player's input, we only care about the first letter, case insensitive match (i.e. "hello" will be interpreted as hit). If the input is invalid, the player is prompted again.
The player must to press Enter before the program receives input. Suggestion: use getline.
At the end of the game, the player is asked to play again.
Automatic Mode
When playing in automatic mode, the user must specify a strategy table file. Thus, you will need to parse the file. You should make another subclass of Player in player.cpp to complete this section. Below is a sample strategy table file:

   4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 AA A2 A3 A4 A5 A6
4  H  H  H  H  H  H  H  H  H  H  H  Dh Dh H  H  H  H  H  H  H  H  H  H
5  H  H  H  H  H  H  H  H  H  H  Dh Dh Dh H  H  H  H  H  H  H  H  H  H
6  H  H  H  H  H  H  H  H  H  H  Dh Dh Dh H  H  H  H  H  H  H  H  H  H
7  H  H  H  H  H  H  H  H  H  Dh Dh Dh Dh H  H  H  H  H  H  H  H  H  H
8  H  H  H  H  H  H  H  H  Dh Dh Dh Dh Dh H  H  H  H  H  H  H  H  H  H
9  Dh Dh Dh H  H  H  H  H  Dh Dh Dh Dh Dh H  H  H  H  H  H  H  H  H  H
10 Dh Dh Dh Dh Dh Dh H  H  Dh Dh Dh Dh Dh H  H  H  H  H  Dh Dh Dh Dh H
11 Dh Dh Dh Dh Dh Dh H  H  Dh Dh Dh Dh Dh H  H  H  H  Dh Dh Dh Dh Dh H
12 S  S  S  H  H  H  H  H  S  S  S  S  S  H  H  H  H  H  H  H  H  H  H
13 S  S  S  H  H  H  H  H  S  S  S  S  S  H  H  H  H  H  H  H  H  S  H
14 S  S  S  H  H  H  H  H  S  S  S  S  S  H  H  H  H  H  H  S  S  S  H
15 S  S  S  H  H  H  H  H  S  S  S  S  S  H  H  H  H  H  S  S  S  S  H
16 S  S  S  H  H  H  H  S  S  S  S  S  S  H  H  H  H  S  S  S  S  S  H
17 S  S  S  S  S  S  S  S  S  S  S  S  S  S  H  H  H  S  S  S  S  S  S
18 S  S  S  S  S  S  S  S  S  S  S  S  S  S  S  H  H  S  S  S  S  S  S
19 S  S  S  S  S  S  S  S  S  S  S  S  S  S  S  S  H  S  S  S  S  S  S
20 S  S  S  S  S  S  S  S  S  S  S  S  S  S  S  S  S  S  S  S  S  S  S
22 P  P  P  P  H  H  H  H  P  P  P  P  P  P  P  H  H  H  H  H  H  P  P
33 P  P  P  P  H  H  H  H  P  P  P  P  P  P  P  H  H  H  H  H  H  H  P
44 H  P  P  H  H  H  H  H  P  P  P  P  P  H  H  H  H  H  H  H  H  H  H
55 Dh Dh Dh Dh Dh Dh H  H  Dh Dh Dh Dh Dh H  H  H  H  H  Dh Dh Dh Dh H
66 P  P  P  H  H  H  H  H  P  P  P  P  P  P  H  H  H  H  H  H  H  P  P
77 P  P  P  P  H  H  H  H  P  P  P  P  P  P  H  H  H  H  H  P  P  P  P
88 P  P  P  P  P  P  H  S  P  P  P  P  P  P  P  H  H  P  P  P  P  P  P
99 P  P  P  S  P  P  S  S  P  P  P  P  P  S  P  P  H  S  S  S  P  P  S
TT S  S  S  S  S  S  S  S  S  P  P  P  P  S  S  S  S  S  S  S  S  S  S
AA P  P  P  P  P  P  P  P  P  P  P  P  P  H  H  H  H  P  P  P  P  P  H
A2 H  H  Dh H  H  H  H  H  Dh Dh Dh Dh Dh H  H  H  H  H  H  H  H  H  H
A3 H  Dh Dh H  H  H  H  H  Dh Dh Dh Dh Dh H  H  H  H  H  H  H  H  H  H
A4 H  Dh Dh H  H  H  H  H  Dh Dh Dh Dh Dh H  H  H  H  H  H  H  H  H  H
A5 Dh Dh Dh H  H  H  H  H  Dh Dh Dh Dh Dh H  H  H  H  H  H  H  H  H  H
A6 Dh Dh Dh H  H  H  H  H  Dh Dh Dh Dh Dh H  H  H  H  H  H  H  H  H  H
A7 Ds Ds Ds S  S  H  H  S  Ds Ds Ds Ds Ds S  H  H  H  S  S  S  S  S  S
A8 S  S  S  S  S  S  S  S  Ds Ds Ds Ds Ds S  S  S  H  S  S  S  S  S  S
A9 S  S  S  S  S  S  S  S  S  Ds Ds Ds Ds S  S  S  S  S  S  S  S  S  S
The format of the strategy table is as follows:

The first row shows the dealer's starting hand. The last six columns are for soft 12 to soft 17. Note that soft 18 or above is merged with hard 18 or above, since the dealer acts the same under both circumstances.
The first column shows the player's starting hand. The first 17 rows are for hard 4 to hard 20. Notice that hard 21 is omitted since the player stands automatically. The next 10 rows are for pairs 22 to AA. Lastly, A2 to A9 are soft 13 to soft 20, respectively.
Each cell contains the recommended action given the player and the dealer's hand. Some actions have an alternative, in case the primary action is not allowed. The secondary actions are in lower case, with equivalent meaning.
H: Hit
S: Stand
D: Double if allowed
P: Split
R: Surrender if allowed
In the case splitting is not allowed (i.e. hand limit reached), look at the equivalent hard value of the hand (e.g. for 77, look at the row for hard 14).
Note that the table is space delimited.
Your objective for this part of the assignment is to parse the table and play Easy Blackjack using the table automatically. If parsing error occurs, then Player::factory should return nullptr and the program will terminate.

After you are complete, you can alter the strategy table and see what strategy gives better player advantage. The higher the player advantage, the more money you expect to win playing the game (See sample output below, with silent mode turned on).

$ ./asst1 -s -a strat.txt 2000000
Hands Played: 2000000
Final Balance: +$208725.50
Player Advantage: 10.44%
Note that the meaning of the word "hand" here is slightly different than our usual usage. It means how many rounds of the game have been played, rather than have many specific hands were played (e.g., in cases where splitting occurred). Therefore, if you played only 1 round of the game, but split during the game, the final "hands played" is still just 1. Below is sample output from manual mode to show how number of hands is counted.

Dealer: Q 7 (17)
Player: 9 K (19)
Stand (S) Hit (H) Double (D) Surrender (R): s
Dealer: Q 7 (17)
Hand 1: 9 K (19)
Result: +$1.00
Current Balance: +$1.00
Press Any Key to Continue, (Q to Quit): 
Dealer: Q J (20)
Player: Q 7 (17)
Stand (S) Hit (H) Double (D) Surrender (R): r
Dealer: Q J (20)
Hand 1: Q 7 (17) SURRENDER
Result: -$0.50
Current Balance: +$0.50
Press Any Key to Continue, (Q to Quit): 
Dealer: 3 3 (6)
Player: A 6 (soft 17)
Stand (S) Hit (H) Double (D) Surrender (R): h
Dealer: 3 3 (6)
Player: A 6 5 (12)
Stand (S) Hit (H): h
Dealer: 3 3 (6)
Player: A 6 5 6 (18)
Stand (S) Hit (H): s
Dealer: 3 3 K K (bust)
Hand 1: A 6 5 6 (18)
Result: +$1.00
Current Balance: +$1.50
Press Any Key to Continue, (Q to Quit): 
Dealer: K 4 (14)
Player: 4 4 (8)
Stand (S) Hit (H) Double (D) Split (P) Surrender (R): p
Dealer: K 4 (14)
Player: 4 A (soft 15)
Stand (S) Hit (H) Double (D): d
Dealer: K 4 (14)
Player: 4 2 (6)
Stand (S) Hit (H) Double (D): h
Dealer: K 4 (14)
Player: 4 2 4 (10)
Stand (S) Hit (H): h
Dealer: K 4 (14)
Player: 4 2 4 4 (14)
Stand (S) Hit (H): s
Dealer: K 4 K (bust)
Hand 1: 4 A A (soft 16) DOUBLE
Hand 2: 4 2 4 4 (14)
Result: +$3.00
Current Balance: +$4.50
Press Any Key to Continue, (Q to Quit): q
Hands Played: 4
Final Balance: +$4.50
Player Advantage: 112.5%

Glossary of Terms
Here, you can find the definition of commonly seen terms that are used in the assignment. More will be added as people ask questions about the assignment.

Shoe: An elongated container used to hold multiple decks of cards. For this assignment, we support two sources of cards: random-generated (InfiniteShoe), or pre-arranged (FileShoe).
Seed: A value passed into a random number generator to reset its internal state. For a deterministic random number generator (the one we're using for this assignment), using the same seed will result in the exact same sequence of psuedo-random numbers being generated, which helps you debug your program.
Hard: In blackjack, a hard hand refers to one where there is no ace that can act as 11 points without going over 21. For example, 69 is a hard 15, and A5K is a hard 16.
Soft: In blackjack, a soft hand refers to one where there is an ace that can act as 11 points without going over 21. For example, A6 is a soft 17. Soft hands are desirable in blackjack because there is no risk of busting if you hit. In the case of A6, if you hit and receive a ten, your hand merely becomes a hard 17 and does not bust.
Hand: In card games, a hand usually has two meanings: 1) number of times a game is played, and 2) a set of cards that is played as a unit. The question "How many hands did you play?" usually refers to how many times you played the game (meaning 1), whereas "How many hands were you playing" refers to how many hands you were playing simultaneously per round of the game (meaning 2). In regular blackjack, you are allowed to start off playing more than one hand, and each of the starting hands can be split up to 4 times!. The usage text (./asst1 -h) for number of hands to be played and the final results text that prints at the end of the program (e.g. Hands Played: 5) refers to meaning 1.
