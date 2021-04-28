using Countdown.Model;
using NUnit.Framework;
using NUnit.Framework.Internal;
using System;
using System.Collections.Generic;

namespace CountdownTestsCSharp
{
    [TestFixture]
    partial class CountdownSessionShould
    {
        private List<Type> _singleGameList;
        private List<Type> _doubleGameList;

        [SetUp]
        public void Initialize()
        {
            _singleGameList = new List<Type> { typeof(MockGame) };
            _doubleGameList = new List<Type> { typeof(MockGame), typeof(MockGame) };
        }

        [Test]
        public void BeConstructable()
        {
            new CountdownSession(_singleGameList);
        }

        [Test]
        public void NotHaveNextGameAfterConstructionWithSingleGameList()
        {
            var session = new CountdownSession(_singleGameList);
            Assert.IsFalse(session.HasNextGame);
        }

        [Test]
        public void HaveNextGameAfterConstructionWithGameListWithMoreThanOneItem()
        {
            var session = new CountdownSession(_doubleGameList);
            Assert.IsTrue(session.HasNextGame);
        }

        [Test]
        public void HaveUninitializedGameBoardAfterConstruction()
        {
            var session = new CountdownSession(_singleGameList);
            Assert.AreEqual(MockGame.UninitializedGameBoardString, session.GameBoard);
        }

        [Test]
        public void GiveInitializeUserMessageAfterConstruction()
        {
            var session = new CountdownSession(_singleGameList);
            Assert.AreEqual(MockGame.InitializeMessageString, session.UserMessage);
        }

        [Test]
        public void HaveInitializedGameBoardAfterSessionInitialized()
        {
            var session = new CountdownSession(_singleGameList);

            session.ExecuteUserInput("foo");

            Assert.AreEqual(MockGame.InitializedGameBoardString, session.GameBoard);
        }

        [Test]
        public void RunGameAfterInitializationIsComplete()
        {
            var session = new CountdownSession(_singleGameList);
            var expectedRunCount = MockGame.RunCount + 1;
            session.ExecuteUserInput("bar");
            Assert.AreEqual(MockGame.RunCount, expectedRunCount);
        }

        [Test]
        public void DisposeGamesOnDispose()
        {
            var expectedDisposeCount = MockGame.DisposeCount + _doubleGameList.Count;

            using (var session = new CountdownSession(_doubleGameList))
            {
            }

            Assert.AreEqual(expectedDisposeCount, MockGame.DisposeCount);
        }

        [Test]
        public void DisposeGamesOnReset()
        {
            var session = new CountdownSession(_doubleGameList);
            var expectedDisposeCount = MockGame.DisposeCount + _doubleGameList.Count;

            session.Reset();

            Assert.AreEqual(expectedDisposeCount, MockGame.DisposeCount);
        }
    }
}
