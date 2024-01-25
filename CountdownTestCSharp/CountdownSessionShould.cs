using Countdown.Model;
using Moq;
using NUnit.Framework;
using NUnit.Framework.Internal;
using Prism.Events;
using System;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace CountdownTestsCSharp
{
    [TestFixture]
    public class CountdownSessionShould
    {
        private GameStateUpdatedEvent _gameStateUpdatedEvent;
        private Mock<IEventAggregator> _mockEventAggregator;
        private List<Type> _singleGameList;
        private List<Type> _doubleGameList;

        [SetUp]
        public void Initialize()
        {
            _gameStateUpdatedEvent = new GameStateUpdatedEvent();
            _mockEventAggregator = new Mock<IEventAggregator>();
            _mockEventAggregator.Setup(ea => ea.GetEvent<GameStateUpdatedEvent>())
                .Returns(_gameStateUpdatedEvent);
            _singleGameList = new List<Type> { typeof(MockGame) };
            _doubleGameList = new List<Type> { typeof(MockGame), typeof(MockGame) };
        }

        [Test]
        public void BeConstructable()
        {
            new CountdownSession(_mockEventAggregator.Object, _singleGameList);
        }

        [Test]
        public void NotHaveNextRoundAfterConstructionWithSingleGameList()
        {
            var session = new CountdownSession(_mockEventAggregator.Object, _singleGameList);
            Assert.IsFalse(session.HasNextRound());
        }

        [Test]
        public void HaveNextRoundAfterConstructionWithGameListWithMoreThanOneItem()
        {
            var session = new CountdownSession(_mockEventAggregator.Object, _doubleGameList);
            Assert.IsTrue(session.HasNextRound());
        }

        [Test]
        public void ShowUninitializedGameBoardAfterConstruction()
        {
            var session = new CountdownSession(_mockEventAggregator.Object, _singleGameList);
            Assert.AreEqual(MockGame.UninitializedGameBoardString, session.CurrentRound().GameBoard);
        }

        [Test]
        public void ShowInitializeUserMessageAfterConstruction()
        {
            var session = new CountdownSession(_mockEventAggregator.Object, _singleGameList);
            Assert.AreEqual(MockGame.InitializeMessageString, session.CurrentRound().Message);
        }

        [Test]
        public async Task ShowInitializedGameBoardAfterSessionInitialized()
        {
            var session = new CountdownSession(_mockEventAggregator.Object, _singleGameList);

            await session.CurrentRound().ExecuteUserInput("foo");

            Assert.AreEqual(MockGame.InitializedGameBoardString, session.CurrentRound().GameBoard);
        }

        [Test]
        public async Task RunGameAfterInitializationIsComplete()
        {
            var session = new CountdownSession(_mockEventAggregator.Object, _singleGameList);
            var expectedRunCount = MockGame.RunCount + 1;
            await session.CurrentRound().ExecuteUserInput("bar");
            Assert.AreEqual(MockGame.RunCount, expectedRunCount);
        }

        [Test]
        public void DisposeGamesOnDispose()
        {
            var expectedDisposeCount = MockGame.DisposeCount + _doubleGameList.Count;

            using (var session = new CountdownSession(_mockEventAggregator.Object, _doubleGameList))
            {
            }

            Assert.AreEqual(expectedDisposeCount, MockGame.DisposeCount);
        }

        [Test]
        public void DisposeGamesOnReset()
        {
            var session = new CountdownSession(_mockEventAggregator.Object, _doubleGameList);
            var expectedDisposeCount = MockGame.DisposeCount + _doubleGameList.Count;

            session.ResetSession();

            Assert.AreEqual(expectedDisposeCount, MockGame.DisposeCount);
        }
    }
}
