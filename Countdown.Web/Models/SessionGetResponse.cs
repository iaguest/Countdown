using Countdown.Model;

namespace Countdown.Web.Models
{
    public class SessionGetResponse
    {
        public int Id { get; set; }
        public int TotalScore { get; set; }
        public RoundGetResponse CurrentRound { get; set; }

        public static SessionGetResponse FromCountdownSession(int id,
                                                              ICountdownSession session)
        {
            return new SessionGetResponse
            {
                Id = id,
                TotalScore = session.TotalScore,
                CurrentRound = new RoundGetResponse
                {
                    Type = session.CurrentRound().Type,
                    RoundState = session.CurrentRound().State,
                    Message = session.CurrentRound().Message,
                    GameBoard = session.CurrentRound().GameBoard,
                    Score = session.CurrentRound().Score,
                }
            };
        }
    }
}
