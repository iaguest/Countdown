using Autofac;
using Countdown.Model;
using Countdown.UI.Data;
using Countdown.UI.ViewModel;

namespace Countdown.UI.Startup
{
    class Bootstrapper
    {
        public IContainer Bootstrap()
        {
            var builder = new ContainerBuilder();

            builder.RegisterType<MainWindow>().AsSelf();

            builder.RegisterType<CountdownDataService>().As<ICountdownDataService>();

            builder.RegisterType<CountdownSession>().As<ICountdownSession>();

            builder.RegisterType<MainViewModel>().AsSelf();

            return builder.Build();
        }
    }
}
