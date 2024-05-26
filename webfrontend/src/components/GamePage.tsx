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

let sessionWasCreated = false;

export const GamePage = () => {
  const [highScore, setHighScore] = React.useState(0);
  const [session, setSession] = React.useState<Session>({
    id: -1,
    totalScore: 0,
    currentRound: {
      type: '',
      roundState: '',
      message: '',
      gameBoard: '',
      score: 0,
    },
  });
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

  const onRoundUpdate = (roundUpdate: Round) => {
    setSession((prevSession) => ({
      ...prevSession,
      currentRound: {
        ...prevSession.currentRound,
        ...roundUpdate,
      },
    }));
  };

  const onEndRunning = async () => {
    console.log('In onEndRunning...');
    try {
      // Ensure the backend is in the expected state
      for (let apiCalls = 0; apiCalls < 10; apiCalls++) {
        const roundUpdate = await getCurrentRound(session.id);
        if (roundUpdate.roundState === 'SOLVING') {
          onRoundUpdate(roundUpdate);
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
    console.log(`In handleUserInput: ${value}`);

    if (session.currentRound.roundState === 'RUNNING') {
      console.log('Ignore user input whilst running...');
      return; // ignore
    }

    try {
      const roundUpdate = await executeUserInput(session.id, {
        content: value,
      });
      if (roundUpdate.roundState === 'DONE') {
        const updatedScore = session.totalScore + (roundUpdate.score || 0);
        setSession((prevSession) => ({
          ...prevSession,
          totalScore: updatedScore,
        }));
        const isAnotherRound = await hasNextRound(session.id);
        setCanResetSession(!isAnotherRound);
      }
      onRoundUpdate(roundUpdate);
    } catch (error) {
      console.error('User input could not be handled, ignoring...');
    }
  };

  const onNextRound = async () => {
    console.log(`In startNextRound`);

    try {
      const updatedRound = await startNextRound(session.id);
      onRoundUpdate(updatedRound);
    } catch (error) {
      handleError(error);
    }
  };

  const onResetSession = async () => {
    console.log('In reset session');

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
                isRunning={session.currentRound.roundState === 'RUNNING'}
                onComplete={() => onEndRunning()}
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
                    session.currentRound.roundState !== 'DONE' ||
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
