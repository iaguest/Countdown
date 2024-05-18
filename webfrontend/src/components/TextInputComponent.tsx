import React, { useState } from 'react';

interface TextInputComponentProps {
  onFinalValue: (value: string, clearInput: () => void) => void; // Pass a method to clear the input
}

const TextInputComponent: React.FC<TextInputComponentProps> = ({
  onFinalValue,
}) => {
  const [inputValue, setInputValue] = useState<string>('');

  const handleKeyDown = (event: React.KeyboardEvent<HTMLInputElement>) => {
    if (event.key === 'Enter') {
      console.log('Enter pressed, processing input');
      onFinalValue(inputValue, () => setInputValue('')); // Pass the current value and method to clear it
      event.preventDefault();
    }
  };

  const handleBlur = (event: React.FocusEvent<HTMLInputElement>) => {
    console.log('Final entered value:', event.target.value);
    onFinalValue(event.target.value, () => setInputValue('')); // Pass the current value and method to clear it
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
