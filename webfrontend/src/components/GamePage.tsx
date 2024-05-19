/** @jsxImportSource @emotion/react */
import { css } from '@emotion/react';
import React from 'react';
import { Page } from './Page';
import { Title } from './Title';
import { Scores } from './Scores';
import Clock from './Clock';
import { Session } from '../types/Session';
import TextInputComponent from './TextInputComponent';
import {
  executeUserInput,
  getCurrentRound,
  startNextRound,
} from '../api/countdown-api';
import { Round } from '../types/Round';
import { sleep } from '../utils';

interface Props {
  session: Session;
}

export const GamePage = ({ session }: Props) => {
  const [highScore, setHighScore] = React.useState(0);
  const [currentScore, setCurrentScore] = React.useState(0);
  const [isRunning, setIsRunning] = React.useState(false);
  const [round, setRound] = React.useState<Round>(session.currentRound);

  const handleError = (error: unknown) => {
    // TODO: Better error handling!
    console.log('An error has occurred');
    throw error;
  };

  const updateRound = (updatedRound: Round) => {
    setRound(updatedRound);
  };

  const onStartRunning = () => {
    console.log('In onStartRunning...');
    setIsRunning(!isRunning);
  };

  const onEndRunning = async () => {
    console.log('In onEndRunning...');
    try {
      // Ensure the backend is in the expected state
      for (let apiCalls = 0; apiCalls < 10; apiCalls++) {
        const roundUpdate = await getCurrentRound(session.id);
        if (roundUpdate.roundState === 'SOLVING') {
          setIsRunning(false);
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

    if (isRunning) {
      return; // ignore
    }

    try {
      const roundUpdate = await executeUserInput(session.id, {
        content: value,
      });
      if (!isRunning && roundUpdate.roundState === 'RUNNING') {
        onStartRunning();
      } else if (roundUpdate.roundState === 'DONE') {
        setCurrentScore(
          roundUpdate.score ? currentScore + roundUpdate.score : currentScore,
        );
      }
      updateRound(roundUpdate);
    } catch (error) {
      // ignore - hopefully benign!
    }
  };

  const nextRound = async () => {
    console.log(`In startNextRound`);

    try {
      const updatedRound = await startNextRound(session.id);
      updateRound(updatedRound);
    } catch (error) {
      handleError(error);
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
            <button
              style={{ padding: '5px' }}
              disabled={round.roundState !== 'DONE'}
              onClick={() => nextRound()}
            >
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
