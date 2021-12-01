//
// Created by frank on 2021/12/1.
//

#ifndef CSE240A_TOURNAMENT_H
#define CSE240A_TOURNAMENT_H
#include <stdint.h>

void init_tournament();

void train_tournament(uint32_t pc, uint8_t outcome);

uint8_t tournament_predict(uint32_t pc);

#endif //CSE240A_TOURNAMENT_H
