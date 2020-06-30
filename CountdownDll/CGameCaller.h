#pragma once

#include "CLettersGame.h"

#ifdef __cplusplus
extern "C" {
#endif

    extern __declspec(dllexport) CLettersGame* CreateLettersGame();

    extern __declspec(dllexport) void DisposeLettersGame(CLettersGame* pLettersGame);

    extern __declspec(dllexport) bool InitializeLettersGame(CLettersGame* pLettersGame,
                                                            const char* input,
                                                            int inputSize,
                                                            char* output,
                                                            int* outputSize);

    extern __declspec(dllexport) char* GetLettersGameBoard(CLettersGame* pLettersGame);

    extern __declspec(dllexport) void RunLettersGame(CLettersGame* pLettersGame);

    extern __declspec(dllexport) char* GetLettersGameEndMessage(CLettersGame* pLettersGame);

    extern __declspec(dllexport) int GetLettersGameScore(CLettersGame* pLettersGame,
                                                         const char* answer,
                                                         int answerSize);

#ifdef __cplusplus
}
#endif
