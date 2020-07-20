using System;

namespace Countdown.Model
{
    public interface ICountdownSession : IDisposable
    {
        event EventHandler<GameStateUpdatedEventArgs> GameStateUpdated;

        string GameType { get; }
        string GameBoard { get; }
        string UserMessage { get; }
        int Score { get; }

        void ExecuteUserInput(string input);

        bool HasNextGame { get; }
        void NextGame();
        void Reset();
    }
}