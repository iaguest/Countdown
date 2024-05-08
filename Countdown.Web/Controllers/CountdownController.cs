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
            var sessionResponse = _sessionManager.GetSession(sessionId);
            if (sessionResponse == null)
            {
                return NotFound();
            }

            return sessionResponse;
        }

        [HttpGet("sessions/{sessionId}/score")]
        public ActionResult<SessionScoreGetResponse> GetSessionScore(int sessionId)
        {
            var sessionScoreResponse = _sessionManager.GetSessionScore(sessionId);
            if (sessionScoreResponse == null)
            {
                return NotFound();
            }

            return sessionScoreResponse;
        }

        [HttpPost("sessions")]
        public ActionResult<SessionGetResponse> CreateSession()
        {
            var createSessionResponse = _sessionManager.CreateSession();
            return CreatedAtAction(
                nameof(GetSession),
                new { sessionId = createSessionResponse.Id },
                createSessionResponse);
        }

        [HttpGet("sessions/{sessionId}/currentRound")]
        public ActionResult<RoundGetResponse> GetCurrentRound(int sessionId)
        {
            var currentRoundResponse = _sessionManager.GetCurrentRound(sessionId);
            if (currentRoundResponse == null)
            {
                return NotFound();
            }

            return currentRoundResponse;
        }

        [HttpGet("sessions/{sessionId}/hasNextRound")]
        public ActionResult<HasNextRoundGetResponse> HasNextRound(int sessionId)
        {
            var hasNextResponse = _sessionManager.HasNextRound(sessionId);
            if (hasNextResponse == null)
            {
                return NotFound();
            }

            return new HasNextRoundGetResponse { HasNextRound = hasNextResponse.HasNextRound };
        }

        [HttpPost("sessions/{sessionId}/nextRound")]
        public ActionResult<RoundGetResponse> StartNextRound(int sessionId)
        {
            var startNextResponse = _sessionManager.StartNextRound(sessionId);
            if (startNextResponse == null)
            {
                return NotFound();
            }

            return startNextResponse;
        }

        [HttpPost("sessions/{sessionId}/currentRound/execute")]
        public ActionResult<UserInputGetResponse> ExecuteUserInput(int sessionId,
                                                                   UserInputPostRequest userInputPostRequest)
        {
            try
            {
                var item = _sessionManager.ExecuteUserInput(sessionId, userInputPostRequest);
                if (item == null)
                {
                    return NotFound();
                }

                return Ok(item);
            }
            catch (Exception ex)
            {
                // Log the exception details here
                return StatusCode(500, $"An error occurred while processing your request. {ex}");
            }
        }

        [HttpPost("sessions/{sessionId}/reset")]
        public ActionResult<SessionGetResponse> ResetSession(int sessionId)
        {
            try
            {
                var item = _sessionManager.ResetSession(sessionId);
                if (item == null)
                {
                    return NotFound(sessionId);
                }

                return Ok(item);
            }
            catch (Exception ex)
            {
                // Log the exception details here
                return StatusCode(500, $"An error occurred while processing your request. {ex}");
            }
        }
    }
}
