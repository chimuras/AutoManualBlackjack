 /*
 * easybj.h
 *
 * Header files for Easy Blackjack.
 *
 * Note: change this file to implement Blackjack
 *
 * University of Toronto
 * Fall 2019
 */
 
#ifndef EASYBJ_H
#define EASYBJ_H

#include <string>
#include <iostream>
#include <map>
#include <vector>

class Player;
class Shoe;
class Config;
class Hand;


int cards_and_points(std::string cards, Hand * hand);
void print_current_hand(Hand * dealer, Hand * player);

class Blackjack {
        Hand * dealer_playing = nullptr;

public:
        
	Player * player;
	Shoe * shoe;
//        std::vector< Hand * > player_hand_stack;
        Hand * first_player_hand = nullptr;
        Hand * evaluated_hand = nullptr;
//        int hand_evaluated = 0;
        double hand_result = 0.0;
	Blackjack(Player * p, Shoe * s);
	~Blackjack();
	
	/*
	 * Start a game of Blackjack
	 *
	 * Returns first hand to be played, nullptr if either dealer or player's
	 * initial hand is blackjack (or both)
	 */
	Hand * start();
	
	/*
	 * Returns dealer's hand
	 */
	Hand * dealer_hand() { return dealer_playing; }
	
	/*
	 * Returns next hand to be played (may be the same hand)
	 */
	Hand * next();
	
	/*
	 * Call once next() returns nullptr
	 */
	void finish();

	friend std::ostream & operator<<(std::ostream &, const Blackjack &);

	// TODO:hoe * used_shoe you may add more functions as appropriate
//        int cards_and_points(std::vector<char> cards, Hand * hand);
//        void print_current_hand(Hand * dealer, Hand * player);
};

/*
 * Returns string representation of currency for v
 */
std::string to_currency(double v);

#endif
