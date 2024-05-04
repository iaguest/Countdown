using System;
using System.Threading.Tasks;
using System.Windows.Input;
using Countdown.Model;
using Countdown.UI.Data;
using Prism.Commands;
using Prism.Events;
using Prism.Mvvm;

namespace Countdown.UI.ViewModel
{
    public class MainViewModel : BindableBase
    {
        private ICountdownDataService _dataService;
        private ICountdownSession _gameSession;
        private string _gameType;
        private string _userMessage;
        private string _gameBoard;
        private string _userInput;
        private int _score;
        private int _highScore;
        private bool _isRunning;
        private bool _canNextButtonExecute;
        private bool _canRestartButtonExecute;
        private Action _onStartRunning;

        public MainViewModel(IEventAggregator eventAggregator,
                             ICountdownDataService dataService,
                             ICountdownSession gameSession)
        {
            eventAggregator.GetEvent<GameStateUpdatedEvent>().Subscribe(OnGameStateUpdated);

            _dataService = dataService;
            _gameSession = gameSession;
            KeyDownEventCommand = new DelegateCommand<KeyEventArgs>(ExecuteUserInput);
            OnNextGameCommand = new DelegateCommand(OnNextGameCommandExecute,
                                                    () => CanNextGameCommandExecute);
            OnRestartCommand = new DelegateCommand(OnRestartCommandExecute,
                                                   () => CanRestartCommandExecute);
            CanNextGameCommandExecute = false;
            CanRestartCommandExecute = false;
            UserInput = string.Empty;

            RefreshDisplay();
        }

        public DelegateCommand<KeyEventArgs> KeyDownEventCommand { get; private set; }

        public DelegateCommand OnNextGameCommand { get; }

        public DelegateCommand OnRestartCommand { get; }

        public ICountdownRound CurrentRound => _gameSession.CurrentRound();

        public string GameType
        {
            get { return _gameType; }
            set { SetProperty(ref _gameType, value); }
        }

        public string GameBoard
        {
            get { return _gameBoard; }
            set { SetProperty(ref _gameBoard, value); }
        }

        public string UserMessage
        {
            get { return _userMessage; }
            set { SetProperty(ref _userMessage, value); }
        }

        public string UserInput
        {
            get { return _userInput; }
            set { SetProperty(ref _userInput, value); }
        }

        public int Score
        {
            get { return _score; }
            set { SetProperty(ref _score, value); }
        }

        public int HighScore
        {
            get { return _highScore; }
            set { SetProperty(ref _highScore, value); }
        }

        public bool IsRunning
        {
            get { return _isRunning; }
            set
            {
                if (value)
                {
                    _onStartRunning();
                }

                SetProperty(ref _isRunning, value);
            }
        }

        public async Task LoadAsync(Action onStartRunning)
        {
            _onStartRunning = onStartRunning;
            await Task.Run(() => { _dataService.Load(); });
            RefreshDisplay();
        }

        private bool CanNextGameCommandExecute
        {
            get { return _canNextButtonExecute; }
            set
            {
                _canNextButtonExecute = value;
                OnNextGameCommand.RaiseCanExecuteChanged();
            }
        }

        private bool CanRestartCommandExecute
        {
            get { return _canRestartButtonExecute; }
            set
            {
                _canRestartButtonExecute = value;
                OnRestartCommand.RaiseCanExecuteChanged();
            }
        }

        private void OnNextGameCommandExecute()
        {
            _gameSession.NextRound();
            CanNextGameCommandExecute = false;
            RefreshDisplay();
        }

        private void OnRestartCommandExecute()
        {
            _gameSession.ResetSession();
            CanRestartCommandExecute = false;
            RefreshDisplay();
        }

        private void ExecuteUserInput(KeyEventArgs args)
        {
            if (args.Key != Key.Return && args.Key != Key.Enter)
            {
                return;
            }

            CurrentRound.ExecuteUserInput(UserInput.ToLower());
            UserInput = string.Empty;
        }

        private async void OnGameStateUpdated()
        {
            if (CurrentRound.State == RoundState.DONE)
            {
                var hasNextGame = _gameSession.HasNextRound();
                CanNextGameCommandExecute = hasNextGame;
                CanRestartCommandExecute = !hasNextGame;
                if (!hasNextGame && _gameSession.TotalScore > _dataService.HighScore)
                {
                    _dataService.HighScore = _gameSession.TotalScore;
                    await Task.Run(() => { _dataService.Save(); });
                }
            }

            RefreshDisplay();
        }

        private void RefreshDisplay()
        {
            GameType = CurrentRound.Type;
            GameBoard = CurrentRound.GameBoard.ToUpper();
            UserMessage = CurrentRound.Message;
            Score = _gameSession.TotalScore;
            HighScore = _dataService.HighScore;
            IsRunning = CurrentRound.State == RoundState.RUNNING;
        }
    }
}
