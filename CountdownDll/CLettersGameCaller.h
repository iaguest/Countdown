#pragma once

#include "CLettersGame.h"

#ifdef __cplusplus
extern "C" {
#endif

    extern __declspec(dllexport) CLettersGame* CreateLettersGame();

    extern __declspec(dllexport) void DisposeLettersGame(CLettersGame* pLettersGame);

    extern __declspec(dllexport) bool CallInitialize(CLettersGame* pLettersGame,
                                                     const char* input,
                                                     int inputSize,
                                                     char* output,
                                                     int* outputSize);

    extern __declspec(dllexport) const char* CallGetGameBoard(CLettersGame* pLettersGame);

#ifdef __cplusplus
}
#endif
