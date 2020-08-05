using Countdown.Model;
using NUnit.Framework;
using NUnit.Framework.Internal;
using System;
using System.Collections.Generic;

namespace CountdownTestsCSharp
{
    [TestFixture]
    class CountdownSessionShould
    {
        #region MockGame

        private class MockGame : IGame
        {
            public MockGame()
            {
                DisposeCount = 0;
                GameBoard = string.Empty;
            }

            #region IGame

            public string InitializeMessage => string.Empty;

            public string StartRunMessage => string.Empty;

            public string GameBoard { get; private set; }

            public string EndRunMessage => string.Empty;

            public void Dispose() { DisposeCount += 1; }

            public bool Initialize(string input, out string output)
            {
                output = string.Empty;
                GameBoard = "MOCKBOARD";
                return true;
            }

            public void Run(Action onDone) { onDone(); }

            public int GetScore(string answer) { return 99; }

            #endregion

            #region MockHelperMethods

            public int DisposeCount { get; private set; }

            #endregion
        }

        #endregion

        private MockGame _mockGame;
        private List<Type> _mockGameSequence;

        [SetUp]
        public void Initialize()
        {
            _mockGame = new MockGame();
            _mockGameSequence = new List<Type> { _mockGame.GetType() };
        }

        [Test]
        public void BeConstructable()
        {
            new CountdownSession(_mockGameSequence);
        }

        [Test]
        public void HaveEmptyGameBoardAfterConstruction()
        {
            var session = new CountdownSession(_mockGameSequence);
            Assert.AreEqual(string.Empty, session.GameBoard);
        }

        [Test]
        public void CallDisposeOnReset()
        {
            var session = new CountdownSession(_mockGameSequence);
            session.Reset();
            Assert.AreEqual(1, _mockGame.DisposeCount);
        }
    }
}
