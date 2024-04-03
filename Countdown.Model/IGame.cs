using System;

namespace Countdown.Model
{
    /// <summary>
    /// Defines a countdown game/ round
    /// </summary>
    public interface IGame : IDisposable
    {
        /// <summary>
        /// A type descriptor for the round
        /// </summary>
        string Type { get; }

        /// <summary>
        /// Message to display to the user
        /// upon initializing the game
        /// </summary>
        string InitializeMessage { get; }

        /// <summary>
        /// Message to display to the user
        /// when the game starts
        /// </summary>
        string StartRunMessage { get; }

        /// <summary>
        /// The current gameboard
        /// </summary>
        string GameBoard { get; }

        /// <summary>
        /// Message to display to the user
        /// when the game ends
        /// </summary>
        string EndRunMessage { get; }

        /// <summary>
        /// Perform a game initialization step
        /// </summary>
        /// <param name="input">User input for the next initialization step</param>
        /// <param name="output">Output string after the completed step</param>
        /// <returns>True if game is initializd, otherwise false</returns>
        bool Initialize(string input, out string output);

        /// <summary>
        /// Run the game
        /// </summary>
        /// <param name="onDone">Action to perform once the game has run</param>
        void Run(Action onDone);

        /// <summary>
        /// Get the user's score for this game based on their answer
        /// </summary>
        /// <param name="answer">User answer input</param>
        /// <returns>Number of points scored</returns>
        int GetScore(string answer);
    }
}