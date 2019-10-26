/*
 * config.cpp
 *
 * Parses program arguments and returns Config object
 *
 * Note: change this file to parse program arguments
 *
 * University of Toronto
 * Fall 2019
 * MY SECOND COMMIT
 */
 
#include "config.h"
#include "player.h"
#include "shoe.h"
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <iostream>

static int
usage(const char * prog) {
	fprintf(stderr, "usage: %s [-h] [-f FILE|-i SEED [-r FILE]] [[-s] -a FILE NUM]\n", prog);
	fprintf(stderr, "Options:\n");
	fprintf(stderr, " -h:\tDisplay this message\n");
	fprintf(stderr, " -f:\tUse file-based shoe\n");
	fprintf(stderr, " -i:\tUse random-based shoe (default)\n");
	fprintf(stderr, " -r:\tRecord random-based shoe to file\n");
	fprintf(stderr, " -a:\tPlay automatically using strategy chart\n");
	fprintf(stderr, " -s:\tSilent mode\n");
	fprintf(stderr, " FILE:\tFile name for associated option\n");
	fprintf(stderr, " SEED:\trandom seed\n");
	fprintf(stderr, " NUM:\tnumber of hands to be played\n");
	return -1;
}

int
Config::process_arguments(int argc, const char * argv[])
{
    /*
     * TODO: implement here start
     */
    int option;
    bool want_silent_mode = false;
    while ((option = getopt (argc, (char* const*)argv, "hf:i:r:sa:")) != -1) {
        switch (option)
            {
            case 'h':
                return usage(argv[0]);
                break;
            case 'f':
                if (this->random_seed && this->random_seed == -1)
                    this->shoe_file = optarg;         
                else {
                    fprintf(stderr, "Error: cannot choose both file and random-based shoe.\n");
                    return -1;
                }
                break;
            case 'i':
                if (this->shoe_file == nullptr && std::atol(optarg) >= 0)
                    this->random_seed = std::atol(optarg);
                else {
                    if (this->shoe_file != nullptr)
                        fprintf(stderr, "Error: cannot choose both file and random-based shoe.\n");
                    else if (std::atol(optarg) < 0)
                        fprintf(stderr, "Error: SEED must be a non-negative integer.\n");
                    return -1;
                }
                break;
            case 'r':
                if (this->random_seed && this->random_seed != -1)
                    this->record_file = optarg;
                else {
                    fprintf(stderr, "Error: recording is only available for random-based shoe.\n");
                    return -1;
                }
                break;
            case 's':
                want_silent_mode = true;
//                if ((argv[optind] && strcmp(argv[optind], "-a") == 0)){
//                    this->silent = true;
//                } else {
//                    fprintf(stderr, "Error: silent mode is only available when playing automatically.\n");
//                    return -1;
//                }
                break;
            case 'a':
                if (argv[optind] && std::atoi(argv[optind]) > 0) {
                    this->strategy_file = optarg;
                    this->num_hands = std::atoi(argv[optind]);
                } else {
                    if (!argv[optind])
                        fprintf(stderr, "Error: must specify number of hands when playing automatically.\n");
                    else if (std::atoi(argv[optind]) <= 0 )
                        fprintf(stderr, "Error: NUM must be a natural number.\n");
                    return -1;
                }
                break;
            case '?':
                if (optopt && optopt == 'f')
                    fprintf(stderr, "%s: option requires an argument -- 'f'\n", argv[0]);
                else if (optopt && optopt == 'i')
                    fprintf(stderr, "%s: option requires an argument -- 'i'\n", argv[0]);
                else if  (optopt && optopt == 'r')
                    fprintf(stderr, "%s: option requires an argument -- 'r'\n", argv[0]);
                else if  (optopt && optopt == 'a')
                    fprintf(stderr, "%s: option requires an argument -- 'a'\n", argv[0]);
                else {
                    fprintf(stderr, "Invalid option");
                    return usage(argv[0]);
                }
                return -1;
                break;
            default:
                continue;
            }
    }
    if (want_silent_mode && this->strategy_file != nullptr){
        this->silent = true;
    } else if (want_silent_mode && this->strategy_file == nullptr) {
        fprintf(stderr, "Error: silent mode is only available when playing automatically.\n");
        return -1;
    }
    /*
     * TODO: implement here end
     */
    
    if (argc == 2 && !strcmp(argv[1], "-h")) {
        return usage(argv[0]);
    }
	player = Player::factory(this);
	if (player == nullptr) {
		fprintf(stderr, "Error: cannot instantiate Player. (bad file?)\n");
		return usage(argv[0]);
	}		
	
	shoe = Shoe::factory(this);
	if (shoe == nullptr) {
		fprintf(stderr, "Error: cannot instantiate Shoe. (bad file?)\n");
		return usage(argv[0]);
	}	
	
	return 0;
}

Config::~Config()
{
	if (player != nullptr)
		delete player;
	
	if (shoe != nullptr)
		delete shoe;
}

