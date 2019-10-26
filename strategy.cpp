///*
// * To change this license header, choose License Headers in Project Properties.
// * To change this template file, choose Tools | Templates
// * and open the template in the editor.
// */
//#include "player.h"
//#include "hand.h"
//#include "easybj.h"
//#include "shoe.h"
//#include "config.h"
//#include "strategy.h"
//#include <iostream>
//#include <string>
//#include <map>
//#include <vector>
//#include <fstream>
//#include <list>
//#include<bits/stdc++.h> 
//
//typedef std::pair<std::string,std::string> map_pair;
//
//char move_generator(std::vector< char > pcards, int ptotal,
//        std::vector< char > dcards, int dtotal, std::string legal_moves,
//        std::map<map_pair, std::string> smap){
//    std::vector<char>::iterator it; 
//    char move;
//    std::string player_string;
//    std::string dealer_string;
//    it = std::find(dcards.begin(), dcards.end(), 'A');
//    if (it != dcards.end()){//first A found
//        if((dtotal<=17)&&(dtotal>=12)){//Confirming value is between 12 to 17
//            if(dcards.at(1)=='A'){//_A, not AA
//                dealer_string+=dcards.at(1);
//                dealer_string+=dcards.at(0);
//            }else{//A_
//                dealer_string+=dcards.at(0);
//                dealer_string+=dcards.at(1);
//            }
//        }else{//A7 and over
//            dealer_string=std::to_string(dtotal);
//        }
//    }else{
//        dealer_string=std::to_string(dtotal);
//    }
//    if(pcards.size()==2){//check if DOUBLE or split is allowed
//        it = std::find(pcards.begin(), pcards.end(), 'A');
//        if (it != pcards.end()){//first A found
//    //        if((dtotal<=17)&&(dtotal>=12)){NO NEED to Confirm whether value is between 12 to 17
//            if(pcards.at(1)=='A'){//_A, not AA
//                player_string+=pcards.at(1);
//                player_string+=pcards.at(0);
//            }else{//A_
//                player_string+=pcards.at(0);
//                player_string+=pcards.at(1);
//            }
//        }else{//no A
//            if(pcards.at(0)==pcards.at(1)){//TWO same cards (except AA)
//                player_string+=pcards.at(0);
//                player_string+=pcards.at(1);
//            }else{
//                player_string=std::to_string(ptotal);
//            }
//        }
//    }else{
//        player_string=std::to_string(ptotal);
//    }
//    std::map<map_pair, std::string>::iterator map_iterator;
//    map_iterator = smap.find(std::make_pair(player_string,dealer_string));
//    if(map_iterator != smap.end())
//        {
//           std::cout << map_iterator->second << "5555\n";
//        }
//    std::string available_moves=smap[{player_string,dealer_string}];
//    for (unsigned int i = 0; i < available_moves.size(); i++){
//        if(legal_moves.find(toupper(available_moves[i]))!= std::string::npos){//legal
//            move=toupper(available_moves[i]);
//            return move;
//        }
//    }
//    return 'S';
//}
//
//
//
//void process_strategy_table(std::string strategy_file, std::map<map_pair, std::string> &smap){
//    std::string strategies="HSDPR,Dh,Ds";
//    std::ifstream file;
//    file.open (strategy_file);
//    std::string word;
//    bool dealer_hands_done=false;
//    std::string top_hand_value;
//    std::list< std::string > dealer_hands;
//    std::string player_hands;
//    while (file >> word){
//        if(!dealer_hands_done){
//            if(top_hand_value.empty()){
//                top_hand_value=word;
//                dealer_hands.push_back(word);
//                continue;
//            }
//            if(top_hand_value==word){
//                dealer_hands_done=true;
//            }else{
//                dealer_hands.push_back(word);
//                continue;
//            }
//        }      
//        size_t found=strategies.find(word);
//        if (found != std::string::npos){//if found
////            std::cout<<player_hands<<dealer_hands.front()<<word<<"\n";
//            smap.insert({std::make_pair(player_hands,dealer_hands.front()),word});
//            dealer_hands.push_back(dealer_hands.front());
//            dealer_hands.pop_front();
//        }else{//not found so store player hand
//            player_hands=word;//current row
//        }
//    }
////    std::cout<<smap[{"98","Q7"}]<<smap[{"K9","32"}]<<"\n";
//    file.close();
//    
//}
