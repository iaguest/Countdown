namespace Countdown.UI.Service
{
    public interface ICountdownDataService
    {
        int HighScore { get; set; }

        void Load();
        void Save();
    }
}