/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hand.h
 * Author: Charles Souliere
 *
 * Created on September 17, 2019, 9:25 PM
 */

#ifndef HAND_H
#define HAND_H


#include <string>
#include <iostream>
#include <map>
#include <vector>

class Player;
class Shoe;
class Config;
class Blackjack;

class Hand {
public:
	std::string cards;
	int card_total = 0;
        bool soft_hand = false;
        bool doubled = false;
        bool surrendered = false;
        bool start_hand = false;
        bool splited_ace = false;
        bool split =  false;
        int hand_index = 1;
        Hand * next_hand = nullptr;
        
        Shoe * shoe_copy = nullptr;
        int total_hands=1;

	Hand(){}
//<<<<<<< HEAD
////	~Hand(){delete next_hand;shoe_copy = nullptr;}
//=======
	~Hand(){delete next_hand;next_hand=nullptr;shoe_copy = nullptr;}
//>>>>>>> 9a45f88d6944cca1ed1a9be5c5b3004c34c29b3b
};

#endif /* HAND_H */

