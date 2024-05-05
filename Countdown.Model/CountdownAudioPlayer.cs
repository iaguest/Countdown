using System;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Media;

namespace Countdown.Model
{
    public class CountdownAudioPlayer : IAudioPlayer
    {
        private readonly MediaPlayer _player;

        public CountdownAudioPlayer()
        {
            _player = new MediaPlayer();
            _player.Open(new Uri("Resources/clock.mp3", UriKind.Relative));
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
