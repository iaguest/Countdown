using System;
using System.Collections.Generic;

namespace CSharpConsole
{
    class Program
    {
        static void Main(string[] args)
        {
            using (var game = new LettersGame())
            {
                var letterTypes = new List<string> { "c", "v", "c", "v", "c", "v", "c", "v", "c" };

                bool isInitialized = false;
                foreach (var letterType in letterTypes)
                    isInitialized = game.Initialize(letterType, out string s);

                if (!isInitialized)
                    throw new InvalidOperationException();

                var board = game.GetGameBoard();
                Console.WriteLine(board);

                game.Run();

                Console.WriteLine("Enter answer: ");
                var answer = Console.ReadLine();

                var score = game.GetScore(answer);
                Console.WriteLine($"Your score is: {score}");

                Console.Write(game.EndMessage());

                Console.ReadLine();
            }
        }
    }
}
