/** @jsxImportSource @emotion/react */
import { css } from '@emotion/react';
import React from 'react';
import { Page } from './Page';
import { Title } from './Title';
import { Scores } from './Scores';
import Clock from './Clock';
import { Session } from '../types/Session';
import TextInputComponent from './TextInputComponent';
import { executeUserInput, getCurrentRound } from '../api/countdown-api';
import { Round } from '../types/Round';

interface Props {
  session: Session;
}

export const GamePage = ({ session }: Props) => {
  const [highScore, setHighScore] = React.useState(0);
  const [isRunning, setIsRunning] = React.useState(false);
  const [round, setRound] = React.useState<Round>(session.currentRound);

  const handleError = (error: unknown) => {
    // TODO: Better error handling!
    console.log('An error has occurred');
    throw error;
  };

  function sleep(ms: number): Promise<void> {
    return new Promise((resolve) => setTimeout(resolve, ms));
  }

  const updateRound = (updatedRound: Round) => {
    setRound(updatedRound);
  };

  const onStartRunning = () => {
    console.log('In onStartRunning...');
    setIsRunning(!isRunning);
  };

  const onEndRunning = async () => {
    console.log('In onEndRunning...');
    setIsRunning(false);
    try {
      for (let attempts = 0; attempts < 10; attempts++) {
        const roundUpdate = await getCurrentRound(session.id);
        if (roundUpdate.roundState === 'SOLVING') {
          updateRound(roundUpdate);
          return;
        }
        await sleep(100);
      }
      throw new Error(`Session id:${session.id} is in an unexpected state...`);
    } catch (error) {
      handleError(error);
    }
  };

  const handleUserInput = async (value: string) => {
    console.log(`In handleUserInput: ${value}`);

    if (!value) {
      return; // ignore
    }

    try {
      const roundUpdate = await executeUserInput(session.id, {
        content: value,
      });
      if (!isRunning && roundUpdate.roundState === 'RUNNING') {
        onStartRunning();
      }
      updateRound(roundUpdate);
    } catch (error) {
      handleError(error);
    }
  };

  return (
    <div>
      <Scores highScore={highScore} currentScore={round.score ?? 0} />
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
          <Clock isRunning={isRunning} onComplete={onEndRunning} />
          <p>{round.gameBoard.toUpperCase()}</p>
          <p>{round.message}</p>
          <TextInputComponent onFinalValue={handleUserInput} />
          <div
            css={css`
              display: flex;
              justify-content: center;
              gap: 20px;
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
