/** @jsxImportSource @emotion/react */
import { css } from '@emotion/react';
import React from 'react';
import { gray5 } from '../Styles';

interface Props {
  highScore: number;
  currentScore: number;
}

export const Scores = ({ highScore, currentScore }: Props) => {
  return (
    <div
      css={css`
        position: fixed;
        box-sizing: border-box;
        top: 0;
        width: 100%;
        display: flex;
        align-items: center;
        justify-content: space-between;
        padding: 10px 20px;
        background-color: #fff;
        border-bottom: 1px solid ${gray5};
        box-shadow: 0 3px 7px 0 rgba(110, 112, 114, 0.21);
      `}
    >
      <p>High Score: {highScore}</p>
      <p>Current Score: {currentScore}</p>
    </div>
  );
};
