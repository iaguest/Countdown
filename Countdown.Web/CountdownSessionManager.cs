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

        public SessionGetResponse? GetSession(int id)
        {
            if (_sessionsPerId.TryGetValue(id, out ICountdownSession? session))
            {
                return SessionGetResponse.FromCountdownSession(id, session);
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
    };
}
