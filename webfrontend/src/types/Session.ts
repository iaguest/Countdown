import { Round } from './Round';

export interface Session {
  id: number;
  totalScore: number;
  currentRound: Round;
}
