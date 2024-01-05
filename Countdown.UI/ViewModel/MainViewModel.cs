using System;
using System.Threading.Tasks;
using System.Windows.Input;
using Countdown.Model;
using Countdown.UI.Data;
using Prism.Commands;
using Prism.Events;

namespace Countdown.UI.ViewModel
{
    public class MainViewModel : ViewModelBase
    {
        private ICountdownDataService _dataService;
        private ICountdownSession _gameSession;
        private bool _canNextButtonExecute;
        private bool _canRestartButtonExecute;

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
        }

        public DelegateCommand<KeyEventArgs> KeyDownEventCommand { get; private set; }

        public DelegateCommand OnNextGameCommand { get; }

        public DelegateCommand OnRestartCommand { get; }

        public string GameType => _gameSession.GameType.Replace("Game", " Round");

        public string GameBoard => _gameSession.GameBoard.ToUpper();

        public string UserMessage => _gameSession.UserMessage;

        public string UserInput { get; set; }

        public string Score => $"Total Score: {_gameSession.Score}";

        public string HighScore => $"High Score: {_dataService.HighScore}";

        public bool IsRunning { get; private set; }

        public async Task LoadAsync()
        {
            await Task.Run(() => { _dataService.Load(); });
            UpdateAllProperties();
        }

        private void ExecuteUserInput(KeyEventArgs args)
        {
            if (args.Key == Key.Return || args.Key == Key.Enter)
            {
                _gameSession.ExecuteUserInput(UserInput.ToLower());
                UserInput = "";
                UpdateAllProperties();
            }
        }

        private async void OnGameStateUpdated(GameState state)
        {
            IsRunning = state == GameState.RUNNING;
            if (state == GameState.DONE)
            {
                var hasNextGame = _gameSession.HasNextGame;
                CanNextGameCommandExecute = hasNextGame;
                CanRestartCommandExecute = !hasNextGame;
                if (!hasNextGame && _gameSession.Score > _dataService.HighScore)
                {
                    _dataService.HighScore = _gameSession.Score;
                    await Task.Run(() => { _dataService.Save(); });
                }
            }
            UpdateAllProperties();
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
            _gameSession.NextGame();
            CanNextGameCommandExecute = false;
        }

        private void OnRestartCommandExecute()
        {
            _gameSession.Reset();
            CanRestartCommandExecute = false;
            UpdateAllProperties();
        }
    }
}
