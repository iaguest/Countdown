using Autofac;
using Countdown.Model;
using Countdown.UI.Data;
using Countdown.UI.ViewModel;
using System;
using System.Collections.Generic;

namespace Countdown.UI.Startup
{
    class Bootstrapper
    {
        public IContainer Bootstrap()
        {
            var builder = new ContainerBuilder();

            builder.RegisterType<MainWindow>().AsSelf();

            builder.RegisterType<CountdownDataService>().As<ICountdownDataService>();

            var defaultGameSequence = new List<Type>
            {
                typeof(LettersGame),
                typeof(LettersGame),
                typeof(NumbersGame),
                typeof(LettersGame),
                typeof(LettersGame),
                typeof(NumbersGame),
                typeof(ConundrumGame),
            };

            builder.Register(o => new CountdownSession(defaultGameSequence)).As<ICountdownSession>();

            builder.RegisterType<MainViewModel>().AsSelf();

            return builder.Build();
        }
    }
}
