using Countdown.Model;

namespace Countdown.Web.Models
{
    public class SessionGetResponse
    {
        public SessionGetResponse(int id, ICountdownSession session)
        {
            Id = id;
            TotalScore = session.TotalScore;
            CurrentRound = new RoundGetResponse(session.CurrentRound());
        }

        public int Id { get; }
        public int TotalScore { get; }
        public RoundGetResponse CurrentRound { get; }
    }
}
