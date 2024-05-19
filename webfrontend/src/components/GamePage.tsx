/** @jsxImportSource @emotion/react */
import { css } from '@emotion/react';
import React from 'react';
import { Page } from './Page';
import { Title } from './Title';
import { Scores } from './Scores';
import Clock from './Clock';
import { Session } from '../types/Session';
import TextInputComponent from './TextInputComponent';
import { executeUserInput } from '../api/countdown-api';
import { Round } from '../types/Round';

interface Props {
  session: Session;
}

export const GamePage = ({ session }: Props) => {
  const [highScore, setHighScore] = React.useState(0);
  const [currentScore, setCurrentScore] = React.useState(0);
  const [isRunning, setIsRunning] = React.useState(false);
  const [round, setRound] = React.useState<Round>(session.currentRound);

  const updateRound = (updatedRound: Round) => {
    setRound(updatedRound);
  };

  const onStartRunning = () => {
    setIsRunning(!isRunning);
  };

  const onEndRunning = () => {
    setIsRunning(false);
  };

  const handleUserInput = async (value: string) => {
    console.log(`in handle user input: ${value}`);

    if (!value) {
      // ignore
      return;
    }

    try {
      const roundUpdate = await executeUserInput(session.id, {
        content: value,
      });
      updateRound(roundUpdate);
      if (!isRunning && roundUpdate.roundState === 'RUNNING') {
        onStartRunning();
      } else {
        onEndRunning();
      }
    } catch (error) {
      // TODO: graceful error handling
      throw error;
    }
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
          <Title>{round.type} Round</Title>
          {/* <button
            css={css`
              visibility: collapse;
            `}
            onClick={onStartRunning}
          >
            Start Clock
          </button> */}
          <Clock isRunning={isRunning} onComplete={onEndRunning} />
          <p>{round.gameBoard.toUpperCase()}</p>
          <p>{round.message}</p>
          {/* <input
            css={css`
              padding: 5px;
            `}
            type="text"
            placeholder="Enter responses here..."
            name="name"
          ></input> */}
          <TextInputComponent onFinalValue={handleUserInput} />
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
