using Autofac;
using Countdown.Model;
using Countdown.UI.Service;
using Countdown.UI.ViewModel;
using Prism.Events;
using System;
using System.Collections.Generic;

namespace Countdown.UI.Startup
{
    class Bootstrapper
    {
        public IContainer Bootstrap()
        {
            var builder = new ContainerBuilder();

            var eventAggregator = new EventAggregator();
            builder.Register(o => eventAggregator).As<IEventAggregator>().SingleInstance();

            builder.RegisterType<MainWindow>().AsSelf();

            builder.RegisterType<CountdownDataService>().As<ICountdownDataService>();

            builder.Register(o => CountdownSession.MakeDefaultCountdownSession(eventAggregator)).As<ICountdownSession>();

            builder.RegisterType<CountdownAudioPlayer>().As<ICountdownAudioPlayer>();

            builder.RegisterType<MainViewModel>().AsSelf();

            return builder.Build();
        }
    }
}
