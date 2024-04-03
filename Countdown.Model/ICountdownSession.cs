using System;

namespace Countdown.Model
{
    /// <summary>
    /// Defines a countdown session
    /// </summary>
    public interface ICountdownSession : IDisposable
    {
        /// <summary>
        /// Total score for the session
        /// </summary>
        int TotalScore { get; }

        /// <summary>
        /// The current round
        /// </summary>
        /// <returns>Current round</returns>
        ICountdownRound CurrentRound();

        /// <summary>
        /// Whether the session has another round
        /// </summary>
        /// <returns>True if there is another round to be played, otherwise false</returns>
        bool HasNextRound();

        /// <summary>
        /// Start the next round
        /// </summary>
        void NextRound();

        /// <summary>
        /// Reset current session
        /// </summary>
        void ResetSession();
    }
}