import Axios, { AxiosRequestConfig } from 'axios';
import { Session } from '../types/Session';
import { Round } from '../types/Round';
import { UserInputRequest } from '../types/UserInputRequest';
import { apiEndpoint } from '../config';
import { HasNextRoundResponse } from '../types/HasNextRoundResponse';

export async function createSession(): Promise<Session> {
  try {
    console.log('In createSession...');

    const response = await Axios.post(
      `${apiEndpoint}/sessions`,
      '',
      makeRequestConfig(),
    );

    const session = response.data;
    console.log(
      `... session item is ${JSON.stringify(
        session,
      )}, returning session data...`,
    );
    return session;
  } catch (error) {
    console.error('Failed to create session');
    throw error;
  }
}

export async function getSession(id: number): Promise<Session> {
  try {
    console.log(`In getSession for id:${id}...`);

    const response = await Axios.get(
      `${apiEndpoint}/sessions/${id}`,
      makeRequestConfig(),
    );

    const session = response.data;
    console.log(
      `... session item is ${JSON.stringify(
        session,
      )}, returning session data...`,
    );
    return session;
  } catch (error) {
    console.error(`Failed to get session with id:${id}`);
    throw error;
  }
}

export async function getCurrentRound(id: number): Promise<Round> {
  try {
    console.log(`In getCurrentRound for session id:${id}...`);

    const response = await Axios.get(
      `${apiEndpoint}/sessions/${id}/currentRound`,
      makeRequestConfig(),
    );

    const round = response.data;
    console.log(
      `... round item is ${JSON.stringify(round)}, returning round data...`,
    );
    return round;
  } catch (error) {
    console.error(`Failed to get current round for session id:${id}`);
    throw error;
  }
}

export async function hasNextRound(id: number): Promise<boolean> {
  try {
    console.log(`In hasNextRound for session id:${id}...`);

    const response = await Axios.get(
      `${apiEndpoint}/sessions/${id}/hasNextRound`,
      makeRequestConfig(),
    );

    const hasNextRound: HasNextRoundResponse = response.data;
    console.log(
      `... hasNextRoundResponse is ${JSON.stringify(
        hasNextRound,
      )}, returning has next round data...`,
    );
    return hasNextRound.hasNextRound;
  } catch (error) {
    console.error(`Failed to get has next round response for session id:${id}`);
    throw error;
  }
}

export async function startNextRound(id: number): Promise<Round> {
  try {
    console.log(`In startNextRound for session id:${id}...`);

    const response = await Axios.post(
      `${apiEndpoint}/sessions/${id}/nextRound`,
      '',
      makeRequestConfig(),
    );

    const round = response.data;
    console.log(
      `... round item is ${JSON.stringify(round)}, returning round data...`,
    );
    return round;
  } catch (error) {
    console.error(`Failed to start next round for session id:${id}`);
    throw error;
  }
}

export async function executeUserInput(
  id: number,
  request: UserInputRequest,
): Promise<Round> {
  try {
    console.log(`In executeUserInput for session id:${id}...`);

    const response = await Axios.post(
      `${apiEndpoint}/sessions/${id}/currentRound/execute`,
      JSON.stringify(request),
      makeRequestConfig(),
    );

    const round = response.data;
    console.log(
      `... round item is ${JSON.stringify(round)}, returning round data...`,
    );
    return round;
  } catch (error) {
    console.error(`Failed to execute user input for session id:${id}`);
    throw error;
  }
}

function makeRequestConfig(): AxiosRequestConfig<string> {
  return {
    headers: {
      'Content-Type': 'application/json',
    },
  };
}
