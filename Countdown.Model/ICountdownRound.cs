using System;
using System.Threading.Tasks;

namespace Countdown.Model
{
    /// <summary>
    /// Defines a countdown round
    /// </summary>
    public interface ICountdownRound : IDisposable
    {
        /// <summary>
        /// A type descriptor for the round
        /// </summary>
        string Type { get; }

        /// <summary>
        /// The current round state
        /// </summary>
        RoundState State { get; }

        /// <summary>
        /// Message prompt to display to the user,
        /// guiding their next action
        /// </summary>
        string Message { get; }

        /// <summary>
        /// The current game board
        /// </summary>
        string GameBoard { get; }

        /// <summary>
        /// The score for this round
        /// </summary>
        int? Score { get; }

        /// <summary>
        /// Execute string based input from the user
        /// </summary>
        /// <param name="input">User input string</param>
        /// <returns>Task</returns>
        Task ExecuteUserInput(string input);
    }
}