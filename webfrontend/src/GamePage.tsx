/** @jsxImportSource @emotion/react */
import { css } from '@emotion/react';
import React from 'react';
import { gray5 } from './Styles';
import { Page } from './Page';
import { PageTitle } from './PageTitle';

export const GamePage = () => {
  return (
    <div>
      <Page>
        <PageTitle>Letters Round</PageTitle>
        <p
          css={css`
            text-align: center;
          `}
        >
          TODO
        </p>
      </Page>
    </div>
  );
};
