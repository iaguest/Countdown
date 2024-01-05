using Prism.Events;
using System;
using System.Threading.Tasks;

namespace Countdown.Model
{
    public interface ICountdownSession : IDisposable
    {
        string GameType { get; }
        string GameBoard { get; }
        string UserMessage { get; }
        int Score { get; }

        Task ExecuteUserInput(string input);

        void NotifyGameStateUpdated(IEventAggregator eventAggregator, GameState state);

        bool HasNextGame { get; }
        void NextGame();
        void Reset();
    }
}