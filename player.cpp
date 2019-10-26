/*
 * player.cpp
 *
 * Note: change this file to implement Player subclass
 *
 * University of Toronto
 * Fall 2019
 */

#include "player.h"
#include "hand.h"
#include "easybj.h"
#include "shoe.h"
#include "config.h"
//#include "strategy.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <list>
#include<bits/stdc++.h> 
std::map<char,int> points_map;
int hands2play;
bool silent_mode;
std::string recording_shoe_file;
std::string base_shoe_file;
std::string strategy_file_copy;
std::string dealer_string="";
//<<<<<<< HEAD
////Hand * first_hand_game = nullptr;
//=======
//>>>>>>> 9a45f88d6944cca1ed1a9be5c5b3004c34c29b3b

typedef std::pair<std::string,std::string> map_pair;

std::map<map_pair, std::string> SMAP;
//typedef std::pair<std::string,std::string> map_pair;

void dealer_string_generator(std::string dcards, int dtotal){
//    std::string::iterator it; 
    std::size_t found = dcards.find('A');
//    it = std::find(dcards.begin(), dcards.end(), 'A');
//    if (it != dcards.end()){//first A found
    if (found!=std::string::npos && found != (unsigned)dcards.back()){
        if((dtotal<=17)&&(dtotal>=12)){//Confirming value is between 12 to 17
            if(dcards.at(1)=='A'){//_A, not AA
                dealer_string+=dcards.at(1);
                dealer_string+=dcards.at(0);
            }else{//A_
                dealer_string+=dcards.at(0);
                dealer_string+=dcards.at(1);
            }
        }else{//A7 and over
            dealer_string=std::to_string(dtotal);
        }
    }else{
        dealer_string=std::to_string(dtotal);
    }
    return;
}

char move_generator(std::string pcards, int ptotal, std::string legal_moves, bool is_soft){
//    std::vector<char>::iterator it; 
//    char move='X';
    std::string player_string="";    
    std::size_t found = pcards.find('A');
    
    if(pcards.size()==2){
        if (found!=std::string::npos && found != (unsigned)pcards.back()){
            if(pcards.at(1)=='A'){//_A, not AA
                player_string+=pcards.at(1);
                player_string+=pcards.at(0);
            }else{//A_
                player_string+=pcards.at(0);
                player_string+=pcards.at(1);
            }
        }else{//no A
            if(ptotal==20){//Combination of T,J,Q,K
                player_string+="TT";
            }else if(pcards.at(0)==pcards.at(1)){//TWO same cards (except AA, 10&10)
                player_string+=pcards.at(1);
                player_string+=pcards.at(0);
                
            }else{
                player_string=std::to_string(ptotal);
            }
        }
    }else{
        if(is_soft){
            player_string+="A";
            player_string+=std::to_string(ptotal-11);
          
        }else{
            player_string=std::to_string(ptotal);
        }
    }
    
    std::map<map_pair, std::string>::iterator map_iterator;
    map_iterator = SMAP.find(std::make_pair(player_string,dealer_string));
    std::string available_moves=SMAP[{player_string,dealer_string}];
//    if(available_moves[0]==('S'||'H')){
//        return available_moves[0];
//    }
    for (unsigned int i = 0; i < available_moves.size(); i++){
        if(legal_moves.find(available_moves[i])!= std::string::npos){//legal
            return available_moves[i];
        } 
    }
//    
//    if(move=='X'){//empty char
    player_string=std::to_string(ptotal);
    map_iterator = SMAP.find(std::make_pair(player_string,dealer_string));
    std::string new_available_moves=SMAP[{player_string,dealer_string}];
    for (unsigned int i = 0; i < new_available_moves.size(); i++){
        if(legal_moves.find(new_available_moves[i])!= std::string::npos){//legal
            return new_available_moves[i];
        } 
    }
//    }
//    std::cout<<"NOT FOUND SOMETHING IS WORNGGGGG"<<player_string<<" "<<dealer_string<<"\n";
    return 'S';
}



void process_strategy_table(std::string strategy_file){
    std::string strategies="HSDPR,Dh,Ds,Dd,Dp,Dr,Rh,Rp,Rd,Rr,Rs";
    std::ifstream file;
    file.open (strategy_file);
    std::string word;
    bool dealer_hands_done=false;
    std::string top_hand_value;
    std::list< std::string > dealer_hands;
    std::string player_hands;
    while (file >> word){
        if(!dealer_hands_done){
            if(top_hand_value.empty()){
                top_hand_value=word;
                dealer_hands.push_back(word);
                continue;
            }
            if(top_hand_value==word){
                dealer_hands_done=true;
            }else{
                dealer_hands.push_back(word);
                continue;
            }
        }      
        size_t found=strategies.find(word);
        if (found != std::string::npos){//if found
            std::transform(word.begin(), word.end(),word.begin(), ::toupper);
            SMAP.insert({std::make_pair(player_hands,dealer_hands.front()),word});
            dealer_hands.push_back(dealer_hands.front());
            dealer_hands.pop_front();
        }else{//not found so store player hand
            player_hands=word;//current row
        }
    }
    file.close();
    
}

