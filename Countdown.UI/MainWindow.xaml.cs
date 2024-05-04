using Countdown.UI.ViewModel;
using System.Windows;

namespace Countdown
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private MainViewModel _viewModel;

        public MainWindow(MainViewModel viewModel)
        {
            InitializeComponent();
            _viewModel = viewModel;
            DataContext = _viewModel;
            Loaded += MainWindow_Loaded;
        }

        private async void MainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            mediaPlayer.Play();
            mediaPlayer.Pause();

            await _viewModel.LoadAsync(() =>
            {
                mediaPlayer.Play();
            });
        }

        private void MediaPlayer_MediaEnded(object sender, RoutedEventArgs e)
        {
            mediaPlayer?.Stop();
        }
    }
}
