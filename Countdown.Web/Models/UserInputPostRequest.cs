using System.ComponentModel.DataAnnotations;

namespace Countdown.Web.Models
{
    public class UserInputPostRequest
    {
        [Required(AllowEmptyStrings = true)]
        public string? Content { get; set; }
    }
}
