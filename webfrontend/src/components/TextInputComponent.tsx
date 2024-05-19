import React, { useState } from 'react';

interface TextInputComponentProps {
  onFinalValue: (value: string) => void;
}

const TextInputComponent: React.FC<TextInputComponentProps> = ({
  onFinalValue,
}) => {
  const [inputValue, setInputValue] = useState<string>('');

  const handleKeyDown = (event: React.KeyboardEvent<HTMLInputElement>) => {
    if (event.key === 'Enter') {
      console.log('Enter pressed, processing input');
      onFinalValue(inputValue);
      setInputValue('');
      event.preventDefault();
    }
  };

  return (
    <input
      style={{ padding: '5px' }}
      type="text"
      placeholder="Enter responses here..."
      name="name"
      value={inputValue}
      onChange={(e) => setInputValue(e.target.value)}
      onKeyDown={handleKeyDown}
    />
  );
};

export default TextInputComponent;
