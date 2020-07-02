using System;
using System.Collections.Generic;

namespace CSharpConsole
{
    class Program
    {
        public static void ExecuteGame(IGame game, IEnumerable<string> inputs, Action<string> onOutput)
        {
            bool isInitialized = false;
            foreach (var input in inputs)
            {
                isInitialized = game.Initialize(input, out string s);
                onOutput(s);
            }

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

        static void Main(string[] args)
        {
            using (var game = new LettersGame())
            {
                var letterTypes = new List<string>
                {
                    "c", "v", "c", "v", "c", "v", "c", "v", "c"
                };

                ExecuteGame(game, letterTypes, (o) => Console.WriteLine(o));
            }
        }
    }
}
