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
    }
}
