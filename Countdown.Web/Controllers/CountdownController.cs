using Countdown.Web.Models;
using Microsoft.AspNetCore.Mvc;

namespace Countdown.Web.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class CountdownController : ControllerBase
    {
        private readonly ICountdownSessionManager _sessionManager;

        public CountdownController(ICountdownSessionManager sessionManager)
        {
            _sessionManager = sessionManager;
        }

        [HttpGet("sessions")]
        public IEnumerable<SessionGetResponse> GetSessions()
        {
            return _sessionManager.GetSessions();
        }

        [HttpGet("sessions/{sessionId}")]
        public ActionResult<SessionGetResponse> GetSession(int sessionId)
        {
            var session = _sessionManager.GetSession(sessionId);
            if (session == null)
            {
                return NotFound();
            }

            return session;
        }

        [HttpPost("sessions")]
        public ActionResult<SessionGetResponse> CreateSession()
        {
            var newSession = _sessionManager.CreateSession();
            return CreatedAtAction(
                nameof(GetSession),
                new { sessionId = newSession.Id },
                newSession);
        }

        [HttpGet("sessions/{sessionId}/currentRound")]
        public ActionResult<RoundGetResponse> GetCurrentRound(int sessionId)
        {
            var round = _sessionManager.GetCurrentRound(sessionId);
            if (round == null)
            {
                return NotFound();
            }

            return round;
        }

        [HttpGet("sessions/{sessionId}/hasNextRound")]
        public ActionResult<HasNextRoundGetResponse> HasNextRound(int sessionId)
        {
            var hasNext = _sessionManager.HasNextRound(sessionId);
            if (hasNext == null)
            {
                return NotFound();
            }

            return new HasNextRoundGetResponse { HasNextRound = hasNext.HasNextRound };
        }
    }
}
