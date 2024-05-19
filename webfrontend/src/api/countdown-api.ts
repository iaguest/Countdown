import Axios, { AxiosRequestConfig } from 'axios';
import { Session } from '../types/Session';
import { Round } from '../types/Round';
import { UserInputRequest } from '../types/UserInputRequest';
import { apiEndpoint } from '../config';

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
    console.error('Failed to create session', error);
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
    console.error(`Failed to get session for id:${id}`, error);
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
    console.error('Failed to execute user input, error');
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
