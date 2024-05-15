import Axios, { AxiosRequestConfig } from 'axios';
import { Session } from '../types/Session';
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
      `... session item is ${JSON.stringify(session)}, returning session...`,
    );
    return session;
  } catch (error) {
    console.error('Failed to create session', error);
    throw error;
  }
}

export async function getSession(id: number): Promise<Session> {
  try {
    console.log('In getSession...');

    const response = await Axios.get(
      `${apiEndpoint}/sessions/${id}`,
      makeRequestConfig(),
    );

    const session = response.data;
    console.log(
      `... session item is ${JSON.stringify(session)}, returning session...`,
    );
    return session;
  } catch (error) {
    console.error('Failed to get session', error);
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
