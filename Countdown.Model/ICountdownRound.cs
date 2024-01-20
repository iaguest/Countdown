using System;
using System.Threading.Tasks;

namespace Countdown.Model
{
    public interface ICountdownRound : IDisposable
    {
        string Type { get; }
        string Message { get; }
        string GameBoard { get; }
        int? Score { get; }

        Task ExecuteUserInput(string input);
    }
}