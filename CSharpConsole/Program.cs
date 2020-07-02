using System;
using System.Collections.Generic;
using System.Linq;

namespace CSharpConsole
{
    class Program
    {
        public static void ExecuteGame(IGame game, IEnumerable<string> inputs, Action<string> onOutput)
        {
            string s;
            bool isInitialized = (inputs.Any()) ? false : game.Initialize(string.Empty, out s);
            foreach (var input in inputs)
            {
                isInitialized = game.Initialize(input, out s);
                onOutput(s);
            }

            if (!isInitialized)
                throw new InvalidOperationException();

            var startMessage = game.StartMessage();
            if (!string.IsNullOrEmpty(startMessage))
                Console.WriteLine(startMessage);

            var board = game.GetGameBoard();
            Console.WriteLine(board);

            game.Run();

            Console.WriteLine("Enter answer: ");
            var answer = Console.ReadLine();

            var score = game.GetScore(answer);
            Console.WriteLine($"Your score is: {score}");

            var endMessage = game.EndMessage();
            if (!string.IsNullOrEmpty(endMessage))
                Console.WriteLine(endMessage);

            Console.ReadLine();
        }

        static void Main(string[] args)
        {
            //using (var game = new LettersGame())
            //{
            //    var letterTypes = new List<string>
            //    {
            //        "c", "v", "c", "v", "c", "v", "c", "v", "c"
            //    };

            //    ExecuteGame(game, letterTypes, (o) => { Console.WriteLine(o); });
            //}

            using (var game = new NumbersGame())
            {
                var numLarge = new List<string> { "2" };
                ExecuteGame(game, numLarge, (o) => { });
            }

            //using (var game = new ConundrumGame())
            //{
            //    ExecuteGame(game, Enumerable.Empty<string>(), (o) => { });
            //}
        }
    }
}
