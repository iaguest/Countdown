using System;
using System.Threading.Tasks;

namespace Countdown.Model
{
    public interface ICountdownSession : IDisposable
    {
        event EventHandler<GameStateUpdatedEventArgs> GameStateUpdated;

        string GameType { get; }
        string GameBoard { get; }
        string UserMessage { get; }
        int Score { get; }

        Task ExecuteUserInput(string input);

        bool HasNextGame { get; }
        void NextGame();
        void Reset();
    }
}