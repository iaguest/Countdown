using System;
using System.Windows.Media;

namespace Countdown.UI.Service
{
    public class CountdownAudioPlayer : ICountdownAudioPlayer
    {
        private const string UriString = "Resources/clock.mp3";

        private readonly MediaPlayer _player;

        public CountdownAudioPlayer()
        {
            _player = new MediaPlayer();
            _player.Open(new Uri(UriString, UriKind.Relative));
        }

        public void Initialise()
        {
            PrepareAudio();
        }

        public void OnStart()
        {
            _player.Play();
        }

        public void OnStop()
        {
            _player.Position = TimeSpan.Zero;
            PrepareAudio();
        }

        private void PrepareAudio()
        {
            _player.Play();
            _player.Pause();
        }
    }
}
