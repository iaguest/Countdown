using Countdown.Model;
using CountdownTestsCSharp;
using Moq;
using NUnit.Framework;
using Prism.Events;
using System.Threading.Tasks;

namespace CountdownTestCSharp
{
    [TestFixture]
    public class CountdownRoundShould
    {
        private Mock<GameStateUpdatedEvent> _mockEvent;
        private Mock<IEventAggregator> _mockEventAggregator;
        private IGame _mockGame;
        private CountdownRound _countdownRound;

        [SetUp]
        public void Initialize()
        {
            _mockEvent = new Mock<GameStateUpdatedEvent>();
            _mockEventAggregator = new Mock<IEventAggregator>();
            _mockEventAggregator
                .Setup(ea => ea.GetEvent<GameStateUpdatedEvent>())
                .Returns(_mockEvent.Object);
            _mockGame = new MockGame();
            _countdownRound = new CountdownRound(
                _mockEventAggregator.Object,
                _mockGame,
                maxAnswerWaitTime: 10);
        }

        [Test]
        public void BeInInitializingStateAfterConstruction()
        {
            Assert.AreEqual(RoundState.INITIALIZING, _countdownRound.State);
        }

        [Test]
        public void NotHavePublishedGameStateUpdatedEventDuringConstruction()
        {
            _mockEvent.Verify(e => e.Publish(), Times.Never);
        }

        [Test]
        public async Task UpdateStateWhenStateChangeOccurs()
        {
            // Completes initialization of mock game
            await _countdownRound.ExecuteUserInput("A");

            Assert.AreNotEqual(RoundState.INITIALIZING, _countdownRound.State);
        }

        [Test]
        public async Task PublishGameStateUpdateEventWhenStateChangeOccurs()
        {
            // Completes initialization of mock game
            await _countdownRound.ExecuteUserInput("X");

            _mockEvent.Verify(e => e.Publish(), Times.AtLeastOnce);
        }
    }
}
