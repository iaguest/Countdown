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

        [HttpGet]
        public IEnumerable<SessionGetResponse> GetSessions()
        {
            return _sessionManager.GetSessions();
        }

        [HttpGet("{sessionId}")]
        public ActionResult<SessionGetResponse> GetSession(int sessionId)
        {
            var session = _sessionManager.GetSession(sessionId);
            if (session == null)
            {
                return NotFound();
            }

            return session;
        }

        [HttpPost]
        public ActionResult<SessionGetResponse> CreateSession()
        {
            var newSession = _sessionManager.CreateSession();
            //return CreatedAtAction(
            //    nameof(GetSession),
            //    new {id = newSession.Id},
            //    newSession);
            return Ok(newSession);
        }
    }
}
