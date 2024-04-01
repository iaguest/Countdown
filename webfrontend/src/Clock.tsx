/** @jsxImportSource @emotion/react */
import { css } from '@emotion/react';
import { useState, useEffect } from 'react';

interface Props {
  isRunning: boolean;
}

const Clock = ({ isRunning }: Props) => {
  const [rotation, setRotation] = useState(0);
  useEffect(() => {
    if (isRunning) {
      const startTime = Date.now();

      const updateRotation = () => {
        const elapsedSeconds = (Date.now() - startTime) / 1000;
        const newRotation = (elapsedSeconds / 30) * 180;
        setRotation(newRotation);
      };

      const intervalId = setInterval(updateRotation, 1000 / 60);

      return () => clearInterval(intervalId);
    }
  }, [isRunning]);

  return (
    <div css={clockContainer}>
      <div css={clockFace}>
        <div css={[clockHand, { transform: `rotate(${rotation - 90}deg)` }]} />
        <div css={crossLine} />
        <div css={[crossLine, crossLineHorizontal]} />
      </div>
    </div>
  );
};

const clockContainer = css`
  display: flex;
  justify-content: center;
  align-items: center;
  height: 300px;
`;

const clockFace = css`
  position: absolute;
  width: 200px;
  height: 200px;
  border: 2px solid #333;
  border-radius: 50%;
`;

const clockHand = css`
  position: absolute;
  top: 0%;
  left: 0%;
  background-color: #333;
  height: 1px;
  width: 95px;
`;

const crossLine = css`
  position: absolute;
  top: 50%;
  /* left: 50%; */
  background-color: #333;
  height: 1px;
  width: 100%;
`;

const crossLineHorizontal = css`
  height: 1px;
  transform: translate(0%, -50%) rotate(90deg);
`;

export default Clock;
