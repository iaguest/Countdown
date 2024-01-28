/** @jsxImportSource @emotion/react */
import { css } from '@emotion/react';
import React from 'react';
//import './App.css';
import { fontFamily, fontSize, gray1 } from './Styles';
import { GamePage } from './GamePage';

function App() {
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
        <GamePage />
      </div>
    </div>
  );
}

export default App;
