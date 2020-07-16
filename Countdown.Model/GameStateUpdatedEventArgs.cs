using System;

namespace Countdown.Model
{
    public class GameStateUpdatedEventArgs : EventArgs
    {
        public GameState NewState { get; set; }
    }
}