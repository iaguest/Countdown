import Axios from 'axios';
import { Session } from '../types/Session';
import { apiEndpoint } from '../config';

export async function createSession(): Promise<Session> {
  console.log('In createSession...');

  const response = await Axios.post(`${apiEndpoint}/sessions`, null, {
    headers: {
      'Content-Type': 'application/json',
    },
  });

  const session = response.data.item;
  console.log(
    `... session item is ${JSON.stringify(session)}, exiting createSession`,
  );
  return session;
}
