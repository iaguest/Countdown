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
                GameBoard = string.Empty;
            }

            public string InitializeMessage => string.Empty;

            public string StartRunMessage => string.Empty;

            public string GameBoard { get; private set; }

            public string EndRunMessage => string.Empty;

            public void Dispose() { }

            public bool Initialize(string input, out string output)
            {
                output = string.Empty;
                GameBoard = "MOCKBOARD";
                return true;
            }

            public void Run(Action onDone) { onDone(); }

            public int GetScore(string answer) { return 99; }
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
    }
}
