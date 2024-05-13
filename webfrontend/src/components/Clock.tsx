/** @jsxImportSource @emotion/react */
import { css } from '@emotion/react';
import { useState, useEffect } from 'react';

interface Props {
  isRunning: boolean;
  onComplete: () => void;
}

const Clock = ({ isRunning, onComplete }: Props) => {
  const [rotation, setRotation] = useState(0);
  useEffect(() => {
    if (isRunning) {
      const startTime = Date.now();

      const updateRotation = () => {
        const elapsedSeconds = (Date.now() - startTime) / 1000;
        if (elapsedSeconds > 30) {
          setRotation(0);
          onComplete();
          return;
        }

        const newRotation = (elapsedSeconds / 30) * 180;
        setRotation(newRotation);
      };

      const intervalId = setInterval(updateRotation, 1000 / 60);

      return () => clearInterval(intervalId);
    }
  }, [isRunning, onComplete]);

  const hourAngles = [30, 60, 120, 150, 210, 240, 300, 330];
  return (
    <div css={clockStyle}>
      <div css={centerMarkStyle}></div>
      <div css={[handStyle, { transform: `rotate(${rotation}deg)` }]} />
      {hourAngles.map((angle, index) => (
        <div key={index} css={hourMarkStyle(angle)}></div>
      ))}
    </div>
  );
};

const clockStyle = css`
  position: relative;
  width: 200px;
  height: 200px;
  border: 5px solid black;
  border-radius: 50%;
  background-color: lightgray;
  display: flex;
  justify-content: center;
  align-items: center;

  &::before,
  &::after {
    content: '';
    position: absolute;
    background-color: black;
  }

  &::before {
    width: 2px;
    height: 100%;
  }

  &::after {
    width: 100%;
    height: 2px;
  }
`;

const centerMarkStyle = css`
  position: absolute;
  width: 10px;
  height: 10px;
  background-color: black;
  border-radius: 50%;
  left: 50%;
  top: 50%;
  transform: translate(-50%, -50%);
`;

const hourMarkStyle = (angle: number) => css`
  position: absolute;
  height: 20px;
  width: 1px;
  background-color: black;
  transform: rotate(${angle}deg) translateX(0px) translateY(-80px);
`;

const handStyle = css`
  position: absolute;
  bottom: 50%;
  width: 4px;
  height: 95px;
  background-color: black;
  transform-origin: 50% 100%;
`;

export default Clock;
