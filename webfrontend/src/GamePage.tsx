/** @jsxImportSource @emotion/react */
import { css } from '@emotion/react';
import React from 'react';
import { gray5 } from './Styles';
import { Page } from './Page';
import { Title } from './Title';
import { Scores } from './Scores';
import Clock from './Clock';
import CountdownClock from './CountdownClock';

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
        <Title>Letters Round</Title>
        <button onClick={onStartRunning}>Start Clock</button>
        <Clock isRunning={isRunning} onComplete={handleOnComplete} />
      </Page>
    </div>
  );
};
