/*
 * easybj.cpp
 *
 * Note: change this file to implement Blackjack logic
 *
 * University of Toronto
 * Fall 2019
 */
#include "shoe.h"
#include "easybj.h"
#include "player.h"
#include "hand.h"
#include <sstream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>


std::map<char,int> point_map;



int cards_and_points(std::string cards, Hand * hand){
    int points=0;
    bool hasAce=false;
    int nonAce=0;
    for (auto i:cards){
        if(i=='A'){
            if (hasAce) {
                points+=-10;
            }
            hasAce=true;
        } else {nonAce = i;}
        points+=point_map[i];
    }
    if (points > 21 && hasAce) {
        points+=-10;
        hand->soft_hand = false;
        return points;
    }
    if(hasAce && point_map[nonAce] < 10 && points <= 21){
        hand->soft_hand = true;
    } else {
        hand->soft_hand = false;
    }
    
    return points;
}

void print_current_hand(Hand * dealer, Hand * player) {
    // print dealer Hand
    std::cout<<"Dealer: ";
    for (auto i:dealer->cards){
        std::cout << i << ' ';
    }
    if (dealer->card_total == 21 && dealer->cards.size() == 2) {
        std::cout<<"(blackjack)";
    }
    else if(dealer->soft_hand){
        std::cout<<"(soft ";
    } else {
        std::cout<<"(";
    }
    std::cout<<dealer->card_total<<")\n"; 
    
    // print player Hand
    std::cout<<"Player: ";
    for (auto i:player->cards){
        std::cout << i << ' ';
    }
    if (player->card_total == 21 && player->cards.size() == 2 && !player->splited_ace && !player->split) {
        std::cout<<"(blackjack)";
    }
    else if (player->card_total > 21) {
        std::cout<<"(bust)";
    }
    else if(player->soft_hand){
        std::cout<<"(soft "<<player->card_total<<")";
    }
    else {
        std::cout<<"("<<player->card_total<<")";
    }

    if (player->doubled) {
        std::cout<<" DOUBLE";
    }
    else if (player->surrendered) {
        std::cout<<" SURRENDER";
    }
    std::cout<<"\n"; 
}

Blackjack::Blackjack(Player * p, Shoe * s)
	: player(p)
	, shoe(s)
{
	/*
	 * TODO: implement this
	 */    
    point_map['2']=2;
    point_map['3']=3;
    point_map['4']=4;
    point_map['5']=5;
    point_map['6']=6;
    point_map['7']=7;
    point_map['8']=8;
    point_map['9']=9;
    point_map['T']=10;
    point_map['J']=10;
    point_map['Q']=10;
    point_map['K']=10;
    point_map['A']=11;
}

//<<<<<<< HEAD
//Blackjack::~Blackjack()
//{
//	/*
//	 * TODO: implement this
//	 */
//    delete this->dealer_playing;
//    Hand * c=this->first_player_hand;
//    Hand * n=this->first_player_hand->next_hand;
//    while (c->next_hand!=nullptr){
//        delete c;
//        c=n;
//        n=n->next_hand;
//        this->first_player_hand=this->first_player_hand->next_hand;
//    }
//=======
Blackjack::~Blackjack() {
    delete dealer_playing;
    delete first_player_hand;
//>>>>>>> 9a45f88d6944cca1ed1a9be5c5b3004c34c29b3b
}

 
Hand * Blackjack::start() 
{   
    hand_result = 0.0;
    //DEALER HAND
    dealer_playing = new Hand;
    first_player_hand = new Hand;
    dealer_playing->start_hand=true;
    first_player_hand->start_hand=true;
    first_player_hand->shoe_copy=shoe;
    dealer_playing->cards+=shoe->pop();
    dealer_playing->cards+=shoe->pop();
    dealer_playing->card_total = cards_and_points(dealer_playing->cards, dealer_playing);
    first_player_hand->cards+=shoe->pop();
    first_player_hand->cards+=shoe->pop();
    first_player_hand->card_total = cards_and_points(first_player_hand->cards, first_player_hand);
    evaluated_hand = first_player_hand;

//    delete player_hand;
    if (first_player_hand->card_total == 21 || dealer_playing->card_total == 21) {
	return nullptr;
    } else {
	return first_player_hand;
    }
}


Hand * Blackjack::next() 
{
//    hand_evaluated++;
//    int hands_left = player_hand_stack.size() - hand_evaluated;
    Hand * next_hand = evaluated_hand->next_hand;
    if (next_hand != nullptr) {
        evaluated_hand = next_hand;
//        print_current_hand(dealer_playing, next_hand);
        return next_hand;
    } else {
	return nullptr;
    }

}