class ManualPlayer : public Player {
public:
	ManualPlayer();
        virtual void play(Hand * hand, const Hand * dealer) override;
        virtual bool again() const override;
	virtual ~ManualPlayer();
//        Shoe *shoe_ptr;
};
//empty for now
class AutoPlayer : public Player {
public:
	AutoPlayer();
        virtual void play(Hand * hand, const Hand * dealer) override;
        virtual bool again() const override;
        virtual ~AutoPlayer();
        std::map<map_pair, std::string> SMAP;
//        Shoe *shoe_ptr;
};
ManualPlayer::ManualPlayer(){
    
}
ManualPlayer::~ManualPlayer()
{
}
void ManualPlayer::play(Hand* hand, const Hand* dealer)
{
//<<<<<<< HEAD
////    if (first_hand_game == nullptr) {
////        first_hand_game = hand;
////    }
//=======
//>>>>>>> 9a45f88d6944cca1ed1a9be5c5b3004c34c29b3b
    if(hand->splited_ace){
        return;
    }
    print_current_hand((Hand*)dealer, hand);
    bool complete=false;
    while(!complete){
        char m;
        if(hand->card_total>=21 || hand->splited_ace){
            
            return;
        }
        std::string moves="";
        std::string print_moves="";
            //Stand (S) and Hit (H) always.
            print_moves+="Stand (S) Hit (H)";
            moves+="SH";
            //Double (D)
            if(hand->cards.size()==2){
                print_moves+=" Double (D)";
                moves+="D";
            }
            if(hand->total_hands<4){
                if(hand->cards.size()==2 && points_map[hand->cards[0]] == points_map[hand->cards[1]]){
                    print_moves+=" Split (P)";
                    moves+="P";
                }
            }
            
            //Surrender (R)
            if(hand->start_hand){
                print_moves+=" Surrender (R)";
                moves+="R";
            }

            print_moves+=": ";
            std::string input="";
            while(input.empty())
            {
                std::cout<<print_moves;
                std::getline(std::cin,input);
                if(!input.empty()) {
                    m = toupper(input.at(0));
                    if (moves.find(m) != std::string::npos){
                        break;
                    }  
                }
            }
        switch(m)
        {
            case 'S':
                if (moves.find('S') == std::string::npos){
                    moves = "SH";
                    break;
                }  
                hand->card_total = cards_and_points(hand->cards, hand);
                hand->start_hand=false;
                moves = "SH";
                return;
            case 'H':
                if (moves.find('H') == std::string::npos){
                    moves = "SH";
                    break;
                }  
//                hand->cards.push_back(hand->shoe_copy->pop());
                hand->cards+=hand->shoe_copy->pop();
                hand->card_total = cards_and_points(hand->cards, hand);
                hand->start_hand=false;
                moves = "SH";
                if (hand->card_total<21)
                    print_current_hand((Hand*)dealer, hand);
                break;
            case 'D':
                if (moves.find('D') == std::string::npos){
                    moves = "SH";
                    break;
                }  
//                hand->cards.push_back(hand->shoe_copy->pop());
                hand->cards+=hand->shoe_copy->pop();
                hand->card_total = cards_and_points(hand->cards, hand);
                hand->doubled=true;
                hand->start_hand=false;
                moves = "SH";
//                if (hand->card_total<21)
//                    hand->bj_copy->print_current_hand((Hand*)dealer, hand);
                return;
            case 'P':{
                if (moves.find('P') == std::string::npos){
                    moves = "SH";
                    break;
                }
                //Secondary Hand
                Hand * second_hand = new Hand;  
                if (hand->cards[0] == 'A' && hand->cards[1] == 'A') {
                    hand->splited_ace = true;
                    second_hand->splited_ace = true;
                } 
                
                second_hand->start_hand=false;
                hand->start_hand=false;
                second_hand->split=true;
                hand->split=true;
                
                second_hand->shoe_copy=hand->shoe_copy;
//                second_hand->cards.push_back(hand->cards.back());//Uses First Hand's 2nd Card ex:TQ will use Q
                second_hand->cards+=hand->cards.back();
                hand->cards.pop_back();//Pop out First Hand's 2nd Card
//                hand->cards.push_back(hand->shoe_copy->pop());//First Hand 2nd Card
                hand->cards+=hand->shoe_copy->pop();
//                second_hand->cards.push_back(hand->shoe_copy->pop());//Second Hand 2nd Card
                second_hand->cards+=hand->shoe_copy->pop();
                hand->card_total = cards_and_points(hand->cards, hand);
                if(hand->next_hand == nullptr) {
                    hand->next_hand = second_hand;
                    second_hand->hand_index = hand->hand_index+1;
                    hand->total_hands+=1;
                    second_hand->total_hands = hand->total_hands;
                } else {
                    Hand *last=hand->next_hand;
                    hand->total_hands+=1;
                    while (last->next_hand != nullptr){
                        last->total_hands = hand->total_hands;
                        last = last->next_hand;
                    }
                    last->next_hand=second_hand;
                    second_hand->hand_index=last->hand_index+1;
//                    last->total_hands = hand->total_hands;
                    second_hand->total_hands = hand->total_hands;
//                    std::cout<<"hand total: "<<hand->total_hands<<"\n";
//                    Hand *last=hand->next_hand;
//                    hand->next_hand=second_hand;
//                    second_hand->hand_index=hand->hand_index+1;
//                    second_hand->next_hand=last;
//                    hand->next_hand=second_hand;
//                    second_hand->next_hand->hand_index=last->hand_index+1;
//                    hand->total_hands+=1;
//                    second_hand->total_hands = hand->total_hands;
//                    second_hand->next_hand->total_hands = hand->total_hands;
//                    if (last->next_hand != nullptr){
//                        last->next_hand->hand_index+=1;
//                        last->next_hand->total_hands = hand->total_hands;
//                    }
                }
//                second_hand->bj_copy=(hand->bj_copy);
                second_hand->card_total = cards_and_points(second_hand->cards, second_hand);
                moves = "SH";
                
                if (hand->card_total<21 && !hand->splited_ace){
                    print_current_hand((Hand*)dealer, hand);
                }
                break;
            }
            case 'R':
                if (moves.find('R') == std::string::npos){
                    moves = "SH";
                    break;
                }  
                hand->surrendered=true;
                hand->start_hand=false;
                moves = "SH";
                return;
            default:
                hand->doubled=false;
                hand->surrendered=false;
                moves = "SH";
                break;
                
        }
        
        
        
    }
    
    
    (void)dealer;
    return;
    
}
bool ManualPlayer::again() const{
//<<<<<<< HEAD
////    delete first_hand_game;
////    first_hand_game = nullptr;
//=======
//>>>>>>> 9a45f88d6944cca1ed1a9be5c5b3004c34c29b3b
    std::string key;
    std::cout<<"Press Any Key to Continue, (Q to Quit): ";
    std::getline(std::cin,key);
    if (key.length() > 0 && (key.at(0) == 'Q' || key.at(0) == 'q'))
        return false;
    else
        return true;
}


