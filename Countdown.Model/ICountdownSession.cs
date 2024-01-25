using System;

namespace Countdown.Model
{
    public interface ICountdownSession : IDisposable
    {
        int TotalScore { get; }

        ICountdownRound CurrentRound();
        bool HasNextRound();
        void NextRound();
        void ResetSession();
    }
}