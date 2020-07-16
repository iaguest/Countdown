using System;
using System.Threading;

namespace Countdown.Model
{
    public class LettersGame : IGame
    {
        static Random _random = new Random();

        public string InitializeMessage => "Vowel(v)/Consonant(c)?";

        public string StartRunMessage => string.Empty;

        public string GameBoard { get; private set; } = string.Empty;

        public string EndRunMessage => "Possible words are DOG, CAT";

        // TODO: Validate input
        public bool Initialize(string input)
        {
            if (GameBoard.Length < 9)
            {
                int num = _random.Next(0, 26);
                char let = (char)('a' + num);
                GameBoard = (GameBoard + let).ToUpper();
            }
            return GameBoard.Length >= 9;
        }

        public void Run(Action onDone)
        {
            Console.Error.WriteLine("Running Letters Game...");
            Thread.Sleep(30000);
            onDone();
        }

        public int GetScore(string answer) { return 5; }
    }
}
