//
// Created by frank on 2021/12/1.
//

#include "tournament.h"
#include "predictor.h"
#include "stdio.h"

uint32_t* globalPHT;
uint32_t* metaPHT;
uint32_t* localPHT;
uint32_t* localHT;
uint32_t globalHistory = 0;
uint8_t globalPredict;
uint8_t localPredict;

void init_tournament() {
    uint32_t size = 1 << ghistoryBits;
    globalPHT = malloc(size * sizeof(uint32_t));
    metaPHT = malloc(size * sizeof(uint32_t));
    for (int i = 0; i < size; i++) {
        globalPHT[i] = WN;
        metaPHT[i] = WT;
    }

    size = 1 << lhistoryBits;
    localPHT = malloc(size * sizeof(uint32_t));
    for (int i = 0; i < size; i++) {
        localPHT[i] = WN;
    }

    size = 1 << pcIndexBits;
    localHT = malloc(size * sizeof(uint32_t));
    for (int i = 0; i < size; i++) {
        localHT[i] = 0;
    }
}

void train_tournament(uint32_t pc, uint8_t outcome) {
    uint32_t pcM = (1 << pcIndexBits) - 1;
    uint32_t localM = (1 << lhistoryBits) - 1;
    uint32_t globalM = (1 << ghistoryBits) - 1;
    uint32_t pcIndex = pcM & pc;
    uint32_t localIndex = localHT[pcIndex];
    uint32_t globalIndex = globalHistory;

    if (localPredict == outcome && globalPredict != outcome && metaPHT[globalIndex] > SN) metaPHT[globalIndex]--;
    else if(localPredict != outcome && globalPredict == outcome && metaPHT[globalIndex] < ST) metaPHT[globalIndex]++;

    if (outcome == 1) {
        if (localPHT[localIndex] < ST) localPHT[localIndex]++;
        if (globalPHT[globalIndex] < ST) globalPHT[globalIndex]++;
    }
    else {
        if (localPHT[localIndex] > SN) localPHT[localIndex]--;
        if (globalPHT[globalIndex] > SN) globalPHT[globalIndex]--;
    }

    localHT[pcIndex] = localM & ((localHT[pcIndex] << 1) | outcome);
    globalHistory = globalM & ((globalHistory << 1) | outcome);
}

uint8_t tournament_predict(uint32_t pc) {
    uint32_t pcM = (1 << pcIndexBits) - 1;
    uint32_t index = pc & pcM;
    uint32_t localH = localHT[index];
    if (localPHT[localH] > WN) localPredict = 1;
    else localPredict = 0;
    index = globalHistory;
    if (globalPHT[index] > WN) globalPredict = 1;
    else globalPredict = 0;
    uint8_t metaPredict = metaPHT[index];
    if (metaPredict < WT) return localPredict;
    else return globalPredict;
}

