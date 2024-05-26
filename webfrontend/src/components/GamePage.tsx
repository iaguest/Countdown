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
  createSession,
  executeUserInput,
  getCurrentRound,
  startNextRound,
  resetSession,
  hasNextRound,
} from '../api/countdown-api';
import { Round } from '../types/Round';
import { sleep } from '../utils';
import { RoundState } from '../types/RoundState';

let sessionWasCreated = false;

const emptySession = (): Session => {
  return {
    id: -1,
    totalScore: 0,
    currentRound: {
      type: '',
      roundState: RoundState.INITIALIZING,
      message: '',
      gameBoard: '',
      score: 0,
    },
  };
};

export const GamePage = () => {
  const [highScore, setHighScore] = React.useState(0);
  const [session, setSession] = React.useState<Session>(emptySession());
  const [canResetSession, setCanResetSession] = React.useState(false);

  React.useEffect(() => {
    if (!sessionWasCreated) {
      sessionWasCreated = true;
      const doCreateSession = async () => {
        const createdSession = await createSession();
        setSession(createdSession);
      };
      doCreateSession();
    }
  }, []);

  const handleError = (error: unknown) => {
    console.log('An error has occurred:', error);
    throw error;
  };

  const updateRound = (roundUpdate: Round) => {
    setSession((prevSession) => ({
      ...prevSession,
      currentRound: {
        ...prevSession.currentRound,
        ...roundUpdate,
      },
    }));
  };

  const onRoundRunComplete = async () => {
    console.log('In onRoundRunComplete...');
    try {
      // Ensure the backend is in the expected state
      for (let apiCalls = 0; apiCalls < 10; apiCalls++) {
        const roundUpdate = await getCurrentRound(session.id);
        if (roundUpdate.roundState === RoundState.SOLVING) {
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

  const onHandleUserInput = async (value: string) => {
    console.log(`In onHandleUserInput: ${value}`);

    if (session.currentRound.roundState === RoundState.RUNNING) {
      console.log('Ignore user input whilst running...');
      return; // ignore
    }

    try {
      const roundUpdate = await executeUserInput(session.id, {
        content: value,
      });
      if (roundUpdate.roundState === RoundState.DONE) {
        const updatedScore = session.totalScore + (roundUpdate.score || 0);
        setSession((prevSession) => ({
          ...prevSession,
          totalScore: updatedScore,
        }));
        const isAnotherRound = await hasNextRound(session.id);
        setCanResetSession(!isAnotherRound);
      }
      updateRound(roundUpdate);
    } catch (error) {
      console.error('User input could not be handled, ignoring...');
    }
  };

  const onNextRound = async () => {
    console.log('In onNextRound');

    try {
      const updatedRound = await startNextRound(session.id);
      updateRound(updatedRound);
    } catch (error) {
      handleError(error);
    }
  };

  const onResetSession = async () => {
    console.log('In onResetSession');

    try {
      const resettedSession = await resetSession(session.id);
      setSession(resettedSession);
      setCanResetSession(false);
    } catch (error) {
      handleError(error);
    }
  };

  return (
    <div>
      {!sessionWasCreated ? null : (
        <div>
          <Scores highScore={highScore} currentScore={session.totalScore} />
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
              <Title>{session.currentRound.type} Round</Title>
              <Clock
                isRunning={
                  session.currentRound.roundState === RoundState.RUNNING
                }
                onComplete={() => onRoundRunComplete()}
              />
              <p>{session.currentRound.gameBoard.toUpperCase()}</p>
              <p>{session.currentRound.message}</p>
              <TextInputComponent onFinalValue={onHandleUserInput} />
              <div
                css={css`
                  display: flex;
                  justify-content: center;
                  gap: 20px;
                `}
              >
                <button
                  style={{ padding: '5px' }}
                  disabled={
                    session.currentRound.roundState !== RoundState.DONE ||
                    canResetSession
                  }
                  onClick={onNextRound}
                >
                  Next Round
                </button>
                <button
                  style={{ padding: '5px' }}
                  disabled={!canResetSession}
                  onClick={onResetSession}
                >
                  Restart Game
                </button>
              </div>
            </div>
          </Page>
        </div>
      )}
    </div>
  );
};
