namespace Countdown.UI.Data
{
    public interface ICountdownDataService
    {
        int HighScore { get; set; }

        void Load();
        void Save();
    }
}