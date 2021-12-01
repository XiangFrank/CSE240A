//
// Created by frank on 2021/12/1.
//

#include "gshare.h"
#include "predictor.h"

uint8_t* PHT;
uint32_t gHistory = 0;

void init_gShare() {
    int size = 1 << ghistoryBits;
    PHT = malloc(size * sizeof(uint8_t));
    for (int i = 0; i < size; i++) {
        PHT[i] = WN;
    }
}

void train_gShare(uint32_t pc, uint8_t outcome) {
    int index = (pc & ((1 << ghistoryBits) - 1)) ^ gHistory;
    if (outcome == 0 && PHT[index] > SN) PHT[index]--;
    else if (outcome == 1 && PHT[index] < ST) PHT[index]++;
    gHistory = ((gHistory << 1) | outcome) & ((1 << ghistoryBits) - 1);
}

uint8_t gShare_predict(uint32_t pc) {
    int index = (pc & ((1 << ghistoryBits) - 1)) ^ gHistory;
    if (PHT[index] < WT) return 0;
    else return 1;
}