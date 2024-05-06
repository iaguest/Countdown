namespace Countdown.UI.Service
{
    public interface ICountdownAudioPlayer
    {
        /// <summary>
        /// Perform any initialization
        /// </summary>
        void Initialise();

        /// <summary>
        /// Handle start
        /// </summary>
        void OnStart();

        /// <summary>
        /// Handle stop
        /// </summary>
        void OnStop();
    }
}
