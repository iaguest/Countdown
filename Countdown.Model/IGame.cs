using System;

namespace Countdown.Model
{
    public interface IGame : IDisposable
    {
        string InitializeMessage { get; }
        string StartRunMessage { get; }
        string GameBoard { get; }
        string EndRunMessage { get; }

        bool Initialize(string input, out string output);
        void Run(Action onDone);
        int GetScore(string answer);

    }
}