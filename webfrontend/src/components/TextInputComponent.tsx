import React, { useState } from 'react';

interface TextInputComponentProps {
  onFinalValue: (value: string) => void; // Define a callback function prop
}

const TextInputComponent: React.FC<TextInputComponentProps> = ({
  onFinalValue,
}) => {
  const [inputValue, setInputValue] = useState<string>('');

  const handleKeyDown = (event: React.KeyboardEvent<HTMLInputElement>) => {
    if (event.key === 'Enter') {
      console.log('Enter pressed, clearing input');
      setInputValue('');
      event.preventDefault();
    }
  };

  const handleBlur = (event: React.FocusEvent<HTMLInputElement>) => {
    console.log('Final entered value:', event.target.value);
    onFinalValue(event.target.value); // Invoke the callback with the final value
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
      onBlur={handleBlur}
    />
  );
};

export default TextInputComponent;
