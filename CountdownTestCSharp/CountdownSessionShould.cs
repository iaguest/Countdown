using Countdown.Model;
using NUnit.Framework;
using NUnit.Framework.Internal;
using Prism.Events;
using System;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace CountdownTestsCSharp
{
    [TestFixture]
    partial class CountdownSessionShould
    {
        private IEventAggregator _eventAggregator;
        private List<Type> _singleGameList;
        private List<Type> _doubleGameList;

        [SetUp]
        public void Initialize()
        {
            _eventAggregator = new EventAggregator();
            _singleGameList = new List<Type> { typeof(MockGame) };
            _doubleGameList = new List<Type> { typeof(MockGame), typeof(MockGame) };
        }

        [Test]
        public void BeConstructable()
        {
            new CountdownSession(_eventAggregator, _singleGameList);
        }

        [Test]
        public void NotHaveNextGameAfterConstructionWithSingleGameList()
        {
            var session = new CountdownSession(_eventAggregator, _singleGameList);
            Assert.IsFalse(session.HasNextRound());
        }

        [Test]
        public void HaveNextGameAfterConstructionWithGameListWithMoreThanOneItem()
        {
            var session = new CountdownSession(_eventAggregator, _doubleGameList);
            Assert.IsTrue(session.HasNextRound());
        }

        [Test]
        public void HaveUninitializedGameBoardAfterConstruction()
        {
            var session = new CountdownSession(_eventAggregator, _singleGameList);
            Assert.AreEqual(MockGame.UninitializedGameBoardString, session.CurrentRound().GameBoard);
        }

        [Test]
        public void GiveInitializeUserMessageAfterConstruction()
        {
            var session = new CountdownSession(_eventAggregator, _singleGameList);
            Assert.AreEqual(MockGame.InitializeMessageString, session.CurrentRound().Message);
        }

        [Test]
        public async Task HaveInitializedGameBoardAfterSessionInitialized()
        {
            var session = new CountdownSession(_eventAggregator, _singleGameList);

            await session.CurrentRound().ExecuteUserInput("foo");

            Assert.AreEqual(MockGame.InitializedGameBoardString, session.CurrentRound().GameBoard);
        }

        [Test]
        public async Task RunGameAfterInitializationIsComplete()
        {
            var session = new CountdownSession(_eventAggregator, _singleGameList);
            var expectedRunCount = MockGame.RunCount + 1;
            await session.CurrentRound().ExecuteUserInput("bar");
            Assert.AreEqual(MockGame.RunCount, expectedRunCount);
        }

        [Test]
        public void DisposeGamesOnDispose()
        {
            var expectedDisposeCount = MockGame.DisposeCount + _doubleGameList.Count;

            using (var session = new CountdownSession(_eventAggregator, _doubleGameList))
            {
            }

            Assert.AreEqual(expectedDisposeCount, MockGame.DisposeCount);
        }

        [Test]
        public void DisposeGamesOnReset()
        {
            var session = new CountdownSession(_eventAggregator, _doubleGameList);
            var expectedDisposeCount = MockGame.DisposeCount + _doubleGameList.Count;

            session.ResetSession();

            Assert.AreEqual(expectedDisposeCount, MockGame.DisposeCount);
        }
    }
}
