import { Round } from './round';

export interface Session {
  id: number;
  totalScore: number;
  currentRound: Round;
}
