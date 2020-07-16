using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Countdown.Model
{
    public class CountdownSession : ICountdownSession
    {
        private IEnumerable<IGame> _games;
        private int _currentGameIndex;
        private GameState _state;

        public CountdownSession()
        {
            _games = new List<IGame>
            {
                new LettersGame(),
                new LettersGame()
            };
            _currentGameIndex = 0;
            Score = 0;
            State = GameState.INITIALIZING;
        }

        public event EventHandler<GameStateUpdatedEventArgs> GameStateUpdated;

        public string GameType => CurrentGame.GetType().Name;

        public string GameBoard => CurrentGame.GameBoard;

        public string UserMessage
        {
            get
            {
                switch (State)
                {
                    case GameState.INITIALIZING:
                        return CurrentGame.InitializeMessage;
                    case GameState.RUNNING:
                        var startMessage = CurrentGame.StartRunMessage;
                        var messagePrefix = startMessage.Any() ? startMessage + "\n" : "";
                        return $"{messagePrefix}Running 30 second countdown...";
                    case GameState.SOLVING:
                        return "Enter answer...";
                    case GameState.DONE:
                        return $"You scored {Score}\n\n{CurrentGame.EndRunMessage}";
                    default:
                        return string.Empty;
                }
            }
        }

        public int Score { get; private set; }

        public async void ExecuteUserInput(string input)
        {
            switch (State)
            {
                case GameState.INITIALIZING:
                    await HandleInitializing(input);
                    break;
                case GameState.SOLVING:
                    HandleSolving(input);
                    break;
                case GameState.RUNNING:
                case GameState.DONE:
                    // do nothing
                    break;
            }
        }

        public bool HasNextGame => _currentGameIndex < _games.Count() - 1;

        public void NextGame()
        {
            _currentGameIndex += 1;
            State = GameState.INITIALIZING;
        }

        private GameState State
        {
            get => _state;
            set
            {
                _state = value;
                OnGameStateUpdated(new GameStateUpdatedEventArgs { NewState = _state });
            }
        }

        private IGame CurrentGame => _games.ElementAt(_currentGameIndex);

        private void HandleSolving(string input)
        {
            Score += CurrentGame.GetScore(input);
            Console.Error.WriteLine($"Score: {Score}");
            State = GameState.DONE;
        }

        private async Task HandleInitializing(string input)
        {
            bool isInitialized = CurrentGame.Initialize(input);
            if (isInitialized)
            {
                Console.Error.WriteLine("Finished initialization...");
                State = GameState.RUNNING;
                await Task.Run(() =>
                {
                    CurrentGame.Run(
                      () =>
                      {
                          State = GameState.SOLVING;
                      });
                });

                return;
            }
            State = GameState.INITIALIZING;
        }

        private void OnGameStateUpdated(GameStateUpdatedEventArgs e)
        {
            GameStateUpdated?.Invoke(this, e);
        }
    }
}