AutoPlayer::AutoPlayer(){
//    SMAP;

    
    

}
AutoPlayer::~AutoPlayer()
{

}
//
void AutoPlayer::play(Hand* hand, const Hand* dealer)
{
//<<<<<<< HEAD
////    if (first_hand_game == nullptr) {
////        first_hand_game = hand;
////    }
//=======
//>>>>>>> 9a45f88d6944cca1ed1a9be5c5b3004c34c29b3b
    if (dealer_string == "") {
        dealer_string_generator(dealer->cards, dealer->card_total);
        
    }
    if(hand->splited_ace){
        return;
    }
    if (!silent_mode) {print_current_hand((Hand*)dealer, hand);}
    bool complete=false;
    while(!complete){
        char m;
        if(hand->card_total>=21 || hand->splited_ace){
            return;
        }
        std::string moves="SH";
//            moves+="SH";
            //Double (D)
            if(hand->cards.size()==2){
                moves+="D";
            }
            if(hand->total_hands<4){
                if(hand->cards.size()==2 && points_map[hand->cards[0]] == points_map[hand->cards[1]]){
//                    print_moves+=" Split (P)";
                    moves+="P";
                }
            }
            
            //Surrender (R)
            if(hand->start_hand){
                moves+="R";
                hand->start_hand=false;
            }
        
        m=move_generator(hand->cards,hand->card_total,moves,hand->soft_hand);
        
        switch(m)
        {
            case 'S':
//                if (moves.find('S') == std::string::npos){
//                    moves = "SH";
//                    break;
//                }  
                hand->card_total = cards_and_points(hand->cards, hand);
//                hand->start_hand=false;
                moves = "SH";
                return;
            case 'H':
//                if (moves.find('H') == std::string::npos){
//                    moves = "SH";
//                    break;
//                }  
//                hand->cards.push_back(hand->shoe_copy->pop());
                hand->cards+=hand->shoe_copy->pop();
                hand->card_total = cards_and_points(hand->cards, hand);
//                hand->start_hand=false;
                moves = "SH";
                if (hand->card_total<21 && !silent_mode)
                    print_current_hand((Hand*)dealer, hand);
                break;
            case 'D':
//                if (moves.find('D') == std::string::npos){
//                    moves = "SH";
//                    break;
//                }  
//                hand->cards.push_back(hand->shoe_copy->pop());
                hand->cards+=hand->shoe_copy->pop();
                hand->card_total = cards_and_points(hand->cards, hand);
                hand->doubled=true;
//                hand->start_hand=false;
                moves = "SH";
                return;
            case 'P':{
//                if (moves.find('P') == std::string::npos){
//                    moves = "SH";
//                    break;
//                }
                //Secondary Hand
                Hand * second_hand = new Hand;  
                if (hand->cards[0] == 'A' && hand->cards[1] == 'A') {
                    hand->splited_ace = true;
                    second_hand->splited_ace = true;
                } 
                
                second_hand->start_hand=false;
//                hand->start_hand=false;
                second_hand->split=true;
                hand->split=true;
                
                second_hand->shoe_copy=hand->shoe_copy;
//                second_hand->cards.push_back(hand->cards.back());//Uses First Hand's 2nd Card ex:TQ will use Q
                second_hand->cards+=hand->cards.back();
                hand->cards.pop_back();//Pop out First Hand's 2nd Card
//                hand->cards.push_back(hand->shoe_copy->pop());//First Hand 2nd Card
                hand->cards+=hand->shoe_copy->pop();
//                second_hand->cards.push_back(hand->shoe_copy->pop());//Second Hand 2nd Card
                second_hand->cards+=hand->shoe_copy->pop();
                hand->card_total = cards_and_points(hand->cards, hand);
                if(hand->next_hand == nullptr) {
                    hand->next_hand = second_hand;
                    second_hand->hand_index = hand->hand_index+1;
                    hand->total_hands+=1;
                    second_hand->total_hands = hand->total_hands;
                } else {
                    
//                    //charles
                    Hand *last=hand->next_hand;
                    hand->total_hands+=1;
                    while (last->next_hand != nullptr){
                        last->total_hands = hand->total_hands;
                        last = last->next_hand;
                    }
                    last->next_hand=second_hand;
                    second_hand->hand_index=last->hand_index+1;
                    last->total_hands = hand->total_hands;
                    second_hand->total_hands = hand->total_hands;

                    
//                    hand->next_hand=second_hand;
//                    second_hand->hand_index=hand->hand_index+1;
//                    second_hand->next_hand=last;
//                    hand->next_hand=second_hand;
//                    second_hand->next_hand->hand_index=last->hand_index+1;
//                    hand->total_hands+=1;
//                    last->total_hands = hand->total_hands;
//                    second_hand->total_hands = hand->total_hands;
//                    second_hand->next_hand->total_hands = hand->total_hands;
//                    if (last->next_hand != nullptr){
////                        last->next_hand->hand_index+=1;
//                        last->next_hand->total_hands = hand->total_hands;
//                    }
                }
//                second_hand->bj_copy=(hand->bj_copy);
                second_hand->card_total = cards_and_points(second_hand->cards, second_hand);
                moves = "SH";
                
                if (!silent_mode && hand->card_total<21 && !hand->splited_ace){
                    print_current_hand((Hand*)dealer, hand);
                }
                break;
            }
            case 'R':
//                if (moves.find('R') == std::string::npos){
//                    moves = "SH";
//                    break;
//                }  
                hand->surrendered=true;
//                hand->start_hand=false;
                moves = "SH";
                return;
            default:
                hand->doubled=false;
                hand->surrendered=false;
                moves = "SH";
                break;
                
        }
        
        
        
    }
    
    
    (void)dealer;
    return;
    
}

//
bool AutoPlayer::again() const{
//<<<<<<< HEAD
////    delete first_hand_game;
////    first_hand_game = nullptr;
//=======
//>>>>>>> 9a45f88d6944cca1ed1a9be5c5b3004c34c29b3b
    if(hands2play==this->get_hands_played()){
        return false;
    }
    dealer_string="";
    return true;
}


Player * Player::factory(const Config * config)
{
	/*
	 * TODO: implement this
	 */
    points_map['2']=2;
    points_map['3']=3;
    points_map['4']=4;
    points_map['5']=5;
    points_map['6']=6;
    points_map['7']=7;
    points_map['8']=8;
    points_map['9']=9;
    points_map['T']=10;
    points_map['J']=10;
    points_map['Q']=10;
    points_map['K']=10;
    points_map['A']=11;


    
    //asst1 -i 500 -a strat.txt 4
    if(config->strategy_file){
        AutoPlayer * player;
        hands2play=config->num_hands;
        silent_mode=config->silent;
        if(SMAP.empty()){
            process_strategy_table(config->strategy_file);   
        }
        player = new AutoPlayer();

                
        return player;
    }else{
        ManualPlayer * player;
        player = new ManualPlayer();

        
        return player;
    }

    
	return nullptr;
}

