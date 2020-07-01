#pragma once

#include "CLettersGame.h"
#include "CNumbersGame.h"
#include "CConundrumGame.h"

#ifdef __cplusplus
extern "C" {
#endif

// Letters Game

    extern __declspec(dllexport) CLettersGame* CreateLettersGame();

    extern __declspec(dllexport) void DisposeLettersGame(CLettersGame* pLettersGame);

    extern __declspec(dllexport) bool InitializeLettersGame(CLettersGame* pLettersGame,
                                                            const char* input,
                                                            int inputSize,
                                                            char* output,
                                                            int* outputSize);

    extern __declspec(dllexport) char* GetLettersGameStartMessage(CLettersGame* pLettersGame);

    extern __declspec(dllexport) char* GetLettersGameBoard(CLettersGame* pLettersGame);

    extern __declspec(dllexport) void RunLettersGame(CLettersGame* pLettersGame);

    extern __declspec(dllexport) char* GetLettersGameEndMessage(CLettersGame* pLettersGame);

    extern __declspec(dllexport) int GetLettersGameScore(CLettersGame* pLettersGame,
                                                         const char* answer,
                                                         int answerSize);

// Numbers Game

    extern __declspec(dllexport) CNumbersGame* CreateNumbersGame();

    extern __declspec(dllexport) void DisposeNumbersGame(CNumbersGame* pNumbersGame);

    extern __declspec(dllexport) bool InitializeNumbersGame(CNumbersGame* pNumbersGame,
                                                            const char* input,
                                                            int inputSize,
                                                            char* output,
                                                            int* outputSize);

    extern __declspec(dllexport) char* GetNumbersGameStartMessage(CNumbersGame* pNumbersGame);

    extern __declspec(dllexport) char* GetNumbersGameBoard(CNumbersGame* pNumbersGame);

    extern __declspec(dllexport) void RunNumbersGame(CNumbersGame* pNumbersGame);

    extern __declspec(dllexport) char* GetNumbersGameEndMessage(CNumbersGame* pNumbersGame);

    extern __declspec(dllexport) int GetNumbersGameScore(CNumbersGame* pNumbersGame,
                                                         const char* answer,
                                                         int answerSize);

// Conundrum Game

    extern __declspec(dllexport) CConundrumGame* CreateConundrumGame();

    extern __declspec(dllexport) void DisposeConundrumGame(CConundrumGame* pConundrumGame);

    extern __declspec(dllexport) bool InitializeConundrumGame(CConundrumGame* pConundrumGame,
                                                              const char* input,
                                                              int inputSize,
                                                              char* output,
                                                              int* outputSize);

    extern __declspec(dllexport) char* GetConundrumGameStartMessage(CConundrumGame* pConundrumGame);

    extern __declspec(dllexport) char* GetConundrumGameBoard(CConundrumGame* pConundrumGame);

    extern __declspec(dllexport) void RunConundrumGame(CConundrumGame* pConundrumGame);

    extern __declspec(dllexport) char* GetConundrumGameEndMessage(CConundrumGame* pConundrumGame);

    extern __declspec(dllexport) int GetConundrumGameScore(CConundrumGame* pConundrumGame,
                                                           const char* answer,
                                                           int answerSize);

#ifdef __cplusplus
}
#endif
