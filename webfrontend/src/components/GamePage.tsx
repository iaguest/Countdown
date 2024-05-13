/** @jsxImportSource @emotion/react */
import { css } from '@emotion/react';
import React from 'react';
import { Page } from './Page';
import { Title } from './Title';
import { Scores } from './Scores';
import Clock from './Clock';

export const GamePage = () => {
  const [highScore, setHighScore] = React.useState(0);
  const [currentScore, setCurrentScore] = React.useState(0);
  const [isRunning, setIsRunning] = React.useState(false);

  const onStartRunning = () => {
    setIsRunning(!isRunning);
  };

  const handleOnComplete = () => {
    setIsRunning(false);
  };

  return (
    <div>
      <Scores highScore={highScore} currentScore={currentScore} />
      <Page>
        <div
          css={css`
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
            text-align: center;

            & > *:not(:first-child) {
              margin-top: 20px; /* Adds top margin to all elements except the first one */
            }
          `}
        >
          <Title>Letters Round</Title>
          {/* <button
            css={css`
              visibility: collapse;
            `}
            onClick={onStartRunning}
          >
            Start Clock
          </button> */}
          <Clock isRunning={isRunning} onComplete={handleOnComplete} />
          <p>Vowel(v)/Consonant(c)?</p>
          <input
            css={css`
              padding: 5px;
            `}
            type="text"
            placeholder="Enter responses here..."
            name="name"
          ></input>
          <div
            css={css`
              display: flex;
              justify-content: center; /* Center the buttons horizontally */
              gap: 20px; /* Adds some space between the two buttons */
            `}
          >
            <button style={{ padding: '5px' }} disabled={true}>
              Next Round
            </button>
            <button style={{ padding: '5px' }} disabled={true}>
              Restart Game
            </button>
          </div>
        </div>
      </Page>
    </div>
  );
};
