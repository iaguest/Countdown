import { RoundState } from './RoundState';

export interface Round {
  type: string;
  roundState: RoundState;
  message: string;
  gameBoard: string;
  score?: number;
}
