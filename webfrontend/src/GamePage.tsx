/** @jsxImportSource @emotion/react */
import { css } from '@emotion/react';
import React from 'react';
import { gray5 } from './Styles';
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
              margin-top: 10px; /* Adds top margin to all elements except the first one */
            }
          `}
        >
          <Title>Letters Round</Title>
          <button onClick={onStartRunning}>Start Clock</button>
          <Clock isRunning={isRunning} onComplete={handleOnComplete} />
        </div>
      </Page>
    </div>
  );
};
