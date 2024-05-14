export interface Round {
  type: string;
  roundState: string;
  message: string;
  gameBoard: string;
  score?: number;
}