std::ostream & operator<<(std::ostream & ostr, const Blackjack & bj)
{
    (void)bj;
    int dph=bj.dealer_playing->card_total;
    // print dealer Hand
    ostr<<"Dealer: ";
    for (auto i:bj.dealer_playing->cards){
        std::cout << i << ' ';
    }
    if (dph == 21 && bj.dealer_playing->cards.size() == 2) {
        ostr<<"(blackjack)";
    }
    else if (dph > 21) {
        ostr<<"(bust)";
    }
    else if(bj.dealer_playing->soft_hand){
        ostr<<"(soft "<<dph<<")";
    }
    else {
        ostr<<"("<<dph<<")";
    }
    ostr<<"\n"; 
    Hand * current_hand = bj.first_player_hand;
    int cph;
    while (current_hand != nullptr) {
        cph=current_hand->card_total;
        ostr<<"Hand"<<" "<<current_hand->hand_index;
        ostr<<": ";
        for (auto i:current_hand->cards){
            std::cout << i << ' ';
        }
        if (cph == 21 && current_hand->cards.size() == 2) {
            if(current_hand->splited_ace || current_hand->split){
                ostr<<"(soft "<<cph<<")";
            } else {
                ostr<<"(blackjack)";
            }
        }
        else if (cph > 21) {
            ostr<<"(bust)";
        }
        else if(current_hand->soft_hand){
            ostr<<"(soft "<<cph<<")";
        }
        else {
            ostr<<"("<<cph<<")";
        }
        
        if (current_hand->doubled) {
            ostr<<" DOUBLE";
        }
        else if (current_hand->surrendered) {
            ostr<<" SURRENDER";
        }
        ostr<<"\n"; 
        
        current_hand = current_hand->next_hand;
    }
	std::cout << "Result: " << to_currency(bj.hand_result) << std::endl;
        double balance;
        balance = bj.player->get_balance();
	std::cout << "Current Balance: " << to_currency(balance) << std::endl;
//<<<<<<< HEAD
//=======
//        
//>>>>>>> 9a45f88d6944cca1ed1a9be5c5b3004c34c29b3b
    return ostr;
}


void Blackjack::finish() 
{
        double profit = 0.;
	bool dealer_moves;
        int fph=first_player_hand->card_total;
        int dph=dealer_playing->card_total;
        
        if (first_player_hand->next_hand == nullptr && 
                ((fph == 21 && first_player_hand->cards.size() == 2 && !first_player_hand->splited_ace)
                || 
                (dph == 21 && dealer_playing->cards.size() == 2))) {
            if (fph == 21 && dph != 21) {
                player->update_balance(1.5);
                hand_result += 1.5;
                return;
//                profit += 1.5;
            } else if (fph != 21 && dph == 21) {
                player->update_balance(-1.0);
                hand_result += -1.0;
                return;
//                profit += -1.0;
            }
            else if (fph > 21 && dph > 21) {
                player->update_balance(-1.0);
                hand_result += -1.0;
                return;
//                    profit+=-1.0;
            }else{
                player->update_balance(0);
//                hand_result += 0;
                return;
            }
//            player->update_balance(profit);
//            hand_result += profit;
//            return;
        }
        if(first_player_hand->surrendered){
            player->update_balance(-0.5);
            hand_result += -0.5;
            return;
        }
        dealer_moves=false;
        
        Hand * chand = first_player_hand;
        while (chand != nullptr) {
            if(chand->card_total<=21){
                dealer_moves=true;
                break;
            }
            chand = chand->next_hand;
        }
        
        
        while (dealer_moves) {
            if (dph <= 16 || (dph == 17 && dealer_playing->soft_hand)) {
                dealer_playing->cards.push_back(shoe->pop());
                dph = cards_and_points(dealer_playing->cards, dealer_playing);
                dealer_playing->card_total=dph;
            } else {
                break;
            }
        }
        
            profit = 0.;
        Hand * current_hand = first_player_hand;
        int cph;
        bool double_true;
        while (current_hand != nullptr) {
            cph=current_hand->card_total;
            double_true=current_hand->doubled;
            if (cph <= 21 && dph <= 21) {
                if (dph < cph) {
                    if (double_true)
                        profit += 2.0;
                    else
                        profit += 1.0;
                }
                else if (dph > cph) {
                    if (double_true)
                        profit += -2.0;
                    else
                        profit += -1.0;
                }
            }
            else if (cph > 21 && dph <= 21) {
                if (double_true)
                    profit += -2.0;
                else
                    profit += -1.0;
            }
            else if (cph <= 21 && dph > 21) {
                if (double_true)
                    profit += 2.0;
                else
                    profit += 1.0;
            }
            else if(cph > 21 && dph > 21) {
                    profit+=-1.0;
            }
            current_hand = current_hand->next_hand;
        }
            player->update_balance(profit);
            hand_result += profit;
}

std::string to_currency(double v)
{
	std::ostringstream ostr;
	
	ostr << std::fixed << std::setprecision(2);
	if (v > 0) {
		ostr << "+$" << v;
	} else if (v < 0) {
		ostr << "-$" << -v;
	}
	else {
		ostr << "$" << v;
	}
	
	return ostr.str();
}

