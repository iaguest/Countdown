using Prism.Events;
using System;
using System.Collections.Generic;
using System.Linq;

namespace Countdown.Model
{
    public sealed class CountdownSession : ICountdownSession
    {
        private const int MAX_ANSWER_WAIT_TIME = 10;
        private readonly IEventAggregator _eventAggregator;
        private readonly IEnumerable<Type> _gameSequence;
        private IList<ICountdownRound> _countdownRounds;
        private int _currentRoundIndex;

        public CountdownSession(IEventAggregator eventAggregator,
                                IEnumerable<Type> gameSequence)
        {
            _eventAggregator = eventAggregator;
            _gameSequence = gameSequence;
            _countdownRounds = new List<ICountdownRound>();

            ResetSession();
        }

        public int TotalScore => _countdownRounds.Sum(o => o.Score ?? 0);

        public static CountdownSession MakeDefaultCountdownSession(IEventAggregator eventAggregator)
        {
            return new CountdownSession(
                eventAggregator,
                new List<Type>
                {
                    typeof(LettersGame),
                    typeof(LettersGame),
                    typeof(NumbersGame),
                    typeof(LettersGame),
                    typeof(LettersGame),
                    typeof(NumbersGame),
                    typeof(ConundrumGame),
                });
        }

        public void Dispose()
        {
            DisposeGames();
        }

        public ICountdownRound CurrentRound()
        {
            return _countdownRounds[_currentRoundIndex];
        }

        public bool HasNextRound()
        {
            return _currentRoundIndex < _countdownRounds.Count - 1;
        }

        public void NextRound()
        {
            if (HasNextRound())
            {
                _currentRoundIndex++;
                return;
            }

            throw new InvalidOperationException();
        }

        public void ResetSession()
        {
            DisposeGames();

            _currentRoundIndex = 0;
            _countdownRounds.Clear();

            if (!_gameSequence.All(o => typeof(IGame).IsAssignableFrom(o)))
                throw new ArgumentException("gameSequence invalid");

            foreach (Type gameType in _gameSequence)
            {
                IGame game = ((IGame)Activator.CreateInstance(gameType));
                _countdownRounds.Add(new CountdownRound(_eventAggregator, game, MAX_ANSWER_WAIT_TIME));
            }
        }

        private void DisposeGames()
        {
            foreach (ICountdownRound round in _countdownRounds)
            {
                round?.Dispose();
            }
        }
    }
}