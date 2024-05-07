using Countdown.Model;

namespace Countdown.Web.Models
{
    public class RoundGetResponse
    {
        public string Type { get; set; }
        public RoundState RoundState { get; set; }
        public string Message { get; set; }
        public string GameBoard { get; set; }
        public int? Score { get; set; }

        public static RoundGetResponse FromCountdownRound(ICountdownRound round)
        {
            return new RoundGetResponse
            {
                Type = round.Type,
                RoundState = round.State,
                Message = round.Message,
                GameBoard = round.GameBoard,
                Score = round.Score,
            };
        }
    }
}
