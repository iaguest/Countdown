using Countdown.Model;

namespace Countdown.Web.Models
{
    public class RoundGetResponse
    {
        public RoundGetResponse(ICountdownRound round)
        {
            Type = round.Type;
            RoundState = round.State;
            Message = round.Message;
            GameBoard = round.GameBoard;
            Score = round.Score;
        }

        public string Type { get; }

        public RoundState RoundState { get; }

        public string Message { get; }

        public string GameBoard { get; }

        public int? Score { get; }
    }
}
