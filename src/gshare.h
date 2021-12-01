//
// Created by frank on 2021/12/1.
//

#ifndef CSE240A_GSHARE_H
#define CSE240A_GSHARE_H
#include <stdint.h>

void init_gShare();

void train_gShare(uint32_t pc, uint8_t outcome);

uint8_t gShare_predict(uint32_t pc);

#endif //CSE240A_GSHARE_H
