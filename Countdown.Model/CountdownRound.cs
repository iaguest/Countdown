using Prism.Events;
using System;
using System.Linq;
using System.Threading.Tasks;

namespace Countdown.Model
{
    public sealed class CountdownRound : ICountdownRound
    {
        private readonly IEventAggregator _eventAggregator;
        private readonly IGame _game;
        private readonly int _maxAnswerWaitTime;
        private int? _score;
        private DateTime _runCompleteDateTime;
        private bool _isAnswerTimeout;
        private RoundState _state;

        public CountdownRound(IEventAggregator eventAggregator,
                              IGame game,
                              int maxAnswerWaitTime)
        {
            _eventAggregator = eventAggregator;
            _game = game;
            _maxAnswerWaitTime = maxAnswerWaitTime;
            _runCompleteDateTime = DateTime.MinValue;
            _state = RoundState.INITIALIZING;
        }

        public string Type => _game.Type;

        public RoundState State
        {
            get => _state;
            private set
            {
                _state = value;
                _eventAggregator.GetEvent<GameStateUpdatedEvent>().Publish();
            }
        }

        public string Message => GetMessage();

        public string GameBoard => _game.GameBoard;

        public int? Score
        {
            get => _score;
            private set => _score = value;
        }

        public void Dispose()
        {
            _game?.Dispose();
        }

        public async Task ExecuteUserInput(string input)
        {
            switch (State)
            {
                case RoundState.INITIALIZING:
                    await HandleInitializing(input);
                    break;
                case RoundState.SOLVING:
                    HandleSolving(input);
                    break;
                case RoundState.RUNNING:
                case RoundState.DONE:
                    // do nothing
                    break;
            }
        }

        private string GetMessage()
        {
            switch (State)
            {
                case RoundState.INITIALIZING:
                    return _game.InitializeMessage;
                case RoundState.RUNNING:
                    return GetRunSolveMessage("Running 30 second countdown...");
                case RoundState.SOLVING:
                    return GetRunSolveMessage("Enter answer...");
                case RoundState.DONE:
                    var timeoutMsg = _isAnswerTimeout ?
                        $" as you took longer than {_maxAnswerWaitTime} seconds to answer."
                        : string.Empty;
                    return $"In this round, you scored {Score}{timeoutMsg}\n\n{_game.EndRunMessage}";
                default:
                    return string.Empty;
            }
        }

        private string GetRunSolveMessage(string tail)
        {
            var startMessage = _game.StartRunMessage;
            var head = startMessage.Any()
                ? startMessage.PadLeft(Math.Max(startMessage.Length, tail.Length)) + "\n\n"
                : "";
            return $"{head}{tail}";
        }

        private async Task HandleInitializing(string input)
        {
            bool isInitialized = _game.Initialize(input, out string output);
            if (isInitialized)
            {
                Console.Error.WriteLine("Finished initialization...");
                State = RoundState.RUNNING;
                await Task.Run(() =>
                {
                    _game.Run(onDone: () =>
                    {
                        State = RoundState.SOLVING;
                        _runCompleteDateTime = DateTime.Now;
                    });
                });

                return;
            }

            State = RoundState.INITIALIZING;
        }

        private void HandleSolving(string input)
        {
            _isAnswerTimeout = (DateTime.Now - _runCompleteDateTime).TotalSeconds > _maxAnswerWaitTime;
            Score = _isAnswerTimeout ? 0 : _game.GetScore(input);
            State = RoundState.DONE;
        }
    }
}
