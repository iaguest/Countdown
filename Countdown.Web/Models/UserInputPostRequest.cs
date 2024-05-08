using System.ComponentModel.DataAnnotations;

namespace Countdown.Web.Models
{
    public class UserInputPostRequest
    {
        [Required]
        public string? Content { get; set; }
    }
}
