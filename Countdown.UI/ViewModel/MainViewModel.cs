using System.Windows.Input;
using Countdown.Model;
using Prism.Commands;

namespace Countdown.UI.ViewModel
{
    public class MainViewModel : ViewModelBase
    {
        private readonly ICountdownSession _gameSession;
        private bool _canClickExecute;

        public MainViewModel(ICountdownSession gameSession)
        {
            _gameSession = gameSession;
            _gameSession.GameStateUpdated += OnGameStateUpdated;
            KeyDownEventCommand = new DelegateCommand<KeyEventArgs>(ExecuteUserInput);
            OnNextGameCommand = new DelegateCommand(OnNextGameCommandExecute,
                                                    () => CanNextGameCommandExecute);
            CanNextGameCommandExecute = false;
            UserInput = string.Empty;
        }

        public DelegateCommand<KeyEventArgs> KeyDownEventCommand { get; private set; }

        public DelegateCommand OnNextGameCommand { get; }

        public string GameType => _gameSession.GameType;

        public string GameBoard => _gameSession.GameBoard;

        public string UserMessage => _gameSession.UserMessage;

        public string UserInput { get; set; }

        public string Score => $"Total Score: {_gameSession.Score}";

        public bool IsRunning { get; private set; }

        private void ExecuteUserInput(KeyEventArgs args)
        {
            if (args.Key == Key.Return || args.Key == Key.Enter)
            {
                _gameSession.ExecuteUserInput(UserInput);
                UserInput = "";
                UpdateAllProperties();
            }
        }

        private void OnGameStateUpdated(object sender, GameStateUpdatedEventArgs e)
        {
            var state = e.NewState;
            IsRunning = state == GameState.RUNNING;
            if (state == GameState.DONE)
                CanNextGameCommandExecute = _gameSession.HasNextGame;
            UpdateAllProperties();
        }

        private bool CanNextGameCommandExecute
        {
            get { return _canClickExecute; }
            set
            {
                _canClickExecute = value;
                OnNextGameCommand.RaiseCanExecuteChanged();
            }
        }

        private void OnNextGameCommandExecute()
        {
            _gameSession.NextGame();
            CanNextGameCommandExecute = false;
        }
    }
}
