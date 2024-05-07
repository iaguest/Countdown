using Countdown.Web.Models;

namespace Countdown.Web
{
    public interface ICountdownSessionManager
    {
        // Probably want to delete this!
        IEnumerable<SessionGetResponse> GetSessions();

        SessionGetResponse? GetSession(int id);

        SessionGetResponse CreateSession();

        RoundGetResponse? GetCurrentRound(int sessionId);

        HasNextRoundGetResponse? HasNextRound(int sessionId);
    }
}