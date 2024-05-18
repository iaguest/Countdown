/** @jsxImportSource @emotion/react */
import { css } from '@emotion/react';
import React, { useState } from 'react';
import { fontFamily, fontSize, gray1 } from './Styles';
import { GamePage } from './components/GamePage';
import { createSession } from './api/countdown-api';
import { Session } from './types/Session';

let sessionWasCreated = false;

function App() {
  const [session, setSession] = useState<Session | null>(null);
  React.useEffect(() => {
    if (!sessionWasCreated) {
      sessionWasCreated = true;
      const doCreateSession = async () => {
        const createdSession = await createSession();
        setSession(createdSession);
      };
      doCreateSession();
    }
  }, []);

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
        {session == null ? null : <GamePage session={session} />}
      </div>
    </div>
  );
}

export default App;
