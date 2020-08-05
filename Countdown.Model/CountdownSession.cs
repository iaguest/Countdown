using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Countdown.Model
{
    public class CountdownSession : ICountdownSession
    {
        private const int MAX_ANSWER_WAIT_TIME = 10;

        private readonly IEnumerable<Type> _gameSequence;
        private IList<IGame> _games;
        private int _currentGameIndex;
        private GameState _state;
        private int _lastScore;
        private DateTime _runCompleteDateTime;
        private bool _isAnswerTimeout;

        public CountdownSession(IEnumerable<Type> gameSequence)
        {
            if (!gameSequence.All(o => typeof(IGame).IsAssignableFrom(o)))
                throw new ArgumentException("gameSequence invalid");
            _gameSequence = gameSequence;

            InitializeSession();
        }

        public void Dispose()
        {
            DisposeGames();
        }

        public void Reset()
        {
            DisposeGames();
            InitializeSession();
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
                        return GetRunSolveMessage("Running 30 second countdown...");
                    case GameState.SOLVING:
                        return GetRunSolveMessage("Enter answer...");
                    case GameState.DONE:
                        var timeoutMsg = _isAnswerTimeout ?
                            $" as you took longer than {MAX_ANSWER_WAIT_TIME} seconds to answer."
                            : string.Empty;
                        return $"In this round, you scored {Score - _lastScore}{timeoutMsg}\n\n{CurrentGame.EndRunMessage}";
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

        private void InitializeSession()
        {
            _games = new List<IGame>();
            foreach (var gameType in _gameSequence)
                _games.Add((IGame)Activator.CreateInstance(gameType));

            _currentGameIndex = 0;
            State = GameState.INITIALIZING;
            _lastScore = 0;
            _runCompleteDateTime = default(DateTime);
            _isAnswerTimeout = false;
            Score = 0;
        }

        private void DisposeGames()
        {
            foreach (var game in _games)
            {
                game?.Dispose();
            }
        }

        private void HandleSolving(string input)
        {
            _lastScore = Score;
            _isAnswerTimeout = (DateTime.Now - _runCompleteDateTime).TotalSeconds > MAX_ANSWER_WAIT_TIME;
            Score += _isAnswerTimeout ? 0 : CurrentGame.GetScore(input);
            State = GameState.DONE;
        }

        private async Task HandleInitializing(string input)
        {
            bool isInitialized = CurrentGame.Initialize(input, out string output);
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
                          _runCompleteDateTime = DateTime.Now;
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

        private string GetRunSolveMessage(string tail)
        {
            var startMessage = CurrentGame.StartRunMessage;
            var head = startMessage.Any()
                ? startMessage.PadLeft(Math.Max(startMessage.Length, tail.Length)) + "\n\n"
                : "";
            return $"{head}{tail}";
        }
    }
}