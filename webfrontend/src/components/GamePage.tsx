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
  const [session, setSession] = React.useState<Session | null>(null);
  const [isRunning, setIsRunning] = React.useState(false);
  const [canReset, setCanReset] = React.useState(false);
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

  const updateRound = (session: Session, roundUpdate: Round) => {
    setSession({
      ...session,
      currentRound: {
        ...session.currentRound,
        ...roundUpdate,
      },
    });
  };

  const onStartRunning = () => {
    console.log('In onStartRunning...');
    setIsRunning(!isRunning);
  };

  const onEndRunning = async (session: Session) => {
    console.log('In onEndRunning...');
    try {
      // Ensure the backend is in the expected state
      for (let apiCalls = 0; apiCalls < 10; apiCalls++) {
        const roundUpdate = await getCurrentRound(session.id);
        if (roundUpdate.roundState === 'SOLVING') {
          setIsRunning(false);
          updateRound(session, roundUpdate);
          return;
        }
        await sleep(100);
      }
      throw new Error(`Session id:${session.id} is in an unexpected state...`);
    } catch (error) {
      handleError(error);
    }
  };

  const onHandleUserInput = async (session: Session, value: string) => {
    console.log(`In handleUserInput: ${value}`);

    if (isRunning) {
      console.log('Ignore user input whilst running...');
      return; // ignore
    }

    try {
      const roundUpdate = await executeUserInput(session.id, {
        content: value,
      });
      if (!isRunning && roundUpdate.roundState === 'RUNNING') {
        onStartRunning();
      } else if (roundUpdate.roundState === 'DONE') {
        const updatedScore = session.totalScore + (roundUpdate.score || 0);
        setSession({
          ...session,
          totalScore: updatedScore,
          currentRound: {
            ...session.currentRound,
            ...roundUpdate,
          },
        });
        const isAnotherRound = await hasNextRound(session.id);
        setCanReset(!isAnotherRound);
        return;
      }
      updateRound(session, roundUpdate);
    } catch (error) {
      console.error('User input could not be handled, ignoring...');
    }
  };

  const onNextRound = async (session: Session) => {
    console.log(`In startNextRound`);

    try {
      const updatedRound = await startNextRound(session.id);
      updateRound(session, updatedRound);
    } catch (error) {
      handleError(error);
    }
  };

  const onResetSession = async (id: number) => {
    console.log('In reset session');

    try {
      const resettedSession = await resetSession(id);
      setSession(resettedSession);
      setCanReset(false);
    } catch (error) {
      handleError(error);
    }
  };

  return (
    <div>
      {session === null ? null : (
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
                isRunning={isRunning}
                onComplete={() => onEndRunning(session)}
              />
              <p>{session.currentRound.gameBoard.toUpperCase()}</p>
              <p>{session.currentRound.message}</p>
              <TextInputComponent
                onFinalValue={(value) => onHandleUserInput(session, value)}
              />
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
                    session.currentRound.roundState !== 'DONE' || canReset
                  }
                  onClick={() => onNextRound(session)}
                >
                  Next Round
                </button>
                <button
                  style={{ padding: '5px' }}
                  disabled={!canReset}
                  onClick={() => onResetSession(session.id)}
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
