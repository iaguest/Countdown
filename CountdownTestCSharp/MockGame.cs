using Countdown.Model;
using System;

namespace CountdownTestsCSharp
{
    public class MockGame : IGame
    {
        public static int DisposeCount = 0;
        public static int RunCount = 0;
        public static int DefaultScore = 99;
        public static string UninitializedGameBoardString = "UNINITIALIZED_BOARD";
        public static string InitializedGameBoardString = "INITIALIZED_BOARD";
        public static string InitializeMessageString = "MOCK_INITIALIZE_MESSAGE";
        public static string StartRunMessageString = "MOCK_START_RUN_MESSAGE";
        public static string EndRunMessageString = "MOCK_END_RUN_MESSAGE";

        public MockGame()
        {
            GameBoard = UninitializedGameBoardString;
        }

        public string Type => "Mock";

        public string InitializeMessage => InitializeMessageString;

        public string StartRunMessage => StartRunMessageString;

        public string GameBoard { get; private set; }

        public string EndRunMessage => EndRunMessageString;

        public void Dispose() { DisposeCount += 1 ; }

        public bool Initialize(string input, out string output)
        {
            output = string.Empty;
            GameBoard = InitializedGameBoardString;
            return true;
        }

        public void Run(Action onDone)
        {
            RunCount += 1;
            onDone();
        }

        public int GetScore(string answer) { return DefaultScore; }
    }
}
