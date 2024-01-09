/** @jsxImportSource @emotion/react */
import { css } from '@emotion/react';
import React from 'react';
//import './App.css';
import { fontFamily, fontSize, gray1 } from './Styles';
import { Scores } from './Scores';
import { GamePage } from './GamePage';

function App() {
  const [highScore, setHighScore] = React.useState(0);
  const [currentScore, setCurrentScore] = React.useState(0);
  return (
    <div
      // this is a tagged template literal
      css={css`
        font-family: ${fontFamily};
        font-size: ${fontSize};
        color: ${gray1};
      `}
    >
      <div className="App">
        <Scores highScore={highScore} currentScore={currentScore} />
        <GamePage />
      </div>
    </div>
  );
}

export default App;
