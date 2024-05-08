using Countdown.Web.Models;

namespace Countdown.Web
{
    public interface ICountdownSessionManager
    {
        // Probably want to delete this!
        IEnumerable<SessionGetResponse> GetSessions();

        SessionGetResponse? GetSession(int id);

        SessionScoreGetResponse? GetSessionScore(int id);

        SessionGetResponse CreateSession();

        RoundGetResponse? GetCurrentRound(int sessionId);

        HasNextRoundGetResponse? HasNextRound(int sessionId);

        RoundGetResponse? StartNextRound(int sessionId);

        UserInputGetResponse? ExecuteUserInput(int sessionId, UserInputPostRequest userInputPostRequest);

        SessionGetResponse? ResetSession(int sessionId);
    }
}