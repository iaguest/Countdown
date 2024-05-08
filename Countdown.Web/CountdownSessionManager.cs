using Countdown.Model;
using Countdown.Web.Models;
using Prism.Events;

namespace Countdown.Web
{
    public class CountdownSessionManager : ICountdownSessionManager
    {
        private readonly IEventAggregator _eventAggregator;
        private Dictionary<int, ICountdownSession> _sessionsPerId;

        public CountdownSessionManager(IEventAggregator eventAggregator)
        {
            _eventAggregator = eventAggregator;

            _sessionsPerId = new Dictionary<int, ICountdownSession>();
        }

        public IEnumerable<SessionGetResponse> GetSessions()
        {
            return _sessionsPerId.Select(o => SessionGetResponse.FromCountdownSession(o.Key, o.Value));
        }

        public SessionGetResponse? GetSession(int sessionId)
        {
            if (_sessionsPerId.TryGetValue(sessionId, out ICountdownSession? session))
            {
                return SessionGetResponse.FromCountdownSession(sessionId, session);
            }

            return null;
        }

        public SessionGetResponse CreateSession()
        {
            CountdownSession newSession = CountdownSession.MakeDefaultCountdownSession(_eventAggregator);
            int sessionId = _sessionsPerId.Count;

            _sessionsPerId.Add(sessionId, newSession);

            return SessionGetResponse.FromCountdownSession(sessionId, newSession);
        }

        public RoundGetResponse? GetCurrentRound(int sessionId)
        {
            if (_sessionsPerId.TryGetValue(sessionId, out ICountdownSession? session))
            {
                return RoundGetResponse.FromCountdownRound(session.CurrentRound());
            }

            return null;
        }

        public HasNextRoundGetResponse? HasNextRound(int sessionId)
        {
            if (_sessionsPerId.TryGetValue(sessionId, out ICountdownSession? session))
            {
                return new HasNextRoundGetResponse { HasNextRound = session.HasNextRound() };
            }

            return null;
        }

        public RoundGetResponse? StartNextRound(int sessionId)
        {
            if (_sessionsPerId.TryGetValue(sessionId, out ICountdownSession? session))
            {
                session.NextRound();
                return RoundGetResponse.FromCountdownRound(session.CurrentRound());
            }

            return null;
        }

        public UserInputGetResponse? ExecuteUserInput(UserInputPostRequest userInputPostRequest)
        {
            if (_sessionsPerId.TryGetValue(userInputPostRequest.Id, out ICountdownSession? session))
            {
                session.CurrentRound().ExecuteUserInput(userInputPostRequest.Content);
                return new UserInputGetResponse
                {
                    CurrentRound = RoundGetResponse.FromCountdownRound(session.CurrentRound())
                };
            }

            return null;
        }
    };
}
