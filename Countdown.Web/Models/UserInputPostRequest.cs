using System.ComponentModel.DataAnnotations;

namespace Countdown.Web.Models
{
    public class UserInputPostRequest
    {
        [Required]
        public int Id { get; set; }

        [Required]
        public string Content { get; set; }
    }
}
